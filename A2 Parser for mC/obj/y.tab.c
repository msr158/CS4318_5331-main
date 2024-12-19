/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20210109

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "src/parser.y"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*#include<../src/tree.h>*/
#include "tree.h"
/*#include<../src/strtab.h>*/

extern int yylineno;
/* nodeTypes refer to different types of internal and external nodes that can be part of the abstract syntax tree.*/
enum nodeTypes {PROGRAM, DECLLIST, DECL, VARDECL, TYPESPEC, FUNDECL,
                FORMALDECLLIST, FORMALDECL, FUNBODY, LOCALDECLLIST,
                STATEMENTLIST, STATEMENT, COMPOUNDSTMT, ASSIGNSTMT,
                CONDSTMT, LOOPSTMT, RETURNSTMT, EXPRESSION, RELOP,
                ADDEXPR, ADDOP, TERM, MULOP, FACTOR, FUNCCALLEXPR,
                ARGLIST, INTEGER, IDENTIFIER, VAR, ARRAYDECL, CHAR,
                FUNCTYPENAME, VARIABLE};

enum opType {ADD, SUB, MUL, DIV, LT, LTE, EQ, GTE, GT, NEQ};

/* NOTE: mC has two kinds of scopes for variables : local and global. Variables declared outside any
function are considered globals, whereas variables (and parameters) declared inside a function foo are local to foo. You should update the scope variable whenever you are inside a production that matches function definition (funDecl production). The rationale is that you are entering that function, so all variables, arrays, and other functions should be within this scope. You should pass this variable whenever you are calling the ST_insert or ST_lookup functions. This variable should be updated to scope = "" to indicate global scope whenever funDecl finishes. Treat these hints as helpful directions only. You may implement all of the functions as you like and not adhere to my instructions. As long as the directory structure is correct and the file names are correct, we are okay with it. */
char* scope = "";
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 27 "src/parser.y"
typedef union
{
    int value;
    struct treenode *node;
    char *strval;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 58 "obj/y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define ID 257
#define INTCONST 258
#define KWD_IF 259
#define KWD_ELSE 260
#define KWD_WHILE 261
#define KWD_INT 262
#define KWD_CHAR 263
#define KWD_RETURN 264
#define KWD_VOID 265
#define OPER_ADD 266
#define OPER_SUB 267
#define OPER_MUL 268
#define OPER_DIV 269
#define OPER_LTE 270
#define OPER_GTE 271
#define OPER_LT 272
#define OPER_GT 273
#define OPER_EQ 274
#define OPER_NEQ 275
#define OPER_ASGN 276
#define LSQ_BRKT 277
#define RSQ_BRKT 278
#define LCRLY_BRKT 279
#define RCRLY_BRKT 280
#define LPAREN 281
#define RPAREN 282
#define COMMA 283
#define SEMICLN 284
#define ERROR 285
#define CHARCONST 286
#define STRCONST 287
#define ILLEGAL_TOKEN 288
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    3,    3,    4,    4,    4,
    5,    5,    6,    6,    7,    7,    8,    9,    9,   10,
   10,   11,   11,   11,   11,   11,   11,   12,   13,   14,
   14,   15,   16,   16,   17,   17,   18,   18,   18,   19,
   19,   19,   19,   19,   19,   20,   20,   21,   21,   22,
   22,   23,   23,   24,   24,   24,   24,   24,   24,   25,
   25,   26,   26,
};
static const YYINT yylen[] = {                            2,
    1,    1,    2,    1,    1,    3,    6,    1,    1,    1,
    6,    5,    1,    3,    2,    4,    4,    0,    2,    0,
    2,    1,    1,    1,    1,    1,    2,    3,    4,    5,
    7,    5,    2,    3,    1,    4,    1,    3,    1,    1,
    1,    1,    1,    1,    1,    1,    3,    1,    1,    1,
    3,    1,    1,    3,    1,    1,    1,    1,    1,    4,
    3,    1,    3,
};
static const YYINT yydefred[] = {                         0,
    8,    9,   10,    0,    0,    2,    4,    0,    5,    3,
    0,    0,    0,    6,    0,    0,    0,    0,   13,    0,
    0,   12,    0,    0,    0,    7,    0,    0,    0,    0,
   11,   14,   19,    0,    0,   57,    0,    0,    0,    0,
    0,   58,   59,    0,    0,   22,   23,   24,   25,   26,
    0,    0,    0,    0,   50,   56,   16,    0,    0,    0,
    0,   33,    0,    0,    0,    0,   17,   21,    0,   40,
   43,   41,   42,   44,   45,   27,    0,   48,   49,    0,
   52,   53,    0,    0,   61,    0,    0,    0,    0,   34,
   28,   54,    0,   55,    0,    0,   51,   36,   60,    0,
    0,    0,   29,    0,    0,   32,    0,   31,
};
static const YYINT yydgoto[] = {                          4,
    5,    6,    7,    8,    9,   18,   19,   22,   29,   44,
   45,   46,   47,   48,   49,   50,   63,   52,   77,   53,
   80,   54,   83,   55,   56,   87,
};
static const YYINT yysindex[] = {                      -132,
    0,    0,    0,    0, -132,    0,    0, -255,    0,    0,
 -267, -254, -167,    0, -245, -229, -196, -258,    0, -216,
 -132,    0, -186, -229, -132,    0, -132, -174, -212, -181,
    0,    0,    0, -269, -224,    0, -169, -129, -202, -212,
 -187,    0,    0, -166, -212,    0,    0,    0,    0,    0,
 -160,  -52, -225, -192,    0,    0,    0, -187, -194, -187,
 -187,    0,    0,  -46, -126,  -25,    0,    0, -187,    0,
    0,    0,    0,    0,    0,    0, -187,    0,    0, -187,
    0,    0, -187,    7,    0,   16, -193,  -12,   -6,    0,
    0,    0,  -31,    0, -225, -192,    0,    0,    0, -187,
 -212, -212,    0,   16, -107,    0, -212,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,  160,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -252,    0, -148,    0,    0,    0, -252,    0, -119,    0,
    0,    0,    0,    0, -165,    0,    0,    0,    0, -119,
    0,    0,    0,    0, -119,    0,    0,    0,    0,    0,
  -89,    0,  -82, -127,    0,    0,    0,    0,    0,    0,
    0,    0, -146,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -141,    0,    0,    0,    0,
    0,    0,    0,    0,  -67, -108,    0,    0,    0,    0,
    0,    0,    0, -133, -221,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,  163,   -8,    5,    0,    0,  144,  147,  145,   -1,
  -21,    0,    0,    0,    0,    0,  -29,  -38,    0,   96,
    0,  107,    0,  111,    0,    0,
};
#define YYTABLESIZE 291
static const YYINT yytable[] = {                         51,
   64,   11,   66,   15,   18,   18,   18,   12,   18,   12,
   51,   18,   27,   13,   14,   51,   14,   17,   27,   84,
   86,   88,   89,   24,   25,   28,   18,   18,   18,   17,
   93,   28,   20,   18,   18,   30,   30,   30,   65,   30,
   78,   79,   30,   68,   35,   36,   37,   94,   38,   21,
   94,   39,   58,   94,   35,   36,   59,   30,   30,   30,
   23,  104,   35,   36,   30,   30,   40,   26,   41,   35,
   36,   51,   51,   42,   43,   81,   82,   51,   41,  105,
  106,   62,   34,   42,   43,  108,   41,   85,   99,  100,
   30,   42,   43,   41,    1,    2,   57,    3,   42,   43,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   60,   35,   67,   16,   69,   35,   35,   35,   55,
   55,   55,   55,   39,   39,   39,   39,   39,   39,    1,
    2,   39,    3,   15,   15,   39,   39,   39,   46,   46,
   62,   62,   46,   46,   46,   46,   46,   46,   63,   63,
   46,   61,  107,   91,   46,   46,   46,   47,   47,    1,
   20,   47,   47,   47,   47,   47,   47,   10,   32,   47,
   31,   33,   95,   47,   47,   47,   55,   55,   55,   55,
   39,   39,   39,   39,   39,   39,   96,   37,   37,   37,
   37,   37,   37,   97,   39,   37,    0,    0,    0,   37,
   37,   37,   38,   38,   38,   38,   38,   38,    0,    0,
   38,    0,    0,    0,   38,   38,   38,   70,   71,   72,
   73,   74,   75,   70,   71,   72,   73,   74,   75,    0,
    0,   76,    0,    0,    0,    0,    0,   90,   70,   71,
   72,   73,   74,   75,   70,   71,   72,   73,   74,   75,
    0,    0,  103,    0,    0,    0,   92,   70,   71,   72,
   73,   74,   75,   70,   71,   72,   73,   74,   75,  101,
    0,    0,    0,    0,    0,  102,   70,   71,   72,   73,
   74,   75,    0,    0,   98,   70,   71,   72,   73,   74,
   75,
};
static const YYINT yycheck[] = {                         29,
   39,  257,   41,  258,  257,  258,  259,  277,  261,  277,
   40,  264,   21,  281,  284,   45,  284,   13,   27,   58,
   59,   60,   61,  282,  283,   21,  279,  280,  281,   25,
   69,   27,  278,  286,  287,  257,  258,  259,   40,  261,
  266,  267,  264,   45,  257,  258,  259,   77,  261,  279,
   80,  264,  277,   83,  257,  258,  281,  279,  280,  281,
  257,  100,  257,  258,  286,  287,  279,  284,  281,  257,
  258,  101,  102,  286,  287,  268,  269,  107,  281,  101,
  102,  284,  257,  286,  287,  107,  281,  282,  282,  283,
  277,  286,  287,  281,  262,  263,  278,  265,  286,  287,
  266,  267,  268,  269,  270,  271,  272,  273,  274,  275,
  276,  281,  278,  280,  282,  276,  282,  283,  284,  266,
  267,  268,  269,  270,  271,  272,  273,  274,  275,  262,
  263,  278,  265,  282,  283,  282,  283,  284,  266,  267,
  282,  283,  270,  271,  272,  273,  274,  275,  282,  283,
  278,  281,  260,  280,  282,  283,  284,  266,  267,    0,
  280,  270,  271,  272,  273,  274,  275,    5,   25,  278,
   24,   27,   77,  282,  283,  284,  266,  267,  268,  269,
  270,  271,  272,  273,  274,  275,   80,  270,  271,  272,
  273,  274,  275,   83,  284,  278,   -1,   -1,   -1,  282,
  283,  284,  270,  271,  272,  273,  274,  275,   -1,   -1,
  278,   -1,   -1,   -1,  282,  283,  284,  270,  271,  272,
  273,  274,  275,  270,  271,  272,  273,  274,  275,   -1,
   -1,  284,   -1,   -1,   -1,   -1,   -1,  284,  270,  271,
  272,  273,  274,  275,  270,  271,  272,  273,  274,  275,
   -1,   -1,  284,   -1,   -1,   -1,  282,  270,  271,  272,
  273,  274,  275,  270,  271,  272,  273,  274,  275,  282,
   -1,   -1,   -1,   -1,   -1,  282,  270,  271,  272,  273,
  274,  275,   -1,   -1,  278,  270,  271,  272,  273,  274,
  275,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 288
#define YYUNDFTOKEN 317
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ID","INTCONST","KWD_IF",
"KWD_ELSE","KWD_WHILE","KWD_INT","KWD_CHAR","KWD_RETURN","KWD_VOID","OPER_ADD",
"OPER_SUB","OPER_MUL","OPER_DIV","OPER_LTE","OPER_GTE","OPER_LT","OPER_GT",
"OPER_EQ","OPER_NEQ","OPER_ASGN","LSQ_BRKT","RSQ_BRKT","LCRLY_BRKT",
"RCRLY_BRKT","LPAREN","RPAREN","COMMA","SEMICLN","ERROR","CHARCONST","STRCONST",
"ILLEGAL_TOKEN",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : declList",
"declList : decl",
"declList : declList decl",
"decl : varDecl",
"decl : funDecl",
"varDecl : typeSpecifier ID SEMICLN",
"varDecl : typeSpecifier ID LSQ_BRKT INTCONST RSQ_BRKT SEMICLN",
"typeSpecifier : KWD_INT",
"typeSpecifier : KWD_CHAR",
"typeSpecifier : KWD_VOID",
"funDecl : typeSpecifier ID LPAREN formalDeclList RPAREN funBody",
"funDecl : typeSpecifier ID LPAREN RPAREN funBody",
"formalDeclList : formalDecl",
"formalDeclList : formalDeclList COMMA formalDecl",
"formalDecl : typeSpecifier ID",
"formalDecl : typeSpecifier ID LSQ_BRKT RSQ_BRKT",
"funBody : LCRLY_BRKT localDeclList statementList RCRLY_BRKT",
"localDeclList :",
"localDeclList : varDecl localDeclList",
"statementList :",
"statementList : statement statementList",
"statement : compoundStmt",
"statement : assignStmt",
"statement : condStmt",
"statement : loopStmt",
"statement : returnStmt",
"statement : expression SEMICLN",
"compoundStmt : LCRLY_BRKT statementList RCRLY_BRKT",
"assignStmt : var OPER_ASGN expression SEMICLN",
"condStmt : KWD_IF LPAREN expression RPAREN statement",
"condStmt : KWD_IF LPAREN expression RPAREN statement KWD_ELSE statement",
"loopStmt : KWD_WHILE LPAREN expression RPAREN statement",
"returnStmt : KWD_RETURN SEMICLN",
"returnStmt : KWD_RETURN expression SEMICLN",
"var : ID",
"var : ID LSQ_BRKT expression RSQ_BRKT",
"expression : addExpr",
"expression : expression relop addExpr",
"expression : var",
"relop : OPER_LTE",
"relop : OPER_LT",
"relop : OPER_GT",
"relop : OPER_GTE",
"relop : OPER_EQ",
"relop : OPER_NEQ",
"addExpr : term",
"addExpr : addExpr addop term",
"addop : OPER_ADD",
"addop : OPER_SUB",
"term : factor",
"term : term mulop factor",
"mulop : OPER_MUL",
"mulop : OPER_DIV",
"factor : LPAREN expression RPAREN",
"factor : var",
"factor : funcCallExpr",
"factor : INTCONST",
"factor : CHARCONST",
"factor : STRCONST",
"funcCallExpr : ID LPAREN argList RPAREN",
"funcCallExpr : ID LPAREN RPAREN",
"argList : expression",
"argList : argList COMMA expression",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 400 "src/parser.y"

int yywarning(char * msg){
    printf("warning: line %d: %s\n", yylineno, msg);
    return 0;
}

int yyerror(char * msg){
    printf("error: line %d: %s\n", yylineno, msg);
    return 0;
}
#line 400 "obj/y.tab.c"

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 1:
#line 58 "src/parser.y"
	{
                    tree* progNode = maketree(PROGRAM);
                    addChild(progNode, yystack.l_mark[0].node);
                    ast = progNode;
                 }
break;
case 2:
#line 66 "src/parser.y"
	{
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, yystack.l_mark[0].node);
                    yyval.node = declListNode;
                 }
break;
case 3:
#line 72 "src/parser.y"
	{
                    /*tree* declListNode = maketree(DECLLIST);*/
                    /*addChild(declListNode, $1);*/
                    /*addChild(declListNode, $2);*/
                    /*$$ = declListNode;*/
                    addChild(yystack.l_mark[-1].node, yystack.l_mark[0].node);
                    yyval.node = yystack.l_mark[-1].node;
                 }
break;
case 4:
#line 84 "src/parser.y"
	{
                    yyval.node = yystack.l_mark[0].node;
                 }
break;
case 5:
#line 88 "src/parser.y"
	{
                    yyval.node = yystack.l_mark[0].node;
                 }
break;
case 6:
#line 94 "src/parser.y"
	{
		            printf("%s\n", yystack.l_mark[-1].strval);
		            tree *declNode = maketree(VARDECL);
                addChild(declNode, yystack.l_mark[-2].node);
                addChild(declNode, maketreeWithVal(IDENTIFIER, yystack.l_mark[-1].strval));
		            yyval.node = declNode;
	            }
break;
case 7:
#line 102 "src/parser.y"
	{
                  printf("%s\n", yystack.l_mark[-4].strval);
                  tree *arrayDeclNode = maketree(ARRAYDECL);
                  addChild(arrayDeclNode, yystack.l_mark[-5].node);
                  addChild(arrayDeclNode, maketreeWithVal(IDENTIFIER, yystack.l_mark[-4].strval));
                  addChild(arrayDeclNode, maketreeWithVal(INTEGER, yystack.l_mark[-2].value));
                  yyval.node = arrayDeclNode;
                }
break;
case 8:
#line 113 "src/parser.y"
	{
                    yyval.node = maketree(TYPESPEC);
                 }
break;
case 9:
#line 117 "src/parser.y"
	{
                    yyval.node = maketree(TYPESPEC);
                 }
break;
case 10:
#line 121 "src/parser.y"
	{
                    yyval.node = maketree(TYPESPEC);
                 }
break;
case 11:
#line 127 "src/parser.y"
	{
                    tree* funDeclNode = maketree(FUNDECL);
                    addChild(funDeclNode, yystack.l_mark[-5].node);
                    tree* idNode = maketreeWithVal(IDENTIFIER, yystack.l_mark[-4].strval);
                    addChild(funDeclNode, idNode);
                    addChild(funDeclNode, yystack.l_mark[-2].node);
                    addChild(funDeclNode, yystack.l_mark[0].node);
                    yyval.node = funDeclNode;
                 }
break;
case 12:
#line 137 "src/parser.y"
	{
                    tree* funDeclNode = maketree(FUNDECL);
                    addChild(funDeclNode, yystack.l_mark[-4].node);
                    tree* idNode = maketreeWithVal(IDENTIFIER, yystack.l_mark[-3].strval);
                    addChild(funDeclNode, idNode);
                    addChild(funDeclNode, yystack.l_mark[0].node);
                    yyval.node = funDeclNode;
                 }
break;
case 13:
#line 148 "src/parser.y"
	{
                    tree* formalDeclListNode = maketree(FORMALDECLLIST);
                    addChild(formalDeclListNode, yystack.l_mark[0].node);
                    yyval.node = formalDeclListNode;
                 }
break;
case 14:
#line 154 "src/parser.y"
	{
                    addChild(yystack.l_mark[-2].node, yystack.l_mark[0].node);
                    yyval.node = yystack.l_mark[-2].node;
                 }
break;
case 15:
#line 161 "src/parser.y"
	{
                    tree* formalDeclNode = maketree(FORMALDECL);
                    addChild(formalDeclNode, yystack.l_mark[-1].node);
                    tree* idNode = maketreeWithVal(IDENTIFIER, yystack.l_mark[0].strval);
                    addChild(formalDeclNode, idNode);
                    yyval.node = formalDeclNode;
                 }
break;
case 16:
#line 169 "src/parser.y"
	{
                    tree* formalDeclNode = maketree(FORMALDECL);
                    addChild(formalDeclNode, yystack.l_mark[-3].node);
                    tree* idNode = maketreeWithVal(IDENTIFIER, yystack.l_mark[-2].strval);
                    addChild(formalDeclNode, idNode);
                    yyval.node = formalDeclNode;
                 }
break;
case 17:
#line 179 "src/parser.y"
	{
                    tree* funBodyNode = maketree(FUNBODY);
                    addChild(funBodyNode, yystack.l_mark[-2].node);
                    addChild(funBodyNode, yystack.l_mark[-1].node);
                    yyval.node = funBodyNode;
                 }
break;
case 18:
#line 188 "src/parser.y"
	{
                    yyval.node = maketree(LOCALDECLLIST);
                 }
break;
case 19:
#line 192 "src/parser.y"
	{
                    /*addChild($2, $1);*/
                    /*$$ = $2;*/
                    addChild(yystack.l_mark[-1].node, yystack.l_mark[0].node);
                    yyval.node = yystack.l_mark[-1].node;
                 }
break;
case 20:
#line 201 "src/parser.y"
	{
                    yyval.node = maketree(STATEMENTLIST);
                 }
break;
case 21:
#line 205 "src/parser.y"
	{
                    addChild(yystack.l_mark[0].node, yystack.l_mark[-1].node);
                    yyval.node = yystack.l_mark[0].node;
                 }
break;
case 28:
#line 220 "src/parser.y"
	{
		     yyval.node = yystack.l_mark[-1].node;
		 }
break;
case 29:
#line 226 "src/parser.y"
	{
		                  tree *assignNode = maketree(ASSIGNSTMT);
		                  addChild(assignNode, yystack.l_mark[-3].node);
                      addChild(assignNode, yystack.l_mark[-1].node);
		                  yyval.node = assignNode;
	                  }
break;
case 30:
#line 235 "src/parser.y"
	{
                    tree* condStmtNode = maketree(CONDSTMT);
                    addChild(condStmtNode, yystack.l_mark[-2].node);
                    addChild(condStmtNode, yystack.l_mark[0].node);
                    yyval.node = condStmtNode;
                 }
break;
case 31:
#line 242 "src/parser.y"
	{
                    tree* condStmtNode = maketree(CONDSTMT);
                    addChild(condStmtNode, yystack.l_mark[-4].node);
                    addChild(condStmtNode, yystack.l_mark[-2].node);
                    addChild(condStmtNode, yystack.l_mark[0].node);
                    yyval.node = condStmtNode;
                 }
break;
case 32:
#line 252 "src/parser.y"
	{
                    tree* loopStmtNode = maketree(LOOPSTMT);
                    addChild(loopStmtNode, yystack.l_mark[-2].node);
                    addChild(loopStmtNode, yystack.l_mark[0].node);
                    yyval.node = loopStmtNode;
                 }
break;
case 33:
#line 261 "src/parser.y"
	{
                    tree* returnStmtNode = maketree(RETURNSTMT);
                    yyval.node = returnStmtNode;
                 }
break;
case 34:
#line 266 "src/parser.y"
	{
                    tree* returnStmtNode = maketree(RETURNSTMT);
                    addChild(returnStmtNode, yystack.l_mark[-1].node);
                    yyval.node = returnStmtNode;
                 }
break;
case 35:
#line 274 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(IDENTIFIER, strdup(yystack.l_mark[0].strval));
                 }
break;
case 36:
#line 278 "src/parser.y"
	{
                    /*tree* varNode = maketree(VARIABLE);*/
                    /*addChild(varNode, maketreeWithVal(IDENTIFIER, strdup($1)));*/
                    /*addChild(varNode, $3);*/
                    /*$$ = varNode;*/

                    tree* arrayNode = maketree(ARRAYDECL);
                    addChild(arrayNode, maketreeWithVal(IDENTIFIER, strdup(yystack.l_mark[-3].strval)));
                    addChild(arrayNode, yystack.l_mark[-1].node);
                    yyval.node = arrayNode;


                 }
break;
case 40:
#line 299 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, "<=");
                 }
break;
case 41:
#line 303 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, "<");
                 }
break;
case 42:
#line 307 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, ">");
                 }
break;
case 43:
#line 311 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, ">=");
                 }
break;
case 44:
#line 315 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, "==");
                 }
break;
case 45:
#line 319 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, "!=");
                 }
break;
case 48:
#line 329 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(ADDOP, "+");
                 }
break;
case 49:
#line 333 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(ADDOP, "-");
                 }
break;
case 52:
#line 343 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(MULOP, "*");
                 }
break;
case 53:
#line 347 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(MULOP, "/");
                 }
break;
case 54:
#line 353 "src/parser.y"
	{
                    yyval.node = yystack.l_mark[-1].node; /* Expression within parentheses*/
                 }
break;
case 55:
#line 357 "src/parser.y"
	{
                    yyval.node = yystack.l_mark[0].node; /* Variable*/
                 }
break;
case 56:
#line 361 "src/parser.y"
	{
                    yyval.node = yystack.l_mark[0].node; /* Function call*/
                 }
break;
case 57:
#line 365 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(INTCONST, yystack.l_mark[0].value); /* Integer constant*/
                 }
break;
case 58:
#line 369 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(CHARCONST, yystack.l_mark[0].value); /* Char constant*/
                 }
break;
case 59:
#line 373 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(STRCONST, yystack.l_mark[0].value); /* String constant*/
                 }
break;
case 60:
#line 379 "src/parser.y"
	{
                    tree* funcCallNode = maketree(FUNCCALLEXPR);
                    addChild(funcCallNode, maketreeWithVal(IDENTIFIER, yystack.l_mark[-3].strval));
                    addChild(funcCallNode, yystack.l_mark[-1].node); /* Arguments*/
                    yyval.node = funcCallNode;
                 }
break;
case 61:
#line 386 "src/parser.y"
	{
                    tree* funcCallNode = maketree(FUNCCALLEXPR);
                    addChild(funcCallNode, maketreeWithVal(IDENTIFIER, yystack.l_mark[-2].strval));
                    yyval.node = funcCallNode; /* No arguments*/
                 }
break;
#line 965 "obj/y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
