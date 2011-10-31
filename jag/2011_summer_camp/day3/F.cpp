#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define M 100000
#define INF 1e9
double dp[2*M+1];
double tmp[2*M+1];

main(){
  int n;
  scanf("%d",&n);
  int a[50];
  for(int i=0;i<n;i++)scanf("%d",&a[i]);
  for(int k=1;k<=2*M;k++)dp[k]=fabs((double)(k-a[0])/a[0]);
  for(int i=1;i<n;i++){
    for(int k=1;k<=2*M;k++)tmp[k]=INF;
    for(int k=1;k<=2*M;k++){
      for(int l=k;l<=2*M;l+=k){
        tmp[l]=min(tmp[l],max(dp[k],fabs((double)(l-a[i])/a[i])));
      }
    }
    for(int k=1;k<=2*M;k++)dp[k]=tmp[k];
  }
  double ans=INF;
  for(int k=1;k<=2*M;k++)ans=min(ans,dp[k]);
  printf("%.12f\n",ans);
}
