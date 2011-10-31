#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

int bitcount(int x){
  if(x==0)return 0;
  return bitcount(x/2)+x%2;
}

main(){
  int n,m;
  scanf("%d%d",&n,&m);
  double l[30],a[30],b[30];
  for(int i=0;i<n;i++){
    scanf("%lf%lf%lf",&l[i],&a[i],&b[i]);
  }
  double ans=0;
  for(int bit=0;bit<(1<<n);bit++){
    if(bitcount(bit)==m){
      double s=0;
      for(int i=0;i<n;i++){
        if(!(bit&(1<<i)))continue;
        for(int j=i+1;j<n;j++){
          if(!(bit&(1<<j)))continue;
          s=s+pow(l[i]-l[j],2)+pow(a[i]-a[j],2)+pow(b[i]-b[j],2);
        }
      }
      ans=max(ans,s);
    }
  }
  printf("%.12f\n",ans);
}
