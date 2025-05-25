/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_B113040052_TAB_H_INCLUDED
# define YY_YY_B113040052_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    AND = 259,                     /* AND  */
    BOOLEAN = 260,                 /* BOOLEAN  */
    CHAR = 261,                    /* CHAR  */
    CLASS = 262,                   /* CLASS  */
    EQ = 263,                      /* EQ  */
    FINAL = 264,                   /* FINAL  */
    FLOAT = 265,                   /* FLOAT  */
    FOR = 266,                     /* FOR  */
    GE = 267,                      /* GE  */
    IF = 268,                      /* IF  */
    INT = 269,                     /* INT  */
    LE = 270,                      /* LE  */
    MM = 271,                      /* MM  */
    NE = 272,                      /* NE  */
    NEW = 273,                     /* NEW  */
    INT_L = 274,                   /* INT_L  */
    FLOAT_L = 275,                 /* FLOAT_L  */
    OR = 276,                      /* OR  */
    PP = 277,                      /* PP  */
    PRINT = 278,                   /* PRINT  */
    RETURN = 279,                  /* RETURN  */
    STATIC = 280,                  /* STATIC  */
    STR = 281,                     /* STR  */
    VOID = 282,                    /* VOID  */
    WHILE = 283,                   /* WHILE  */
    TRUE = 284,                    /* TRUE  */
    FALSE = 285,                   /* FALSE  */
    COMMENT = 286,                 /* COMMENT  */
    INVALID_TOKEN = 287,           /* INVALID_TOKEN  */
    UMINUS = 288,                  /* UMINUS  */
    ERROR_PREC = 289,              /* ERROR_PREC  */
    IFX = 290,                     /* IFX  */
    ELSE = 291,                    /* ELSE  */
    YY_PARSE_classes = 292,        /* YY_PARSE_classes  */
    YY_PARSE_lines = 293           /* YY_PARSE_lines  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 136 "B113040052.y"

    char* sval;
    struct {
        int line;
        int col;
    } pos;

#line 110 "B113040052.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);

// Return type when parsing one classes.
typedef struct
{
  int yystatus;
  int yynerrs;
} yyparse_classes_t;

// Parse one classes.
yyparse_classes_t yyparse_classes (void);

// Return type when parsing one lines.
typedef struct
{
  int yystatus;
  int yynerrs;
} yyparse_lines_t;

// Parse one lines.
yyparse_lines_t yyparse_lines (void);


#endif /* !YY_YY_B113040052_TAB_H_INCLUDED  */
