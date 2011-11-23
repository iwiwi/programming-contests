#include <stdio.h>
#include <queue>
#include <utility>
#include <assert.h>
using namespace std;
#define INF 1010101010
int adj[20][3]=
  {
    {5,1,4},
    {6,2,0},
    {7,3,1},
    {8,4,2},
    {9,0,3},
    {0,10,11},
    {1,11,12},
    {2,12,13},
    {3,13,14},
    {4,14,10},
    {5,9,15},
    {6,5,16},
    {7,6,17},
    {8,7,18},
    {9,8,19},
    {10,19,16},
    {11,15,17},
    {12,16,18},
    {13,17,19},
    {14,18,15},
  };

int rot(int a,int b,int x){
  for(int i=0;i<=2;i++){
    if(adj[a][i]==b)return adj[a][(i+x+3)%3];
  }
  assert(0);
}

#define M 110

int cost[2*M+1][2*M+1][20][20];

main(){
  for(;;){
    int gx,gy;
    int ga;
    scanf("%d%d%d",&gx,&gy,&ga);
    if(gx==0 && gy==0 && ga==0)return 0;
    for(int i=-M;i<=M;i++)for(int j=-M;j<=M;j++)for(int a=0;a<20;a++)for(int b=0;b<20;b++)cost[M+i][M+j][a][b]=INF;
    cost[M+0][M+0][0][5]=0;
    queue<pair<pair<int,int>,pair<int,int> > > que;
    que.push(make_pair(make_pair(0,0),make_pair(0,5)));
    for(;!que.empty();){
      pair<pair<int,int>,pair<int,int> > h=que.front();
      que.pop();
      int x=h.first.first;
      int y=h.first.second;
      int a=h.second.first;
      int b=h.second.second;
      int nowc=cost[M+x][M+y][a][b];
      //printf("%d %d %d %d: %d\n",x,y,a,b,nowc);
      if(x==gx && y==gy && a==ga){
	printf("%d\n",nowc);
	break;
      }
      int dx[2][3]={{0,-1,1},{0,1,-1}};
      int dy[2][3]={{1,0,0},{-1,0,0}};
      for(int d=0;d<3;d++){
	int na=rot(a,b,3-d);
	int nb=rot(na,a,d);
	int nx=x+dx[(x+y)&1][d];
	int ny=y+dy[(x+y)&1][d];
	if(nx<-M || nx>M || ny<-M || ny>M)continue;
	if(cost[M+nx][M+ny][na][nb]>nowc+1){
	  cost[M+nx][M+ny][na][nb]=nowc+1;
	  que.push(make_pair(make_pair(nx,ny),make_pair(na,nb)));
	}
      }
    }
  }
}
