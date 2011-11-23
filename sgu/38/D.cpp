#include <stdio.h>

main(){
  int n;
  scanf("%d",&n);
  int k=n/14;
  int ans=-1;
  if(k<=1){
    if(n==21)ans=1;
  }else{
    if(n%14>=2 && n%14<=12)ans=k;
  }
  printf("%d\n",ans);
}
