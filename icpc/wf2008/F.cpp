#include <stdio.h>

main(){
  for(int casenum=1;;casenum++){
    long long l;
    scanf("%lld",&l);
    if(l==0)return 0;
    printf("Case %d: ",casenum);
    if(l%2==0){
      long long x=l/2;
      printf("%lld\n",x*x*(x+1)*(x-1)/12);
    }
    else printf("0\n");
  }
}
