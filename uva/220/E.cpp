#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
long long x0[1000],x1[1000],y0[1000],y1[1000];

long long n;
int m;

long long calc(long long x){
  vector<long long> ev;
  for(int i=0;i<m;i++){
    if(x>=x0[i] && x<x1[i]){
      ev.push_back(y0[i]);
      ev.push_back(y1[i]);
    }
  }
  ev.push_back(x);
  ev.push_back(n);
  sort(ev.begin(),ev.end());

  //for(int i=0;i<ev.size();i++)printf("%lld ",ev[i]);puts("");

  long long ret=0;
  for(int i=0;i<ev.size();i++){
    long long prev=(i==0?0:ev[i-1]);
    if(i%2==1)ret+=(ev[i]-prev);
  }
  return ret;
}

main(){
  int testcases;
  scanf("%d",&testcases);
  for(int casenum=1;casenum<=testcases;casenum++){
    int queries;
    m=0;
    scanf("%lld%d ",&n,&queries);
    for(int i=0;i<queries;i++){
      char buf[1000];
      gets(buf);
      int comma=0;
      for(int k=0;buf[k];k++)if(buf[k]==',')comma++;
      long long y,x,ysiz,xsiz,t;
      if(comma==2){
        long long siz;
        sscanf(buf,"(%lld, %lld, %lld) - %lld",&y,&x,&siz,&t);
        xsiz=ysiz=siz;
      }else{
        sscanf(buf,"(%lld, %lld, %lld, %lld) - %lld",&y,&x,&xsiz,&ysiz,&t);
      }
      //printf("%lld %lld %lld %lld %lld\n",x,y,xsiz,ysiz,t);
      x--;y--;
      if(t%2==1){
        if(x+xsiz<=n && y+ysiz<=n){
          x0[m]=x;x1[m]=x+xsiz;
          y0[m]=y;y1[m]=y+ysiz;
          m++;
        }
        if(x+xsiz<=n && y+ysiz>n){
          x0[m]=x;x1[m]=x+xsiz;
          y0[m]=y;y1[m]=n;
          m++;
          x0[m]=x;x1[m]=x+xsiz;
          y0[m]=0;y1[m]=y+ysiz-n;
          m++;
        }
        if(x+xsiz>n && y+ysiz<=n){
          x0[m]=x;x1[m]=n;
          y0[m]=y;y1[m]=y+ysiz;
          m++;
          x0[m]=0;x1[m]=x+xsiz-n;
          y0[m]=y;y1[m]=y+ysiz;
          m++;
        }
        if(x+xsiz>n && y+ysiz>n){
          x0[m]=x;x1[m]=n;
          y0[m]=y;y1[m]=n;
          m++;
          x0[m]=x;x1[m]=n;
          y0[m]=0;y1[m]=y+ysiz-n;
          m++;
          x0[m]=0;x1[m]=x+xsiz-n;
          y0[m]=y;y1[m]=n;
          m++;
          x0[m]=0;x1[m]=x+xsiz-n;
          y0[m]=0;y1[m]=y+ysiz-n;
          m++;
        }
      }
    }
    
    vector<int> kiru;
    for(int i=0;i<m;i++){
      kiru.push_back(x0[i]);
      kiru.push_back(x1[i]);
      kiru.push_back(y0[i]);
      kiru.push_back(y1[i]);
      //      printf("%lld %lld - %lld %lld\n",x0[i],y0[i],x1[i],y1[i]);
    }
    kiru.push_back(0);
    kiru.push_back(n);
    sort(kiru.begin(),kiru.end());
    kiru.erase(unique(kiru.begin(),kiru.end()),kiru.end());
    
    long long ans=0;

    //for(int i=0;i<n;i++)printf("%d: %lld\n",i,calc(i));

    for(int t=0;t<kiru.size()-1;t++){
      ans+=(calc(kiru[t])+calc(kiru[t+1]-1))*(kiru[t+1]-kiru[t])/2;
    }
    
    printf("Case %d: %lld\n",casenum,ans);
  }
}
