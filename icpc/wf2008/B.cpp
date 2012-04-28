#include <stdio.h>
#include <utility>
#include <string>
using namespace std;

pair<long long,long long> hoge(string s){
  if(!(s[s.length()-1]>='0' && s[s.length()-1]<='9')){
    if(s==string("+n"))return make_pair(1,1);
    if(s==string("-n"))return make_pair(-1,1);
    long long ret;
    sscanf(s.c_str(),"%lldn",&ret);
    return make_pair(ret,1);
  }
  int ruijo=-1;
  for(int i=0;i<(int)s.length();i++)if(s[i]=='^')ruijo=i;
  if(ruijo==-1){
    long long ret;
    sscanf(s.c_str(),"%lld",&ret);
    return make_pair(ret,0);
  }
  if(s[0]=='+' && s[1]=='n'){
    long long d;
    sscanf(s.c_str(),"+n^%lld",&d);
    return make_pair(1,d);
  }
  if(s[0]=='-' && s[1]=='n'){
    long long d;
    sscanf(s.c_str(),"-n^%lld",&d);
    return make_pair(-1,d);
  }
  long long c,d;
  sscanf(s.c_str(),"%lldn^%lld",&c,&d);
  return make_pair(c,d);
}

main(){
  for(int casenum=1;;casenum++){
    char buf[10000];
    gets(buf);
    if(buf[0]=='.')return 0;
    char bunsi[10000];
    int l=0;
    long long bunbo;
    if(buf[1]!='-')bunsi[l++]='+';
    for(int i=0;buf[i];i++){
      if(buf[i]=='/'){
        sscanf(buf+i+1,"%lld",&bunbo);
        break;
      }
      if(buf[i]!='(' && buf[i]!=')')bunsi[l++]=buf[i];
    }
    bunsi[l++]='+';
    bunsi[l]=0;
    //printf("%s / %lld\n",bunsi,bunbo);
    string tmp;
    long long coef[200]={};
    for(int i=0;i<l;i++){
      if(bunsi[i]=='+' || bunsi[i]=='-'){
        if(i>0){
          pair<long long,long long> ret=hoge(tmp);
          //printf("%s %lld %lld\n",tmp.c_str(),ret.first,ret.second);
          coef[ret.second]=ret.first;
        }
        tmp=string("")+bunsi[i];
      }else{
        tmp=tmp+bunsi[i];
      }
      //printf("%s",tmp.c_str());
    }
    //for(int i=0;i<=100;i++)printf("%lld ",coef[i]);puts("");
    //printf("bunbo=%lld\n",bunbo);
    bool ok=true;
    for(int n=0;n<=210;n++){
      long long sum=0;
      long long p=1;
      for(int i=0;i<=100;i++){
        sum=(sum+coef[i]*p)%bunbo;
        p=(p*n)%bunbo;
      }
      if(sum!=0)ok=false;
    }
    printf("Case %d: ",casenum);
    if(ok)puts("Always an integer");
    else puts("Not always an integer");
  }
}
