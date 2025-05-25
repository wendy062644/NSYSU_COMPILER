/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 4 "B113040052.y"

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

#line 203 "B113040052.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "B113040052.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_AND = 4,                        /* AND  */
  YYSYMBOL_BOOLEAN = 5,                    /* BOOLEAN  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_CLASS = 7,                      /* CLASS  */
  YYSYMBOL_EQ = 8,                         /* EQ  */
  YYSYMBOL_FINAL = 9,                      /* FINAL  */
  YYSYMBOL_FLOAT = 10,                     /* FLOAT  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_INT = 14,                       /* INT  */
  YYSYMBOL_LE = 15,                        /* LE  */
  YYSYMBOL_MM = 16,                        /* MM  */
  YYSYMBOL_NE = 17,                        /* NE  */
  YYSYMBOL_NEW = 18,                       /* NEW  */
  YYSYMBOL_INT_L = 19,                     /* INT_L  */
  YYSYMBOL_FLOAT_L = 20,                   /* FLOAT_L  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_PP = 22,                        /* PP  */
  YYSYMBOL_PRINT = 23,                     /* PRINT  */
  YYSYMBOL_RETURN = 24,                    /* RETURN  */
  YYSYMBOL_STATIC = 25,                    /* STATIC  */
  YYSYMBOL_STR = 26,                       /* STR  */
  YYSYMBOL_VOID = 27,                      /* VOID  */
  YYSYMBOL_WHILE = 28,                     /* WHILE  */
  YYSYMBOL_TRUE = 29,                      /* TRUE  */
  YYSYMBOL_FALSE = 30,                     /* FALSE  */
  YYSYMBOL_COMMENT = 31,                   /* COMMENT  */
  YYSYMBOL_INVALID_TOKEN = 32,             /* INVALID_TOKEN  */
  YYSYMBOL_33_ = 33,                       /* '<'  */
  YYSYMBOL_34_ = 34,                       /* '>'  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_UMINUS = 40,                    /* UMINUS  */
  YYSYMBOL_ERROR_PREC = 41,                /* ERROR_PREC  */
  YYSYMBOL_IFX = 42,                       /* IFX  */
  YYSYMBOL_ELSE = 43,                      /* ELSE  */
  YYSYMBOL_YY_PARSE_classes = 44,          /* YY_PARSE_classes  */
  YYSYMBOL_45_ = 45,                       /* '}'  */
  YYSYMBOL_YY_PARSE_lines = 46,            /* YY_PARSE_lines  */
  YYSYMBOL_47_n_ = 47,                     /* '\n'  */
  YYSYMBOL_48_ = 48,                       /* '{'  */
  YYSYMBOL_49_ = 49,                       /* ';'  */
  YYSYMBOL_50_ = 50,                       /* '='  */
  YYSYMBOL_51_ = 51,                       /* ','  */
  YYSYMBOL_52_ = 52,                       /* '('  */
  YYSYMBOL_53_ = 53,                       /* ')'  */
  YYSYMBOL_54_ = 54,                       /* '['  */
  YYSYMBOL_55_ = 55,                       /* ']'  */
  YYSYMBOL_56_ = 56,                       /* '.'  */
  YYSYMBOL_57_ = 57,                       /* '&'  */
  YYSYMBOL_58_ = 58,                       /* '|'  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_classes = 60,                   /* classes  */
  YYSYMBOL_lines = 61,                     /* lines  */
  YYSYMBOL_class_def = 62,                 /* class_def  */
  YYSYMBOL_63_1 = 63,                      /* $@1  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_declare = 65,                   /* declare  */
  YYSYMBOL_compound = 66,                  /* compound  */
  YYSYMBOL_67_3 = 67,                      /* $@3  */
  YYSYMBOL_68_4 = 68,                      /* $@4  */
  YYSYMBOL_id_item = 69,                   /* id_item  */
  YYSYMBOL_id_list = 70,                   /* id_list  */
  YYSYMBOL_maybe_missing_semi = 71,        /* maybe_missing_semi  */
  YYSYMBOL_variable_decl = 72,             /* variable_decl  */
  YYSYMBOL_function_decl = 73,             /* function_decl  */
  YYSYMBOL_init_decl = 74,                 /* init_decl  */
  YYSYMBOL_arr_or_obj = 75,                /* arr_or_obj  */
  YYSYMBOL_spec_type__ = 76,               /* spec_type__  */
  YYSYMBOL_args = 77,                      /* args  */
  YYSYMBOL_tuple = 78,                     /* tuple  */
  YYSYMBOL_tuple_items = 79,               /* tuple_items  */
  YYSYMBOL_generic_id = 80,                /* generic_id  */
  YYSYMBOL_type = 81,                      /* type  */
  YYSYMBOL_type_id = 82,                   /* type_id  */
  YYSYMBOL_const_expr = 83,                /* const_expr  */
  YYSYMBOL_Infixop = 84,                   /* Infixop  */
  YYSYMBOL_lvalue = 85,                    /* lvalue  */
  YYSYMBOL_statement = 86,                 /* statement  */
  YYSYMBOL_statement_star = 87,            /* statement_star  */
  YYSYMBOL_assign_stmt = 88,               /* assign_stmt  */
  YYSYMBOL_simple_call_decl = 89,          /* simple_call_decl  */
  YYSYMBOL_expr = 90,                      /* expr  */
  YYSYMBOL_factor = 91,                    /* factor  */
  YYSYMBOL_conditional = 92,               /* conditional  */
  YYSYMBOL_bool_expr = 93,                 /* bool_expr  */
  YYSYMBOL_loop = 94,                      /* loop  */
  YYSYMBOL_while_expr__ = 95,              /* while_expr__  */
  YYSYMBOL_ForInitOpt = 96,                /* ForInitOpt  */
  YYSYMBOL_for_init_list = 97,             /* for_init_list  */
  YYSYMBOL_single_for_init = 98,           /* single_for_init  */
  YYSYMBOL_for_expr__ = 99,                /* for_expr__  */
  YYSYMBOL_ForUpdateOpt = 100,             /* ForUpdateOpt  */
  YYSYMBOL_for_update_list = 101,          /* for_update_list  */
  YYSYMBOL_return = 102,                   /* return  */
  YYSYMBOL_para_list = 103                 /* para_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2180

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  181
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  301

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      47,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    39,    57,     2,
      52,    53,    37,    35,    51,    36,    56,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    49,
      33,    50,    34,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    58,    45,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    40,    41,
      42,    43,    44,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   175,   175,   175,   177,   178,   179,   189,   191,   197,
     206,   208,   206,   210,   212,   213,   214,   215,   216,   217,
     221,   221,   224,   224,   234,   251,   257,   266,   267,   271,
     272,   295,   308,   316,   336,   340,   365,   376,   390,   391,
     401,   402,   403,   406,   407,   408,   421,   422,   426,   427,
     428,   429,   430,   431,   434,   435,   436,   439,   440,   441,
     442,   443,   444,   445,   448,   460,   461,   462,   463,   464,
     465,   468,   468,   468,   468,   468,   468,   468,   468,   468,
     468,   468,   468,   468,   468,   468,   471,   472,   476,   477,
     484,   491,   492,   493,   494,   495,   496,   497,   500,   501,
     502,   526,   536,   547,   548,   549,   550,   551,   552,   553,
     554,   560,   561,   562,   563,   564,   565,   566,   567,   568,
     569,   570,   571,   572,   573,   574,   581,   588,   593,   598,
     603,   608,   626,   630,   631,   632,   633,   634,   644,   652,
     660,   661,   662,   663,   664,   675,   683,   701,   702,   703,
     720,   721,   736,   744,   760,   774,   775,   782,   793,   800,
     815,   825,   827,   831,   832,   836,   843,   846,   853,   862,
     863,   873,   875,   878,   879,   883,   884,   885,   890,   892,
     893,   894
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "AND", "BOOLEAN",
  "CHAR", "CLASS", "EQ", "FINAL", "FLOAT", "FOR", "GE", "IF", "INT", "LE",
  "MM", "NE", "NEW", "INT_L", "FLOAT_L", "OR", "PP", "PRINT", "RETURN",
  "STATIC", "STR", "VOID", "WHILE", "TRUE", "FALSE", "COMMENT",
  "INVALID_TOKEN", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UMINUS", "ERROR_PREC", "IFX", "ELSE", "YY_PARSE_classes", "'}'",
  "YY_PARSE_lines", "'\\n'", "'{'", "';'", "'='", "','", "'('", "')'",
  "'['", "']'", "'.'", "'&'", "'|'", "$accept", "classes", "lines",
  "class_def", "$@1", "$@2", "declare", "compound", "$@3", "$@4",
  "id_item", "id_list", "maybe_missing_semi", "variable_decl",
  "function_decl", "init_decl", "arr_or_obj", "spec_type__", "args",
  "tuple", "tuple_items", "generic_id", "type", "type_id", "const_expr",
  "Infixop", "lvalue", "statement", "statement_star", "assign_stmt",
  "simple_call_decl", "expr", "factor", "conditional", "bool_expr", "loop",
  "while_expr__", "ForInitOpt", "for_init_list", "single_for_init",
  "for_expr__", "ForUpdateOpt", "for_update_list", "return", "para_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-268)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-179)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     149,    15,  -268,    30,    91,  -268,    64,  -268,  -268,  -268,
    -268,  -268,  1584,  -268,  1682,  -268,  -268,  1682,  -268,  -268,
    1682,  1704,    33,    77,  2037,   534,     4,  1682,  -268,    77,
     576,   618,   660,   702,   136,  1832,   864,  1704,    67,  -268,
    -268,  1704,  1704,  1704,  1704,  -268,  1704,  1704,  -268,  1704,
    1704,  1709,  1743,  1748,  1770,  1704,  -268,  -268,  -268,  -268,
     798,  2073,   166,  1622,  -268,  2141,  1862,   -11,   -11,  1862,
    2109,   -11,   -11,   366,   164,   408,   164,   450,   102,   492,
     102,   102,  -268,  1704,  -268,  -268,  2023,  2073,    98,    45,
    -268,  -268,   238,  -268,  -268,   238,  -268,  -268,  -268,  -268,
    -268,   107,    40,  -268,  -268,  -268,  -268,   119,   238,    40,
      40,   144,  -268,  1167,    50,    80,   171,   179,     6,   158,
     238,  -268,  -268,   119,  -268,  -268,  -268,   238,     2,   175,
     238,  -268,  -268,  -268,  -268,  -268,   175,   297,   184,  -268,
       6,    97,  -268,  -268,  1704,   199,  -268,  -268,  -268,  -268,
    -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,  -268,
    -268,   178,     2,   175,  -268,  -268,  -268,  1658,   115,    73,
    -268,   297,  -268,  1219,  1507,  -268,  -268,  -268,  -268,    92,
     186,    94,   917,     9,   111,  1682,  1682,   155,   324,    20,
     147,  1682,  1267,  -268,  1315,  -268,     1,   192,  -268,  -268,
     118,  1910,  -268,  -268,  1363,  1411,  -268,   967,  -268,  -268,
    -268,  -268,  -268,    93,  1662,  1798,    57,   248,   143,  1704,
    1017,  -268,  1946,   170,  1807,   175,  1593,  1545,  -268,  -268,
    -268,  1704,   864,   162,  -268,  -268,  1067,  -268,  1117,  -268,
    -268,  -268,   235,   147,   110,     6,   201,   205,  -268,   840,
    -268,  2073,   210,  -268,  1871,  -268,  -268,   755,   223,  1982,
     206,  -268,   175,  -268,  1704,   -42,  1798,  1662,  1267,  -268,
    1459,  -268,   230,  2073,  1704,   233,  -268,   240,  -268,  2073,
     336,  1267,   147,   147,   147,   847,  -268,   231,   242,  -268,
     175,   175,   175,  1704,   864,  -268,   336,  2073,   224,  -268,
    -268
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     7,     0,     0,     4,     0,    10,     1,     6,
       5,     2,     0,    54,     0,   134,   135,     0,   136,   144,
       0,     0,    86,   124,     0,     0,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   139,
     138,     0,     0,     0,     0,   126,     0,     0,   125,     0,
       0,     0,     0,     0,     0,     0,     8,   145,    11,   140,
       0,   179,     0,     0,    56,   116,   118,   121,   120,   119,
     117,   122,   123,     0,   111,     0,   112,     0,   113,     0,
     114,   115,    13,     0,   137,    55,     0,   180,    19,    64,
      61,    60,     0,    59,    58,     0,    62,    12,    16,    15,
      14,     0,    42,    63,    64,    18,    17,     0,    43,    41,
      40,    25,    27,     0,     0,    25,     0,     0,     0,     0,
      43,    33,    29,     0,    31,    57,    32,     0,     0,    44,
       0,    65,    66,    67,    69,    26,    68,    36,     0,    28,
       0,     0,    20,    34,     0,     0,    84,    82,    81,    80,
      83,    85,    77,    76,    71,    72,    73,    74,    75,    78,
      79,     0,     0,    45,    24,    98,    98,     0,    47,     0,
      37,    70,    35,     0,     0,    55,    48,    49,    50,     0,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,    92,    86,   124,    99,    88,
       0,     0,    93,    94,     0,     0,    95,     0,    39,    51,
      52,    53,    38,     0,   161,     0,   133,   133,     0,     0,
       0,   176,     0,     0,     0,   108,   133,     0,   149,   106,
     104,     0,     0,   138,    91,    97,     0,   153,     0,   155,
      23,   170,    54,     0,     0,     0,     0,   162,   163,     0,
     144,   150,     0,    90,     0,   175,   160,     0,     0,     0,
       0,    89,   168,   167,     0,     0,     0,     0,     0,   110,
       0,   101,   137,   165,     0,     0,   164,   147,   154,   166,
     171,     0,     0,     0,     0,     0,   173,     0,   172,   148,
     107,   105,   109,     0,     0,   169,     0,   103,     0,   174,
     102
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -268,  -268,  -268,    74,  -268,  -268,   207,    -8,  -268,  -268,
     173,   187,  -268,  -268,  -268,  -268,  -268,   218,   188,  -268,
    -268,    81,   -88,  -268,   137,  -268,    42,  -186,   141,  -268,
    -267,    -6,    54,  -268,  -208,  -268,  -268,  -268,  -268,    46,
    -268,  -268,  -268,  -268,  -231
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     4,     6,    98,    26,    82,   194,   195,   165,   166,
     112,   113,   124,    99,   100,   135,   170,   101,   117,   179,
     180,    22,   102,   103,   137,   161,    23,   198,   173,   199,
     200,   201,    25,   202,   252,   203,   204,   246,   247,   248,
     205,   287,   288,   206,    62
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      24,   260,  -133,   141,   109,    45,   228,   110,   274,    13,
     213,    48,   144,   286,    38,    35,   258,   229,   237,   239,
     118,   223,     3,   230,    51,    52,    53,    54,    55,   299,
      61,    63,   118,     7,  -133,    65,    66,    67,    68,   140,
      69,    70,   145,    71,    72,    74,    76,    78,    80,    81,
     142,   231,    58,   232,    29,    37,    29,    38,   275,    29,
     114,   214,    29,   298,    11,    12,    30,    13,    31,    29,
      64,    32,   224,   -86,    33,     5,    29,    87,    10,   -86,
      14,    30,   277,    15,    16,    36,    17,    37,    30,    38,
      18,     8,   181,    39,   114,   289,    19,   108,     3,    40,
      20,   104,    29,    90,    91,   125,  -107,    92,    93,    36,
     111,    37,    94,    38,    30,    29,    21,    29,    45,    29,
     143,    29,   115,    95,    48,    96,   245,    30,   125,    30,
     119,    30,   263,    30,   176,   177,     9,    27,   167,    13,
    -131,   178,   164,   105,  -131,   208,   241,   106,  -131,   212,
      13,  -131,    14,  -131,   172,    15,    16,  -131,    17,    39,
     264,    13,    18,   215,   144,    40,    38,   234,    19,  -131,
    -131,  -131,    20,  -131,  -131,  -131,   130,   131,   132,   245,
      45,    13,   222,  -131,   133,  -131,    48,  -131,    21,  -131,
     134,  -131,   253,     1,   119,     2,   120,   131,   132,   129,
     136,    53,    54,    55,   133,   209,   210,   219,    39,   251,
     134,   261,   211,   254,   233,   197,   197,    83,   251,    84,
     126,   163,   123,   256,    29,   259,    61,    29,   218,   144,
     127,    38,   128,    29,   197,   127,    30,   162,   -64,    31,
      32,   104,   136,    90,    91,    33,   197,   197,    93,    29,
     266,   168,    94,   169,   196,   196,   267,    83,   273,   272,
     251,    30,    29,   268,   -86,    96,   216,   217,   279,    29,
     -86,   225,   226,   196,    30,    83,   270,   300,    29,  -102,
      29,    30,   280,   281,   295,   196,   196,   297,    61,    86,
      30,    29,    30,   296,   116,   244,   139,   -86,   171,    29,
      36,   146,    37,    30,    38,   147,   107,   174,   138,   148,
     197,    30,   149,   276,   150,     0,     0,     0,   151,     0,
       0,     0,     0,   197,   262,   220,   265,    13,     0,     0,
     152,   153,   154,   155,   156,   157,   158,     0,     0,    13,
      14,     0,     0,    15,    16,     0,    17,     0,   244,   196,
      18,     0,   282,     0,   159,   160,    19,     0,   283,   187,
      20,   285,   196,   290,   291,   292,     0,    27,     0,    13,
    -127,   190,   284,   221,  -127,     0,    21,   285,  -127,     0,
       0,  -127,    14,  -127,     0,    15,    16,  -127,    17,     0,
       0,     0,    18,     0,     0,     0,     0,     0,    19,  -127,
    -127,  -127,    20,  -127,  -127,  -127,     0,     0,     0,    27,
       0,    13,  -128,  -127,     0,  -127,  -128,  -127,    21,  -127,
    -128,  -127,     0,  -128,    14,  -128,     0,    15,    16,  -128,
      17,     0,     0,     0,    18,     0,     0,     0,     0,     0,
      19,  -128,  -128,  -128,    20,  -128,  -128,  -128,     0,     0,
       0,    27,     0,    13,  -129,  -128,     0,  -128,  -129,  -128,
      21,  -128,  -129,  -128,     0,  -129,    14,  -129,     0,    15,
      16,  -129,    17,     0,     0,     0,    18,     0,     0,     0,
       0,     0,    19,  -129,  -129,  -129,    20,  -129,  -129,  -129,
       0,     0,     0,    27,     0,    13,  -130,  -129,     0,  -129,
    -130,  -129,    21,  -129,  -130,  -129,     0,  -130,    14,  -130,
       0,    15,    16,  -130,    17,     0,     0,     0,    18,     0,
       0,     0,     0,     0,    19,  -130,  -130,  -130,    20,  -130,
    -130,  -130,     0,     0,     0,    57,     0,     0,  -132,  -130,
       0,  -130,  -132,  -130,    21,  -130,  -132,  -130,     0,  -132,
    -132,  -132,     0,     0,     0,  -132,  -132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,     0,     0,     0,    57,     0,     0,
    -146,  -132,     0,  -132,  -146,  -132,     0,  -132,  -146,  -132,
       0,  -146,  -146,  -146,     0,     0,     0,  -146,  -146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,     0,     0,     0,    57,
       0,     0,  -143,  -146,     0,  -146,  -143,  -146,     0,  -146,
    -143,  -146,     0,  -143,  -143,  -143,     0,     0,     0,  -143,
    -143,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -143,  -143,  -143,  -143,  -143,  -143,  -143,     0,     0,
       0,    57,     0,     0,  -142,  -143,     0,  -143,  -142,  -143,
       0,  -143,  -142,  -143,     0,  -142,  -142,  -142,     0,     0,
       0,  -142,  -142,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
       0,     0,     0,    57,     0,     0,  -141,  -142,     0,  -142,
    -141,  -142,     0,  -142,  -141,  -142,     0,  -141,  -141,  -141,
       0,     0,     0,  -141,  -141,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,     0,     0,     0,     0,     0,     0,     0,  -141,
       0,  -141,     0,  -141,     0,  -141,    27,  -141,    13,  -131,
    -159,  -159,  -159,  -131,  -159,  -159,  -159,  -131,  -159,  -159,
    -131,    14,  -131,     0,    15,    16,  -131,    17,  -159,  -159,
    -159,    18,  -159,  -159,     0,     0,     0,    19,  -131,  -131,
    -131,    20,  -131,  -131,  -131,     0,     0,     0,  -159,    27,
    -159,    13,  -131,  -159,     0,     0,  -131,    21,  -131,     0,
    -131,     0,     0,  -131,    14,  -131,     0,    15,    16,  -131,
      17,     0,     0,     0,    18,     0,     0,     0,     0,     0,
      19,  -131,  -131,  -131,    20,  -131,  -131,  -131,     0,     0,
       0,    27,     0,    13,  -131,     0,     0,     0,  -131,  -131,
      21,  -131,  -131,     0,     0,  -131,    14,  -131,     0,    15,
      16,  -131,    17,   229,     0,    60,    18,    13,     0,   230,
       0,     0,    19,  -131,  -131,  -131,    20,  -131,  -131,  -131,
      14,     0,     0,    15,    16,     0,    17,     0,     0,  -131,
      18,     0,    21,  -131,     0,     0,    19,   293,     0,   294,
      20,   144,     0,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -178,    21,  -178,    27,     0,
      13,  -131,  -100,  -100,  -100,  -131,  -100,  -100,  -100,  -131,
    -100,  -100,  -131,    14,  -131,     0,    15,    16,  -131,    17,
    -100,  -100,  -100,    18,  -100,  -100,     0,     0,     0,    19,
    -131,  -131,  -100,    20,  -131,  -131,  -131,     0,     0,     0,
    -100,     0,   164,     0,     0,  -100,  -131,     0,    27,    21,
      13,  -131,  -100,  -100,  -100,  -131,  -100,  -100,  -100,  -131,
    -100,  -100,  -131,    14,  -131,     0,    15,    16,  -131,    17,
    -100,  -100,  -100,    18,  -100,  -100,     0,     0,     0,    19,
    -131,  -131,  -100,    20,  -131,  -131,  -131,     0,     0,     0,
    -100,     0,   240,     0,     0,  -100,  -131,     0,    27,    21,
      13,  -131,  -177,  -177,  -177,  -131,  -177,  -177,  -177,  -131,
    -177,  -177,  -131,    14,  -131,     0,    15,    16,  -131,    17,
    -177,  -177,  -177,    18,  -177,  -177,     0,     0,     0,    19,
    -131,  -131,  -131,    20,  -131,  -131,  -131,     0,     0,     0,
    -177,     0,  -177,     0,     0,  -177,  -131,     0,    27,    21,
      13,  -131,  -156,  -156,  -156,  -131,  -156,  -156,  -156,  -131,
    -156,  -156,  -131,    14,  -131,     0,    15,    16,  -131,    17,
    -156,  -156,  -156,    18,  -156,  -156,     0,     0,     0,    19,
    -131,  -131,  -131,    20,  -131,  -131,  -131,     0,     0,     0,
    -156,     0,   164,     0,     0,  -156,  -131,     0,    27,    21,
      13,  -131,  -157,  -157,  -157,  -131,  -157,  -157,  -157,  -131,
    -157,  -157,  -131,    14,  -131,     0,    15,    16,  -131,    17,
    -157,  -157,  -157,    18,  -157,  -157,     0,     0,     0,    19,
    -131,  -131,  -131,    20,  -131,  -131,  -131,     0,     0,     0,
    -157,     0,   164,     0,     0,  -157,  -131,     0,   121,    21,
     -30,     0,   -30,   -30,   -30,     0,   -30,   -30,   -30,     0,
     -30,   -30,     0,   -30,     0,     0,   -30,   -30,     0,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,     0,     0,     0,   -30,
       0,     0,   -30,   -30,     0,     0,     0,     0,     0,     0,
     -30,     0,   -30,     0,     0,   -30,   122,     0,   123,   -30,
     182,     0,    13,     0,   -13,   -13,   -13,     0,   -13,   -13,
     183,     0,   184,   -13,     0,   185,     0,     0,    15,    16,
       0,   186,   187,   188,   -13,    18,   -13,   189,     0,     0,
       0,    19,     0,     0,   190,   191,     0,     0,     0,     0,
       0,     0,   192,     0,   193,     0,     0,   142,   227,     0,
      13,    21,   -13,   -13,   -13,     0,   -13,   -13,   183,     0,
     184,   -13,     0,   185,     0,     0,    15,    16,     0,   186,
     187,   188,   -13,    18,   -13,   189,     0,     0,     0,    19,
       0,     0,   190,   191,     0,     0,     0,     0,     0,     0,
     192,     0,   -13,     0,     0,   142,    88,     0,    89,    21,
      90,    91,     3,     0,    92,    93,   -96,     0,   -96,    94,
       0,   -96,     0,     0,   -96,   -96,     0,   -96,   -96,   -96,
      95,   -96,    96,   -96,     0,     0,     0,   -96,     0,     0,
     -96,   -96,     0,     0,     0,     0,     0,     0,   -96,     0,
     -96,     0,     0,   -96,   236,     0,    13,   -96,   -13,   -13,
     -13,     0,   -13,   -13,   183,     0,   184,   -13,     0,   185,
       0,     0,    15,    16,     0,   186,   187,   188,   -13,    18,
     -13,   189,     0,     0,     0,    19,     0,     0,   190,   191,
       0,     0,     0,     0,     0,     0,   192,     0,   -13,     0,
       0,   142,   238,     0,    13,    21,   -13,   -13,   -13,     0,
     -13,   -13,   183,     0,   184,   -13,     0,   185,     0,     0,
      15,    16,     0,   186,   187,   188,   -13,    18,   -13,   189,
       0,     0,     0,    19,     0,     0,   190,   191,     0,     0,
       0,     0,     0,     0,   192,     0,   -13,     0,     0,   142,
     278,     0,  -158,    21,  -158,  -158,  -158,     0,  -158,  -158,
    -158,     0,  -158,  -158,     0,  -158,     0,     0,  -158,  -158,
       0,  -158,  -158,  -158,  -158,  -158,  -158,  -158,     0,     0,
       0,  -158,     0,     0,  -158,  -158,     0,     0,     0,     0,
       0,     0,  -158,     0,  -158,     0,     0,  -158,   207,     0,
      13,  -158,   -13,   -13,   -13,     0,   -13,   -13,   183,     0,
     184,   -13,     0,   185,     0,     0,    15,    16,     0,   186,
     187,   188,   -13,    18,   -13,   189,     0,     0,     0,    19,
       0,     0,   190,   191,     0,     0,    27,     0,    13,  -131,
     192,     0,     0,  -131,     0,   142,     0,  -131,     0,    21,
    -131,    14,  -131,     0,    15,    16,  -131,    17,     0,     0,
       0,    18,     0,     0,     0,     0,     0,    19,  -131,  -131,
    -131,    20,  -131,  -131,  -131,    27,     0,    13,  -131,     0,
     164,     0,  -131,     0,  -131,     0,  -131,    21,     0,  -131,
      14,  -131,     0,    15,    16,  -131,    17,     0,     0,   -86,
      18,     0,     0,     0,     0,   -86,    19,  -131,  -131,  -131,
      20,  -131,  -131,  -131,     0,     0,    41,     0,     0,     0,
      42,    28,     0,     0,    43,     0,    21,    44,    45,    46,
       0,     0,  -109,    47,    48,    36,     0,    37,     0,    38,
       0,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,    55,    41,     0,     0,   242,    42,    90,    91,     0,
      43,     0,    93,    44,    45,    46,    94,    85,     0,    47,
      48,     0,     0,    27,   243,    13,     0,     0,     0,    96,
       0,    49,    50,    51,    52,    53,    54,    55,    14,     0,
       0,    15,    16,     0,    17,    34,     0,    13,    18,     0,
      73,     0,    13,   175,    19,     0,     0,     0,    20,     0,
      14,     0,     0,    15,    16,    14,    17,     0,    15,    16,
      18,    17,     0,     0,    21,    18,    19,     0,     0,     0,
      20,    19,     0,     0,    75,    20,    13,     0,     0,    77,
       0,    13,     0,     0,     0,     0,    21,     0,     0,    14,
       0,    21,    15,    16,    14,    17,     0,    15,    16,    18,
      17,    79,     0,    13,    18,    19,     0,     0,     0,    20,
      19,     0,     0,     0,    20,     0,    14,     0,     0,    15,
      16,     0,    17,     0,     0,    21,    18,     0,     0,   249,
      21,    13,    19,     0,     0,     0,    20,     0,   257,     0,
      13,     0,     0,     0,    14,     0,     0,    15,    16,     0,
      17,     0,    21,    14,    18,     0,    15,    16,     0,    17,
     250,     0,     0,    18,    20,     0,    41,     0,     0,   250,
      42,     0,     0,    20,    43,     0,     0,    44,    45,    46,
      21,     0,     0,    47,    48,     0,     0,     0,     0,    21,
       0,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,    55,     0,     0,    43,    41,     0,    44,    45,    42,
       0,     0,     0,    43,    48,    59,    44,    45,    46,     0,
       0,     0,    47,    48,     0,    49,    50,    51,    52,    53,
      54,    55,     0,     0,    49,    50,    51,    52,    53,    54,
      55,     0,     0,     0,    41,     0,     0,     0,    42,     0,
       0,     0,    43,     0,   269,    44,    45,    46,     0,     0,
       0,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    50,    51,    52,    53,    54,    55,
      41,     0,     0,     0,    42,     0,     0,     0,    43,   235,
       0,    44,    45,    46,     0,     0,     0,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      50,    51,    52,    53,    54,    55,    41,     0,     0,     0,
      42,     0,     0,     0,    43,   255,     0,    44,    45,    46,
       0,     0,     0,    47,    48,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,    55,     0,     0,    88,     0,    89,     0,    90,    91,
       3,   271,    92,    93,     0,     0,     0,    94,     0,     0,
       0,    41,     0,     0,     0,    42,     0,     0,    95,    43,
      96,     0,    44,    45,    46,     0,     0,     0,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,    97,     0,
      49,    50,    51,    52,    53,    54,    55,    41,     0,     0,
       0,    42,     0,     0,    56,    43,     0,     0,    44,    45,
      46,     0,     0,     0,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      53,    54,    55,    41,     0,     0,     0,    42,     0,     0,
       0,    43,     0,     0,    44,    45,    46,     0,     0,     0,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,    53,    54,    55,    42,
       0,     0,     0,    43,     0,     0,    44,    45,    46,     0,
       0,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,    53,    54,
      55
};

static const yytype_int16 yycheck[] =
{
       6,   232,     1,     1,    92,    16,   192,    95,    50,     3,
       1,    22,    54,   280,    56,    21,   224,    16,   204,   205,
     108,     1,     7,    22,    35,    36,    37,    38,    39,   296,
      36,    37,   120,     3,     1,    41,    42,    43,    44,   127,
      46,    47,   130,    49,    50,    51,    52,    53,    54,    55,
      48,    50,    48,    52,    12,    54,    14,    56,   266,    17,
      54,    52,    20,   294,     0,     1,    12,     3,    14,    27,
       3,    17,    52,    16,    20,     1,    34,    83,     4,    22,
      16,    27,   268,    19,    20,    52,    22,    54,    34,    56,
      26,     0,    19,    16,    54,   281,    32,    52,     7,    22,
      36,     3,    60,     5,     6,    55,    49,     9,    10,    52,
       3,    54,    14,    56,    60,    73,    52,    75,    16,    77,
     128,    79,     3,    25,    22,    27,   214,    73,    55,    75,
      50,    77,    22,    79,    19,    20,    45,     1,   144,     3,
       4,    26,    45,    45,     8,    53,    53,    49,    12,    55,
       3,    15,    16,    17,   162,    19,    20,    21,    22,    16,
      50,     3,    26,    52,    54,    22,    56,    49,    32,    33,
      34,    35,    36,    37,    38,    39,    18,    19,    20,   267,
      16,     3,   188,    47,    26,    49,    22,    51,    52,    53,
      32,    55,    49,    44,    50,    46,    52,    19,    20,   118,
     119,    37,    38,    39,    26,    19,    20,    52,    16,   215,
      32,    49,    26,   219,    22,   173,   174,    51,   224,    53,
      49,   140,    51,    53,   182,   231,   232,   185,   186,    54,
      51,    56,    53,   191,   192,    51,   182,    53,     3,   185,
     186,     3,   161,     5,     6,   191,   204,   205,    10,   207,
      49,    52,    14,    54,   173,   174,    51,    51,   264,    53,
     266,   207,   220,    53,    16,    27,   185,   186,   274,   227,
      22,   190,   191,   192,   220,    51,    53,    53,   236,    49,
     238,   227,    49,    43,    53,   204,   205,   293,   294,    82,
     236,   249,   238,    51,   107,   214,   123,    49,   161,   257,
      52,     4,    54,   249,    56,     8,    88,   166,   120,    12,
     268,   257,    15,   267,    17,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,   281,   243,     1,   245,     3,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,     3,
      16,    -1,    -1,    19,    20,    -1,    22,    -1,   267,   268,
      26,    -1,    16,    -1,    57,    58,    32,    -1,    22,    23,
      36,   280,   281,   282,   283,   284,    -1,     1,    -1,     3,
       4,    35,    36,    49,     8,    -1,    52,   296,    12,    -1,
      -1,    15,    16,    17,    -1,    19,    20,    21,    22,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,     1,
      -1,     3,     4,    47,    -1,    49,     8,    51,    52,    53,
      12,    55,    -1,    15,    16,    17,    -1,    19,    20,    21,
      22,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,     1,    -1,     3,     4,    47,    -1,    49,     8,    51,
      52,    53,    12,    55,    -1,    15,    16,    17,    -1,    19,
      20,    21,    22,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,     1,    -1,     3,     4,    47,    -1,    49,
       8,    51,    52,    53,    12,    55,    -1,    15,    16,    17,
      -1,    19,    20,    21,    22,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,     1,    -1,    -1,     4,    47,
      -1,    49,     8,    51,    52,    53,    12,    55,    -1,    15,
      16,    17,    -1,    -1,    -1,    21,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,     1,    -1,    -1,
       4,    47,    -1,    49,     8,    51,    -1,    53,    12,    55,
      -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,     1,
      -1,    -1,     4,    47,    -1,    49,     8,    51,    -1,    53,
      12,    55,    -1,    15,    16,    17,    -1,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,     1,    -1,    -1,     4,    47,    -1,    49,     8,    51,
      -1,    53,    12,    55,    -1,    15,    16,    17,    -1,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,     1,    -1,    -1,     4,    47,    -1,    49,
       8,    51,    -1,    53,    12,    55,    -1,    15,    16,    17,
      -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      -1,    49,    -1,    51,    -1,    53,     1,    55,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    43,     1,
      45,     3,     4,    48,    -1,    -1,     8,    52,    53,    -1,
      12,    -1,    -1,    15,    16,    17,    -1,    19,    20,    21,
      22,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,     1,    -1,     3,     4,    -1,    -1,    -1,     8,    51,
      52,    53,    12,    -1,    -1,    15,    16,    17,    -1,    19,
      20,    21,    22,    16,    -1,     1,    26,     3,    -1,    22,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      16,    -1,    -1,    19,    20,    -1,    22,    -1,    -1,    49,
      26,    -1,    52,    53,    -1,    -1,    32,    50,    -1,    52,
      36,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    48,    49,    -1,     1,    52,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    48,    49,    -1,     1,    52,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    48,    49,    -1,     1,    52,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    48,    49,    -1,     1,    52,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    48,    49,    -1,     1,    52,
       3,    -1,     5,     6,     7,    -1,     9,    10,    11,    -1,
      13,    14,    -1,    16,    -1,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    48,    49,    -1,    51,    52,
       1,    -1,     3,    -1,     5,     6,     7,    -1,     9,    10,
      11,    -1,    13,    14,    -1,    16,    -1,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    -1,    -1,    48,     1,    -1,
       3,    52,     5,     6,     7,    -1,     9,    10,    11,    -1,
      13,    14,    -1,    16,    -1,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    48,     1,    -1,     3,    52,
       5,     6,     7,    -1,     9,    10,    11,    -1,    13,    14,
      -1,    16,    -1,    -1,    19,    20,    -1,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      45,    -1,    -1,    48,     1,    -1,     3,    52,     5,     6,
       7,    -1,     9,    10,    11,    -1,    13,    14,    -1,    16,
      -1,    -1,    19,    20,    -1,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    45,    -1,
      -1,    48,     1,    -1,     3,    52,     5,     6,     7,    -1,
       9,    10,    11,    -1,    13,    14,    -1,    16,    -1,    -1,
      19,    20,    -1,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    45,    -1,    -1,    48,
       1,    -1,     3,    52,     5,     6,     7,    -1,     9,    10,
      11,    -1,    13,    14,    -1,    16,    -1,    -1,    19,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    -1,    -1,    48,     1,    -1,
       3,    52,     5,     6,     7,    -1,     9,    10,    11,    -1,
      13,    14,    -1,    16,    -1,    -1,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    35,    36,    -1,    -1,     1,    -1,     3,     4,
      43,    -1,    -1,     8,    -1,    48,    -1,    12,    -1,    52,
      15,    16,    17,    -1,    19,    20,    21,    22,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,     1,    -1,     3,     4,    -1,
      45,    -1,     8,    -1,    49,    -1,    12,    52,    -1,    15,
      16,    17,    -1,    19,    20,    21,    22,    -1,    -1,    16,
      26,    -1,    -1,    -1,    -1,    22,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,     4,    -1,    -1,    -1,
       8,    47,    -1,    -1,    12,    -1,    52,    15,    16,    17,
      -1,    -1,    49,    21,    22,    52,    -1,    54,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,     4,    -1,    -1,     3,     8,     5,     6,    -1,
      12,    -1,    10,    15,    16,    17,    14,    55,    -1,    21,
      22,    -1,    -1,     1,    22,     3,    -1,    -1,    -1,    27,
      -1,    33,    34,    35,    36,    37,    38,    39,    16,    -1,
      -1,    19,    20,    -1,    22,     1,    -1,     3,    26,    -1,
       1,    -1,     3,    55,    32,    -1,    -1,    -1,    36,    -1,
      16,    -1,    -1,    19,    20,    16,    22,    -1,    19,    20,
      26,    22,    -1,    -1,    52,    26,    32,    -1,    -1,    -1,
      36,    32,    -1,    -1,     1,    36,     3,    -1,    -1,     1,
      -1,     3,    -1,    -1,    -1,    -1,    52,    -1,    -1,    16,
      -1,    52,    19,    20,    16,    22,    -1,    19,    20,    26,
      22,     1,    -1,     3,    26,    32,    -1,    -1,    -1,    36,
      32,    -1,    -1,    -1,    36,    -1,    16,    -1,    -1,    19,
      20,    -1,    22,    -1,    -1,    52,    26,    -1,    -1,     1,
      52,     3,    32,    -1,    -1,    -1,    36,    -1,     1,    -1,
       3,    -1,    -1,    -1,    16,    -1,    -1,    19,    20,    -1,
      22,    -1,    52,    16,    26,    -1,    19,    20,    -1,    22,
      32,    -1,    -1,    26,    36,    -1,     4,    -1,    -1,    32,
       8,    -1,    -1,    36,    12,    -1,    -1,    15,    16,    17,
      52,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    12,     4,    -1,    15,    16,     8,
      -1,    -1,    -1,    12,    22,    53,    15,    16,    17,    -1,
      -1,    -1,    21,    22,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,     4,    -1,    -1,    -1,     8,    -1,
      -1,    -1,    12,    -1,    53,    15,    16,    17,    -1,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
       4,    -1,    -1,    -1,     8,    -1,    -1,    -1,    12,    49,
      -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      34,    35,    36,    37,    38,    39,     4,    -1,    -1,    -1,
       8,    -1,    -1,    -1,    12,    49,    -1,    15,    16,    17,
      -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,     1,    -1,     3,    -1,     5,     6,
       7,    49,     9,    10,    -1,    -1,    -1,    14,    -1,    -1,
      -1,     4,    -1,    -1,    -1,     8,    -1,    -1,    25,    12,
      27,    -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      33,    34,    35,    36,    37,    38,    39,     4,    -1,    -1,
      -1,     8,    -1,    -1,    47,    12,    -1,    -1,    15,    16,
      17,    -1,    -1,    -1,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,     4,    -1,    -1,    -1,     8,    -1,    -1,
      -1,    12,    -1,    -1,    15,    16,    17,    -1,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    37,    38,    39,     8,
      -1,    -1,    -1,    12,    -1,    -1,    15,    16,    17,    -1,
      -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    44,    46,     7,    60,    62,    61,     3,     0,    45,
      62,     0,     1,     3,    16,    19,    20,    22,    26,    32,
      36,    52,    80,    85,    90,    91,    63,     1,    47,    85,
      91,    91,    91,    91,     1,    90,    52,    54,    56,    16,
      22,     4,     8,    12,    15,    16,    17,    21,    22,    33,
      34,    35,    36,    37,    38,    39,    47,     1,    48,    53,
       1,    90,   103,    90,     3,    90,    90,    90,    90,    90,
      90,    90,    90,     1,    90,     1,    90,     1,    90,     1,
      90,    90,    64,    51,    53,    55,    65,    90,     1,     3,
       5,     6,     9,    10,    14,    25,    27,    45,    62,    72,
      73,    76,    81,    82,     3,    45,    49,    76,    52,    81,
      81,     3,    69,    70,    54,     3,    70,    77,    81,    50,
      52,     1,    49,    51,    71,    55,    49,    51,    53,    80,
      18,    19,    20,    26,    32,    74,    80,    83,    77,    69,
      81,     1,    48,    66,    54,    81,     4,     8,    12,    15,
      17,    21,    33,    34,    35,    36,    37,    38,    39,    57,
      58,    84,    53,    80,    45,    67,    68,    90,    52,    54,
      75,    83,    66,    87,    87,    55,    19,    20,    26,    78,
      79,    19,     1,    11,    13,    16,    22,    23,    24,    28,
      35,    36,    43,    45,    65,    66,    80,    85,    86,    88,
      89,    90,    92,    94,    95,    99,   102,     1,    53,    19,
      20,    26,    55,     1,    52,    52,    80,    80,    85,    52,
       1,    49,    90,     1,    52,    80,    80,     1,    86,    16,
      22,    50,    52,    22,    49,    49,     1,    86,     1,    86,
      45,    53,     3,    22,    80,    81,    96,    97,    98,     1,
      32,    90,    93,    49,    90,    49,    53,     1,    93,    90,
     103,    49,    80,    22,    50,    80,    49,    51,    53,    53,
      53,    49,    53,    90,    50,    93,    98,    86,     1,    90,
      49,    43,    16,    22,    36,    80,    89,   100,   101,    86,
      80,    80,    80,    50,    52,    53,    51,    90,   103,    89,
      53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    59,    60,    60,    60,    60,    61,    61,    61,
      63,    64,    62,    65,    65,    65,    65,    65,    65,    65,
      67,    66,    68,    66,    66,    69,    69,    70,    70,    71,
      71,    72,    72,    72,    73,    73,    74,    74,    75,    75,
      76,    76,    76,    77,    77,    77,    78,    78,    79,    79,
      79,    79,    79,    79,    80,    80,    80,    81,    81,    81,
      81,    81,    81,    81,    82,    83,    83,    83,    83,    83,
      83,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    85,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    87,    87,
      87,    88,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    92,    92,
      93,    93,    93,    94,    94,    94,    94,    94,    95,    95,
      95,    96,    96,    97,    97,    98,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   102,   103,   103,
     103,   103
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     3,     3,     0,     1,     2,     2,     0,     3,     3,
       0,     0,     7,     0,     2,     2,     2,     3,     3,     2,
       0,     4,     0,     5,     2,     1,     3,     1,     3,     1,
       0,     3,     4,     3,     5,     6,     1,     3,     3,     3,
       2,     2,     1,     0,     2,     4,     1,     0,     1,     1,
       1,     2,     2,     2,     1,     4,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     3,
       3,     2,     1,     1,     1,     1,     1,     2,     0,     2,
       2,     4,     4,     3,     2,     2,     2,     2,     2,     2,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     2,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     4,     2,     2,
       3,     2,     2,     2,     1,     2,     2,     5,     7,     2,
       1,     1,     1,     2,     5,     2,     2,     2,     4,     3,
       3,     0,     1,     1,     3,     3,     4,     2,     2,     8,
       3,     0,     1,     1,     3,     3,     2,     2,     0,     1,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}



/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

// Extract data from the parser.
typedef struct
{
  YYSTYPE yyvalue;
  int yynerrs;
} yy_parse_impl_t;

// Run a full parse, using YYCHAR as switching token.
static int
yy_parse_impl (int yychar, yy_parse_impl_t *yyimpl);


yyparse_classes_t
yyparse_classes (void)
{
  yyparse_classes_t yyres;
  yy_parse_impl_t yyimpl;
  yyres.yystatus = yy_parse_impl (YY_PARSE_classes, &yyimpl);
  yyres.yynerrs = yyimpl.yynerrs;
  return yyres;
}

yyparse_lines_t
yyparse_lines (void)
{
  yyparse_lines_t yyres;
  yy_parse_impl_t yyimpl;
  yyres.yystatus = yy_parse_impl (YY_PARSE_lines, &yyimpl);
  yyres.yynerrs = yyimpl.yynerrs;
  return yyres;
}


int
yyparse (void)
{
  return yy_parse_impl (YY_PARSE_classes, YY_NULLPTR);
}

static int
yy_parse_impl (int yychar, yy_parse_impl_t *yyimpl)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));


  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */



  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 1: /* $accept: YY_PARSE_classes classes $end  */
#line 175 "B113040052.y"
        {  YYACCEPT; }
#line 2035 "B113040052.tab.c"
    break;

  case 2: /* $accept: YY_PARSE_lines lines $end  */
#line 175 "B113040052.y"
        {  YYACCEPT; }
#line 2041 "B113040052.tab.c"
    break;

  case 6: /* classes: classes '}'  */
#line 179 "B113040052.y"
              {
    fprintf(stderr, "Line %d, char: %d, unmatched '}'\n",
    last_token_line, last_token_col);
    error_reported = yylineno;
    tokens[0] = '\0';
    yyclearin;
    yyerrok;
}
#line 2054 "B113040052.tab.c"
    break;

  case 8: /* lines: lines expr '\n'  */
#line 191 "B113040052.y"
                  {
    if (!error_reported) {
        flushLine();  // 印出對應這一行的內容（如需要）
    }
    error_reported = 0; // reset 錯誤狀態
}
#line 2065 "B113040052.tab.c"
    break;

  case 9: /* lines: lines error '\n'  */
#line 197 "B113040052.y"
                   {
    if (!error_reported) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        error_reported = yylineno;
    }
    yyerrok;
}
#line 2077 "B113040052.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 206 "B113040052.y"
                    {
    my_insert((yyvsp[0].sval), TYPE_KIND);
}
#line 2085 "B113040052.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 208 "B113040052.y"
      { push(); }
#line 2091 "B113040052.tab.c"
    break;

  case 12: /* class_def: CLASS ID $@1 '{' $@2 declare '}'  */
#line 208 "B113040052.y"
                              { pop(); }
#line 2097 "B113040052.tab.c"
    break;

  case 20: /* $@3: %empty  */
#line 221 "B113040052.y"
      { PUSH(); }
#line 2103 "B113040052.tab.c"
    break;

  case 21: /* compound: '{' $@3 statement_star '}'  */
#line 223 "B113040052.y"
    { POP(); }
#line 2109 "B113040052.tab.c"
    break;

  case 22: /* $@4: %empty  */
#line 224 "B113040052.y"
      { PUSH(); }
#line 2115 "B113040052.tab.c"
    break;

  case 23: /* compound: '{' $@4 statement_star error '}'  */
#line 226 "B113040052.y"
          {
    fprintf(stderr, "Line %d, char: %d, compound block had error before closing brace\n",
    (yylsp[-1]).first_line, (yylsp[-1]).first_column);
    POP();
    tokens[0] = '\0';
    error_reported = (yylsp[-1]).first_line;
    yyclearin; yyerrok;
}
#line 2128 "B113040052.tab.c"
    break;

  case 24: /* compound: error '}'  */
#line 234 "B113040052.y"
            {
    // 這裡通常是單一 else block 出錯所致，避免多報錯
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, malformed compound block\n", (yylsp[0]).first_line, (yylsp[0]).first_column);
        error_reported = (yylsp[0]).first_line;
    }
    POP();
    yyclearin; yyerrok;
}
#line 2142 "B113040052.tab.c"
    break;

  case 25: /* id_item: ID  */
#line 252 "B113040052.y"
{
    chk_dupid_id((yyvsp[0].sval));
    last_token_line = (yylsp[0]).last_line;
    last_token_col  = (yylsp[0]).last_column;
}
#line 2152 "B113040052.tab.c"
    break;

  case 26: /* id_item: ID '=' init_decl  */
#line 258 "B113040052.y"
{
    chk_dupid_id((yyvsp[-2].sval));
    last_token_line = (yyvsp[0].pos).line;
    last_token_col  = (yyvsp[0].pos).col;
}
#line 2162 "B113040052.tab.c"
    break;

  case 30: /* maybe_missing_semi: %empty  */
#line 272 "B113040052.y"
  {
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
#line 2187 "B113040052.tab.c"
    break;

  case 31: /* variable_decl: spec_type__ id_list maybe_missing_semi  */
#line 295 "B113040052.y"
                                         {
    if (error_reported == yylineno) {
        // 我們剛剛在 maybe_missing_semi 報錯，現在來判斷是否要改回報 Line 10
        if (tokens[0] != '\0' && strcmp(tokens, "int") == 0 && last_token_line < yylineno) {
            // 下一行是新的宣告，而且上一個 token 是 NEW Point() 結尾
            // 重新印一次錯誤，把位置改回上一行
            fprintf(stderr, "Line %d, char: %d, statement without semicolon\n",
            last_token_line, last_token_col + 1);
            error_reported = last_token_line;
        }
    }
}
#line 2204 "B113040052.tab.c"
    break;

  case 32: /* variable_decl: error spec_type__ id_list ';'  */
#line 308 "B113040052.y"
                                {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, recovered declaration\n", yylineno, token_col);
    }
    skip_next_decl_typecheck = 1;
    yyerrok;
}
#line 2216 "B113040052.tab.c"
    break;

  case 33: /* variable_decl: spec_type__ id_list error  */
#line 316 "B113040052.y"
                            {
    if ((yylsp[-1]).last_line < (yylsp[0]).first_line) {
        // 判斷是否前一行已報過錯（常見於沒加分號）
        fprintf(stderr,
        "Line %d, char: %d, statement without semicolon\n",
        (yylsp[-1]).last_line, (yylsp[-1]).last_column + 1);
    } else if (error_reported != (yylsp[0]).first_line) {
        // ✅ 只有當這行尚未報錯時才顯示 syntax error
        fprintf(stderr,
        "Line %d, char: %d, syntax error near '%s'\n",
        (yylsp[0]).first_line, (yylsp[0]).first_column, tokens);
        error_reported = (yylsp[0]).first_line;
    }

    skip_next_decl_typecheck = 1;
    yyerrok;
}
#line 2238 "B113040052.tab.c"
    break;

  case 34: /* function_decl: ID '(' args ')' compound  */
#line 336 "B113040052.y"
                         {
    if (my_insert((yyvsp[-4].sval), FUNC_KIND) < 0)
    fprintf(stderr, "Line %d, char: %d, duplicate identifier '%s'\n", yylineno, token_col, (yyvsp[-4].sval));
}
#line 2247 "B113040052.tab.c"
    break;

  case 35: /* function_decl: spec_type__ ID '(' args ')' compound  */
#line 340 "B113040052.y"
                                       {
    if (my_insert((yyvsp[-4].sval), FUNC_KIND) < 0)
    fprintf(stderr, "Line %d, char: %d, duplicate identifier '%s'\n", yylineno, token_col, (yyvsp[-4].sval));
}
#line 2256 "B113040052.tab.c"
    break;

  case 36: /* init_decl: const_expr  */
#line 365 "B113040052.y"
             {
    (yyval.pos).line = yylineno;
    (yyval.pos).col  = token_col + token_width;

    last_token_line = (yyval.pos).line;
    last_token_col  = (yyval.pos).col;

    // 👇 加入
    last_init_line = (yyval.pos).line;
    last_init_col  = (yyval.pos).col;
}
#line 2272 "B113040052.tab.c"
    break;

  case 37: /* init_decl: NEW type arr_or_obj  */
#line 376 "B113040052.y"
                      {
    (yyval.pos).line = (yylsp[-1]).first_line;
    (yyval.pos).col  = (yylsp[-1]).first_column + 2;

    last_token_line = (yyval.pos).line;
    last_token_col  = (yyval.pos).col;

    // 👇 加入
    last_init_line = (yyval.pos).line;
    last_init_col  = (yyval.pos).col;
}
#line 2288 "B113040052.tab.c"
    break;

  case 38: /* arr_or_obj: '[' INT_L ']'  */
#line 390 "B113040052.y"
                  { (yyval.pos).line = (yylsp[0]).last_line; (yyval.pos).col = (yylsp[0]).last_column; }
#line 2294 "B113040052.tab.c"
    break;

  case 39: /* arr_or_obj: '(' tuple ')'  */
#line 391 "B113040052.y"
                  { (yyval.pos).line = (yylsp[0]).last_line; (yyval.pos).col = (yylsp[0]).last_column; }
#line 2300 "B113040052.tab.c"
    break;

  case 44: /* args: type generic_id  */
#line 407 "B113040052.y"
                  { chk_dupid_id((yyvsp[0].sval)); }
#line 2306 "B113040052.tab.c"
    break;

  case 45: /* args: args ',' type generic_id  */
#line 408 "B113040052.y"
                           { chk_dupid_id((yyvsp[0].sval)); }
#line 2312 "B113040052.tab.c"
    break;

  case 54: /* generic_id: ID  */
#line 434 "B113040052.y"
                               { (yyval.sval) = (yyvsp[0].sval); }
#line 2318 "B113040052.tab.c"
    break;

  case 55: /* generic_id: generic_id '[' expr ']'  */
#line 435 "B113040052.y"
                            { (yyval.sval) = (yyvsp[-3].sval); }
#line 2324 "B113040052.tab.c"
    break;

  case 56: /* generic_id: generic_id '.' ID  */
#line 436 "B113040052.y"
                             { (yyval.sval) = (yyvsp[0].sval); }
#line 2330 "B113040052.tab.c"
    break;

  case 57: /* type: type '[' ']'  */
#line 439 "B113040052.y"
                          { (yyval.sval) = (yyvsp[-2].sval); }
#line 2336 "B113040052.tab.c"
    break;

  case 64: /* type_id: ID  */
#line 448 "B113040052.y"
            {
    if (!is_type((yyvsp[0].sval))) {
        if (!skip_next_decl_typecheck && error_reported != yylineno) {
            fprintf(stderr, "Line %d, char: %d, undefined type '%s'\n", yylineno, token_col, (yyvsp[0].sval));
            error_reported = yylineno;
        }
    }
    skip_next_decl_typecheck = 0; // 重置
    (yyval.sval) = (yyvsp[0].sval);
}
#line 2351 "B113040052.tab.c"
    break;

  case 69: /* const_expr: INVALID_TOKEN  */
#line 464 "B113040052.y"
                { /* already有处理*/ }
#line 2357 "B113040052.tab.c"
    break;

  case 86: /* lvalue: generic_id  */
#line 471 "B113040052.y"
                              { (yyval.sval) = (yyvsp[0].sval); }
#line 2363 "B113040052.tab.c"
    break;

  case 87: /* lvalue: generic_id '[' expr ']'  */
#line 472 "B113040052.y"
                              { (yyval.sval) = (yyvsp[-3].sval); }
#line 2369 "B113040052.tab.c"
    break;

  case 89: /* statement: lvalue PP ';'  */
#line 477 "B113040052.y"
                {
    if (!is_variable((yyvsp[-2].sval))) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
        yylineno, token_col, (yyvsp[-2].sval));
        error_reported = yylineno;
    }
}
#line 2381 "B113040052.tab.c"
    break;

  case 90: /* statement: PP lvalue ';'  */
#line 484 "B113040052.y"
                {
    if (!is_variable((yyvsp[-1].sval))) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
        yylineno, token_col, (yyvsp[-1].sval));
        error_reported = yylineno;
    }
}
#line 2393 "B113040052.tab.c"
    break;

  case 100: /* statement_star: statement_star error  */
#line 502 "B113040052.y"
                       {
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
#line 2419 "B113040052.tab.c"
    break;

  case 101: /* assign_stmt: generic_id '=' expr ';'  */
#line 526 "B113040052.y"
                        {
    if (!is_variable((yyvsp[-3].sval))) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n", yylineno, token_col, (yyvsp[-3].sval));
        error_reported = yylineno;
    }
}
#line 2430 "B113040052.tab.c"
    break;

  case 102: /* simple_call_decl: generic_id '(' para_list ')'  */
#line 536 "B113040052.y"
                             {
    if (!is_function((yyvsp[-3].sval))) {
        // print 不是內建 function
        if (strcmp((yyvsp[-3].sval), "print") == 0) {
            fprintf(stderr, "Line %d, char: %d, undefined function 'print'\n", last_token_line, token_col);
        } else {
            fprintf(stderr, "Line %d, char: %d, undefined function '%s'\n", last_token_line, token_col, (yyvsp[-3].sval));
        }
        error_reported = yylineno;
    }
}
#line 2446 "B113040052.tab.c"
    break;

  case 110: /* simple_call_decl: PRINT '(' expr ')'  */
#line 554 "B113040052.y"
                     {
    my_insert("print", FUNC_KIND); // 加上這句
}
#line 2454 "B113040052.tab.c"
    break;

  case 125: /* expr: expr PP  */
#line 574 "B113040052.y"
          {
    if (!is_variable((yyvsp[-1].sval))) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
        yylineno, token_col, (yyvsp[-1].sval));
        error_reported = yylineno;
    }
}
#line 2466 "B113040052.tab.c"
    break;

  case 126: /* expr: expr MM  */
#line 581 "B113040052.y"
          {
    if (!is_variable((yyvsp[-1].sval))) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
        yylineno, token_col, (yyvsp[-1].sval));
        error_reported = yylineno;
    }
}
#line 2478 "B113040052.tab.c"
    break;

  case 127: /* expr: expr '+' error  */
#line 588 "B113040052.y"
                 {
    fprintf(stderr, "Line %d, char: %d, invalid token after '+'\n", (yylsp[0]).first_line, (yylsp[0]).first_column);
    error_reported = yylineno;
    yyclearin; yyerrok;
}
#line 2488 "B113040052.tab.c"
    break;

  case 128: /* expr: expr '-' error  */
#line 593 "B113040052.y"
                 {
    fprintf(stderr, "Line %d, char: %d, invalid token after '-'\n", (yylsp[0]).first_line, (yylsp[0]).first_column);
    error_reported = yylineno;
    yyclearin; yyerrok;
}
#line 2498 "B113040052.tab.c"
    break;

  case 129: /* expr: expr '*' error  */
#line 598 "B113040052.y"
                 {
    fprintf(stderr, "Line %d, char: %d, invalid token after '*'\n", (yylsp[0]).first_line, (yylsp[0]).first_column);
    error_reported = yylineno;
    yyclearin; yyerrok;
}
#line 2508 "B113040052.tab.c"
    break;

  case 130: /* expr: expr '/' error  */
#line 603 "B113040052.y"
                 {
    fprintf(stderr, "Line %d, char: %d, invalid token after '/'\n", (yylsp[0]).first_line, (yylsp[0]).first_column);
    error_reported = yylineno;
    yyclearin; yyerrok;
}
#line 2518 "B113040052.tab.c"
    break;

  case 131: /* expr: error  */
#line 608 "B113040052.y"
        {
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
    (yyval.sval) = NULL;
}
#line 2541 "B113040052.tab.c"
    break;

  case 137: /* factor: generic_id '(' para_list ')'  */
#line 634 "B113040052.y"
                               {
    if (!is_function((yyvsp[-3].sval))) {
        if (strcmp((yyvsp[-3].sval), "print") == 0) {
            fprintf(stderr, "Line %d, char: %d, undefined function 'print'\n", last_token_line, token_col);
        } else {
            fprintf(stderr, "Line %d, char: %d, undefined function '%s'\n", last_token_line, token_col, (yyvsp[-3].sval));
        }
        error_reported = yylineno;
    }
}
#line 2556 "B113040052.tab.c"
    break;

  case 138: /* factor: lvalue PP  */
#line 644 "B113040052.y"
            {
    if (!is_variable((yyvsp[-1].sval))) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
                yylineno, token_col, (yyvsp[-1].sval));
        error_reported = yylineno;
    }
    (yyval.sval) = (yyvsp[-1].sval);
}
#line 2569 "B113040052.tab.c"
    break;

  case 139: /* factor: lvalue MM  */
#line 652 "B113040052.y"
            {
    if (!is_variable((yyvsp[-1].sval))) {
        fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
                yylineno, token_col, (yyvsp[-1].sval));
        error_reported = yylineno;
    }
    (yyval.sval) = (yyvsp[-1].sval);
}
#line 2582 "B113040052.tab.c"
    break;

  case 144: /* factor: INVALID_TOKEN  */
#line 664 "B113040052.y"
                {
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
#line 2598 "B113040052.tab.c"
    break;

  case 145: /* factor: factor error  */
#line 675 "B113040052.y"
               {
    if (error_reported != yylineno) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        error_reported = yylineno;
    }
    yyclearin;
    yyerrok;
}
#line 2611 "B113040052.tab.c"
    break;

  case 146: /* factor: error factor  */
#line 683 "B113040052.y"
               {
    if (error_reported != yylineno) {
        fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
        error_reported = yylineno;
    }
    //fprintf(stderr, "** Syntax Error at Line %d **\n", yylineno);
    error_reported = yylineno;
    yyclearin;
    yyerrok;
}
#line 2626 "B113040052.tab.c"
    break;

  case 149: /* conditional: ELSE statement  */
#line 703 "B113040052.y"
                 {
    fprintf(stderr, "Line %d, char: %d, 'else' without matching 'if'\n",
    (yylsp[-1]).first_line, (yylsp[-1]).first_column);
    error_reported = (yylsp[-1]).first_line;
    yyclearin; yyerrok;
}
#line 2637 "B113040052.tab.c"
    break;

  case 150: /* bool_expr: expr  */
#line 720 "B113040052.y"
                { (yyval.sval) = NULL; }
#line 2643 "B113040052.tab.c"
    break;

  case 151: /* bool_expr: INVALID_TOKEN  */
#line 721 "B113040052.y"
                {
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
    (yyval.sval) = "invalid";  // ✨ 關鍵
}
#line 2663 "B113040052.tab.c"
    break;

  case 152: /* bool_expr: error  */
#line 736 "B113040052.y"
        {
    fprintf(stderr, "Line %d, char: %d, invalid condition\n", last_token_line, last_token_col);
    error_reported = yylineno;
    yyclearin; yyerrok;
    (yyval.sval) = "invalid";  // ✨ 關鍵
}
#line 2674 "B113040052.tab.c"
    break;

  case 153: /* loop: while_expr__ statement  */
#line 744 "B113040052.y"
                         {
    if ((yyvsp[-1].sval) && strcmp((yyvsp[-1].sval), "invalid") == 0) {
        // 防止 statement 被吃掉，直接報錯並同步（保留 '}'）
        fprintf(stderr, "Line %d, char: %d, invalid while condition, block skipped\n", last_token_line, last_token_col);
        error_reported = yylineno;

        // 手動吃掉可能殘留的 token（如 ';'）避免卡住
        int sync_count = 0;
        while (yychar != '}' && yychar != CLASS && yychar != YYEOF) {
            yychar = yylex();
            if (++sync_count > 100) break;
        }

        yyclearin; yyerrok;
    }
}
#line 2695 "B113040052.tab.c"
    break;

  case 154: /* loop: WHILE '(' bool_expr ')' error  */
#line 760 "B113040052.y"
                                {
    fprintf(stderr, "Line %d, char: %d, invalid while-block after condition\n", (yylsp[0]).first_line, (yylsp[0]).first_column);
    error_reported = (yylsp[0]).first_line;
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
#line 2714 "B113040052.tab.c"
    break;

  case 156: /* loop: while_expr__ error  */
#line 775 "B113040052.y"
                     {
    fprintf(stderr, "Line %d, char: %d, syntax error after while condition\n",
    last_token_line, last_token_col);
    tokens[0] = '\0';
    error_reported = yylineno;
    yyclearin; yyerrok;
}
#line 2726 "B113040052.tab.c"
    break;

  case 157: /* loop: for_expr__ error  */
#line 782 "B113040052.y"
                   {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, syntax error after for condition\n", last_token_line, last_token_col);
        error_reported = yylineno;
    }
    tokens[0] = '\0';
    yyclearin; yyerrok;
}
#line 2739 "B113040052.tab.c"
    break;

  case 158: /* while_expr__: WHILE '(' bool_expr ')'  */
#line 793 "B113040052.y"
                        {
    if ((yyvsp[-1].sval) && strcmp((yyvsp[-1].sval), "invalid") == 0) {
        (yyval.sval) = "invalid";  // 傳遞錯誤狀態給 loop
    } else {
        (yyval.sval) = NULL;
    }
}
#line 2751 "B113040052.tab.c"
    break;

  case 159: /* while_expr__: WHILE '(' error  */
#line 800 "B113040052.y"
                  {
      fprintf(stderr, "Line %d, char: %d, malformed while condition\n",
      (yylsp[0]).first_line, (yylsp[0]).first_column);
      error_reported = (yylsp[0]).first_line;
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
#line 2771 "B113040052.tab.c"
    break;

  case 160: /* while_expr__: WHILE error ')'  */
#line 815 "B113040052.y"
                  {
    fprintf(stderr, "Line %d, char: %d, invalid condition inside while\n",
    last_token_line, last_token_col);
    tokens[0] = '\0';
    error_reported = yylineno;
    yyclearin;
    yyerrok;
}
#line 2784 "B113040052.tab.c"
    break;

  case 165: /* single_for_init: generic_id '=' expr  */
#line 836 "B113040052.y"
                     {
    if (!is_variable((yyvsp[-2].sval)))
    fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
    yylineno, token_col, (yyvsp[-2].sval));
    error_reported = yylineno;
    tokens[0] = '\0';
}
#line 2796 "B113040052.tab.c"
    break;

  case 166: /* single_for_init: type generic_id '=' expr  */
#line 843 "B113040052.y"
                           {
    chk_dupid_id((yyvsp[-2].sval)); // 宣告 inline 變數
}
#line 2804 "B113040052.tab.c"
    break;

  case 167: /* single_for_init: generic_id PP  */
#line 846 "B113040052.y"
                {
    if (!is_variable((yyvsp[-1].sval)))
    fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
    yylineno, token_col, (yyvsp[-1].sval));
    error_reported = yylineno;
    tokens[0] = '\0';
}
#line 2816 "B113040052.tab.c"
    break;

  case 168: /* single_for_init: PP generic_id  */
#line 853 "B113040052.y"
                {
    if (!is_variable((yyvsp[0].sval)))
    fprintf(stderr, "Line %d, char: %d, undefined variable '%s'\n",
    yylineno, token_col, (yyvsp[0].sval));
    error_reported = yylineno;
    tokens[0] = '\0';
}
#line 2828 "B113040052.tab.c"
    break;

  case 170: /* for_expr__: FOR error ')'  */
#line 863 "B113040052.y"
                {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, syntax error in for-loop expression\n", last_token_line, last_token_col);
        error_reported = yylineno;
    }
    yyclearin;
    yyerrok;
}
#line 2841 "B113040052.tab.c"
    break;

  case 177: /* return: RETURN error  */
#line 885 "B113040052.y"
               {
    fprintf(stderr, "Line %d, char: %d, invalid return expression\n", last_token_line, last_token_col);
    yyclearin; yyerrok;
}
#line 2850 "B113040052.tab.c"
    break;

  case 181: /* para_list: error  */
#line 894 "B113040052.y"
        {
    if (error_reported != yylineno) {
        fprintf(stderr, "Line %d, char: %d, invalid function parameter list\n", last_token_line, last_token_col);
        error_reported = yylineno;
    }
    tokens[0] = '\0';
    yyclearin;
    yyerrok;
}
#line 2864 "B113040052.tab.c"
    break;


#line 2868 "B113040052.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  if (yyimpl)
    yyimpl->yynerrs = yynerrs;
  return yyresult;
}

#line 905 "B113040052.y"

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
