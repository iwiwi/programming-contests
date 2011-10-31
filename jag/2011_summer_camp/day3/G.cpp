#include <stdio.h>
#include <algorithm>
using namespace std;
int f[200][200];
int n;
int ans;

int hoge[200];
int cnt;

void saiki(int p){
  if(p==n){
    int score=0;
    //for(int i=0;i<cnt;i++)printf("%d ",hoge[i]);puts("");
    if(cnt>=2){
      for(int i=0;i<cnt;i++){
        int mini=1010101010;
        for(int j=0;j<cnt;j++){
          if(j==i)continue;
          mini=min(mini,f[hoge[i]][hoge[j]]);
        }
        score+=mini;
      }
    }else{
      score=0;
    }
    ans=max(ans,score);
    return;
  }

  bool ok=true;
  for(int j=0;j<cnt;j++){
    if(f[hoge[j]][p]==0){ok=false;break;}
  }
  if(ok){
    hoge[cnt]=p;
    cnt++;
    saiki(p+1);
    cnt--;
  }
  saiki(p+1);
}

main(){
  int m;
  scanf("%d%d",&n,&m);
  for(int i=0;i<m;i++){
    int u,v,c;
    scanf("%d%d%d",&u,&v,&c);
    u--;v--;
    f[u][v]=f[v][u]=c;
  }
  ans=0;
  /*
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)printf("%d ",f[i][j]);
    puts("");
  }
  */

  cnt=0;
  saiki(0);
  printf("%d\n",ans);
}
