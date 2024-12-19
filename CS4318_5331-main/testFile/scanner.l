 
 
 /* definitions */

%{
#include<stdio.h>
#include "tokendef.h"

 /* variables declared */
int scancol = 1;
int yycol = 1;
int scanlineno = 1;
int i = 0;

char* yyerror;

void updateCol();              
void countLines(); 
int processString(); 
%}

 
newline         \n              
whitespace      [ \t]+         
integer         0[1-9][0-9]*   
integerlead0  0[0-9]+
character       \'([^\']|\\[\\nt\'])\'         

 /* String can contain any characters between the double quotes other than a newline or
 // unescaped doublequotes.
 */
string       \"(\\\"|[^\n\"])*\"                     

 /* multiline string has \n somewhere in the middle */
multlnstring \"(\\\"|[^\"])*\n(\\\"|[^\"])*\"            

 /* If the end quote is found, one of the two regexes above will be matched. Otherwise,
 // the string is unterminated.
 */
untermstring \"(\\\"|[^\n\"])*          

 /* matches single-line comments */
comment   \/\*(.)*\*\/      
 /*matches multlncomment */
multlncomment   \/\*(.|\n)*\*\/      
 /* identifies a unterminated comment */
untermcomment   \/\*(.|\n)*
 /*matches valid identifiers */ 
identifier      [a-zA-Z][a-zA-Z0-9]*          
 /* identifies illegal identifiers */ 
illidentifier   [0-9]+[a-zA-Z][a-zA-Z0-9]*     

yylineno = 1;

%%

 /* rules */
 /* Keywords */;
 /* reserved key words that are returned if read */
"if" { updateCol(); return KWD_IF; }
"else" { updateCol(); return KWD_ELSE; }
"while" { updateCol(); return KWD_WHILE; }
"int" { updateCol(); return KWD_INT; }
"string" { updateCol(); return KWD_STRING; }
"char" { updateCol(); return KWD_CHAR; }
"return" { updateCol(); return KWD_RETURN; }
"void" { updateCol(); return KWD_VOID; }

 /* Operators */;
 /* returns a seperate token for each symbol */

\+ { updateCol(); return OPER_ADD; }
\- { updateCol(); return OPER_SUB; }
\* { updateCol(); return OPER_MUL; }
\/ { updateCol(); return OPER_DIV; }
\% { updateCol(); return OPER_MOD; }
\< { updateCol(); return OPER_LT; }
\> { updateCol(); return OPER_GT; }
\>= { updateCol(); return OPER_GTE; }
\<= { updateCol(); return OPER_LTE; }
\== { updateCol(); return OPER_EQ; }
\!= { updateCol(); return OPER_NEQ; }
\= { updateCol(); return OPER_ASGN; }
\[ { updateCol(); return LSQ_BRKT; }
\] { updateCol(); return RSQ_BRKT; }
\{ { updateCol(); return LCRLY_BRKT; }
\} { updateCol(); return RCRLY_BRKT; }
\( { updateCol(); return LPAREN; }
\) { updateCol(); return RPAREN; }
\, { updateCol(); return COMMA; }
\; { updateCol(); return SEMICLN; }
\@ { updateCol(); return OPER_AT; }
\+\+ { updateCol(); return OPER_INC; } 
\-\- { updateCol(); return OPER_DEC; }
\&& { updateCol(); return OPER_AND; }
\|\| { updateCol(); return OPER_OR; }
\! { updateCol(); return OPER_NOT; }

 /* Identifiers */;
 /* begins with uppercase or lowercase letter */
{identifier}    { updateCol(); return ID; }                           
{illidentifier} { yyerror = "Illegal identifier"; return ERROR; }   

 /* Constants */;
 /* int, char, and string contstants */ 
{integer}       { updateCol(); return INTCONST; }                                  
{integerlead0}  { yyerror = "Integers may not have leading zeros"; return ERROR; }   
{character}     { updateCol(); return CHARCONST; }                                  
{string}        { updateCol(); return processString(); }
{untermstring}  { updateCol(); yyerror = "Unterminated string"; return ERROR; }
{multlnstring}  { updateCol(); countLines(); yyerror = "String spans multiple lines"; return ERROR; }

 /* Comments */;
 /* sequence of symbols enclosed within pair of symbols */ 
{comment}       { updateCol(); }                     
{untermcomment} { yyerror = "Unterminated comment"; return ERROR; }    
{multlncomment} { updateCol(); countLines();  /*Skip multi-line comment*/  }         

 /* Other */;
 /* scanner does nothing when theres newline, tab, or space */ 
{newline}       { scanlineno++; yylineno = scanlineno;  scancol = 1; }                               
{whitespace}    { updateCol(); /* skip whitespace */ }      
.               { return ILLEGAL_TOK; }

%%

 /* user routines */
 
 /* function to update column count */
void updateCol(){
        yycol = scancol;
        scancol += yyleng;           
}
 /* function to update line count */
void countLines(){
        yylineno = scanlineno;
        for(i = 0; i < yyleng; i++){
            if(yytext[i] == '\n'){
                scanlineno++;
            }
        }          
}

 /* function to process string */ 
int processString(){
    /*for (int p = 0; while p < yyleng; p++) {
        if (*p == '\\') {
            p++;  // Skip over escape character
            if (!(*p == 'n' || *p == 't' || *p == '\\' || *p == '\"')) {
                yyerror = "Illegal escape sequence";
                return ERROR;
            }
        }
    } */
    return STRCONST;
}                                  
