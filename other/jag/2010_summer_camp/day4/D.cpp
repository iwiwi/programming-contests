#include <stdio.h>
#include <queue>
#include <algorithm>
#include <utility>
#define INF 1e9
using namespace std;

int wall[200][200];

int chk[100][100];
int cost[100][100];
int xsize,ysize;
int sx,sy,gx,gy;

int bfs(void){
	queue<pair<int,int> > que;
	
	que.push(make_pair(sx,sy));
	for(int i=0;i<xsize;i++)for(int j=0;j<ysize;j++){chk[i][j]=0;cost[i][j]=INF;}
	cost[sx][sy]=0;
	chk[sx][sy]=1;
	int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
	
	for(;!que.empty();){
		pair<int,int> t=que.front();
		que.pop();
		int x=t.first,y=t.second;
		if(x==gx && y==gy)break;
		for(int d=0;d<4;d++){
			int nx=x+dx[d],ny=y+dy[d];
			if(nx>=0 && nx<xsize && ny>=0 && ny<ysize && wall[x+nx][y+ny]==0 && chk[nx][ny]==0){
				que.push(make_pair(nx,ny));
				cost[nx][ny]=cost[x][y]+1;
				chk[nx][ny]=1;
			}
		}
	}
	/*
	for(int j=0;j<ysize;j++){
		for(int i=0;i<xsize;i++){
			printf("%d ",cost[i][j]);
		}
		puts("");
	}
	puts("");
	*/
	return cost[gx][gy];
}

main(){
	int n;
	scanf("%d%d%d",&xsize,&ysize,&n);
	for(int i=0;i<n;i++){
		int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1==x2){
			for(int i=min(y1,y2);i<max(y1,y2);i++){
				if(x1+x2-1>=0)wall[x1+x2-1][i+i+1-1]=1;
			}
		}else{
			for(int i=min(x1,x2);i<max(x1,x2);i++){
				if(y1+y2-1>=0)wall[i+i+1-1][y1+y2-1]=1;
			}
		}
	}
	scanf("%d%d%d%d",&sx,&sy,&gx,&gy);
	
	int init=bfs();
	
	int ans=0;
	
	for(int i=0;i<=2*xsize-2;i++){
		for(int j=0;j<=2*ysize-2;j++){
			if((i+j)%2==0)continue;
			if(wall[i][j]==1)continue;
			
			wall[i][j]=1;
			
			int d=bfs();
			
			if(d!=INF){
				ans=max(ans,d-init);
			}
			
			wall[i][j]=0;
		}
	}
	printf("%d\n",ans);
}