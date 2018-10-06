  /* Copyright (C) 2017-2018 Free Software Foundation, Inc.
    Created by Marwen : 05/03/2017.
   */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
 #define Max_ligne 1000
 #define Max_UL 20
 #define nbreVar 200
   int LU=0; //LU = 1: a LU is detected
 extern int errno;
 int row=1,col=1;//la ligne et la colonne actuelle
 int etat=0; //L'etat actuelle du AF
 typedef struct sym
 {char* att;
  char* UL;
 }symbole;
  typedef struct varId
  {int num;
  float val;
  char* lexeme;
  char* type;
  }varId;
 /* This function return 0 if a lexical unit detected 1 otherwise
    @arg1 :Structure contain th LU and an att 
    @arg2 :The current char just readed 
 */
  void Analex(FILE*,symbole *, int);
  int RangerId(char ch[]); 
//This function return 1 if the ch is a key word 0 if it is a varName
  int UniLexId(char *ch);
  void Erreur();
  int isletter(int c)
   {
    if ((c>=97 && c <=122)||(c>64 && c<91))
      return 1;
    else return 0;
   }
   int isDigit(int c)
   { int x = c-48;
     if (x>=0 && x<=9)
      return 1;
     else return 0;
   }
      //Global variables
   const char* MotsCle[3]={"var","entier","reel"};
   varId tab[nbreVar];   
    int c=0;    //  =>retourner le caractere lu  =-1(eol)
    int nbreMot=0;
    char aux[2];
     int nbreVarAct=0; 
int main(int argc,char *argv[])  
{/*puts("   °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°") ;
puts( "   °°°°°                  ANALYSEUR LEXICAL                    °°°°°°°°°°°°°°°°°") ;
puts( "   °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°") ;
printf("\n\n");*/

   FILE* prog=NULL;
  prog=fopen("code_Src.txt","r");
 
  char inst[Max_ligne];
  int i,l;
  char*m[2][90]={"9999"}; //For Sem. Analyse
  for(l=0;l<2;l++)
   for(i=0;i<90;i++)
     m[l][i]=malloc(sizeof(char*));
  int j=-1;
  symbole *sym;
   sym=malloc(sizeof(symbole));
   sym->UL=malloc(10*sizeof(char));
   sym->att=malloc(10*sizeof(char));
  if (prog != NULL)
    {
     while((c=fgetc(prog)) != EOF )    //EOF <=> finDuProg==NULL
      {
        if(c == '\n') {
        col=1;row++;nbreMot++;}
        else
        {
         Analex(prog,sym,c);
         if( LU == 1 )   {LU = 0;					
           m[0][++j]=sym->UL;				//Remplir le table de l'ASem
           m[1][j]=sym->att;
           printf("le nouveau Ul est: %s\n",m[0][j]);
           }
        free(sym);
	    sym=malloc(sizeof(symbole));
	    sym->UL=malloc(sizeof(char*));
	    sym->att=malloc(sizeof(char*));
        }
         			//Passer instruction par inst au AS puis au ASem
      }
   fclose(prog);
   free(sym);
  }
  else
   { puts("Erreur d'ouverture :");
      perror("prog");
    }
   puts("");
   puts("   Voila l'affichage finale *******");
    for(l=0;l<2;l++)
    {  for(i=0;i<=j;i++)
       printf("%s\t",m[l][i]);
    printf("\n\n");
    }
return 0;
} //fin du main()

 void Analex(FILE* prog,symbole *s, int car)
 {//printf("%c\t%d\t%d\t%d\n",car,row,col,etat);
  int n;
 while( !LU )
 {    switch(etat)
         {
         case 0: if ( (car == ' ') || (car == '\t') ) {nbreMot++;  LU = 0; }//UL n'est pas complete 
                 else if( isletter(car) )
                   {etat = 1;s->UL[0]=car;  LU = 0;} //UL n'est pas complete }
                 else if( isDigit(car) )
                   {etat = 3;s->att[0] = car; s->UL = "Nb";  LU = 0; }//UL n'est pas complete }
                 else if( car == ':') {etat = 5;  LU = 0; }//UL n'est pas complete 
                 else if (car == '+')
                  {s->att = "+"; s->UL = "Add";  LU = 1;}
                 else if (car == '*')
                  {s->att = "*"; s->UL = "Mul";  LU = 1;}
                 else if (car == '-')
                  {s->att = "-"; s->UL = "Sub";  LU = 1;}
                 else if (car == '/')
                  {s->att = "/"; s->UL = "DivR"; LU = 1;}
                 else if (car == '%')
                  {s->att = "%"; s->UL = "Mod";  LU = 1;}
                  else if (car == ';')
                  {s->att = ";"; s->UL = "PV";   LU = 1;}
                 else if (car == '(')
                  {s->att = "("; s->UL = "POv";  LU = 1;}
                 else if (car == ')')
                  {s->att = ")"; s->UL = "PFe";  LU = 1;}
                 else if (car == EOF) 
                  {s->att = "0"; s->UL = "EOF";  LU = 1;}         
                 else {Erreur();etat=0;  LU = 0; }//UL n'est pas complete }
            break;
         case 1: aux[0]=car;
                   if( (isletter(car)) || (isDigit(car)) || car=='_' )
                      {strncat(s->UL,aux,1); LU = 0;}       //UL n'est pas complete
                   else if (car == ',')//New variable is possible to be declared 
                     { if( UniLexId(s->UL) ) {Erreur();etat=0; LU = 1;}//Pas de virgule aprés mot clé
                       else 
                       { n = RangerId(s->UL);  sprintf(s->att, "%d", n);
                       s->UL="id"; etat=0; LU = 1; //Register the LU detected without register the ','
                       }
                      }
                   else
                    {if( UniLexId(s->UL) ) s->att="0";
                     else {s->UL="id";  n= RangerId(s->UL); sprintf(s->att, "%d", n);} //convertir int->char*
                     ungetc(car,prog);etat=0;  LU = 1; 
                    }
             break;
	      case 3:aux[0]=car;
	           if(isDigit(car))
                      {strncat(s->att,aux,1);  LU = 0;}
               else if(car == '.')  // cas d'un flottant
                        { if( index(s->att,'.') != NULL )  //Le nb contient déja un '.'
                         {Erreur();   LU = 1;}
                          else 
                          {strncat(s->att,aux,1);car=fgetc(prog);
                            if(isDigit(car))
                             {strncat(s->att,aux,1);  LU = 0 ;}
                            else  //par exmple 12.;
                             {strncpy(s->att,s->att,strlen(s->att)-1);//Eliminer le dernier .
                             puts("A number is expected here! ");Erreur();  LU = 1;}
                          }
                        }
                else
                 {etat=0; ungetc(car,prog);   LU = 1;
                 }
              break;
            case 5:if (car == ':')
                  { s->att = "::"; s->UL = "DivE";}
                  else if (car == '=')
                  { s->att = ":="; s->UL = "OppAff";}
                  else
                  {ungetc(car,prog); s->att = ":"; s->UL = "2Pnts";}
               etat=0;  LU = 1;
             break;         
        }
    if( LU == 1 ) break;
    else 
     {aux[0]=car;
      car = getc(prog);
      if( car == '\n' ) //fin de ligne et l'UL n'est pas complet
      {s->UL = (strlen(s->UL)> 0 )?s->UL:aux; //utile le cas il y a ':' à la fin de ligne
      printf("LU %s is not recognized \n",s->UL);Erreur();
       break;}
     }
  }
  //return s;
 }
int RangerId(char *ch)
  {int indice=0;
  for (indice=0;indice < nbreVarAct;indice++)
     if(tab[indice].lexeme == ch)
        return indice+1;
  tab[nbreVarAct].val=-1;//Ce champ va etre remplie durant l'analyse sémantique:Les variables sont initialisées à 0;
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
 void Erreur()
 {
 printf("\nErreur :caractére inattendu! at ligne: %d ,colonne: %d \n",row,col);
 }
