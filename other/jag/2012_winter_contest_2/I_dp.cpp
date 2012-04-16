#include <stdio.h>
#include <string.h>
#define P 1000000009
long long dp[10101][80];
long long board[10101][80];
main(){
  for(int casenum=1;;casenum++){
    long long yoko,tate,pts;
    scanf("%lld%lld%lld",&yoko,&tate,&pts);
    if(yoko==0)return 0;
    memset(dp,0,sizeof(dp));
    memset(board,0,sizeof(board));
    for(int i=0;i<pts;i++){
      long long p,q;
      scanf("%lld%lld",&q,&p);q--;p--;
      board[p][q]=-1;
    }
    dp[0][0]=1;
    for(int i=1;i<tate;i++){
      for(int j=0;j<yoko;j++){
        dp[i][j]=dp[i-1][j];
        if(j>0)dp[i][j]+=dp[i-1][j-1];
        if(j<yoko-1)dp[i][j]+=dp[i-1][j+1];
        dp[i][j]%=P;
        if(board[i][j]==-1)dp[i][j]=0;
        //printf("%lld ",dp[i][j]);
      }
      //puts("");
    }
    printf("Case %d: %lld\n",casenum,dp[tate-1][yoko-1]);
  }
}
