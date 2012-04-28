#include<stdio.h>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
#define MP make_pair
#define MAX 765

int dx[6]={1,-1,0,0,0,0};
int dy[6]={0,0,1,-1,0,0};
int dz[6]={0,0,0,0,1,-1};
int ddir[6]={0,0,1,1,2,2};

int xx,yy,zz;
int sx,sy,sz,sdir;
int gx,gy,gz,gdir;
int ans;

bool board[30][30][30];

bool isin(int x,int y,int z){
  return ((1<=x && x<=xx) && (1<=y && y<=yy) && (1<=z && z<=zz));
}

bool oku(int x,int y,int z,vector<int> &mx,vector<int> &my,vector<int> &mz){
  //printf("  oku:(%d,%d,%d)\n",x,y,z);
  if(!isin(x,y,z))return false;
  if(board[x][y][z])return false;

  //printf("oketa:(%d,%d,%d)\n",x,y,z);
  board[x][y][z]=true;
  mx.push_back(x);
  my.push_back(y);
  mz.push_back(z);
  return true;
}

void saiki(int x,int y,int z,int dir,int num){

  //printf("\n");
  //printf("(%d,%d,%d) %d num=%d\n",x,y,z,dir,num);
  //printf("Block:");
  for(int i=0;i<=xx;i++)for(int j=0;j<=yy;j++)for(int k=0;k<=zz;k++){
        //if(board[i][j][k])printf("(%d,%d,%d)",i,j,k);
  }
  //printf("\n");

  if(x==gx && y==gy && z==gz && dir==gdir){
    ans=min(ans,num);
    return;
  }
  if(!isin(x,y,z))return;
  if(num>=6)return;

  for(int i=1;i<=2;i++){
    for(int j=0;j<6;j++){
      if(ddir[j]==ddir[dir])continue;
      //printf("try: i=%d j=%d\n",i,j);
      vector<int> mx,my,mz;

      int nx=x,ny=y,nz=z,ndir=dir;
      bool ok=true;

      ok&=oku(nx,ny,nz,mx,my,mz);
      for(int k=0;k<i;k++){
        nx+=dx[ndir];
        ny+=dy[ndir];
        nz+=dz[ndir];
        ok&=oku(nx,ny,nz,mx,my,mz);
      }

      ndir=j;
      int ii;
      if(i==1)ii=2;
      if(i==2)ii=1;
      for(int k=0;k<ii;k++){
        nx+=dx[ndir];
        ny+=dy[ndir];
        nz+=dz[ndir];
        ok&=oku(nx,ny,nz,mx,my,mz);
      }
      nx+=dx[ndir];
      ny+=dy[ndir];
      nz+=dz[ndir];

      if(!ok){
        for(int k=0;k<mx.size();k++){
          board[mx[k]][my[k]][mz[k]]=false;
          //printf("rej(%d,%d,%d)\n",mx[k],my[k],mz[k]);
        }
        continue;
      }

      //printf("Go! i=%d j=%d\n",i,j);
      saiki(nx,ny,nz,ndir,num+1);
      //printf("out\n");

      for(int k=0;k<mx.size();k++){
        board[mx[k]][my[k]][mz[k]]=false;
        //printf("rej(%d,%d,%d)\n",mx[k],my[k],mz[k]);
      }
    }
  }

  return;
}

int main(void){
  map<string,int> ma;
  ma["+x"]=0;
  ma["-x"]=1;
  ma["+y"]=2;
  ma["-y"]=3;
  ma["+z"]=4;
  ma["-z"]=5;

  for(int casenum=1;;casenum++){
    scanf("%d",&xx);
    if(xx==0)break;
    scanf("%d %d",&yy,&zz);
    for(int i=0;i<=xx;i++)for(int j=0;j<=yy;j++)for(int k=0;k<=zz;k++)board[i][j][k]=false;
    char ch[100];
    scanf("%d %d %d %s",&sx,&sy,&sz,ch);
    sdir=ma[string(ch)];
    scanf("%d %d %d %s",&gx,&gy,&gz,ch);
    gdir=ma[string(ch)];
    //if(sx==gx && sy==gy && sz==gz){
    //  ans=0;
    //}else{
      gx+=dx[gdir];
      gy+=dy[gdir];
      gz+=dz[gdir];
      ans=MAX;
      saiki(sx,sy,sz,sdir,0);
      //}
    printf("Case %d: ",casenum);
    if(ans==MAX)printf("Impossible\n");
    else printf("%d\n",ans);
  }
  return 0;
}
