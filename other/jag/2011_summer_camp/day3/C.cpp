#include<stdio.h>
#include<string.h>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
#define MP make_pair
typedef long long ll;

const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};

int xx,yy,n;
char board[100][100];
int mat[3][100][100];
int tx[2000],ty[2000];

bool routeok;
vector<pair<int,int> > route;
bool check[100][100];

vector<pair<int,int> > allroute;

int turn[100][100];

void search(int sx,int sy,int gx,int gy){
	//printf("(%d,%d)\n",sx,sy);
	check[sx][sy]=true;
	if(routeok)return;
	route.push_back(MP(sx,sy));
	if(sx==gx && sy==gy){
		//printf("oh!\n");
		routeok=true;
		return;
	}
	for(int k=0;k<4;k++){
		int nx=sx+dx[k];
		int ny=sy+dy[k];
		if(!(0<=nx && nx<xx && 0<=ny && ny<yy))continue;
		if(board[nx][ny]=='#')continue;
		if(check[nx][ny])continue;
		search(nx,ny,gx,gy);
		if(routeok)return;
	}
	route.pop_back();
	return;
}

int main(void){
	scanf("%d %d %d",&yy,&xx,&n);
	for(int j=0;j<yy;j++){
		char ch[1000];
		scanf("%s",ch);
		for(int i=0;i<xx;i++)board[i][j]=ch[i];
	}
	for(int k=0;k<3;k++){
		for(int j=0;j<yy;j++){
			for(int i=0;i<xx;i++){
				scanf("%d",&mat[k][i][j]);
			}
		}
	}
	for(int i=0;i<n;i++){
		scanf("%d %d",&ty[i],&tx[i]);
	}

	for(int k=0;k<n-1;k++){
		routeok=false;
		route.clear();
		for(int i=0;i<xx;i++)for(int j=0;j<yy;j++)check[i][j]=false;
		//if(tx[k]==tx[k+1] && ty[k]==ty[k+1])continue;
		search(tx[k],ty[k],tx[k+1],ty[k+1]);
		//printf("%d : (%d)\n",k,(int)route.size());
		for(int i=0;i<(int)route.size();i++)allroute.push_back(route[i]);
	}
	allroute.erase(unique(allroute.begin(),allroute.end()),allroute.end());

	memset(turn,-1,sizeof(turn));
	ll ans=0;
	//printf("[%d]\n",(int)allroute.size());
	for(int i=0;i<(int)allroute.size();i++){
		int x=allroute[i].first;
		int y=allroute[i].second;
		//printf("%d %d\n",x,y);
		if(turn[x][y]==-1){
			ans+=mat[1][x][y];
			turn[x][y]=i;
		}else{
			ll a=((ll)i-(ll)turn[x][y])*(ll)mat[0][x][y];
			ll b=(ll)mat[1][x][y]+(ll)mat[2][x][y];
			ans+=min(a,b);
			turn[x][y]=i;
		}
	}
	for(int i=0;i<xx;i++){
		for(int j=0;j<yy;j++){
			if(turn[i][j]==-1)continue;
			ans+=mat[2][i][j];
		}
	}
	
	printf("%lld\n",ans);

	return 0;
}

