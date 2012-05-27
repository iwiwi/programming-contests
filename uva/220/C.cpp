#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
int a[20][20][20][100];

int x0[3000],x1[3000],y0[3000],y1[3000],z0[3000],z1[3000],w0[3000],w1[3000];

main(){
  for(int casenum=1;;casenum++){
    int n,xsiz,ysiz,zsiz,wsiz,q;
    scanf("%d%d%d%d%d",&n,&xsiz,&ysiz,&zsiz,&q);
    if(n==0 && xsiz==0 && ysiz==0 && zsiz==0 && q==0)return 0;
    wsiz=96;
    for(int i=0;i<n;i++){
      char t0[20],t1[20];
      scanf("%d%d%d%d%d%d%s%s",&x0[i],&y0[i],&z0[i],&x1[i],&y1[i],&z1[i],t0,t1);
      int hour,minute;
      sscanf(t0,"%d:%d",&hour,&minute);w0[i]=hour*4+minute/15;
      sscanf(t1,"%d:%d",&hour,&minute);w1[i]=hour*4+minute/15;
    }
    printf("3D World %d:\n",casenum);
    for(int qq=0;qq<q;qq++){
      int xx,yy,zz;
      char tt[20];
      scanf("%d%d%d%s",&xx,&yy,&zz,tt);
      int hour,minute;
      sscanf(tt,"%d:%d",&hour,&minute);int ww=hour*4+minute/15;
      memset(a,0,sizeof(a));
      for(int i=0;i<n;i++){
 
        int px0=max(0,x0[i]-xx+1);
        int px1=min(xsiz-xx+1,x1[i]);
        int py0=max(0,y0[i]-yy+1);
        int py1=min(ysiz-yy+1,y1[i]);
        int pz0=max(0,z0[i]-zz+1);
        int pz1=min(zsiz-zz+1,z1[i]);
        int pw0=max(0,w0[i]-ww+1);
        int pw1=min(wsiz-ww+1,w1[i]);
        
        /*
        int px0=max(0,x0[i]-xx);
        int px1=min(xsiz-xx+1,x1[i]+1);
        int py0=max(0,y0[i]-yy);
        int py1=min(ysiz-yy+1,y1[i]+1);
        int pz0=max(0,z0[i]-zz);
        int pz1=min(zsiz-zz+1,z1[i]+1);
        int pw0=max(0,w0[i]-ww);
        int pw1=min(wsiz-ww+1,w1[i]+1);
        */

        //printf("%d %d  %d %d  %d %d  %d %d\n",px0,px1,py0,py1,pz0,pz1,pw0,pw1);
        /*
        a[px0][py0][pz0][pw0]=1;
        a[px0][py0][pz0][pw1]=-1;
        a[px0][py0][pz1][pw0]=-1;
        a[px0][py0][pz1][pw1]=1;
        a[px0][py1][pz0][pw0]=-1;
        a[px0][py1][pz0][pw1]=1;
        a[px0][py1][pz1][pw0]=1;
        a[px0][py1][pz1][pw1]=-1;
        a[px1][py0][pz0][pw0]=-1;
        a[px1][py0][pz0][pw1]=1;
        a[px1][py0][pz1][pw0]=1;
        a[px1][py0][pz1][pw1]=-1;
        a[px1][py1][pz0][pw0]=1;
        a[px1][py1][pz0][pw1]=-1;
        a[px1][py1][pz1][pw0]=-1;
        a[px1][py1][pz1][pw1]=1;
        */
        
        for(int b=0;b<16;b++){
          int px,py,pz,pw;
          if(b&1)px=px1; else px=px0;
          if(b&2)py=py1; else py=py0;
          if(b&4)pz=pz1; else pz=pz0;
          if(b&8)pw=pw1; else pw=pw0;
          a[px][py][pz][pw]+=(__builtin_popcount(b)%2==1?-1:1);
        }
        
      }
      for(int t=0;t<4;t++){
        for(int i=0;i<xsiz-xx+1;i++){
          for(int j=0;j<ysiz-yy+1;j++){
            for(int k=0;k<zsiz-zz+1;k++){
              for(int l=0;l<wsiz-ww+1;l++){
                if(t==0){
                  if(i>0)a[i][j][k][l]+=a[i-1][j][k][l];
                }else if(t==1){
                  if(j>0)a[i][j][k][l]+=a[i][j-1][k][l];
                }else if(t==2){
                  if(k>0)a[i][j][k][l]+=a[i][j][k-1][l];
                }else if(t==3){
                  if(l>0)a[i][j][k][l]+=a[i][j][k][l-1];
                }
              }
            }
          }
        }
      }
      int ans=0;
      for(int l=0;l<wsiz-ww+1;l++){
        for(int i=0;i<xsiz-xx+1;i++){
          for(int j=0;j<ysiz-yy+1;j++){
            for(int k=0;k<zsiz-zz+1;k++){
              if(a[i][j][k][l]<0) printf("%d %d %d %d:%d\n",i,j,k,l,a[i][j][k][l]);
              assert(a[i][j][k][l]>=0);
              if(a[i][j][k][l]==0)ans++;
            }
          }
        }
      }
      if(ans>0)printf("%d safe place(s) found\n",ans);
      else printf("No safe place(s) found\n");
    }
  }
}
