#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

void main()
{ /*FILE* prog=NULL;
  prog=fopen("code_Src.txt","r");
   int c,i,l;
  while((c=fgetc(prog)) != EOF)
   {if(c == '\n') puts("eol"); 
      printf("%c\t",c);
      }
      int j=0;
      char*m[2][90]={"9999"}; //For Sem. Analyse
  for(l=0;l<2;l++)
   for(i=0;i<90;i++)
     m[l][i]=malloc(sizeof(char*));
   m[0][++j]="tet";
   printf("le nouveau Ul est: %s\n",m[0][0]);*/
  char *ch,*aux;
  ch=malloc(sizeof(char*));
    aux=malloc(sizeof(char*));
  ch="102";
  aux = (strlen(aux)> 0)?aux:ch;
   printf("%s\n",aux);
  ch="5464.sd";
   printf("%s\n",ch);
   /*int pos=*strchr(ch,'4');
    printf("%d\n",pos);
 strncpy(ch,ch,pos);
  if (prog != NULL){
  printf("%s\n",ch);
  /*ungetc(c,stdin);
  scanf("%c",&x);*/
 
 // printf("%c\n",x);
  //}
  //else 
  //perror("prog");
  /*ungetc(c,s);
  fgets(s,100,prog);
  printf("%s\n",s);
  /*c=fgetc(prog);
  printf("%c\n",c);
  ungetc(c,prog);
  c=fgetc(prog);
  printf("%c\n",c); //ca marche trés bien */
}
