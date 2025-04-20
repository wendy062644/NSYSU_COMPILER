%{
#include<stdio.h>
#include<string.h>
unsigned charCount = 1, idCount = 0, lineCount = 1;
void logToken(const char *type, const char *text);


typedef struct node {
    char name[128];
    struct node* next;
} node;

node* symbol_table[1024];

unsigned int hash(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = (((hash << 5) + hash) + c) % 1024; // (hash * 33 + c) % 1024
    return hash % 1024;
}

void create() {
    for (int i = 0; i < 1024; ++i) {
        symbol_table[i] = NULL;
    }
}

int lookup(const char* s) {
    unsigned int idx = hash(s);
    node* curr = symbol_table[idx];
    while (curr != NULL) {
        if (strcmp(curr->name, s) == 0) {
            return idx; // found
        }
        curr = curr->next;
    }
    return -1; // not found
}

int insert(const char* s) {
    if (lookup(s) != -1) return -1; // already exists
    unsigned int idx = hash(s);
    node* newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->name, s);
    newnode->next = symbol_table[idx];
    symbol_table[idx] = newnode;
    return idx;
}

void dump() {
    printf("The symbol table contains:\n");
    for (int i = 0; i < 1024; ++i) {
        node* curr = symbol_table[i];
        while (curr != NULL) {
            printf("%s\n", curr->name);
            curr = curr->next;
        }
    }
}
%}

/* Regular Expressions */
addition (\+|\+\+)
subtraction (\-|\-\-)
multiplication (\*)
division (\/|%)
assignment (\=)
relational (\<|\<=|\>=|\>|\==|\!=)
logical (\&\&|\|\||\!)
bitwise \^
/* operate ^ */

space [ \t]
eol \n
reserved_word boolean|break|byte|case|char|catch|class|const|continue|default|do|double|else|extends|false|final|finally|float|for|if|implements|int|long|main|new|print|private|protected|public|return|short|static|string|switch|this|true|try|void|while
symbol [,\:\;\(\)\[\]\{\}]
id [A-Za-z_][A-Za-z0-9_]*
integer [+-]?[0-9]+
hex_integer 0[xX][0-9a-fA-F]+
float ([+-]?(([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)([eE][+-]?[0-9]+)?[fF]?|[0-9]+[eE][+-]?[0-9]+[fF]?))
string \"([^\\\"]|\\.)*\"
comment (\/\/.*|\/\*([^*]|\*+[^*/])*\*+\/)

%%
{addition} {
    logToken("operator", yytext);
    charCount += yyleng;
}

{subtraction} {
    logToken("operator", yytext);
    charCount += yyleng;
}

{multiplication} {
    logToken("operator", yytext);
    charCount += yyleng;
}

{division} {
    logToken("operator", yytext);
    charCount += yyleng;
}

{assignment} {
    logToken("operator", yytext);
    charCount += yyleng;
}

{relational} {
    logToken("operator", yytext);
    charCount += yyleng;
}

{logical} {
    logToken("operator", yytext);
    charCount += yyleng;
}

{space} {
    charCount++;
}

{eol} {
    lineCount++;
    charCount = 1;
}

{reserved_word} {
    logToken("reserved word", yytext);
    charCount += yyleng;
}

{symbol} {
    logToken("symbol", yytext);
    charCount += yyleng;
}

{integer} {
    logToken("integer", yytext);
    charCount += yyleng;
}

{hex_integer} {
    logToken("integer", yytext);
    charCount += yyleng;
}

{float} {
    logToken("float", yytext);
    charCount += yyleng;
}

{string} {
    int index = 0;
    for(int i = 1; i < strlen(yytext)-1; i++) {
        if(yytext[i] == '\\') {
            if (yytext[i+1] == '"') {
                yytext[index++] = '"';
                i++;
            }
            else if (yytext[i+1] == '\\') {
                yytext[index++] = '\\';
                i++;
            }
            else {
                continue;
            }
        } else {
            yytext[index++] = yytext[i];
        }
    }
    yytext[yyleng-2] = '\0';
    charCount++;
    logToken("string", yytext);
    charCount += yyleng-1;
}

{comment} {
    logToken("comment", yytext);
    charCount += yyleng;
}

{id} {
    logToken("ID", yytext);
    charCount += yyleng;
    insert(yytext);
}

[\r\v\f]  {
    /* Do nothing */
}

. {
    logToken("error", yytext);
    charCount += yyleng;
}

%%

void logToken(const char *type, const char *text) {
    if(type[0] == 'a'||type[0] == 'e'||type[0] == 'i'||type[0] == 'o'||type[0] == 'u'||
       type[0] == 'A'||type[0] == 'E'||type[0] == 'I'||type[0] == 'O'||type[0] == 'U') {
        printf("Line: %d, 1st char: %d, \"%s\" is an \"%s\".\n", lineCount, charCount, text, type);
    }
    else {
        printf("Line: %d, 1st char: %d, \"%s\" is a \"%s\".\n", lineCount, charCount, text, type);
    }
}

int main() {
    create();
    yylex();
    dump();
    return 0;
}

