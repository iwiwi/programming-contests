#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<vector>
#include<string>
#include<queue>
#include<map>
#include<functional>
#include<algorithm>
using namespace std;
#define MP make_pair

int dx[8]={1,1,1,0,0,-1,-1,-1};
int dy[8]={1,0,-1,1,-1,1,0,-1};
int kx[8]={2,2,-2,-2,1,1,-1,-1};
int ky[8]={1,-1,1,-1,2,-2,2,-2};

int rx[4]={1,0,0,-1};
int ry[4]={0,1,-1,0};
int bx[4]={1,1,-1,-1};
int by[4]={1,-1,1,-1};

bool hit[(1<<15)+10][16][16];
char board[16][16];
int teki[16][16];
char nowboard[16][16];
int xx,yy;

int dp[(1<<15)+10][16][16];

bool range(int x,int y){
  return (0<=x && x<xx && 0<=y && y<yy);
}

int main(void){
  int n=0;
  int sx,sy;
  vector<int> tx,ty;
  vector<char> tt;
  scanf("%d %d",&yy,&xx);
  memset(teki,-1,sizeof(teki));
  for(int j=0;j<yy;j++){
    char ch[100];
    scanf("%s",ch);
    for(int i=0;i<xx;i++){
      if(ch[i]=='*'){
        ch[i]='.';
        sx=i;sy=j;
      }
      if(ch[i]!='.'){
        tx.push_back(i);
        ty.push_back(j);
        tt.push_back(ch[i]);
        teki[i][j]=tt.size()-1;
      }
      board[i][j]=ch[i];
    }
  }
  n=tt.size();
  for(int i=0;i<(1<<n);i++){
    for(int x=0;x<xx;x++)for(int y=0;y<yy;y++)nowboard[x][y]=board[x][y];
    for(int j=0;j<n;j++){
      if((i&(1<<j))==0)nowboard[tx[j]][ty[j]]='.';
    }
    for(int j=0;j<n;j++){
      if((i&(1<<j))==0)continue;
      int x=tx[j],y=ty[j];
      char t=tt[j];
      if(t=='K'){
        for(int k=0;k<8;k++){
          int nx=x+kx[k];
          int ny=y+ky[k];
          if(!range(nx,ny))continue;
          hit[i][nx][ny]=true;
        }
      }
      if(t=='R' || t=='B'){
        int rbx[4],rby[4];
        for(int k=0;k<4;k++){
          if(t=='R'){rbx[k]=rx[k];rby[k]=ry[k];}
          if(t=='B'){rbx[k]=bx[k];rby[k]=by[k];}
        }
        for(int k=0;k<4;k++){
          int nx=x,ny=y;
          while(1){
            nx+=rbx[k];
            ny+=rby[k];
            if(!range(nx,ny))break;
            hit[i][nx][ny]=true;
            if(nowboard[nx][ny]!='.')break;
          }
        }
      }
    }
  }
  memset(dp,-1,sizeof(dp));
  queue<pair<int,pair<int,int> > > qu;
  qu.push(MP((1<<n)-1,MP(sx,sy)));
  dp[(1<<n)-1][sx][sy]=0;
  bool dekita=false;
  while(qu.size()){
    int st=qu.front().first;
    int x=qu.front().second.first;
    int y=qu.front().second.second;
    //printf("%d (%d,%d) %d\n",st,x,y,dp[st][x][y]);
    qu.pop();
    if(st==0){printf("%d\n",dp[st][x][y]);dekita=true;break;}
    for(int i=0;i<8;i++){
      int nx=x+dx[i];
      int ny=y+dy[i];
      int nst=st;
      if(!range(nx,ny))continue;
      if(hit[st][nx][ny])continue;
      if(teki[nx][ny]!=-1 && (st&(1<<teki[nx][ny]))!=0){
        nst^=(1<<teki[nx][ny]);
      }
      if(dp[nst][nx][ny]!=-1)continue;
      dp[nst][nx][ny]=dp[st][x][y]+1;
      qu.push(MP(nst,MP(nx,ny)));
    }
  }
  if(!dekita){
    printf("-1\n");
  }
  return 0;
}
