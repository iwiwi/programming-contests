#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

long long gcd(long long a,long long b){
  return b?gcd(b,a%b):a;
}

long long myabs(long long x){return x>0?x:-x;}

map<long long, vector<long long> > cache;

main(){
  int datanum;
  scanf("%d ",&datanum);
  for(int datacnt=1;datacnt<=datanum;datacnt++){
    char buf[200];
    gets(buf);
    int l=strlen(buf);
    int appear[256]={};
    for(int i=0;i<l;i++)appear[buf[i]]=1;
    long long coef[10]={};
    int cnt=1;
    for(char c='a';c<='z';c++){
      if(appear[c]==1){
        long long sum=0;
        for(int k=0;k<l;k++){
          if(buf[k]==c)sum=sum*10+1;
          else sum=sum*10;
        }
        if(c==buf[0]){
          coef[0]=sum;
        }else{
          coef[cnt++]=sum;
        }
      }
    }
    //for(int k=0;k<=9;k++)printf("coef=%lld\n",coef[k]);
    long long ans=0;
    for(int i=1;i<=9;i++){
      ans=gcd(ans,myabs(coef[0]-coef[i]));
      //printf("%lld\n",coef[0]-coef[i]);
    }
    for(int i=1;i<=9;i++){
      long long sum=0;
      for(int k=0;k<=9;k++)sum+=coef[k]*((i+k)%10);
      ans=gcd(ans,sum);
      //printf("%lld\n",sum);
    }
    if(ans<0)ans=-ans;

    vector<long long> divs;
    if(cache.count(ans)==1){
      divs=cache[ans];
    }else{
      for(long long d=1;d*d<=ans;d++){
        if(ans%d==0){
          divs.push_back(d);
          if(d*d!=ans)divs.push_back(ans/d);
        }
      }
      sort(divs.begin(),divs.end());
      cache[ans]=divs;
    }
    printf("Case %d:",datacnt);
    for(int i=0;i<divs.size();i++)cout << " " << divs[i];
    puts("");
  }
}
