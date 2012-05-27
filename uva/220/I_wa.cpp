#include <stdio.h>
#include <complex>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

#define EPS 1e-9

typedef complex<double> point;

point readpt(){double x,y;scanf("%lf%lf",&x,&y);return point(x,y);}

vector<point> pts;
vector<int> vcost;
int v;
vector<pair<int,int> > adj[2000];
int n;
double a[50],b[50],c[50];

bool matagu(point p1,point p2){
  for(int i=0;i<n;i++){
    double val1=a[i]*real(p1)+b[i]*imag(p1)+c[i];
    double val2=a[i]*real(p2)+b[i]*imag(p2)+c[i];
    if(val1<-EPS && val2>EPS)return true;
    if(val2<-EPS && val1>EPS)return true;
  }
  return false;
}

int dist[2000][2000];

point tocpx(pair<double,double> hoge){return point(hoge.first,hoge.second);}

main(){
  for(int casenum=1;;casenum++){
    int cnum;
    int q;
    scanf("%d%d%d",&n,&cnum,&q);
    if(n==0)return 0;
    for(int i=0;i<n;i++){
      scanf("%lf%lf%lf",&a[i],&b[i],&c[i]);
    }
    double x[1010],y[1010],cost[1010];
    point pc[1010];
    for(int i=0;i<cnum;i++){
      scanf("%lf%lf%lf",&x[i],&y[i],&cost[i]);
      pc[i]=point(x[i],y[i]);
    }
    printf("Case %d:\n",casenum);
    v=0;
    pts.clear();
    for(int i=0;i<n;i++){
      vector<pair<double,pair<double,double> > > koten;
      for(int j=0;j<n;j++){
        if(i!=j){
          double bunbo=a[i]*b[j]-b[i]*a[j];
          double cx=(-c[i]*b[j]+c[j]*b[i])/bunbo;
          double cy=(-a[i]*c[j]+a[j]*c[i])/bunbo;
          double naiseki=cx*b[i]-cy*a[i];
          koten.push_back(make_pair(naiseki,make_pair(cx,cy)));
        }
      }
      sort(koten.begin(),koten.end());
      if(koten.size()>1){
        for(int p=0;p<koten.size()-1;p++)pts.push_back((tocpx(koten[p].second)+tocpx(koten[p+1].second))/2.0);
        pts.push_back(tocpx(koten[0].second)-point(b[i],-a[i]));
        pts.push_back(tocpx(koten[koten.size()-1].second)+point(b[i],-a[i]));
      }else{
        pts.push_back(tocpx(koten[0].second)+point(b[i],-a[i]));
        pts.push_back(tocpx(koten[0].second)-point(b[i],-a[i]));
      }
    }
    vcost.resize(pts.size());
    for(int i=0;i<pts.size();i++){
      vcost[i]=1;
    }
    for(int i=0;i<pts.size();i++){
      for(int j=0;j<cnum;j++){
        if(!matagu(pts[i],pc[j]))vcost[i]+=cost[j];
      }
    }
    for(int qq=0;qq<q;qq++){
      point start,goal;
      start=readpt();
      goal=readpt();
      pts.push_back(start);
      pts.push_back(goal);
      vcost.push_back(0);
      vcost.push_back(0);
      //write here
      int v=pts.size();      
      for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
          if(i==j)dist[i][j]=0;
          else if(matagu(pts[i],pts[j]))dist[i][j]=1010101010;
          else dist[i][j]=vcost[j];
        }
      }
      int dijk[2000];
      int chk[2000]={};
      for(int i=0;i<v;i++)dijk[i]=1010101010;
      dijk[v-2]=0;
      /*
      for(int i=0;i<v;i++){
        for(int j=0;j<v;j++)printf("%2d ",dist[i][j]==1010101010?-8:dist[i][j]);puts("");
      }
      */
      for(;;){
        int mincost=1010101010,mi=-1;
        for(int i=0;i<v;i++){
          if(chk[i]==0){
            if(dijk[i]<mincost)mincost=dijk[i],mi=i;
          }
        }
        //printf("%d %d\n",mincost,mi);
        chk[mi]=1;
        if(mi==v-1){
          break;
        }
        for(int j=0;j<v;j++){
          dijk[j]=min(dijk[j],dijk[mi]+dist[mi][j]);
        }
      }
      
      //for(int k=0;k<v;k++)for(int i=0;i<v;i++)for(int j=0;j<v;j++)dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
      printf("%d\n",dijk[v-1]);
      //printf("%d\n",dist[v-2][v-1]);
      pts.pop_back();
      pts.pop_back();
      vcost.pop_back();
      vcost.pop_back();
    }
  }
}
