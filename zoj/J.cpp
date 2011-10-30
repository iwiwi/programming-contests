#include <stdio.h>
#define P 100000007
#define HALF (P+1)/2
#define modp(x) ((((x)%P)+P)%P)
#define M 10000
main(){
  long long n;
  for(;scanf("%lld",&n)>0;){
    long long ans=0;
    for(long long m=1;m<=M;m++){
      long long lb=n/(m+1);
      long long ub=n/m;
      //d=lb+1..ub
      ans=modp(ans+modp(n*modp((ub-lb)*m)));
      ans=modp(ans-modp(modp((m*(m+1))/2)*modp((lb+1+ub)*(ub-lb)/2)));
    }
    for(long long d=1;d<=n/(M+1);d++){
      ans=modp(ans+modp(n*(n/d)));
      ans=modp(ans-modp(d*modp((n/d)*(n/d+1)/2)));
    }
    printf("%lld\n",ans);
  }
}
