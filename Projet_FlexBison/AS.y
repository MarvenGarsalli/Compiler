%{ 
#include <stdio.h>
#include <stdlib.h>
extern int lineNumber;

 extern FILE * yyin;
 void yyerror(char const * msg);
%}
%token Nb Plus Minus Mult DivR DivE Semicolon Virgule PO PF Mod Assign Ident Op Pnts
%token Var Entier Reel 
%start calcul

%%
calcul : L_DCL L_I ;
L_DCL : DCL A ;
A : L_DCL | ;
DCL : Var L_ID Pnts TYPE ;
L_ID : Ident B ;
B : Virgule L_ID | ;
TYPE : Entier  | Reel ;
L_I : I C ;
C : L_I | ;
I : Ident Assign E ;
E : Nb | Ident | PO E PF | E Op E  ;
%%

void yyerror(char const * msg)
  {
  printf("line: %d ; %s\n",lineNumber,msg );
  }
int main(int argc,char* argv[])
{if(argc < 2 )  {puts("Veuiller entrer le fichier code_src à compiler"); return -1;}
 else yyin=fopen(argv[1],"r");
 lineNumber=1;

puts("*********** Début de l'ANALYSEUR Syntaxique **************");
  if(!yyparse()) 
   puts( "   °°°°°                  SUCCESS                    °°°°°°°°°°°°°°°°°") ;
return 0;
}
