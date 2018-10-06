%{ 
extern int lineNumber; // definie dans prog.y, utilise par notre code pour \n
int nbCol;
 void yyerror(char const * msg); // definie dans prog.y, utilise par notre code pour .
#include "test.hpp" // genere par prog.y --> constantes START, END ...
%}
%option noyywrap
integer [0-9]+
real [0-9]+\.[0-9]*|\.[0-9]+
ident [a-zA-Z_][0-9a-zA-Z_]*
Op    [:]+[=:]|[/*-+%]
Nb    {integer}|{real}
%%
"var" { return(Var); }
"entier" { return(Entier); }
"Reel" { return(Reel); }
":=" {nbCol+=yyleng; return(Assign); }
";" {++nbCol; return(Semicolon); }
"," {++nbCol; return Virgule; }
"(" {++nbCol; return PO; }
")" {++nbCol; return PF; }


":"  {++nbCol; return Pnts;}


"\n" { ++lineNumber;nbCol=0; }
[ \t]+ {++nbCol; /* nothing to be done */ }
. { char msg[0x20]; sprintf(msg,"lexical error <%s>",yytext); yyerror(msg); }
{Nb} {nbCol+=yyleng; return(Nb); }
{ident} {nbCol+=yyleng; return(Ident); }
{Op}  {return Op; }
%%



