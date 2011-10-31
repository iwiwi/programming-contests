#include <stdio.h>
#include <algorithm>
using namespace std;
main(){
  int H,N,P,M,K;
  scanf("%d%d%d%d%d",&H,&N,&P,&M,&K);P--;
  double dp[110][110];
  for(int x=0;x<N;x++)for(int k=0;k<=K;k++)dp[x][k]=0;
  dp[P][0]=1;
  int yoko[600];
  for(int h=1;h<=H;h++)yoko[h]=-1;
  for(int i=0;i<M;i++){
    int a,b;
    scanf("%d%d",&a,&b);b--;
    yoko[H+1-a]=b;
  }
  int I=H-M;
  int i=0;
  for(int h=1;h<=H;h++){
    if(yoko[h]==-1){
      i++;
      double tmp[110][110];
      for(int x=0;x<N;x++){
        for(int k=0;k<=K;k++){
          tmp[x][k]=0;
          tmp[x][k]+=dp[x][k]*(double)((I-i+1)-(K-k))/(I-i+1);
          if(k>0){
            double nokori=1;
            double s=0;
            if(x>0){s+=dp[x-1][k-1]/(N-1);nokori-=1.0/(N-1);}
            if(x<N-1){s+=dp[x+1][k-1]/(N-1);nokori-=1.0/(N-1);}
            s+=dp[x][k-1]*nokori;
            tmp[x][k]+=s*(double)(K-k+1)/(I-i+1);
          }
        }
      }
      for(int x=0;x<N;x++)for(int k=0;k<=K;k++)dp[x][k]=tmp[x][k];
    }else{
      for(int k=0;k<=K;k++)swap(dp[yoko[h]][k],dp[yoko[h]+1][k]);
    }
    //for(int k=0;k<=K;k++){for(int x=0;x<N;x++)printf("%f ",dp[x][k]);puts("");}
    //puts("");
  }
  double ans=0;
  for(int x=0;x<N;x++)ans=max(ans,dp[x][K]);
  printf("%.10f\n",ans);
}
