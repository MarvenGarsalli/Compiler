%{ /*-------- prog.y --------*/
#include <stdio.h>
#include <iostream>
using namespace std;
int yylex(void);
// defini dans progL.cpp, utilise par yyparse()
void yyerror(const char * msg); // defini plus loin, utilise par yyparse()
int lineNumber;   // notre compteur de lignes
extern FILE * yyin; // defini dans progL.cpp, utilise par main()
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
void yyerror(const char * msg)
{
cerr << "line " << lineNumber << ": " << msg << endl;
}
int main(int argc,char ** argv)
{
if(argc>1) yyin=fopen(argv[1],"r"); // check result !!!
lineNumber=1;
if(!yyparse()) cerr << "Success" << endl;
return(0);
}
