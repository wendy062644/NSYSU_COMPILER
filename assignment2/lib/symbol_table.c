#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

#define MAX_SCOPE 100
#define TABLE_SIZE 211

typedef struct Symbol {
    char name[64];
    struct Symbol* next;
} Symbol;

static Symbol* scopes[MAX_SCOPE];  // symbol stack
static int scope_top = -1;
static int debug = 0;

unsigned int hash(const char* str) {
    unsigned int h = 0;
    while (*str) h = (h << 4) + *str++;
    return h % TABLE_SIZE;
}

void push() {
    if (scope_top + 1 >= MAX_SCOPE) {
        fprintf(stderr, "Too many nested scopes!\n");
        exit(1);
    }
    scopes[++scope_top] = NULL;
    if (debug) printf(">> Enter scope %d\n", scope_top);
}

void pop() {
    Symbol* s = scopes[scope_top--];
    while (s) {
        Symbol* tmp = s;
        s = s->next;
        free(tmp);
    }
    if (debug) printf("<< Exit scope %d\n", scope_top + 1);
}

int insert(const char* name) {
    unsigned int h = hash(name);
    Symbol* cur = scopes[scope_top];
    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            return -1; // duplicate
        }
        cur = cur->next;
    }
    Symbol* new_sym = malloc(sizeof(Symbol));
    strcpy(new_sym->name, name);
    new_sym->next = scopes[scope_top];
    scopes[scope_top] = new_sym;
    if (debug) printf("Insert %s into scope %d\n", name, scope_top);
    return 0;
}

void set_dbg(int x) {
    debug = x;
}

