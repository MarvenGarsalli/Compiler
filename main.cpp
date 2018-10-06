#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
int existe(vector<string>cle,string s)
{for(int i=0;i<cle.size();i++)
        if (cle[i]== s)
        return i;
    return -1;
}
int position(string m[2][90],int k,string s)
{for(int i=0;i<k;i++)
        if (m[0][i] == s)
        return i;
    return -1;
}
bool valide (string ch)
{for(int i=0;i<ch.length();i++)
    {if(ch[i]<'0' )
      return false;
      else if(ch[i]>57 && ch[i]<65)
        return false;
      else if (ch[i]>90 && ch[i]<97)
        return false;
      else if(ch[i]>122)
        return false;
    }
return true;
}

int main()
{puts("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°") ;
puts( "°°°°°                  ANALYSEUR LEXICAL                    °°°°°°°°°°°°°°°°°") ;
puts( "°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°") ;
cout<<endl<<endl;
    ifstream prog("prog.txt");
 string m[2][90]={"9999"};//cout<<m[0][3]<<endl;
 vector<string> cle(20);///pour conserver les mots cle
 cle[0]="Deb";
 cle.push_back("Fin");
 cle.push_back("Var");
 cle.push_back("si");
 cle.push_back("alors");
 cle.push_back(";");
 cle.push_back(",");
 cle.push_back(":");
 cle.push_back(":=");
 cle.push_back("id");
 cle.push_back("entier");
 cle.push_back("reel");
 cle.push_back("Lire");
 cle.push_back("Ecrire");
 cle.push_back("nb");
 cle.push_back("nbr");
 cle.push_back("+");
 cle.push_back(">=");
 cle.push_back("*");
 cle.push_back("(");
 cle.push_back(")");
 string ch;
 int k=0,v=0,cpt(49),fin(0),inst(1),nbcom(0);
 while (prog)
{   prog >>ch;
m[0][k]=ch;
///cout<<m[0][k]<<endl;
if(fin == 0)
 {if (ch[ch.length()-1] == ';' && ch.length()>1)
 {m[0][k]=ch.substr(0,ch.length()-1);v=1;ch=m[0][k];}///cout<<ch<<endl;}   //getline(prog,ch);
///*** La partie verification ***////
 int pos=existe(cle,ch);
if (pos != -1)             ///ch est un symbole(mot cle)
{  if(ch=="Dep"||ch=="Var"||ch=="Lire"||ch=="Ecrire"||ch=="entier"||ch=="reel"||ch=="si"||ch=="alors")
        m[1][k]="0";
   else if(ch == ":=")
      { m[0][k]="opaff";m[1][k]="0";}
   else if(ch == ";")
      {m[0][k]="pv";m[1][k]="0";}
   else if(ch== ":")
      {m[0][k]="2p";m[1][k]="0";}
      else if(ch== ",")
      {m[0][k]="v";m[1][k]="0";}
   else if(ch== "+")
      {m[0][k]="oprel";m[1][k]="ADD";}
   else if(ch== "*")
      {m[0][k]="oprel";m[1][k]="MUL";}
   else if(ch== ">=")
      {m[0][k]="oprel";m[1][k]="GE";}
   else if(ch== "(")
      {m[0][k]="oprel";m[1][k]="POV";}
   else if(ch== ")")
      {m[0][k]="oprel";m[1][k]="PFE";}
   else
   {pos=-1;}
}
if (pos == -1)  ///ch est un id ou cte ou n'est pas un symbol
{if(ch[0] == 'l' && valide(ch))
   {int p_col=position(m,k,ch);//cout<<p_col<<endl;
   if(p_col==-1)
    {m[1][k]=cpt;cpt++;}
   else
    m[1][k]=m[1][p_col];nbcom++;
   }
else if (  atoi(ch.c_str()) < 27365000 &&  atoi(ch.c_str()) >= 0 )
   {m[0][k]="nb";m[1][k]=ch ;}
else if (  atoi(ch.c_str())< 44365000.0009 && atoi(ch.c_str()) >= 0.0009)
   {m[0][k]="nbr";m[1][k]=ch;}
else
   {cout<<"Erreur,verifier l'instruction n° "<<inst<<endl;return 0;}
}
 }
if(v==1)
{k++;ch=";";
m[0][k]="pv";m[1][k]="0";
}
k++;
v=0;
if(ch==";")
    {fin=1;inst++;}
else fin=0;
}
///cout<<k<<endl;
/*** Affichage du resultat finale ***/
for(int i=0;i<k-1;i++)
{if(m[1][i]=="")
   {if(m[0][i][0]=='l')
     {int p_col=position(m,i,m[0][i]);///cout<<p_col<<endl;
      if(p_col == -1)
      {cpt=0;for(int j=0;j<=i;j++)
                if(m[0][j][0]=='l')
                   cpt++;///cpt=atoi(m[1][j].c_str());
                m[1][i]=(cpt-nbcom)+50;
        for(int j=i+1;j<k-2;j++)
         if(m[0][j][0]=='l')
           m[1][j]=++cpt;

       }
      else
       m[1][k]=m[1][p_col];
     }
     else
    m[1][i]="0";
   }
}
for(int i=0;i<k-1;i++)
    {if(m[0][i][0]=='l')
       m[0][i]="id";
    cout<<m[0][i]<<"\t";}
cout<<endl;
for(int i=0;i<k-1;i++)
    cout<<m[1][i]<<"\t";
cout<<endl<<endl<<endl;
char c=1;
cout<<"°°°°°°°°°°°°°°°°°°°°°"<<c<<c<<c<<c<<c<<c<<c<<c<<"  FIN  "<<c<<c<<c<<c<<c<<c<<c<<c<<"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°"<<endl ;
       return 0;
}
