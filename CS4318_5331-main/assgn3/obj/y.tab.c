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
#include<../src/strtab.h>

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
   27,    0,    1,    1,    2,    2,    3,    3,    4,    4,
    4,    5,    5,    6,    6,    7,    7,    8,    9,    9,
   10,   10,   11,   11,   11,   11,   11,   12,   13,   13,
   14,   14,   15,   16,   16,   17,   17,   18,   18,   19,
   19,   19,   19,   19,   19,   20,   20,   21,   21,   22,
   22,   23,   23,   24,   24,   24,   24,   24,   25,   25,
   26,   26,
};
static const YYINT yylen[] = {                            2,
    0,    2,    1,    2,    1,    1,    3,    6,    1,    1,
    1,    6,    5,    1,    3,    2,    4,    4,    0,    2,
    0,    2,    1,    1,    1,    1,    1,    3,    4,    2,
    5,    7,    5,    2,    3,    1,    4,    1,    3,    1,
    1,    1,    1,    1,    1,    1,    3,    1,    1,    1,
    3,    1,    1,    3,    1,    1,    1,    1,    4,    3,
    1,    3,
};
static const YYINT yydefred[] = {                         1,
    0,    0,    9,   10,   11,    0,    3,    5,    0,    6,
    4,    0,    0,    0,    7,    0,    0,    0,    0,   14,
    0,    0,   13,    0,    0,    0,    8,    0,    0,    0,
    0,   12,   15,   20,    0,    0,   57,    0,    0,    0,
    0,    0,   58,    0,    0,   23,   24,   25,   26,   27,
    0,    0,    0,    0,   50,   56,   17,    0,    0,    0,
    0,   34,   55,    0,    0,    0,   18,   22,    0,   40,
   43,   41,   42,   44,   45,   30,    0,   48,   49,    0,
   52,   53,    0,    0,   60,    0,    0,    0,    0,   35,
   28,   54,    0,    0,    0,   51,   37,   59,    0,    0,
    0,   29,    0,    0,   33,    0,   32,
};
static const YYINT yydgoto[] = {                          1,
    6,    7,    8,    9,   10,   19,   20,   23,   30,   44,
   45,   46,   47,   48,   49,   50,   63,   52,   77,   53,
   80,   54,   83,   55,   56,   87,    2,
};
static const YYINT yysindex[] = {                         0,
    0, -149,    0,    0,    0, -149,    0,    0, -247,    0,
    0,  -78, -220, -249,    0, -238, -230, -191, -251,    0,
 -216, -149,    0, -197, -230, -149,    0, -149, -175, -214,
 -183,    0,    0,    0, -258, -225,    0, -124, -123, -233,
 -214, -240,    0, -181, -214,    0,    0,    0,    0,    0,
 -139,  -98, -169, -151,    0,    0,    0, -240, -203, -240,
 -240,    0,    0,  -83, -120,  -62,    0,    0, -240,    0,
    0,    0,    0,    0,    0,    0, -240,    0,    0, -240,
    0,    0, -240, -204,    0,  -29, -177,  -56,  -43,    0,
    0,    0,  -77, -169, -151,    0,    0,    0, -240, -214,
 -214,    0,  -29,  -99,    0, -214,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,  162,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -252,    0, -158,    0,    0,    0, -252,    0,  -97,
    0,    0,    0,    0,    0, -182,    0,    0,    0,    0,
  -97,    0,    0,    0,  -97,    0,    0,    0,    0,    0,
 -125,    0, -119, -163,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -150,    0,    0,    0,    0,
    0,    0,    0, -104, -144,    0,    0,    0,    0,    0,
    0,    0, -147, -222,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,  175,  -20,   47,    0,    0,  156,  159,  157,   36,
  134,    0,    0,    0,    0,    0,  -30,  -39,    0,  -54,
    0,  120,    0,  119,    0,    0,    0,
};
#define YYTABLESIZE 246
static const YYINT yytable[] = {                         51,
   64,   28,   66,   84,   19,   19,   19,   28,   19,   12,
   51,   19,    3,    4,   51,    5,   36,   37,   13,   86,
   88,   89,   94,   36,   37,   15,   19,   19,   19,   93,
   25,   26,   17,   19,   31,   31,   31,   16,   31,   21,
   42,   31,   36,   37,   38,   43,   39,   42,   22,   40,
   62,   58,   43,   36,   37,   59,   31,   31,   31,  103,
   18,   78,   79,   31,   41,   24,   42,   27,   29,   51,
   51,   43,   18,   97,   29,   51,   65,   42,   85,   31,
   68,   35,   43,   36,   36,   36,   36,   36,   36,   36,
   36,   36,   36,   36,   57,   36,   78,   79,   67,   36,
   36,   36,   46,   46,   98,   99,   46,   46,   46,   46,
   46,   46,    3,    4,   46,    5,   81,   82,   46,   46,
   46,   47,   47,   16,   16,   47,   47,   47,   47,   47,
   47,   61,   61,   47,   62,   62,   69,   47,   47,   47,
   55,   55,   55,   55,   55,   55,   55,   55,   55,   55,
   38,   38,   38,   38,   38,   38,   60,   61,   55,   91,
  106,    2,   38,   38,   38,   39,   39,   39,   39,   39,
   39,   70,   71,   72,   73,   74,   75,   39,   39,   39,
   11,   33,   21,   32,   34,   76,   70,   71,   72,   73,
   74,   75,   70,   71,   72,   73,   74,   75,   13,   95,
   90,   96,   14,    0,    0,   15,  102,   70,   71,   72,
   73,   74,   75,   70,   71,   72,   73,   74,   75,   92,
    0,    0,    0,    0,    0,  100,   70,   71,   72,   73,
   74,   75,    0,  104,  105,    0,    0,    0,  101,  107,
   70,   71,   72,   73,   74,   75,
};
static const YYINT yycheck[] = {                         30,
   40,   22,   42,   58,  257,  258,  259,   28,  261,  257,
   41,  264,  262,  263,   45,  265,  257,  258,  277,   59,
   60,   61,   77,  257,  258,  284,  279,  280,  281,   69,
  282,  283,  282,  286,  257,  258,  259,  258,  261,  278,
  281,  264,  257,  258,  259,  286,  261,  281,  279,  264,
  284,  277,  286,  257,  258,  281,  279,  280,  281,   99,
   14,  266,  267,  286,  279,  257,  281,  284,   22,  100,
  101,  286,   26,  278,   28,  106,   41,  281,  282,  277,
   45,  257,  286,  266,  267,  268,  269,  270,  271,  272,
  273,  274,  275,  276,  278,  278,  266,  267,  280,  282,
  283,  284,  266,  267,  282,  283,  270,  271,  272,  273,
  274,  275,  262,  263,  278,  265,  268,  269,  282,  283,
  284,  266,  267,  282,  283,  270,  271,  272,  273,  274,
  275,  282,  283,  278,  282,  283,  276,  282,  283,  284,
  266,  267,  268,  269,  270,  271,  272,  273,  274,  275,
  270,  271,  272,  273,  274,  275,  281,  281,  284,  280,
  260,    0,  282,  283,  284,  270,  271,  272,  273,  274,
  275,  270,  271,  272,  273,  274,  275,  282,  283,  284,
    6,   26,  280,   25,   28,  284,  270,  271,  272,  273,
  274,  275,  270,  271,  272,  273,  274,  275,  277,   80,
  284,   83,  281,   -1,   -1,  284,  284,  270,  271,  272,
  273,  274,  275,  270,  271,  272,  273,  274,  275,  282,
   -1,   -1,   -1,   -1,   -1,  282,  270,  271,  272,  273,
  274,  275,   -1,  100,  101,   -1,   -1,   -1,  282,  106,
  270,  271,  272,  273,  274,  275,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 288
#define YYUNDFTOKEN 318
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
"ILLEGAL_TOKEN",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"$$1 :",
"program : $$1 declList",
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
"compoundStmt : LCRLY_BRKT statementList RCRLY_BRKT",
"assignStmt : var OPER_ASGN expression SEMICLN",
"assignStmt : expression SEMICLN",
"condStmt : KWD_IF LPAREN expression RPAREN statement",
"condStmt : KWD_IF LPAREN expression RPAREN statement KWD_ELSE statement",
"loopStmt : KWD_WHILE LPAREN expression RPAREN statement",
"returnStmt : KWD_RETURN SEMICLN",
"returnStmt : KWD_RETURN expression SEMICLN",
"var : ID",
"var : ID LSQ_BRKT addExpr RSQ_BRKT",
"expression : addExpr",
"expression : expression relop addExpr",
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
#line 552 "src/parser.y"

int yywarning(char * msg){
    printf("warning: line %d: %s\n", yylineno, msg);
    return 0;
}

int yyerror(char * msg){
    printf("error: line %d: %s\n", yylineno, msg);
    return 0;
}

//int checkParameters(){

//}
#line 393 "obj/y.tab.c"

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
#line 57 "src/parser.y"
	{
                     new_scope();
                  }
break;
case 2:
#line 61 "src/parser.y"
	{
                    tree* progNode = maketree(PROGRAM);
                    addChild(progNode, yystack.l_mark[-1].node);
                    ast = progNode;
                 }
break;
case 3:
#line 69 "src/parser.y"
	{
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, yystack.l_mark[0].node);
                    yyval.node = declListNode;
                 }
break;
case 4:
#line 75 "src/parser.y"
	{
                    tree* declListNode = maketree(DECLLIST);
                    addChild(declListNode, yystack.l_mark[-1].node);
                    addChild(declListNode, yystack.l_mark[0].node);
                    yyval.node = declListNode;
                 }
break;
case 5:
#line 85 "src/parser.y"
	{
                    tree* declNode = maketree(DECL);
                    addChild(declNode, yystack.l_mark[0].node);
                    yyval.node = declNode;
                 }
break;
case 6:
#line 91 "src/parser.y"
	{
                    tree* declNode = maketree(DECL);
                    addChild(declNode, yystack.l_mark[0].node);
                    yyval.node = declNode;
                 }
break;
case 7:
#line 99 "src/parser.y"
	{
		            printf("%s\n", yystack.l_mark[-1].strval);
		            tree *declNode = maketree(VARDECL);
                  addChild(declNode, yystack.l_mark[-2].node);
                  addChild(declNode, maketreeWithVal(IDENTIFIER, -1));   /*insert identifier into table  (the index, ex in parser)*/
		            yyval.node = declNode;
	            }
break;
case 8:
#line 107 "src/parser.y"
	{
                  printf("%s\n", yystack.l_mark[-4].strval);
                  tree *arrayDeclNode = maketree(ARRAYDECL);
                  addChild(arrayDeclNode, yystack.l_mark[-5].node);
                  addChild(arrayDeclNode, maketreeWithVal(IDENTIFIER, -1));   /*insert identifier into table*/
                  addChild(arrayDeclNode, maketreeWithVal(INTEGER, yystack.l_mark[-2].value));      /*insert identifier into table*/
                  yyval.node = arrayDeclNode;
                }
break;
case 9:
#line 118 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(TYPESPEC, INT_TYPE);

                 }
break;
case 10:
#line 123 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(TYPESPEC, CHAR_TYPE);
                 }
break;
case 11:
#line 127 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(TYPESPEC, VOID_TYPE);
                 }
break;
case 12:
#line 133 "src/parser.y"
	{
                    int scope = 0;
                    int index = ST_insert(yystack.l_mark[-4].strval, yystack.l_mark[-5].node->val, FUNCTION, &scope);
                    tree* funDeclNode = maketree(FUNDECL);
                    addChild(funDeclNode, yystack.l_mark[-5].node);
                    tree* idNode = maketreeWithVal(IDENTIFIER, index);     /*same as above*/
                    addChild(funDeclNode, idNode);
                    addChild(funDeclNode, yystack.l_mark[-2].node);
                    addChild(funDeclNode, yystack.l_mark[0].node);
                    yyval.node = funDeclNode;
                 }
break;
case 13:
#line 145 "src/parser.y"
	{
                    int scope = 0;
                    int index = ST_insert(yystack.l_mark[-3].strval, yystack.l_mark[-4].node->val, FUNCTION, &scope);
                    tree* funDeclNode = maketree(FUNDECL);
                    addChild(funDeclNode, yystack.l_mark[-4].node);
                    tree* idNode = maketreeWithVal(IDENTIFIER, index);     /*same as above*/
                    addChild(funDeclNode, idNode);
                    addChild(funDeclNode, yystack.l_mark[0].node);
                    yyval.node = funDeclNode;
                 }
break;
case 14:
#line 158 "src/parser.y"
	{
                    tree* formalDeclListNode = maketree(FORMALDECLLIST);
                    addChild(formalDeclListNode, yystack.l_mark[0].node);
                    yyval.node = formalDeclListNode;
                 }
break;
case 15:
#line 164 "src/parser.y"
	{
                    tree* formalDeclListNode = maketree(FORMALDECLLIST);
                    addChild(formalDeclListNode, yystack.l_mark[-2].node);
                    addChild(formalDeclListNode, yystack.l_mark[0].node);
                    yyval.node = formalDeclListNode;
                 }
break;
case 16:
#line 173 "src/parser.y"
	{
                    tree* formalDeclNode = maketree(FORMALDECL);
                    addChild(formalDeclNode, yystack.l_mark[-1].node);
                    tree* idNode = maketreeWithVal(IDENTIFIER, yystack.l_mark[0].strval);
                    addChild(formalDeclNode, idNode);
                    yyval.node = formalDeclNode;
                 }
break;
case 17:
#line 181 "src/parser.y"
	{
                    tree* formalDeclNode = maketree(FORMALDECL);
                    addChild(formalDeclNode, yystack.l_mark[-3].node);
                    tree* idNode = maketreeWithVal(IDENTIFIER, yystack.l_mark[-2].strval);
                    addChild(formalDeclNode, idNode);
                    yyval.node = formalDeclNode;
                 }
break;
case 18:
#line 191 "src/parser.y"
	{
                    tree* funBodyNode = maketree(FUNBODY);
                    if(yystack.l_mark[-2].node != NULL){
                     addChild(funBodyNode, yystack.l_mark[-2].node);
                    }
                    if(yystack.l_mark[-1].node != NULL){
                     addChild(funBodyNode, yystack.l_mark[-1].node);
                    }
                    yyval.node = funBodyNode;
                 }
break;
case 19:
#line 204 "src/parser.y"
	{
                    yyval.node = NULL;

                 }
break;
case 20:
#line 209 "src/parser.y"
	{
                    tree* localDecList = maketree(LOCALDECLLIST);   /*create node*/
                    addChild(localDecList, yystack.l_mark[-1].node);                     /* add children*/
                    if(yystack.l_mark[0].node != NULL){
                     addChild(localDecList, yystack.l_mark[0].node);
                    }
                    yyval.node = localDecList;                              /* return value*/
                 }
break;
case 21:
#line 220 "src/parser.y"
	{
                    yyval.node = NULL;
                 }
break;
case 22:
#line 224 "src/parser.y"
	{
                    tree* statementList = maketree(STATEMENTLIST);
                    addChild(statementList, yystack.l_mark[-1].node);
                    if(yystack.l_mark[0].node != NULL){
                     addChild(statementList, yystack.l_mark[0].node);
                    }
                    yyval.node = statementList;                              /*correct to here     // make them return stuff  , $$ =*/
                 }
break;
case 23:
#line 235 "src/parser.y"
	{
                  tree* StmtNode = maketree(STATEMENT);
                  addChild(StmtNode, yystack.l_mark[0].node);
                  yyval.node = StmtNode;
                }
break;
case 24:
#line 241 "src/parser.y"
	{
                  tree* StmtNode = maketree(STATEMENT);
                  addChild(StmtNode, yystack.l_mark[0].node);
                  yyval.node = StmtNode;
                }
break;
case 25:
#line 247 "src/parser.y"
	{
                  tree* StmtNode = maketree(STATEMENT);
                  addChild(StmtNode, yystack.l_mark[0].node);
                  yyval.node = StmtNode;
                }
break;
case 26:
#line 253 "src/parser.y"
	{
                  tree* StmtNode = maketree(STATEMENT);
                  addChild(StmtNode, yystack.l_mark[0].node);
                  yyval.node = StmtNode;
                }
break;
case 27:
#line 259 "src/parser.y"
	{
                  tree* StmtNode = maketree(STATEMENT);
                  addChild(StmtNode, yystack.l_mark[0].node);
                  yyval.node = StmtNode;
                }
break;
case 28:
#line 267 "src/parser.y"
	{
		            tree* compoundStmtNode = maketree(COMPOUNDSTMT);
                  addChild(compoundStmtNode, yystack.l_mark[-1].node);
                  yyval.node = compoundStmtNode;
		          }
break;
case 29:
#line 275 "src/parser.y"
	{
		            tree *assignNode = maketree(ASSIGNSTMT);
		            addChild(assignNode, yystack.l_mark[-3].node);
                  addChild(assignNode, yystack.l_mark[-1].node);
		            yyval.node = assignNode;
	             }
break;
case 30:
#line 282 "src/parser.y"
	{
                  tree *assignNode = maketree(ASSIGNSTMT);
		            addChild(assignNode, yystack.l_mark[-1].node);
		            yyval.node = assignNode;
                }
break;
case 31:
#line 290 "src/parser.y"
	{
                  tree* condStmtNode = maketree(CONDSTMT);
                  addChild(condStmtNode, yystack.l_mark[-2].node);
                  addChild(condStmtNode, yystack.l_mark[0].node);
                  yyval.node = condStmtNode;
                }
break;
case 32:
#line 297 "src/parser.y"
	{
                  tree* condStmtNode = maketree(CONDSTMT);
                  addChild(condStmtNode, yystack.l_mark[-4].node);
                  addChild(condStmtNode, yystack.l_mark[-2].node);
                  addChild(condStmtNode, yystack.l_mark[0].node);
                  yyval.node = condStmtNode;
                }
break;
case 33:
#line 307 "src/parser.y"
	{
                  tree* loopStmtNode = maketree(LOOPSTMT);
                  addChild(loopStmtNode, yystack.l_mark[-2].node);
                  addChild(loopStmtNode, yystack.l_mark[0].node);
                  yyval.node = loopStmtNode;
                }
break;
case 34:
#line 316 "src/parser.y"
	{
                  tree* returnStmtNode = maketree(RETURNSTMT);
                  yyval.node = returnStmtNode;
                }
break;
case 35:
#line 321 "src/parser.y"
	{
                  tree* returnStmtNode = maketree(RETURNSTMT);
                  addChild(returnStmtNode, yystack.l_mark[-1].node);
                  yyval.node = returnStmtNode;
                }
break;
case 36:
#line 329 "src/parser.y"
	{
                    tree* varNode = maketree(VARIABLE);
                    symEntry* temp = ST_lookup(yystack.l_mark[0].strval);
                    if(temp == NULL){
                     yyerror("Undeclared Variable");
                    }
                    addChild(varNode, maketree(IDENTIFIER));
                    yyval.node = varNode;
                   }
break;
case 37:
#line 339 "src/parser.y"
	{
                    tree* varNode = maketree(VARIABLE);
                    symEntry* temp = ST_lookup(yystack.l_mark[-3].strval);                             
                    if(temp == NULL){
                     yyerror("Undeclared Variable");
                    }
                    addChild(varNode, maketree(IDENTIFIER));
                    addChild(varNode, yystack.l_mark[-1].node);
                    yyval.node = varNode;
                   }
break;
case 38:
#line 352 "src/parser.y"
	{
                  /*tree* exprNode = maketree(EXPRESSION);*/
                  /*addChild(exprNode, $1);*/
                  yyval.node = yystack.l_mark[0].node;
                 }
break;
case 39:
#line 358 "src/parser.y"
	{
                  tree* exprNode = maketree(EXPRESSION);
                  addChild(exprNode, yystack.l_mark[-2].node);
                  addChild(exprNode, yystack.l_mark[-1].node);
                  addChild(exprNode, yystack.l_mark[0].node);
                  yyval.node = exprNode;
                 }
break;
case 40:
#line 368 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, LTE);
                 }
break;
case 41:
#line 372 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, LT);
                 }
break;
case 42:
#line 376 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, GT);
                 }
break;
case 43:
#line 380 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, GTE);
                 }
break;
case 44:
#line 384 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, EQ);
                 }
break;
case 45:
#line 388 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(RELOP, NEQ);
                 }
break;
case 46:
#line 394 "src/parser.y"
	{
                  /*tree* addExprNode = maketree(ADDEXPR);*/
                  /*addChild(addExprNode, $1);*/
                  yyval.node = yystack.l_mark[0].node;
                 }
break;
case 47:
#line 400 "src/parser.y"
	{
                  if((yystack.l_mark[-2].node->nodeKind == INTEGER || yystack.l_mark[0].node->nodeKind == CHAR) && (yystack.l_mark[0].node->nodeKind == INTEGER || yystack.l_mark[0].node->nodeKind == CHAR)){
                     if(yystack.l_mark[-1].node->val == ADD){
                        yyval.node = maketreeWithVal(INTEGER, yystack.l_mark[-2].node->val + yystack.l_mark[0].node->val);
                     }
                     else{
                        yyval.node = maketreeWithVal(INTEGER, yystack.l_mark[-2].node->val - yystack.l_mark[0].node->val);
                     }
                  }
                  else{
                     tree* addExprNode = maketree(ADDEXPR);
                     addChild(addExprNode, yystack.l_mark[-2].node);
                     addChild(addExprNode, yystack.l_mark[-1].node);
                     addChild(addExprNode, yystack.l_mark[0].node);
                     yyval.node = addExprNode;
                  }
                 }
break;
case 48:
#line 420 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(ADDOP, ADD);
                 }
break;
case 49:
#line 424 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(ADDOP, SUB);
                 }
break;
case 50:
#line 430 "src/parser.y"
	{
                  /*tree* termNode = maketree(TERM);*/
                  /*addChild(termNode, $1);*/
                  yyval.node = yystack.l_mark[0].node;
                 }
break;
case 51:
#line 436 "src/parser.y"
	{
                  if((yystack.l_mark[-2].node->nodeKind == INTEGER || yystack.l_mark[0].node->nodeKind == CHAR) && (yystack.l_mark[0].node->nodeKind == INTEGER || yystack.l_mark[0].node->nodeKind == CHAR)){
                     if(yystack.l_mark[-1].node->val == MUL){
                        yyval.node = maketreeWithVal(INTEGER, yystack.l_mark[-2].node->val * yystack.l_mark[0].node->val);
                     }
                     else{
                        yyval.node = maketreeWithVal(INTEGER, yystack.l_mark[-2].node->val / yystack.l_mark[0].node->val);
                     }
                  }
                  else{
                     tree* termNode = maketree(TERM);
                     addChild(termNode, yystack.l_mark[-2].node);
                     addChild(termNode, yystack.l_mark[-1].node);
                     addChild(termNode, yystack.l_mark[0].node);
                     yyval.node = termNode;
                  }
                 }
break;
case 52:
#line 456 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(MULOP, MUL);
                 }
break;
case 53:
#line 460 "src/parser.y"
	{
                    yyval.node = maketreeWithVal(MULOP, DIV);
                 }
break;
case 54:
#line 466 "src/parser.y"
	{
                     /*tree* factorNode = maketree(FACTOR);*/
                     /*addChild(factorNode, $2);*/
                     yyval.node = yystack.l_mark[-1].node;
                 }
break;
case 55:
#line 472 "src/parser.y"
	{
                     /*tree* factorNode = maketree(FACTOR);*/
                     /*addChild(factorNode, $1);*/
                     yyval.node = yystack.l_mark[0].node;
                 }
break;
case 56:
#line 478 "src/parser.y"
	{
                     /*tree* factorNode = maketree(FACTOR);*/
                     /*addChild(factorNode, $1);*/
                     yyval.node = yystack.l_mark[0].node;
                 }
break;
case 57:
#line 484 "src/parser.y"
	{
                     /*tree* factorNode = maketree(FACTOR);*/
                     tree* intNode = maketreeWithVal(INTEGER, yystack.l_mark[0].value);          
                     /*addChild(factorNode, intNode);*/
                     yyval.node = intNode;
                 }
break;
case 58:
#line 491 "src/parser.y"
	{
                     /*tree* factorNode = maketree(FACTOR);*/
                     tree* charNode = maketreeWithVal(CHAR, yystack.l_mark[0].value);
                     /*addChild(factorNode, charNode);*/
                     yyval.node = charNode;
                 }
break;
case 59:
#line 500 "src/parser.y"
	{
                    tree* funcCallNode = maketree(FUNCCALLEXPR);
                    symEntry* temp = ST_lookup(yystack.l_mark[-3].strval);
                    if(temp == NULL){
                     yyerror("Undeclared function");
                    }
                    else if(temp->size < yystack.l_mark[-1].node->numChildren){
                     yyerror("Too many arguments");
                    }
                    else if(temp->size > yystack.l_mark[-1].node->numChildren){
                     yyerror("Too few arguments");
                    }
                    /*if(functionDecl == -1){*/
                     /*yyerror("Incorrect number of arguments");*/
                    /*}*/
                    addChild(funcCallNode, maketreeWithVal(IDENTIFIER, yystack.l_mark[-3].strval));
                    addChild(funcCallNode, yystack.l_mark[-1].node); /* Arguments*/
                    yyval.node = funcCallNode;
                 }
break;
case 60:
#line 520 "src/parser.y"
	{
                    tree* funcCallNode = maketree(FUNCCALLEXPR);
                    symEntry* temp = ST_lookup(yystack.l_mark[-2].strval);
                    if(temp == NULL){
                     yyerror("Undeclared function");
                    }
                    addChild(funcCallNode, maketreeWithVal(IDENTIFIER, yystack.l_mark[-2].strval));
                    yyval.node = funcCallNode; /* No arguments*/
                 }
break;
case 61:
#line 532 "src/parser.y"
	{
                  tree* argListNode = maketree(ARGLIST);
                  addChild(argListNode, yystack.l_mark[0].node);
                  yyval.node = argListNode;
                 }
break;
case 62:
#line 538 "src/parser.y"
	{
                  /*tree* argListNode = maketree(ARGLIST); */
                  /*addChild(argListNode, $1);*/
                  /*addChild(argListNode, $3);*/
                  /*$$ = argListNode;*/

                  addChild(yystack.l_mark[-2].node, yystack.l_mark[0].node);
                  yyval.node = yystack.l_mark[-2].node;
                 }
break;
#line 1154 "obj/y.tab.c"
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
