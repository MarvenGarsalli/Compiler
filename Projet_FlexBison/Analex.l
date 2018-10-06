%{
#include <stdlib.h>
#include "AS.h"
#define nbreVar 200  //Nombre des variables 
	int RangerId(char *ch);
	int UniLexId(char *ch);
	void yyerror(const char * msg); // definie dans AS.y, utilise par notre code pour .
	int lineNumber; 

int nbreVarAct=0; 
char* m[2][90]={"9999"};
const char* MotsCle[3]={"var","entier","reel"};
  typedef struct varId
  {int num;
  float val;
  char* lexeme;
  char* type;
  }varId;
 varId tab[nbreVar];	int nbCol;
%}

%option noyywrap
integer [0-9]+
real [0-9]+\.[0-9]*|\.[0-9]+
ident [a-zA-Z_][0-9a-zA-Z_]*
Op    [:]+[=:]|[/*-+%]
Nb    {integer}|{real}

%%
{Nb} {nbCol+=yyleng; return(Nb); }
{ident} {nbCol+=yyleng; return(Ident); }
":=" {nbCol+=yyleng; return(Assign); }
";" {++nbCol; return(Semicolon); }
"," {++nbCol; return Virgule; }
"(" {++nbCol; return PO; }
")" {++nbCol; return PF; }
"+"  {++nbCol; return(Plus); }
"-"  {++nbCol; return(Minus); }
"*"  {++nbCol; return(Mult); }
"/"  {++nbCol; return(DivR); }
":"  {++nbCol; return Pnts;}
"::" {nbCol+=yyleng; return DivE;}
"%"  {nbCol++; return Mod;}
"\n" { ++lineNumber;nbCol=0; }
[ \t]+ {++nbCol; /* nothing to be done */ }
. { char msg[0x20]; sprintf(msg,"lexical error <%s>",yytext); yyerror(msg); }
%%
/*
int RangerId(char *ch)
  {int indice=0;
  for (indice=0;indice < nbreVarAct;indice++)
     if(tab[indice].lexeme == ch)
        return indice+1;
  tab[nbreVarAct].val=-1;
  tab[nbreVarAct].lexeme=malloc(sizeof(char*));
  tab[nbreVarAct].lexeme=ch;
  tab[nbreVarAct].type=malloc(sizeof(char*));
  tab[nbreVarAct].type="";
  tab[nbreVarAct].num=++nbreVarAct;
  return  nbreVarAct; 
  }
int UniLexId(char *ch)
  {int i;
  for(i=0;i<3;i++)
     if( !(strcmp(ch,MotsCle[i])) )
      return 1;
  return 0; 
  }
int main(int argc,char* argv[])
{if(argc < 2 )  {puts("Veuiller entrer le fichier code_src à compiler"); return -1;}
 else yyin=fopen(argv[1],"r");
 lineNumber=1;nbCol=1;
 
int result,l,c;
   for(l=0;l<2;l++)
   for(c=0;c<90;c++)
     m[l][c]=malloc(sizeof(char*));
     c=0;
 while(result=yylex())
  switch(result)
  {case Nb:fprintf(stderr,"Nb [%s]\n",yytext);m[0][c]="nb";m[1][c]=yytext; break;
  case Ident:fprintf(stderr,"IDENT [%s]\n",yytext); 
  		if(UnilexId(yytext)) {m[0][c]=yytext;m[1][c]="0";}	  
  		else {m[0][c]="id";n = RangerId(s->UL);s->UL="id";  sprintf(s->att, "%d", n);} 
  break;
  case Plus:fprintf(stderr,"Plus [%s]\n",yytext);m[0][c]="Add";m[1][c]=yytext; break;
  case Minus:fprintf(stderr,"Minus [%s]\n",yytext);m[0][c]="Minus";m[1][c]=yytext; break;
  case Mult:fprintf(stderr,"Mult [%s]\n",yytext);m[0][c]="Mult";m[1][c]=yytext; break;
  case DivR:fprintf(stderr,"DivR [%s]\n",yytext);m[0][c]="DivR";m[1][c]=yytext; break;
  case DivE:fprintf(stderr,"DivE [%s]\n",yytext);m[0][c]="DivE";m[1][c]=yytext; break;
  case Mod:fprintf(stderr,"Mod [%s]\n",yytext);m[0][c]="Mod";m[1][c]=yytext; break;
  case Semicolon:fprintf(stderr,"Semicolon [%s]\n",yytext);m[0][c]="Semicolon";m[1][c]=yytext; break;
  case PO:fprintf(stderr,"PO [%s]\n",yytext);m[0][c]="PO";m[1][c]=yytext; break;
  case PF:fprintf(stderr,"PF [%s]\n",yytext);m[0][c]="PF";m[1][c]=yytext; break;
  case Assign:fprintf(stderr,"Assign [%s] \n",yytext);m[0][c]="Assign";m[1][c]=yytext; break;
  }
puts("*********** Fin de l'ANALYSEUR LEXICAL **************");
return 0; 
}
*/
