#include <stdio.h>
#include <algorithm>
using namespace std;

#define INF 999999999

int x[2000],y[2000];

int dp[2000][2000]; //[i,j]
int pos[2000][2000];

int main(){
  int n;
  int i,j,k,l;
  scanf("%d",&n);

  for(i=0;i<n;i++){
    scanf("%d%d",&x[i],&y[i]);
  }

  for(i=0;i<n;i++){
    dp[i][i]=0;
    pos[i][0] = i;
  }
  
  for(l=1;l<n;l++){
    for(i=0;i+l<n;i++){
      j=i+l;
      dp[i][j]=INF;
      
      int klb = pos[i][l - 1];
      int kub = min(j - 1, pos[i + 1][l - 1]);
      // printf("[%d, %d]\n", klb, kub);
      for (k = klb; k <= kub; k++) {
        int t = dp[i][k] + dp[k+1][j] + (x[k+1]-x[i]) + (y[k]-y[j]);
        if (t < dp[i][j]) {
          dp[i][j] = t;
          pos[i][l] = k;
        }
      }
      /*
      for(k=i;k<j;k++){
        dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+(x[k+1]-x[i])+(y[k]-y[j]));
      }
      */
      //printf("%d %d: %d\n",i,j,dp[i][j]);
    }
  }

  printf("%d\n",dp[0][n-1]);
  return 0;
}
