#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<iostream>
#include<algorithm>
using namespace std;

char ch[1000];

int n;
string name[20000];
int type[20000];
int num[20000];
bool re[20000];

map<string,int> conv;

bool used[20000];
int prev[20000];

vector<int> ans;

void myassert1(bool b) {
  if (b == false) {
    for (;;);  // TLE
  }
}

void myassert2(bool b) {
  if (b == false) {
    *(int*)0 = 0;  // RE
  }
}



void read(int pos){
  if(2<=pos && pos<n-1)ans.push_back(pos);

  myassert1(used[pos] == false);

  used[pos]=true;
  if(num[pos]==1){
    prev[type[pos]]=pos;
  }
  return;
}

int main(void){
  while(1){
    scanf("%d",&n);
    if(n==0)break;
    for(int i=0;i<n+100;i++){
      name[i]="";
      type[i]=-1;
      num[i]=0;
      re[i]=false;
      prev[i]=-1;
      used[i]=false;
    }
    conv.clear();
    int cnt=0;
    for(int ii=0;ii<n;ii++){
      int i=ii+2;
      scanf("%s",ch);
      string st=string(ch);
      if(st[0]=='-')continue;
      if(st[st.size()-1]=='v'){re[i]=true;st.erase(st.begin()+st.size()-1);}
      if(st.size()==0)continue;
      int pos=0;
      while(isalpha(st[pos]))pos++;
      string tst=st.substr(0,pos);
      string nst=st.substr(pos);
      name[i]=tst;
      if(conv.count(tst)==0){
        conv[tst]=cnt;
        cnt++;
      }
      sscanf(nst.c_str(),"%d",&num[i]);
    }
    n+=3;
    for(int i=0;i<n;i++){
      if(name[i]=="")continue;
      type[i]=conv[name[i]];
    }
    for(int i=n-2;i>=0;i--){
      if(re[i] && num[i]==0 && num[i+1]!=0){
        type[i]=type[i+1];
        name[i]=name[i+1];
        num[i]=num[i+1];
      }
    }
    //for(int i=0;i<n;i++)printf("[%s] %d\n",name[i].c_str(),num[i]);
    ans.clear();
    int pos=1;
    while(1){
      int next;
      if(pos>=n-1)break;
      read(pos);
      if(re[pos-1]){
        next=pos-1;
      }else if(num[pos]>=1){
        int aru=-1;
        for(int i=0;i<pos;i++){
          if(!used[i] && type[i]==type[pos] && num[i]==num[pos]+1){aru=i;}
        }
        if(aru!=-1){
          while(re[aru])aru++;
          next=aru;
        }else{
          pos=prev[type[pos]];
          goto four;
        }
      }else{
     four:
        next=pos;
        //cout << used[next] << endl;
        while(used[next] || num[next]>=2 || re[next])next++;
        //printf("[%d]\n",next);
      }
      pos=next;
    }

    myassert2((int)ans.size() == n - 3);

    for(int i=0;i<(int)ans.size();i++){
      printf("%d\n",ans[i]-1);
    }
  }
  return 0;
}
