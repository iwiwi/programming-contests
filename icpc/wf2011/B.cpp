#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
int calc(int p,int q,int r,int x,int y,int z){
  vector<int> cons;
  if(p-q!=0){if((x-y)%(p-q)!=0)return 0; else cons.push_back((x-y)/(p-q));} else{if(x-y!=0)return 0;}
  if(q-r!=0){if((y-z)%(q-r)!=0)return 0; else cons.push_back((y-z)/(q-r));} else{if(y-z!=0)return 0;}
  if(r-p!=0){if((x-x)%(r-p)!=0)return 0; else cons.push_back((z-x)/(r-p));} else{if(z-x!=0)return 0;}
  if(cons.empty())return 2;
  sort(cons.begin(),cons.end());
  if(cons[0]!=cons.back())return 0;
  if(cons[0]==0)return 0;
  return 1;
}

main(){
  //printf("%d must be 1\n",calc(0,1,2,4,5,6));
  //printf("%d must be 2\n",calc(0,0,0,));

  for(int casenum=1;;casenum++){
    int x[6],y[6];
    scanf("%d%d%d%d%d%d",&x[0],&y[0],&x[1],&y[1],&x[2],&y[2]);
    if(x[0]==0 && y[0]==0 && x[1]==0 && y[1]==0 && x[2]==0 && y[2]==0)return 0;
    scanf("%d%d%d%d%d%d",&x[3],&y[3],&x[4],&y[4],&x[5],&y[5]);
    int ans=0;
    for(int i=0;i<40;i++){
      int rx,ry;
      if(i<20){rx=10;ry=i-10;}else{rx=30-i;ry=10;}
      double c=rx/sqrt(rx*rx+ry*ry);
      double s=ry/sqrt(rx*rx+ry*ry);
      int ix[3],iy[3];
      for(int k=0;k<3;k++){
        ix[k]=(int)floor(x[k]*c-y[k]*s+0.5);
        iy[k]=(int)floor(x[k]*s+y[k]*c+0.5);
      }
      //printf("%d %d %d %d %d %d\n",ix[0],iy[0],ix[1],iy[1],ix[2],iy[2]);
      int perm[3]={3,4,5};
      do{
        //printf("calcx %d %d %d; %d %d %d=%d\n",ix[0],ix[1],ix[2],x[perm[0]],x[perm[1]],x[perm[2]],calc(ix[0],ix[1],ix[2],x[perm[0]],x[perm[1]],x[perm[2]]));
        //printf("calcy %d %d %d; %d %d %d=%d\n",iy[0],iy[1],iy[2],y[perm[0]],y[perm[1]],y[perm[2]],calc(iy[0],iy[1],iy[2],y[perm[0]],y[perm[1]],y[perm[2]]));
        ans+=calc(ix[0],ix[1],ix[2],x[perm[0]],x[perm[1]],x[perm[2]])*calc(iy[0],iy[1],iy[2],y[perm[0]],y[perm[1]],y[perm[2]]);
      }while(next_permutation(perm,perm+3));
      //printf("ans=%d\n",ans);
    }
    printf("Case %d: ",casenum);
    if(ans==0)puts("no solution");
    if(ans==1)puts("equivalent solutions");
    if(ans>=2)puts("inconsistent solutions");
  }
}
