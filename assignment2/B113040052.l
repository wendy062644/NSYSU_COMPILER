%{
#include<stdio.h>
#include<string.h>
#include "B113040052.tab.h"

void flushPendingError(void);
unsigned charCount = 1, idCount = 0, lineCount = 1;
void logToken(const char *type, const char *text);
char tokens[256];
char lineBuffer[1024] = "";
int token_col = 1;
extern int yylineno;
int skipFlush = 0;

int operator_error_reported = 0;
int last_token_col = 1;
int last_token_line = 1;
int token_width = 1;

#define SET_TOKEN_INFO()                                    \
    do {                                                    \
        /* token 起始欄位 (= 本行已掃過的字元+1) */          \
        int startCol = charCount;                           \
                                                            \
        /* -------- 你原本存到 parser 的四個變數 ---------- */\
        token_col       = startCol;                         \
        last_token_col  = startCol;                         \
        last_token_line = yylineno;                         \
        token_width     = yyleng;                           \
        strncpy(tokens, yytext, sizeof tokens);             \
                                                            \
        /* ---------------- 位置資訊給 Bison ---------------- */\
        yylloc.first_line   = yylineno;                     \
        yylloc.last_line    = yylineno;                     \
        yylloc.first_column = startCol;                     \
        yylloc.last_column  = startCol + yyleng - 1;        \
                                                            \
        /* --------- 記得把游標往後推 ------------- */        \
        charCount += yyleng;                                \
    } while (0)

void appendToLine(const char *text) {
    if (strlen(lineBuffer) + strlen(text) + 1 < sizeof(lineBuffer)) {
        strcat(lineBuffer, text);
        strcat(lineBuffer, " "); // 加空格
    }
}

void flushLine() {
    if (strlen(lineBuffer) > 0) {
        printf("line %d: %s\n", lineCount, lineBuffer);
        lineBuffer[0] = '\0';
    }
    token_col = 1; // reset 每行開頭
}
%}

/* Regular Expressions */
addition (\+|\+\+)
subtraction (\-|\-\-)
multiplication (\*)
division (\/|%)
assignment (\=)
relational (\<=|\>=|\==|\!=|\<|\>)
logical (\&\&|\|\||\!)
bitwise \^

space [ \t]
eol \n
symbol [,\:\;\(\)\[\]\{\}]
id [A-Za-z_][A-Za-z0-9_]*
integer [+-]?[0-9]+
hex_integer 0[xX][0-9a-fA-F]+
float   ([0-9]+\.[0-9]*([eE][+-]?[0-9]+)?[fF]?)|([0-9]+[eE][+-]?[0-9]+[fF]?)
string \"([^\\\"]|\\.)*\"

%%


"print"   { SET_TOKEN_INFO(); appendToLine(yytext); return PRINT; }
"int"     { SET_TOKEN_INFO(); yylval.sval = strdup("int"); appendToLine(yytext); return INT; }
"float"   { SET_TOKEN_INFO(); yylval.sval = strdup("float"); appendToLine(yytext); return FLOAT; }
"class"   { SET_TOKEN_INFO(); yylval.sval = strdup("class"); appendToLine(yytext); return CLASS; }
"void"    { SET_TOKEN_INFO(); yylval.sval = strdup("void"); appendToLine(yytext); return VOID; }
"main"    { SET_TOKEN_INFO(); yylval.sval = strdup("main"); appendToLine(yytext); return ID; }
"if"      { SET_TOKEN_INFO(); yylval.sval = strdup("if"); appendToLine(yytext); return IF; }
"else"    { SET_TOKEN_INFO(); yylval.sval = strdup("else"); appendToLine(yytext); return ELSE; }
"for"     { SET_TOKEN_INFO(); yylval.sval = strdup("for"); appendToLine(yytext); return FOR; }
"while"   { SET_TOKEN_INFO(); yylval.sval = strdup("while"); appendToLine(yytext); return WHILE; }
"return"  { SET_TOKEN_INFO(); yylval.sval = strdup("return"); appendToLine(yytext); return RETURN; }
"final"   { SET_TOKEN_INFO(); yylval.sval = strdup("final"); appendToLine(yytext); return FINAL; }
"new"     { SET_TOKEN_INFO(); yylval.sval = strdup("new"); appendToLine(yytext); return NEW; }
"static"  { SET_TOKEN_INFO(); yylval.sval = strdup("static"); appendToLine(yytext); return STATIC; }
"boolean" { SET_TOKEN_INFO(); yylval.sval = strdup("boolean"); appendToLine(yytext); return BOOLEAN; }
"char"    { SET_TOKEN_INFO(); yylval.sval = strdup("char"); appendToLine(yytext); return CHAR; }
"true"    { SET_TOKEN_INFO(); yylval.sval = strdup("true"); appendToLine(yytext); return TRUE; }
"false"   { SET_TOKEN_INFO(); yylval.sval = strdup("false"); appendToLine(yytext); return FALSE; }
"**/" {
    strcpy(tokens, yytext);
    fprintf(stderr, "Line %d, char: %d, invalid token '%s'\n", yylineno, token_col, yytext);
    return INVALID_TOKEN;
}

"//".* {
    SET_TOKEN_INFO();
    appendToLine(yytext); // 讓註解跟 source code 一起進 lineBuffer
}

^[ \t]*\n {
    // 單獨一行只有空白+換行，直接輸出 line N:
    if (strlen(lineBuffer) > 0) flushLine();
    else printf("line %d:\n", lineCount);
    lineCount++; charCount = 1; yylineno = lineCount; tokens[0] = '\0';
}

"/*"([^*]|\*+[^*/])*\*+"/" {
    char *p = yytext;
    int last = 0;
    // 如果 block comment 是從新的一行開始，且開頭是 \n
    if (p[0] == '\n') {
        // 強制補一個空行
        if (strlen(lineBuffer) > 0) {
            flushLine();
        } else {
            printf("line %d:\n", lineCount);
        }
        lineCount++;
        last = 1; // 接下來從第 2 個字元處理註解
    }
    for (int i = last; p[i] != 0; ++i) {
        if (p[i] == '\n') {
            char tmp[1024];
            int len = i - last;
            if (len > 0) {
                strncpy(tmp, &p[last], len);
                tmp[len] = '\0';
                appendToLine(tmp);
            } else {
                flushLine();
            }
            flushLine();
            lineCount++;
            last = i + 1;
        }
    }
    // 剩下的內容
    if (p[last] != 0) {
        appendToLine(&p[last]);
        flushLine();
    }
}

"/*".* {
    // ❌ 不完整結尾的 block comment
    fprintf(stderr, "Line %d, char: %d, unterminated block comment\n", lineCount, charCount);
    flushLine();
    return 0;  // 強制結束 → 傳回 EOF
}

"++"         { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return PP; }
"--"         { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return MM; }
([+*/%]-|[+*/%][+*/%]|[-+*/%]{3,}) {
    if (!operator_error_reported) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        operator_error_reported = 1;
    }
    SET_TOKEN_INFO();
    appendToLine(yytext);
    strncpy(tokens, yytext, sizeof(tokens));
    return INVALID_TOKEN;
}
"=="         { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return EQ; }
"!="         { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return NE; }
"<="         { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return LE; }
">="         { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return GE; }
"&&"         { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return AND; }
"||"         { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return OR; }
"+"          { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return '+'; }
"-"          { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return '-'; }
"*"          { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return '*'; }
"/"          { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return '/'; }
"%"          { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return '%'; }
"="          { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return '='; }
">"          { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return '>'; }
"<"          { SET_TOKEN_INFO(); appendToLine(yytext); charCount += yyleng; return '<'; }

 /*
"++"|"--"|"=="|"!="|">="|"<="|"&&"|"||"|"+"|"-"|"*"|"/"|"%"|"="|">"|"<" {
    SET_TOKEN_INFO(); appendToLine(yytext);
    charCount += yyleng;
    return yytext[0];
}*/

{space}+ {
    tokens[0] = '\0';
    for (int i = 0; i < yyleng; i++) {
        charCount += (yytext[i] == '\t') ? 4 : 1;
    }
}

{eol} {
    flushPendingError();  // 先印錯誤訊息
    if (strlen(lineBuffer) > 0)
        flushLine();      // 再印本行內容
    lineCount++; charCount = 1;
    yylineno = lineCount;
    tokens[0] = '\0';
    operator_error_reported = 0;
}

{symbol} {
    SET_TOKEN_INFO(); appendToLine(yytext);
    logToken("symbol", yytext); charCount += yyleng;
    return yytext[0];
}

{integer} {
    SET_TOKEN_INFO(); appendToLine(yytext);
    logToken("integer", yytext); charCount += yyleng;
    return INT_L;
}

{hex_integer} {
    SET_TOKEN_INFO(); appendToLine(yytext);
    logToken("integer", yytext); charCount += yyleng;
    return INT_L;
}

{float} {
    SET_TOKEN_INFO(); appendToLine(yytext);
    logToken("float", yytext); charCount += yyleng;
    return FLOAT_L;
}

{string} {
    SET_TOKEN_INFO();
    char tmp[80] = {0}; int index = 0;
    for (int i = 1; i < strlen(yytext)-1 && index < 79; i++) {
        if (yytext[i] == '\\') {
            if (yytext[i+1] == '\"') { tmp[index++] = '"'; i++; }
            else if (yytext[i+1] == '\\') { tmp[index++] = '\\'; i++; }
        } else tmp[index++] = yytext[i];
    }
    tmp[index] = '\0';
    strncpy(tokens, tmp, sizeof(tokens));
    logToken("string", tmp);
    appendToLine(yytext);
    charCount += yyleng;
    return STR;
}

{id} {
    SET_TOKEN_INFO();
    yylval.sval = strdup(yytext);
    logToken("ID", yytext);
    appendToLine(yytext);
    charCount += yyleng;
    return ID;
}

[\r\v\f] { /* Do nothing */ }

<<EOF>> {
    if (strlen(lineBuffer) > 0)
        flushLine();
    return 0;
}

. {
    SET_TOKEN_INFO();
    fprintf(stderr, "Line %d, char: %d, unknown symbol '%s'\n", yylineno, token_col, yytext);
    charCount += yyleng;
    return -1; // 確保 parser 拋棄
}

%%

void logToken(const char *type, const char *text) {
    // Optional debug output
}

