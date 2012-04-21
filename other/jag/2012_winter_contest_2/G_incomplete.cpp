#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

#define MP make_pair

char ch[200000];

int defoct=4;
int defdur=32;
int defvol=100;

int noteconv[256];

struct Note{
  int pitch;
  string pitch_note;

  int dur;
  string dur_num;
  string dur_dot;

  int vol;
};

void init(){
  noteconv['C']=0;
  noteconv['D']=2;
  noteconv['E']=4;
  noteconv['F']=5;
  noteconv['G']=7;
  noteconv['A']=9;
  noteconv['B']=11;
  return;
}

bool isnote(char ch){
  if('A'<=ch && ch<='G')return true;
  return false;
}

int readnum(char *ch,int n,int &pos){
  int ans=0;
  for(;;){
    if(pos>=n)break;
    if(!isdigit(ch[pos]))break;
    ans*=10;
    ans+=(ch[pos]-'0');
    pos++;
  }
  return ans;
}

int readdot(char *ch,int n,int &pos){
  int ans=0;
  for(;;){
    if(pos>=n)break;
    if(ch[pos]!='.')break;
    ans++;
    pos++;
  }
  return ans;
}

string numtost(int num){
  char ch[10];
  sprintf(ch,"%d",num);
  return string(ch);
}

string dottost(int dot){
  string st;
  for(int i=0;i<dot;i++)st+='.';
  return st;
}

void MMLseiri(char *ch,int n,vector<int> &in){
  in.clear();

  vector<Note> tmp;

  int nowoct=defoct;
  int nowdur=defdur;
  int vol=defvol;

  int pos=0;
  for(;;){
    if(pos>=n)break;
    if(isnote(ch[pos])){
      pos++;
      int num=readnum(ch,n,pos);
      
    }else if()
  }

  return;
}

int main(void){
  init();
  for(;;){
    scanf("%s",ch);
    int n=strlen(ch);
    if(ch[0]=='*')break;
    
    vector<Note> in;
    MMLseiri(ch,n,in);
  }
  return 0;
}
