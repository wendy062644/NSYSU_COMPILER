%define parse.trace
%start classes
%start lines
%{
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include "lib/symbol_table.h"

    typedef struct {
        char name[64];
        int kind; // 1: var, 2: func
    } SymbolEntry;

    #define YYLTYPE_IS_TRIVIAL 1

    int yylex();
    // int yydebug = 1;
    int fatal_error_count = 0;
    void yyerror(const char *s);
    extern char tokens[80];
    extern int token_width;

    int skip_next_decl_typecheck = 0;

    int error_reported = 0;
    extern int last_token_col;
    extern int last_token_line;

    extern int yylineno;
    extern int token_col;

    static int parse_depth = 0;
    extern void push(void);
    extern void pop(void);
    #define PUSH() do { parse_depth++; push(); } while(0)
    #define POP()  do { parse_depth--; pop(); }  while(0)

    #define MAX_SYMBOLS 256
    #define VAR_KIND 1
    #define FUNC_KIND 2
    #define TYPE_KIND 3

    #define MAX_DEPTH 16

    static SymbolEntry local_table[MAX_DEPTH][MAX_SYMBOLS];
    static int local_symbol_count[MAX_DEPTH] = {0};
    static int current_depth = 0;

    int last_init_line = 0;
    int last_init_col  = 0;

    int my_insert(const char *name, int kind) {
        for (int i = 0; i < local_symbol_count[current_depth]; ++i) {
            if (strcmp(local_table[current_depth][i].name, name) == 0)
            return -1;
        }
        strncpy(local_table[current_depth][local_symbol_count[current_depth]].name, name, 63);
        local_table[current_depth][local_symbol_count[current_depth]].kind = kind;
        ++local_symbol_count[current_depth];
        return 0;
    }

    int is_variable(const char *name) {
        for (int d = current_depth; d >= 0; --d) {
            for (int i = 0; i < local_symbol_count[d]; ++i) {
                if (strcmp(local_table[d][i].name, name) == 0 && local_table[d][i].kind == VAR_KIND)
                return 1;
            }
        }
        return 0;
    }

    void push(void) {
        if (current_depth < MAX_DEPTH - 1) {
            ++current_depth;
            local_symbol_count[current_depth] = 0; // 新層開始，清空符號表數量
        }
    }

    void pop(void) {
        if (current_depth > 0) {
            local_symbol_count[current_depth] = 0; // 離開時清空當前層符號表
            --current_depth;
        }
    }

    int is_function(const char *name) {
        for (int d = current_depth; d >= 0; --d) {
            for (int i = 0; i < local_symbol_count[d]; ++i) {
                if (strcmp(local_table[d][i].name, name) == 0)
                return local_table[d][i].kind == FUNC_KIND;
            }
        }
        return 0;
    }

    int is_type(const char *name) {
        for (int d = current_depth; d >= 0; --d) {
            for (int i = 0; i < local_symbol_count[d]; ++i) {
                if (strcmp(local_table[d][i].name, name) == 0)
                return local_table[d][i].kind == TYPE_KIND;
            }
        }
        return 0;
    }

    void flushLine();

    int pending_error = 0;
    char pending_message[256];

    void flushPendingError() {
        if (pending_error) {
            fprintf(stderr, "%s", pending_message);
            pending_error = 0;
        }
    }
    #define DUP_ID "duplicate id.\n"
    #define MISS_SEMI "Missing semicolum.\n"
    #define show_errmsg(x) fprintf(stderr, x)

    #undef chk_dupid_id
    #define chk_dupid_id(name) do {                                      \
    if (!error_reported || error_reported != yylineno) {             \
    int res = my_insert(name, VAR_KIND);                         \
    if (res < 0) {                                               \
    fprintf(stderr, "Line %d, char: %d, duplicate identifier '%s'\n", \
    yylineno, token_col, name);                      \
    error_reported = yylineno;                               \
}                                                            \
}                                                                \
} while (0)
%}

%union {
    char* sval;
    struct {
        int line;
        int col;
    } pos;
}

%token <sval> ID AND BOOLEAN CHAR CLASS EQ FINAL FLOAT FOR GE IF INT LE MM NE NEW INT_L FLOAT_L OR PP PRINT RETURN STATIC STR VOID WHILE TRUE FALSE COMMENT

%token INVALID_TOKEN

%left OR
%left AND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS

%nonassoc ERROR_PREC
%nonassoc IFX
%nonassoc ELSE

%type <sval> generic_id
%type <sval> id_list_init
%type <sval> init_or_not__
%type <sval> id_list
%type <sval> type_id
%type <sval> expr
%type <sval> type
%type <pos> arr_or_obj
%type <pos> init_decl
%type <sval> factor
%type <sval> lvalue
%type <sval> bool_expr
%type <sval> while_expr__

%%
classes:
/* empty */
| class_def                     // ← 加這個：允許單獨 class 成立
| classes class_def
| classes '}' {
    if (current_depth == 0 && !error_reported) {
        fprintf(stderr, "Line %d, char: %d, unmatched '}'\n",
                last_token_line, last_token_col);
        error_reported = yylineno;
    }
    yyclearin;
    yyerrok;
}
;

lines:
/* empty */
| lines expr '\n' {
    if (!error_reported) {
        flushLine();  // 印出對應這一行的內容（如需要）
    }
    error_reported = 0; // reset 錯誤狀態
}
| lines error '\n' {
    if (!error_reported) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        error_reported = yylineno;
    }
    yyerrok;
}
;

class_def: CLASS ID {
    my_insert($2, TYPE_KIND);
} '{' { push(); } declare '}' { pop(); } ;
// 處理變數或函數宣告
declare:
/* empty */
| declare error '\n' {
    if (!error_reported) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        error_reported = yylineno;
    }
    // 吃完這行剩下的 token
    int sync_count = 0;
    while (yychar != '\n' && yychar != YYEOF) {
        yychar = yylex();
        if (++sync_count > 100) break;
    }
    yyclearin;
    yyerrok;
}
| declare function_decl
| declare variable_decl
| declare class_def
| declare error ';'
| declare error '}'
| declare error
;
// 處理區塊
compound
: '{' { PUSH(); }
statement_star
'}' { POP(); }
| '{' { PUSH(); }
statement_star
error '}' {
    fprintf(stderr, "Line %d, char: %d, compound block had error before closing brace\n",
    @4.first_line, @4.first_column);
    POP();
    tokens[0] = '\0';
    error_reported = @4.first_line;
    yyclearin; yyerrok;
}
| error '}' {
    // 這裡通常是單一 else block 出錯所致，避免多報錯
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, malformed compound block\n", @2.first_line, @2.first_column);
        error_reported = @2.first_line;
    }
    POP();
    yyclearin; yyerrok;
}
;

spec_decl__:
variable_decl
| function_decl
;

id_item
: ID                           /* e.g.  int x; */
{
    chk_dupid_id($1);
    last_token_line = @1.last_line;
    last_token_col  = @1.last_column;
}
| ID '=' init_decl             /* e.g.  x = ... */
{
    chk_dupid_id($1);
    last_token_line = $3.line;
    last_token_col  = $3.col;
}
;

id_list:
id_item
| id_list ',' id_item
;

maybe_missing_semi
: ';'
| {
    int report_line = last_init_line; // ← 不是 last_token_line
    int report_col = last_init_col + 1;

    if ((strcmp(tokens, "int") == 0 || strcmp(tokens, "float") == 0 ||
    strcmp(tokens, "char") == 0 || strcmp(tokens, "boolean") == 0 ||
    strcmp(tokens, "void") == 0 || is_type(tokens)) &&
    report_line < yylineno) {

        fprintf(stderr, "Line %d, char: %d, statement without semicolon\n",
        report_line, report_col);
        error_reported = report_line;
    } else {
        fprintf(stderr, "Line %d, char: %d, syntax error: expected semicolon\n",
        yylineno, token_col);
        error_reported = yylineno;
    }

    yyerrok;
}
;

variable_decl
: spec_type__ id_list maybe_missing_semi {
    if (error_reported == yylineno) {
        // 我們剛剛在 maybe_missing_semi 報錯，現在來判斷是否要改回報 Line 10
        if (tokens[0] != '\0' && strcmp(tokens, "int") == 0 && last_token_line < yylineno) {
            // 下一行是新的宣告，而且上一個 token 是 NEW Point() 結尾
            // 重新印一次錯誤，把位置改回上一行
            fprintf(stderr, "Line %d, char: %d, statement without semicolon\n",
            last_token_line, last_token_col + 1);
            error_reported = last_token_line;
        }
        yyclearin;
        yyerrok;
        tokens[0] = '\0';
    }
}

| error spec_type__ id_list ';' {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, recovered declaration\n", yylineno, token_col);
    }
    skip_next_decl_typecheck = 1;
    yyerrok;
}

| spec_type__ id_list error {
    if (@2.last_line < @3.first_line) {
        // 判斷是否前一行已報過錯（常見於沒加分號）
        fprintf(stderr,
        "Line %d, char: %d, statement without semicolon\n",
        @2.last_line, @2.last_column + 1);
    } else if (error_reported != @3.first_line) {
        // ✅ 只有當這行尚未報錯時才顯示 syntax error
        fprintf(stderr,
        "Line %d, char: %d, syntax error near '%s'\n",
        @3.first_line, @3.first_column, tokens);
        error_reported = @3.first_line;
    }

    skip_next_decl_typecheck = 1;
    yyerrok;
}
;

function_decl:
ID '(' args ')' compound {
    if (my_insert($1, FUNC_KIND) < 0)
    fprintf(stderr, "Line %d, char: %d, duplicate identifier '%s'\n", yylineno, token_col, $1);
}
| spec_type__ ID '(' args ')' compound {
    if (my_insert($2, FUNC_KIND) < 0)
    fprintf(stderr, "Line %d, char: %d, duplicate identifier '%s'\n", yylineno, token_col, $2);
}
;

decl_impl:
'=' init_decl {
    //last_token_line = yylineno;
    //last_token_col = token_col + token_width;
    last_token_line = $2.line;
    last_token_col  = $2.col;
}
| ',' id_list {
    last_token_line = yylineno;
    last_token_col = token_col + token_width;
}
|
',' ID                              { chk_dupid_id($2); }
| ',' ID '=' init_decl                { chk_dupid_id($2); }
| decl_impl ',' ID                    { chk_dupid_id($3); }
| decl_impl ',' ID '=' init_decl      { chk_dupid_id($3); }
;

init_decl
: const_expr {
    $$.line = yylineno;
    $$.col  = token_col + token_width;

    last_token_line = $$.line;
    last_token_col  = $$.col;

    // 👇 加入
    last_init_line = $$.line;
    last_init_col  = $$.col;
}
| NEW type arr_or_obj {
    $$.line = @2.first_line;
    $$.col  = @2.first_column + 2;

    last_token_line = $$.line;
    last_token_col  = $$.col;

    // 👇 加入
    last_init_line = $$.line;
    last_init_col  = $$.col;
}
;

arr_or_obj
: '[' INT_L ']'   { $$.line = @3.last_line; $$.col = @3.last_column; }
| '(' tuple ')'   { $$.line = @3.last_line; $$.col = @3.last_column; }
;

final_decl__: final_decl_chk__ const_expr // For the class had not decl.
| final_decl_chk__ NEW type arr_or_obj
;

final_decl_chk__: FINAL type generic_id { chk_dupid_id($3); } '=';

spec_type__:
STATIC type
| FINAL type
| type
;

args:
| type generic_id { chk_dupid_id($2); }
| args ',' type generic_id { chk_dupid_id($4); }

init_or_not__: generic_id                         { $$ = $1; }
| generic_id '=' const_expr         { $$ = $1; }
| init_or_not__ ',' generic_id       { $$ = $3; }
| init_or_not__ ',' generic_id '=' const_expr { $$ = $3; }

id_list_init:
generic_id '=' const_expr          { $$ = $1; }
| id_list_init ',' generic_id '=' const_expr { $$ = $3; }
;

tuple:
tuple_items
| /* empty */
;

tuple_items:
INT_L
| FLOAT_L
| STR
| tuple_items INT_L
| tuple_items FLOAT_L
| tuple_items STR
;

generic_id: ID                 { $$ = $1; }                      // 傳 ID 的名字
| generic_id '[' expr ']'   { $$ = $1; }
| generic_id '.' ID          { $$ = $3; };            // 傳最後層的名稱


type: type '[' ']'        { $$ = $1; }
| INT
| FLOAT
| CHAR
| BOOLEAN
| VOID
| type_id
;

type_id: ID {
    if (!is_type($1)) {
        if (!skip_next_decl_typecheck && error_reported != yylineno) {
            fprintf(stderr, "Line %d, char: %d, undefined type '%s'\n", yylineno, token_col, $1);
            error_reported = yylineno;

            // 👉 強制吃掉直到這行結束為止
            int sync_count = 0;
            while (yychar != '\n' && yychar != ';' && yychar != '}' && yychar != YYEOF) {
                yychar = yylex();
                if (++sync_count > 100) break;
            }

            yyclearin;
            yyerrok;
        }
    }
    skip_next_decl_typecheck = 0; // 重置
    $$ = $1;
}

const_expr:
INT_L
| FLOAT_L
| STR
| generic_id
| INVALID_TOKEN { /* already有处理*/ }
| const_expr Infixop const_expr
;

Infixop: '+' | '-' | '*' | '/' | '%' | '>' | '<' | '&' | '|' | LE | GE | EQ | NE | AND | OR ;

lvalue
: generic_id                  { $$ = $1; }
| generic_id '[' expr ']'     { $$ = $1; }  // 回傳 base name 給 is_variable()
;

statement:
assign_stmt
| lvalue PP ';' {
    if (!is_variable($1)) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
        yylineno, token_col, $1);
        error_reported = yylineno;
    }
}
| PP lvalue ';' {
    if (!is_variable($2)) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
        yylineno, token_col, $2);
        error_reported = yylineno;
    }
}
| simple_call_decl ';'
| compound
| conditional
| loop
| return
| declare
| expr ';'
;

statement_star:
| statement_star statement
| statement_star error {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, unrecoverable error\n", last_token_line, last_token_col);
        error_reported = yylineno;
    }
    tokens[0] = '\0';

    int sync_count = 0;
    // 遇到常見的語句開頭、結尾或結構 token 為止
    while (yychar != ';' && yychar != '}' && yychar != ')' &&
    yychar != CLASS && yychar != IF && yychar != FOR &&
    yychar != WHILE && yychar != RETURN && yychar != PRINT &&
    yychar != YYEOF) {
        yychar = yylex();
        sync_count++;
        if (sync_count > 100) break;
    }

    yyclearin;
    yyerrok;
}
;

assign_stmt:
generic_id '=' expr ';' {
    if (!is_variable($1)) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n", yylineno, token_col, $1);
        error_reported = yylineno;
    }
}
;
;
// 處理簡單的函式呼叫，如 f(a);
simple_call_decl:
generic_id '(' para_list ')' {
    if (!is_function($1)) {
        // print 不是內建 function
        if (strcmp($1, "print") == 0) {
            fprintf(stderr, "Line %d, char: %d, undefined function 'print'\n", last_token_line, token_col);
        } else {
            fprintf(stderr, "Line %d, char: %d, undefined function '%s'\n", last_token_line, token_col, $1);
        }
        error_reported = yylineno;
    }
}
| generic_id '=' expr
| generic_id PP
| PP generic_id
| generic_id MM
| MM generic_id
| '+' generic_id
| '-' generic_id
| PRINT '(' expr ')' {
    my_insert("print", FUNC_KIND); // 加上這句
}
;
// 處理單純的表達式，如 a + b;
expr
: expr '+' expr
| expr '-' expr
| expr '*' expr
| expr '/' expr
| expr '%' expr
| expr AND expr
| expr OR expr
| expr EQ expr
| expr NE expr
| expr LE expr
| expr GE expr
| expr '<' expr
| expr '>' expr
| lvalue
| expr MM '-' expr {
    fprintf(stderr, "Line %d, char: %d, invalid token sequence '-- -'\n",
            @2.first_line, @2.first_column);
    error_reported = @2.first_line;
}
// ++ -
| expr PP '-' expr {
    fprintf(stderr, "Line %d, char: %d, invalid token sequence '++ -'\n", @2.first_line, @2.first_column);
    error_reported = @2.first_line;
}

// ++ +
| expr PP '+' expr {
    fprintf(stderr, "Line %d, char: %d, invalid token sequence '++ +'\n", @2.first_line, @2.first_column);
    error_reported = @2.first_line;
}

// ++ ++
| expr PP PP expr {
    fprintf(stderr, "Line %d, char: %d, invalid token sequence '++ ++'\n", @2.first_line, @2.first_column);
    error_reported = @2.first_line;
}

// ++ --
| expr PP MM expr {
    fprintf(stderr, "Line %d, char: %d, invalid token sequence '++ --'\n", @2.first_line, @2.first_column);
    error_reported = @2.first_line;
}

// -- +
| expr MM '+' expr {
    fprintf(stderr, "Line %d, char: %d, invalid token sequence '-- +'\n", @2.first_line, @2.first_column);
    error_reported = @2.first_line;
}

// -- ++
| expr MM PP expr {
    fprintf(stderr, "Line %d, char: %d, invalid token sequence '-- ++'\n", @2.first_line, @2.first_column);
    error_reported = @2.first_line;
}

// -- --
| expr MM MM expr {
    fprintf(stderr, "Line %d, char: %d, invalid token sequence '-- --'\n", @2.first_line, @2.first_column);
    error_reported = @2.first_line;
}

| expr PP {
    if (!is_variable($1)) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
        yylineno, token_col, $1);
        error_reported = yylineno;
    }
}
| expr MM {
    if (!is_variable($1)) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
        yylineno, token_col, $1);
        error_reported = yylineno;
    }
}
| expr '+' error {
    fprintf(stderr, "Line %d, char: %d, invalid token after '+'\n", @3.first_line, @3.first_column);
    error_reported = yylineno;
    yyclearin; yyerrok;
}
| expr '-' error {
    fprintf(stderr, "Line %d, char: %d, invalid token after '-'\n", @3.first_line, @3.first_column);
    error_reported = yylineno;
    yyclearin; yyerrok;
}
| expr '*' error {
    fprintf(stderr, "Line %d, char: %d, invalid token after '*'\n", @3.first_line, @3.first_column);
    error_reported = yylineno;
    yyclearin; yyerrok;
}
| expr '/' error {
    fprintf(stderr, "Line %d, char: %d, invalid token after '/'\n", @3.first_line, @3.first_column);
    error_reported = yylineno;
    yyclearin; yyerrok;
}
| error {
    if (error_reported != yylineno) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        error_reported = yylineno;
    }

    // 加入同步（跳過直到常見語句分隔符）
    int sync_count = 0;
    while (yychar != ';' && yychar != ')' &&
    yychar != '}' && yychar != YYEOF) {
        yychar = yylex();
        if (++sync_count > 100) break;
    }

    yyclearin;
    yyerrok;
    $$ = NULL;
}
| factor
;

factor
: generic_id
| INT_L
| FLOAT_L
| STR
| generic_id '(' para_list ')' {
    if (!is_function($1)) {
        if (strcmp($1, "print") == 0) {
            fprintf(stderr, "Line %d, char: %d, undefined function 'print'\n", last_token_line, token_col);
        } else {
            fprintf(stderr, "Line %d, char: %d, undefined function '%s'\n", last_token_line, token_col, $1);
        }
        error_reported = yylineno;
    }
}
| lvalue PP {
    if (!is_variable($1)) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
                yylineno, token_col, $1);
        error_reported = yylineno;
    }
    $$ = $1;
}
| lvalue MM {
    if (!is_variable($1)) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
                yylineno, token_col, $1);
        error_reported = yylineno;
    }
    $$ = $1;
}
| '(' expr ')'
| '-' factor %prec UMINUS
| PP factor
| MM factor
| INVALID_TOKEN {
    if (error_reported != yylineno) {
        fprintf(stderr,
        "Line %d, char: %d, invalid token in expression\n",
        last_token_line, last_token_col);
        error_reported = yylineno;
    }
    tokens[0] = '\0';
    yyclearin;
    yyerrok;
}
| factor error {
    if (error_reported != yylineno) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        error_reported = yylineno;
    }
    yyclearin;
    yyerrok;
}
| error factor {
    if (error_reported != yylineno) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        error_reported = yylineno;
    }
    //fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
    error_reported = yylineno;
    yyclearin;
    yyerrok;
}
;

term: factor
| term '*' factor
| term '/' factor
;
// 處理 if-else 條件語句
conditional
: IF '(' bool_expr ')' statement %prec IFX
| IF '(' bool_expr ')' statement ELSE statement
| ELSE statement {
    fprintf(stderr, "Line %d, char: %d, 'else' without matching 'if'\n",
    @1.first_line, @1.first_column);
    error_reported = @1.first_line;
    yyclearin; yyerrok;
}
;

if_expr__: IF '(' bool_expr ')';

if_simple__  : if_expr__ simple_call_decl;
if_compound__: if_expr__ compound;

else_simple__: ELSE simple_call_decl;
else_compound__: ELSE compound;

bool_expr
: expr          { $$ = NULL; }
| INVALID_TOKEN {
    fprintf(stderr, "Line %d, char: %d, invalid token in condition\n", last_token_line, last_token_col);
    error_reported = yylineno;
    tokens[0] = '\0';

    // 吃到 ')' 作同步
    int sync_count = 0;
    while (yychar != ')' && yychar != YYEOF) {
        yychar = yylex();
        if (++sync_count > 100) break;
    }

    yyclearin; yyerrok;
    $$ = "invalid";  // ✨ 關鍵
}
| error {
    fprintf(stderr, "Line %d, char: %d, invalid condition\n", last_token_line, last_token_col);
    error_reported = yylineno;
    yyclearin; yyerrok;
    $$ = "invalid";  // ✨ 關鍵
}
;
// 處理 while 或 for 等迴圈
loop
: while_expr__ statement {
    if ($1 && strcmp($1, "invalid") == 0) {
        // 報錯：條件錯誤
        fprintf(stderr, "Line %d, char: %d, invalid while condition, skipping statement\n", last_token_line, last_token_col);
        error_reported = yylineno;

        // ⛔ 不再吃掉整個 block，保留 '{' 和 '}'
        // 只略過 statement 的內部 token（例如 print）到 ';' 或 '}'
        int sync_count = 0;
        while (yychar != ';' && yychar != '}' &&
       yychar != PRINT && yychar != ID &&
       yychar != CLASS && yychar != RETURN &&
       yychar != IF && yychar != WHILE &&
       yychar != FOR && yychar != YYEOF) {
            yychar = yylex();
            if (++sync_count > 100) break;
        }

        yyclearin;
        yyerrok;
    }
}
| WHILE '(' bool_expr ')' error {
    fprintf(stderr, "Line %d, char: %d, invalid while-block after condition\n", @5.first_line, @5.first_column);
    error_reported = @5.first_line;
    tokens[0] = '\0';
    yyclearin;
    yyerrok;

    // 同步到 '}' 或 ';'
    int sync_count = 0;
    while (yychar != '}' && yychar != ';' && yychar != YYEOF) {
        yychar = yylex();
        if (++sync_count > 100) break;
    }
}
| for_expr__  statement
| while_expr__ error {
    fprintf(stderr, "Line %d, char: %d, syntax error after while condition\n",
    last_token_line, last_token_col);
    tokens[0] = '\0';
    error_reported = yylineno;
    yyclearin; yyerrok;
}
| for_expr__ error {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, syntax error after for condition\n", last_token_line, last_token_col);
        error_reported = yylineno;
    }
    tokens[0] = '\0';
    yyclearin; yyerrok;
}
;

while_expr__:
WHILE '(' bool_expr ')' {
    if ($3 && strcmp($3, "invalid") == 0) {
        $$ = "invalid";  // 傳遞錯誤狀態給 loop
    } else {
        $$ = NULL;
    }
}
| WHILE '(' error {
      fprintf(stderr, "Line %d, char: %d, malformed while condition\n",
      @3.first_line, @3.first_column);
      error_reported = @3.first_line;
      tokens[0] = '\0';
      yyclearin;
      yyerrok;

      // 做基本同步，吃到 ')' 為止
      int sync_count = 0;
      while (yychar != ')' && yychar != YYEOF) {
          yychar = yylex();
          if (++sync_count > 100) break;
      }
  }
| WHILE error ')' {
    fprintf(stderr, "Line %d, char: %d, invalid condition inside while\n",
    last_token_line, last_token_col);
    tokens[0] = '\0';
    error_reported = yylineno;
    yyclearin;
    yyerrok;
}
;

ForInitOpt:
/* empty */
| for_init_list
;

for_init_list:
single_for_init
| for_init_list ',' single_for_init
;

single_for_init:
generic_id '=' expr  {
    if (!is_variable($1))
    fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
    yylineno, token_col, $1);
    error_reported = yylineno;
    tokens[0] = '\0';
}
| type generic_id '=' expr {
    chk_dupid_id($2); // 宣告 inline 變數
}
| generic_id PP {
    if (!is_variable($1))
    fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
    yylineno, token_col, $1);
    error_reported = yylineno;
    tokens[0] = '\0';
}
| PP generic_id {
    if (!is_variable($2))
    fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
    yylineno, token_col, $2);
    error_reported = yylineno;
    tokens[0] = '\0';
}
;

for_expr__: FOR '(' ForInitOpt ';' bool_expr ';' ForUpdateOpt ')'
| FOR error ')' {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, syntax error in for-loop expression\n", last_token_line, last_token_col);
        error_reported = yylineno;
    }
    yyclearin;
    yyerrok;
}
;

ForUpdateOpt:
/* empty */
| for_update_list
;
for_update_list:
simple_call_decl
| for_update_list ',' simple_call_decl
;
// 處理 return 
return:
RETURN expr ';'
| RETURN ';'
| RETURN error {
    fprintf(stderr, "Line %d, char: %d, invalid return expression\n", last_token_line, last_token_col);
    yyclearin; yyerrok;
};

para_list:
/* empty */
| expr
| para_list ',' expr
| error {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, invalid function parameter list\n", last_token_line, last_token_col);
        error_reported = yylineno;
    }
    tokens[0] = '\0';
    yyclearin;
    yyerrok;
}
;

%%
void yyerror(const char *s) {
    if (error_reported == yylineno || error_reported == last_token_line)
    return;

    const char *tok = (tokens[0] == '\0') ? "<EOL>" : tokens;
    snprintf(pending_message, sizeof(pending_message),
    "Line %d, char: %d, a syntax error at \"%s\"\n",
    last_token_line, last_token_col, tok);

    pending_error = 1;
    tokens[0] = '\0';
    error_reported = yylineno;
}

int main() {
    //my_insert("print", FUNC_KIND);
    tokens[0] = '\0';
    yyparse();
    int t;
    while ((t = yylex()) > 0); // 把剩下的 token 都掃過
    flushLine();
    return 0;
}
