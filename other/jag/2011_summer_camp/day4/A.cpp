#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
#define EPS 1e-9
#define INF 1e9
char board[1000][1000];
int ysize,xsize;

char b(int x,int y){
  if(x<0 || x>=xsize || y<0 || y>=ysize)return '.'; else return board[x][y];
}

main(){
  scanf("%d%d ",&ysize,&xsize);
  for(int j=ysize-1;j>=0;j--){
    char buf[1000];
    gets(buf);
    for(int i=0;i<xsize;i++)board[i][j]=buf[i];
  }
  vector<pair<double,int> > ev;
  for(int i=0;i<=xsize;i++){
    for(int j=0;j<=ysize;j++){
      if(i<xsize && b(i,j)!=b(i,j-1) && j>0){ //(i,j)-(i+1,j)
        //printf("%d,%d (%c)- %d,%d(%c)\n",i,j,b(i,j),i+1,j,b(i+1,j));
        ev.push_back(make_pair((double)j/(i+1)+EPS,1));
        ev.push_back(make_pair((i==0?INF:(double)j/i)-EPS,-1));
        //printf("%f-%f\n",(double)j/(i+1),(i==0?INF:(double)j/i));
      }
      if(j<ysize && b(i,j)!=b(i-1,j) && i>0){ //(i,j)-(i,j+1)
        //printf("%d,%d - %d,%d\n",i,j,i,j+1);
        ev.push_back(make_pair((double)j/i+EPS,1));
        ev.push_back(make_pair((double)(j+1)/i-EPS,-1));
        //printf("%f-%f\n",(double)j/i,(double)(j+1)/i);
      }
    }
  }
  sort(ev.begin(),ev.end());
  int cnt=(board[0][0]=='#'?1:0);
  int ans=0;
  for(int i=0;i<ev.size();i++){
    cnt+=ev[i].second;
    ans=max(cnt,ans);
  }
  printf("%d\n",ans/2+1);
}
