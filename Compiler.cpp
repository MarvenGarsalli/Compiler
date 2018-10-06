#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;
int existe(vector<string>cle,string s);
template <T,U>typedef struct dwf
{T id;
U nom;
}table;

int main()
{table<string,string> lexeme;
vector<table<string,string>> tabSymbole;
vector<table<int,string>> idVar; //La table des identificateurs variables
 vector<string> cle(20);///pour conserver les mots clés
    cle[0]="Deb";
   cle.push_back("Fin"); cle.push_back("Var"); cle.push_back("si"); cle.push_back("alors"); cle.push_back(";"); cle.push_back(",");cle.push_back(":");       	cle.push_back(":="); cle.push_back("id"); cle.push_back("entier"); cle.push_back("reel"); cle.push_back("Lire"); cle.push_back("Ecrire");
   cle.push_back("nb"); cle.push_back("nbr"); cle.push_back("+"); cle.push_back(">="); cle.push_back("*"); cle.push_back("("); cle.push_back(")");
 
ifstream prog("prog.txt");
string mot,pv="";
if(prog)
  while(prog>>mot)
  { if(mot[mot.length()-1] == ";") {pv=";";mot=mot.substr(0,mot.length()-1);}
   if (existe(cle,mot))
  {if(ch=="Dep"||ch=="Var"||ch=="Lire"||ch=="Ecrire"||ch=="entier"||ch=="reel"||ch=="si"||ch=="alors") lexeme.id="0";lexeme.nom=ch;tabSymbole.push_back(lexeme);
   else if(ch == ":=") lexeme.id="0";lexeme.nom="opaff";tabSymbole.push_back(lexeme);
   else if(ch == ";")  lexeme.id="0";lexeme.nom="pv";tabSymbole.push_back(lexeme);
   else if(ch== ":")   lexeme.id="0";lexeme.nom="2p";tabSymbole.push_back(lexeme);
   else if(ch== ",")   lexeme.id="0";lexeme.nom="v";tabSymbole.push_back(lexeme);
   else if(ch== "+")   lexeme.id="oprel";lexeme.nom="ADD";tabSymbole.push_back(lexeme);
      {m[0][k]="oprel";m[1][k]="ADD";}
   else if(ch== "*")
      {m[0][k]="oprel";m[1][k]="MUL";}
   else if(ch== ">=")
      {m[0][k]="oprel";m[1][k]="GE";}
   else if(ch== "(")
      {m[0][k]="oprel";m[1][k]="POV";}
   else if(ch== ")")
      {m[0][k]="oprel";m[1][k]="PFE";}
   
  }


return 0;
}


//p=make_pair(1,"a");cout<<p.first<<"   |   "<<p.second<<endl;
int existe(vector<string>cle,string s)
{for(int i=0;i<cle.size();i++)
        if (cle[i]== s)
        return i;
    return -1;
}
