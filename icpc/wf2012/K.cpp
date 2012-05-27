#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int dp[10100][52];

int cnt[10100][52];

#define INF 1010101010

int main(){
  for(int casenum=1;;casenum++){
    int n;
    if(scanf("%d",&n)<=0)return 0;
    //printf("read %d\n",n);
    memset(cnt,0,sizeof(cnt));
    int maxh=0;
    for(int i=0;i<n;i++){
      int a;
      scanf("%d",&a);
      //printf("read %d\n",a);
      for(int j=0;j<a;j++){
	int h;
	scanf("%d",&h);
	//printf("read %d\n",h);
	cnt[h][i]++;
	maxh=max(maxh,h);
      }
    }
    for(int h=maxh;h>=1;h--){
      int m=0;
      for(int i=0;i<n;i++){
	if(cnt[h][i]>0)m++;
      }
      if(h==maxh){
	for(int i=0;i<n;i++){
	  if(cnt[h][i]>0)dp[h][i]=m;
	  else dp[h][i]=INF;
	}
      }else{
	//printf("h=%d: m=%d\n",h,m);
	for(int i=0;i<n;i++){
	  if(m==0)dp[h][i]=dp[h+1][i];
	  else{
	    if(cnt[h][i]==0)dp[h][i]=INF;
	    else{
	      dp[h][i]=INF;
	      for(int j=0;j<n;j++){
		int e;
		if((m==1 && j==i) || (m>=2 && j!=i && cnt[h][j]>0))e=m-1; else e=m;
		dp[h][i]=min(dp[h][i],dp[h+1][j]+e);
	      }
	    }
	  }
	}
      }
    }
    /*
    for(int h=maxh;h>=1;h--){
      printf("%d: ",h);
      for(int i=0;i<n;i++)printf("%d ",dp[h][i]);puts("");
    }
    */
    int mini=INF;
    for(int i=0;i<n;i++)mini=min(mini,dp[1][i]);
    printf("Case %d: %d\n",casenum,2*mini-n-1);
  }
}
