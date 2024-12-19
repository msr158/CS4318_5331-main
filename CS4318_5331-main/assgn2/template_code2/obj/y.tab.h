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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
{
    int value;
    struct treenode *node;
    char *strval;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
