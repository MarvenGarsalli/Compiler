#include <stdlib.h>
#include <stdio.h>
#include <string.h>

  char[6] UniLexId(char ch[]);
int main(int argc, char *argv[])
{char c='5';
exit;
char* m[2][90]={"9999"};
m[1][2]="1";
char ch[20]="tets";
char ch1[]="jkgk";
ch1=UniLexId("kjh");
strcat(ch,ch1);
printf("%s\n",ch);
int x = (int)c-48;
printf("%d\n",x);
FILE* fichier = NULL;
int caractereActuel = 0;
fichier = fopen("code_Src.txt", "r");
if (fichier != NULL)
{
// Boucle de lecture des caractères un à un
do
{
caractereActuel = fgetc(fichier); // On lit le caractère
printf("%c", caractereActuel); // On l'affiche
} while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
fclose(fichier);
}
}
char[6] UniLexId(char ch[])
  {
  if( ch=="var" || ch=="entier" || ch=="reel")
    return ch;
  else
    return "Id"; 
  }
