#include <stdio.h>

long long powmod(long long a,long long b,long long m){
  if(b==0)return 1;
  if(b%2==1)return (powmod(a,b-1,m)*a)%m;
  long long c=powmod(a,b/2,m);
  return (c*c)%m;
}

long long binom(long long a,long long b,long long p){ //a,b<p
  long long ret=1;
  for(long long i=0;i<b;i++){
    ret=(ret*(a-i))%p;
    ret=(ret*powmod(i+1,p-2,p))%p;
  }
  return ret;
}

long long binommod(long long a,long long b,long long p){
  long long x=a,y=b;
  long long ret=1;
  for(;x>0||y>0;){
    ret=(ret*binom(x%p,y%p,p))%p;
    x/=p;y/=p;
  }
  return ret;
}

main(){
  long long n,m,p;
  for(;scanf("%lld%lld%lld",&n,&m,&p)>0;){
    printf("%lld\n",binommod(n+1-m,m,p));
  }
}
