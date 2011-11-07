#include <stdio.h>
#include <string.h>
#include <math.h>
#include <utility>
#include <algorithm>
using namespace std;
#define INF 1e12
int numv[60];
int px[60][30];
int py[60][30];
int edg[60][30][30];

double dist[60][30][60][30];

int sqnorm(int x,int y){
  return x*x+y*y;
}

int dot(int x1,int y1,int x2,int y2){return x1*x2+y1*y2;}
int det(int x1,int y1,int x2,int y2){return x1*y2-x2*y1;}

main(){
  for(;;){
    memset(numv,0,sizeof(numv));
    memset(px,0,sizeof(px));
    memset(py,0,sizeof(py));
    memset(edg,0,sizeof(edg));

    int n;
    scanf("%d",&n);
    if(n==0)return 0;

    for(int i=0;i<n;i++)for(int j=0;j<n;j++)for(int k=0;k<20;k++)for(int l=0;l<20;l++)dist[i][k][j][l]=((i==j&&k==l)?0:INF);

    for(int i=0;i<n;i++){
      scanf("%d",&numv[i]);
      for(int j=0;j<numv[i];j++)scanf("%d%d",&px[i][j],&py[i][j]);
      int b;
      scanf("%d",&b);
      for(int j=0;j<b;j++){
        int p,q;
        scanf("%d%d",&p,&q);
        p--;q--;
        edg[i][p][q]=edg[i][q][p]=1;
        dist[i][p][i][q]=dist[i][q][i][p]=hypot((double)px[i][p]-px[i][q],(double)py[i][p]-py[i][q]);
      }
      int c;
      scanf("%d",&c);
      for(int j=0;j<c;j++){
        int p,x,q;
        scanf("%d%d%d",&p,&x,&q);
        p--;x--;q--;
        dist[i][p][x][q]=0;
      }
    }
    int sl,sn;
    int dl,dn;
    scanf("%d%d%d%d",&sl,&sn,&dl,&dn);
    sl--;sn--;dl--;dn--;
    for(int i=0;i<n;i++){
      for(int j=0;j<i;j++){
        if(numv[j]!=numv[i])continue;
        //bool same=false;
        for(int p=0;p<numv[j];p++){
          for(int q=0;q<numv[j];q++){
            if(p==q)continue;
            if(sqnorm(px[i][0]-px[i][1],py[i][0]-py[i][1])!=sqnorm(px[j][p]-px[j][q],py[j][p]-py[j][q]))continue;
            pair<pair<int,int>,int> ngi[numv[i]],ngj[numv[j]];
            for(int r=0;r<numv[i];r++){
              int ni=dot(px[i][1]-px[i][0],py[i][1]-py[i][0],px[i][r]-px[i][0],py[i][r]-py[i][0]);
              int gi=det(px[i][1]-px[i][0],py[i][1]-py[i][0],px[i][r]-px[i][0],py[i][r]-py[i][0]);
              int nj=dot(px[j][q]-px[j][p],py[j][q]-py[j][p],px[j][r]-px[j][p],py[j][r]-py[j][p]);
              int gj=det(px[j][q]-px[j][p],py[j][q]-py[j][p],px[j][r]-px[j][p],py[j][r]-py[j][p]);
              ngi[r]=make_pair(make_pair(ni,gi),r);
              ngj[r]=make_pair(make_pair(nj,gj),r);
            }
            sort(ngi,ngi+numv[i]);
            sort(ngj,ngj+numv[j]);
            bool ng=false;
            for(int r=0;r<numv[i];r++)if(ngi[r].first!=ngj[r].first)ng=true;
            if(ng)continue;
            for(int r=0;r<numv[i];r++){
              for(int s=0;s<numv[i];s++){
                if(edg[i][ngi[r].second][ngi[s].second]!=edg[j][ngj[r].second][ngj[s].second])ng=true;
              }
            }
            if(ng)continue;
            //printf("%d-%d: 0->%d 1->%d\n",i,j,p,q);
            for(int r=0;r<numv[i];r++){
              dist[i][ngi[r].second][j][ngj[r].second]=0;
              dist[j][ngj[r].second][i][ngi[r].second]=0;
              //printf ("%d %d=%d %d\n",i,ngi[r].second,j,ngj[r].second);
            }
            //same=true;
            //break;
          }
          //if(same)break;
        }
        //if(same)break;
      }
    }
    /*
    for(int i=0;i<n;i++)for(int p=0;p<numv[i];p++)for(int j=0;j<n;j++)for(int q=0;q<numv[j];q++){
            if(dist[i][p][j][q]<INF)printf("%d %d - %d %d: %f\n",i,p,j,q,dist[i][p][j][q]);
          }
    */
    double cost[60][30];
    bool kimata[60][30];
    for(int i=0;i<n;i++)for(int j=0;j<numv[i];j++){cost[i][j]=INF;kimata[i][j]=false;}
    cost[sl][sn]=0;
    for(;;){
      double m=INF;
      int mi=-1,mj=-1;
      for(int i=0;i<n;i++){
        for(int j=0;j<numv[i];j++){
          if(!kimata[i][j] && cost[i][j]<m){m=cost[i][j];mi=i;mj=j;}
        }
      }
      if(mi==-1)break;

      //printf("%d %d: %f\n",mi,mj,cost[mi][mj]);
      kimata[mi][mj]=true;
      for(int i=0;i<n;i++){
        for(int j=0;j<numv[i];j++){
          cost[i][j]=min(cost[i][j],cost[mi][mj]+dist[mi][mj][i][j]);
        }
      }
    }
    double ans;
    if(cost[dl][dn]>=INF-1)ans=-1;
    else ans=cost[dl][dn];
    printf("%.10f\n",ans);
  }
}
