#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <deque>
using namespace std;
#define INF 1000000000

char wall[2100][120];
int block[2100][120];
int dp[2100][120];
bool check[2100][120];
int n,w,t1,t2,t3;

int solve(int kai,int from){
  int ans=INF;
  if(check[kai][from]){ans=dp[kai][from];goto done;}
  check[kai][from]=true;
  if(kai==0){ans=0;goto done;}
  if(wall[kai][from]=='|'){ans=INF;goto done;}
  {
    int cost=-t1;
    for(int pos=from-1;pos>=0;pos--){
      if(block[kai][pos]==0)break;
      if(wall[kai][pos]=='|')break;
      if(abs(pos-from)==1 && wall[kai][pos]=='#')break;
      cost+=t1;
      if(wall[kai][pos]=='#')cost+=t3;
      int now=cost+t2*(block[kai-1][pos]+1)+solve(kai-1,pos);
      if(now==INF)continue;
      ans=min(ans,now);
    }
    cost=-t1;
    for(int pos=from+1;pos<w;pos++){
      if(block[kai][pos]==0)break;
      if(wall[kai][pos]=='|')break;
      if(abs(pos-from)==1 && wall[kai][pos]=='#')break;
      cost+=t1;
      if(wall[kai][pos]=='#')cost+=t3;
      int now=cost+t2*(block[kai-1][pos]+1)+solve(kai-1,pos);
      if(now==INF)continue;
      ans=min(ans,now);
    }
  }
 done:
  //printf("dp[%d][%d]=%d\n",kai,from,ans);
  return dp[kai][from]=ans;
}

int main(void){
  while(scanf("%d %d",&n,&w)==2){
    scanf("%d %d %d",&t1,&t2,&t3);
    memset(wall,0,sizeof(wall));
    memset(block,0,sizeof(block));
    for(int i=0;i<n;i++){
      char ch[110];
      scanf("%s",ch);
      for(int j=0;j<w;j++)wall[i+1][j+2]=ch[j];
      scanf("%s",ch);
      for(int j=0;j<w;j++)block[i+1][j+2]=ch[j]-'0';
    }
    n++;w+=4;
    for(int i=0;i<n;i++)for(int j=0;j<w;j++)dp[i][j]=INF;
    memset(check,0,sizeof(check));
    int ans=solve(n-1,1);
    if(ans==INF)ans=-1;
    else ans-=t2;
    printf("%d\n",ans);
  }
  return 0;
}
