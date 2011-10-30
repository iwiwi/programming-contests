#include <stdio.h>
#define P 1000000007

long long powmod(long long a,long long b,long long m){
  if(b==0)return 1;
  if(b%2==1)return (powmod(a,b-1,m)*a)%m;
  long long c=powmod(a,b/2,m);
  return (c*c)%m;
}

main(){
  long long n,k;
  for(;scanf("%lld%lld",&n,&k)>0;){
    printf("%lld\n",powmod(powmod(2,k,P)-1,n,P));
  }
}
