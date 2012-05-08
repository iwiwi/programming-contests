#include <stdio.h>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <assert.h>
#include <string>
#include <algorithm>
using namespace std;
/*
void myassert(int hoge){
  //if(!hoge)for(;;);
}
*/
set<string> visited;
vector<string> sorted;
map<string, vector<string> > adj;

void saiki(string p){
  if(adj.count(p)==0)return;
  if(visited.count(p)!=0)return;
  visited.insert(p);
  for(int i=0;i<adj[p].size();i++)saiki(adj[p][i]);
  //printf("%s!!!!\n",p.c_str());
  sorted.push_back(p);
}

int main(){
  for(int casenum=1;;casenum++){
    adj.clear();
    int n,g,u;
    scanf("%d%d%d",&n,&g,&u);
    if(n==0 && g==0 && u==0)return 0;
    int gatetype[30];
    string in1[30],in2[30];
    string gatename[30];
    for(int i=0;i<g;i++){
      char buf[10];
      scanf("%s",buf);
      if(buf[0]=='n'){
        char tmp1[10];
        scanf("%s",tmp1);
        gatetype[i]=3;
        char hoge[10];
        sprintf(hoge,"g%d",i+1);
        gatename[i]=string(hoge);
        in1[i]=string(tmp1);
        in2[i]=string(tmp1);
      }else{
        char tmp1[10],tmp2[10];
        scanf("%s%s",tmp1,tmp2);
        if(buf[0]=='a')gatetype[i]=0;
        if(buf[0]=='o')gatetype[i]=1;
        if(buf[0]=='x')gatetype[i]=2;
        char hoge[10];
        sprintf(hoge,"g%d",i+1);
        gatename[i]=string(hoge);
        in1[i]=string(tmp1);
        in2[i]=string(tmp2);        
      }
      if(adj.count(gatename[i])==0)adj[gatename[i]]=vector<string>();
      adj[gatename[i]].push_back(in1[i]);
      adj[gatename[i]].push_back(in2[i]);
    }
    visited.clear();
    sorted.clear();
    for(int i=0;i<n;i++){
      char tmp[20];
      sprintf(tmp,"i%d",i+1);
      visited.insert(string(tmp));
    }
    for(int i=0;i<g;i++){
      char tmp[20];
      sprintf(tmp,"g%d",i+1);
      if(visited.count(string(tmp))==0)saiki(string(tmp));
    }
    vector<int> outgate;
    for(int i=0;i<u;i++){int tmp;scanf("%d",&tmp);outgate.push_back(tmp);}
    int obs;
    scanf("%d",&obs);
    vector<pair<int,int> > v;
    for(int i=0;i<obs;i++){
      int inp=0,oup=0;
      for(int j=0;j<n;j++){
        int tmp;
        scanf("%d",&tmp);
        //inp=inp*2+tmp;
        inp+=(1<<j)*tmp;
      }
      for(int j=0;j<u;j++){
        int tmp;
        scanf("%d",&tmp);
        //oup=oup*2+tmp;
        oup+=(1<<j)*tmp;
      }
      v.push_back(make_pair(inp,oup));
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
/*
    vector<int> inp[30],oup[30];
    for(int i=0;i<obs;i++){
      for(int j=0;j<n;j++){
        int tmp;
        scanf("%d",&tmp);
        inp[i].push_back(tmp);
      }
      for(int j=0;j<u;j++){
        int tmp;
        scanf("%d",&tmp);
        oup[i].push_back(tmp);
      }
    }
*/    
    vector<int> okfault;

    for(int fault=-1;fault<3*g;fault++){
      //printf("fault #%d:\n",fault);
        bool ok=true;
      for(int k=0;k<v.size();k++){
        map<string,int> var;
        for(int i=0;i<n;i++){
          char intmp[20];
          sprintf(intmp,"i%d",i+1);
          var.insert(make_pair(string(intmp),(v[k].first>>i)&1));
        }
        //int done[30]={};
        //for(int t=0;t<g;t++){
        //bool proceed=false;
        for(int t=0;t<g;t++){
          int i;
          sscanf(sorted[t].c_str(),"g%d",&i);i--;
          //if(done[i]==1)continue;
          //if(var.count(in1[i])>0 && var.count(in2[i])>0){
          int x=var[in1[i]],y=var[in2[i]];
          int z;
          if(gatetype[i]==0)z=min(x,y);
          if(gatetype[i]==1)z=max(x,y);
          if(gatetype[i]==2)z=(x+y)%2;
          if(gatetype[i]==3)z=1-x;
          if(fault==i*3)z=1-z;
          if(fault==i*3+1)z=0;
          if(fault==i*3+2)z=1;
          var.insert(make_pair(gatename[i],z));
          //printf("simulate gate %d (%s %s %d): %d %d %d\n",i,in1[i].c_str(),in2[i].c_str(),gatetype[i],x,y,z);
          //done[i]=1;
          //proceed=true;
          //break;
              //}
        }
          //myassert(proceed);
          //}
        /*
        for(map<string,int>::iterator ite=var.begin();ite!=var.end();ite++){
          printf("%s %d\n",(*ite).first.c_str(),(*ite).second);
        }
        puts("");
        */
        for(int i=0;i<u;i++){
          char outtmp[20];
          sprintf(outtmp,"g%d",outgate[i]);
          assert(var.count(string(outtmp))>0);
          if(var[string(outtmp)]!=((v[k].second>>i)&1))ok=false;
        }
      }
      if(ok)okfault.push_back(fault);
    }
    assert(okfault.size()>0);

    printf("Case %d: ",casenum);
    if(okfault[0]==-1)puts("No faults detected");
    else{
      if(okfault.size()>=2)puts("Unable to totally classify the failure");
      else if(okfault[0]%3==0)printf("Gate %d is failing; output inverted\n",okfault[0]/3+1);
      else if(okfault[0]%3==1)printf("Gate %d is failing; output stuck at 0\n",okfault[0]/3+1);
      else if(okfault[0]%3==2)printf("Gate %d is failing; output stuck at 1\n",okfault[0]/3+1);

    }
  }
}
