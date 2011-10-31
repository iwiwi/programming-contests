#include <stdio.h>
#include <vector>
#include <utility>
#include <assert.h>
#include <algorithm>
#include <stdlib.h>

using namespace std;

long long s[110000],t[110000];
long long p[110000];

int pos(long long a[],int siz,long long x){
  if(x<a[0])return 0;
  if(x>a[siz-1])return siz;
  int lb=0,ub=siz-1;
  for(;ub-lb>1;){
    //printf("%d-%d\n",lb,ub);
    int mid=(ub+lb)/2;
    if(a[mid]<x)lb=mid; else ub=mid;
  }
  return lb+1;
}

void myassert() {
  *((int*)0) = 0;
}

void myTLE(){
  while(1);
}

main(){
  int n,m;
  //myassert();
  scanf("%d%d",&n,&m);
  for(int i=0;i<n;i++){
    scanf("%lld%lld",&s[i],&t[i]);
  }
  for(int i=0;i<m;i++)scanf("%lld",&p[i]);
  sort(p,p+m);
  vector<pair<long long,pair<int,int> > > ev;
  for(int i=0;i<n;i++){
    ev.push_back(make_pair(s[i],make_pair(s[i]<t[i]?1:-1,1)));
    ev.push_back(make_pair(t[i],make_pair(s[i]<t[i]?-1:1,(abs(pos(p,m,s[i])-pos(p,m,t[i]))%2)?0:1)));
  }
  for(int i=0;i<m;i++)ev.push_back(make_pair(p[i],make_pair(0,0)));
  sort(ev.begin(),ev.end());
  long long tot=0,act=0;
  long long ans=0;
  for(int i=0;i<ev.size();i++){
    if(i>0){
      //printf("%lld-%lld %lldhon / %lldhon\n",ev[i-1].first,ev[i].first,act,tot);
      //if(!(ev[i].first!=ev[i-1].first))myTLE();
      ans+=(ev[i].first-ev[i-1].first)*act;
    }
    if(ev[i].second.first==0){
      act=tot-act;
    }else{
      tot+=ev[i].second.first;
      act+=ev[i].second.first*ev[i].second.second;
    }
    if(!(act>=0 && act<=tot))myassert();
  }
  printf("%lld\n",ans);
}
