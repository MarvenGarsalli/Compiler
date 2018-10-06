  /* Copyright (C) 2017-2018 Free Software Foundation, Inc.
    Created by Marwen : 05/03/2017.
    Without Semantic Analyse !! 
   */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

 #define Max_ligne 1000
 #define Max_UL 20
 #define nbreVar 200
   int Error = 0;//Le cas :il n'y a pas d'erreur
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
  void* Analex(FILE*,symbole *, int);
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
  //  		Les Données necassaire à l'Analye syntaxique 
  	  symbole *sym;
  	  FILE* prog=NULL;
  	  int j=-1;
  	 char*m[2][90]={"9999"}; //For Sem. Analyse
  void calcul();
  void L_DCL();
  void L_I();
  void DCL();
  void A();
  void TYPE();
  void L_ID(); 
  void B();
  void I();
  void C();
  void E();
  void D();
  
int main(int argc,char *argv[])  
{puts("      °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°") ;
puts( "      °°°°°                  ANALYSEUR LEXICAL & SANTAXIQUE       °°°°°°°°°°°°°°°°°") ;
puts( "      °°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°") ;
printf("\n\n");

  prog=fopen("code_Src.txt","r");
 
  char inst[Max_ligne];
  int i,l;
  for(l=0;l<2;l++)
   for(i=0;i<90;i++)
     m[l][i]=malloc(sizeof(char*));
   sym=malloc(sizeof(symbole));
   sym->UL=malloc(10*sizeof(char));
   sym->att=malloc(10*sizeof(char));
  if (prog != NULL)
    {
     while((c=fgetc(prog)) != EOF )    
      {
        if(c == '\n') {
        col=1;row++;nbreMot++;}
        else
        {
          Analex(prog,sym,c);
          calcul();
        }
      }
   fclose(prog);
   free(sym);
  }
  else
   { puts("Erreur d'ouverture :");
      perror("prog");
    }
   puts("\n   Voila l'affichage finale *******");
    			/*for(l=0;l<2;l++) {  for(i=0;i<=j;i++) printf("%s\t",m[l][i]); printf("\n\n");   }*/
     for(i=0;i<=j;i++)   //Pour un affichage structuré
       printf("%s\t",m[0][i]);
     printf("\n\n");
       for(i=0;i<=j;i++)
       printf("%s\t  ",m[1][i]);
     printf("\n\n");
return 0;
} //fin du main()

 void* Analex(FILE* prog,symbole *s, int car)
 {
  int n;
 while( !LU )
 {    switch(etat)
         {
         case 0: while( car == '\n' ) { LU = 0;col=1;row++; car = fgetc(prog);  /*return NULL;*/ }
                 if ( (car == ' ') || (car == '\t') ) { LU = 0; }//UL n'est pas complete 
                 else if( isletter(car) )
                   {etat = 1;s->UL[0]=car;  LU = 0;} //UL n'est pas complete }
                 else if( isDigit(car) )
                   {etat = 3;s->att[0] = car; s->UL = "Nb";  LU = 0; }//UL n'est pas complete }
                 else if( car == ':') {etat = 5;  LU = 0; }//UL n'est pas complete 
                 else if (car == ',')
                  {s->att = ","; s->UL = "Vg";  LU = 1;}
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
               nbreMot++;
            break;
         case 1: aux[0]=car;
                   if( (isletter(car)) || (isDigit(car)) || car=='_' )
                      {strncat(s->UL,aux,1); LU = 0;}       //UL n'est pas complete
                   else if (car == ',')//New variable is possible to be declared 
                     {nbreMot++;
                       if( UniLexId(s->UL) ) {Erreur();etat=0; LU = 1;}//Pas de virgule aprés mot clé
                       else 
                       { n = RangerId(s->UL);  sprintf(s->att, "%d", n);   ungetc(car,prog);col--;
                       s->UL="id"; etat=0; LU = 1; //Register the LU detected without register the ','
                       }
                      }
                   else
                    {if( UniLexId(s->UL) ) s->att="0";
                     else {n= RangerId(s->UL); sprintf(s->att, "%d", n);s->UL="id";  } //convertir int->char*
                    ungetc(car,prog);col--;etat=0;  LU = 1; 
                    }
             break;
	      case 3:aux[0]=car;
	           if(isDigit(car))
                      {strncat(s->att,aux,1);  LU = 0;}
               else if(car == '.')  // cas d'un flottant
                        { if( index(s->att,'.') != NULL )  //Le nb contient déja un '.'
                             {Erreur();   LU = 1;}
                         else 
                           {strncat(s->att,aux,1);car=fgetc(prog);col++;
                            if(isDigit(car))
                             {aux[0]=car;strncat(s->att,aux,1);  LU = 0 ;}
                            else  //par exmple 12.;
                             {strncpy(s->att,s->att,strlen(s->att)-1);//Eliminer le dernier .
                             puts("A number is expected here! ");Erreur();  LU = 1;}
                          }
                        }
                else
                 {etat=0; ungetc(car,prog);col--;   LU = 1;
                 }
              break;
            case 5:if (car == ':')
                  { s->att = "::"; s->UL = "DivE";}
                  else if (car == '=')
                  { s->att = ":="; s->UL = "OpAff";}
                  else
                  {ungetc(car,prog);col--; s->att = ":"; s->UL = "2Pnts";}
               etat=0;  LU = 1;
             break;         
        }
    if( LU == 1 ) break;
    else 
     {aux[0]=car;
      car = fgetc(prog);col++;
      if( car == '\n' ) //fin de ligne et l'UL n'est pas complet
       {s->UL = (strlen(s->UL)> 0 )?s->UL:aux; //utile le cas il y a ':' à la fin de ligne
       printf("LU %s is not recognized \n",s->UL);Erreur();break;
       }
     }
  }
  //return s;
 }
int RangerId(char *ch)
  {int indice=0;
  for (indice=0;indice < nbreVarAct;indice++)
     if( !strcmp(tab[indice].lexeme,ch) )
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
 {Error = 1;
 printf("\nErreur :caractére inattendu! at ligne: %d ,colonne: %d \n",row,col);
 }
	  //############## L'implementation des fonctions ANALYSEUR SYNATAXIQUE  #################
  void ErreurSyntaxique(char *s)
 {Error = 1;
 printf("Erreur :caractére inattendu! at ligne: %d ,colonne: %d \n",row,col-(int)strlen(sym->UL) );
 printf("Syntaxic error:May be '%s' is expected.",s);
 }	  
  void* accepter(char *s)
  {
  if( !(strcmp(sym->UL,s) ) )
     {//printf("\n\tSymbole actuel correct:\t%s\n",sym->UL);
 					                      //do { //Alternative pour la recuperation sur erreur : parcourir les UL jusqu'à trouver sym->UL == s 
     if( LU == 1 )   {LU = 0;					
       m[0][++j]=sym->UL;				
       m[1][j]=sym->att;
       }
    free(sym);  //Pour eviter segmentation fault: Pour reutiliser une @ il faut comme ça
    sym=malloc(sizeof(symbole));
    sym->UL=malloc(sizeof(char*));
    sym->att=malloc(sizeof(char*));
     c=fgetc(prog);col++;
      Analex(prog,sym,c);
     printf("\n\tSymbole suivant:\t%s\n",sym->UL);
      if(sym->UL == "EOF")
      {puts( "\n\n   °°°°°°°°°                  SUCCESS SA finish                  °°°°°°°°°°°°°°°°°");return 0; }
     }  					                         //}while(sym->UL != s ); 
  else if( sym->UL != "EOF" )
    ErreurSyntaxique(s); 
    }
  void calcul() {
  L_DCL();
  L_I();
  }
  void L_DCL() {
  DCL();
  A();
  }
  void DCL()  {
  if( !(strcmp(sym->UL,"var") && (sym->UL != "EOF")) )
   {accepter("var");
    L_ID(); 
    accepter("2Pnts");
    TYPE();
    accepter("PV");
   }
   else if(sym->UL != "EOF")
   { printf("Syntaxic error DCL(): %s at ligne: %d ,colonne: %d \n",sym->UL,row,col); }
  }
  void A()  {
    if( !(strcmp(sym->UL,"var")) )  // nouvelle declaration est possible
      L_DCL();
  }
  void L_ID() {
   if( !(strcmp(sym->UL,"id")) )
     { accepter("id"); B(); }
   else if(sym->UL != "EOF")
     {printf("Syntaxic error L_ID(): %s at ligne: %d ,colonne: %d \n",sym->UL,row,col); }
  }
  void B() {
   if( !(strcmp(sym->UL,"Vg")) )  //Declaration of new var is possible
     { accepter("Vg"); L_ID(); }
  }
  void L_I()  {
    I();
    C();
  }
  void I() {
   if( !(strcmp(sym->UL,"id")) )
    { accepter("id"); accepter("OpAff");E();accepter("PV"); }
   else if(sym->UL != "EOF")
    {printf("Syntaxic error DCL(): %s at ligne: %d ,colonne: %d \n",sym->UL,row,col-(int)strlen(sym->UL)); }
  }
  void C() {
   if( !(strcmp(sym->UL,"id")) )  //Nouvelle affectation possible
    L_I();
  }
  void TYPE() {   //entier reel sont définies comme mots clés
   if( !(strcmp(sym->UL,"entier")) )
    accepter("entier");
   else if( !(strcmp(sym->UL,"reel")) )
    accepter("reel");
   else if(sym->UL != "EOF")
     {printf("Syntaxic error TYPE(): %s at ligne: %d ,colonne: %d \n",sym->UL,row,col-(int)strlen(sym->UL)); }
   }
  void E() {
    if( !(strcmp(sym->UL,"id")) )
     {accepter("id"); D();}
    else if( !(strcmp(sym->UL,"Nb")) )
     {accepter("Nb"); D();}
    else if( !(strcmp(sym->UL,"PO")) )
     {accepter("PO"); E(); accepter("PF");D(); }
    else if(sym->UL != "EOF")
     {printf("Syntaxic error E(): %s at ligne: %d ,colonne: %d \n",sym->UL,row,col-(int)strlen(sym->UL)); }
  }
  void D() {
    if( !(strcmp(sym->UL,"Add")) )
     {accepter("Add"); E(); D();}
    else if( !(strcmp(sym->UL,"Sub")) )
     {accepter("Sub"); E(); D();}
    else if( !(strcmp(sym->UL,"Mul")) )
     {accepter("Mul"); E(); D();}
    else if( !(strcmp(sym->UL,"DivR")) )
     {accepter("DivR"); E(); D();}
    else if( !(strcmp(sym->UL,"DivE")) )
     {accepter("DivE"); E(); D();}
    else if( !(strcmp(sym->UL,"Mod")) )
     {accepter("Mod"); E(); D();}
    else
     {}
  }
