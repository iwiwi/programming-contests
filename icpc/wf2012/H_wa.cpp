#include <stdio.h>
#include <complex>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
using namespace std;

typedef complex<double> point;

#define INF 1e12
#define EPS 1e-12

point readpt(){
  double x,y;
  scanf("%lf%lf",&x,&y);
  return point(x,y);
}

double dist[200][200];
double mindist[200][200];

double dot(point p,point q){return real(conj(p)*q);}
double det(point p,point q){return imag(conj(p)*q);}

int ccw(point a,point b,point c){
  b-=a;c-=a;
  if(det(b,c)>EPS)return 1;
  if(det(b,c)<-EPS)return -1;
  if(dot(b,c)<-EPS)return 2;
  if(abs(b)<abs(c)-EPS)return -2;
  return 0;
}

bool cross_s_s(point p1,point p2,point p3,point p4){
  return ccw(p1,p2,p3)*ccw(p1,p2,p4)<=0
    && ccw(p3,p4,p1)*ccw(p3,p4,p2)<=0;
}

point crosspt_s_s(point p1,point q1,point p2,point q2){
  point d1=q1-p1,d2=q2-p2;
  double d=det(d1,d2);
  return p1+d1*det(p2-p1,d2)/d;  
}

point reflect(point p,point a,point b){
  point d=(b-a)/abs(b-a);
  return 2.0*(a+d*dot(p-a,d))-p;
}

double calcdist(point p,point q,vector<pair<point,point> >& w){
  point now=p;
  vector<pair<point,point> > hoge;
  for(int i=0;i<w.size();i++){
    now=reflect(now,w[i].first,w[i].second);
    for(int j=0;j<i;j++){
      hoge[j].first=reflect(hoge[j].first,w[i].first,w[i].second);
      hoge[j].second=reflect(hoge[j].second,w[i].first,w[i].second);
    }
    hoge.push_back(w[i]);
  }
  double prev=0;
  for(int i=0;i<hoge.size();i++){
    if(!cross_s_s(now,q,hoge[i].first,hoge[i].second))return INF;
    point r=crosspt_s_s(now,q,hoge[i].first,hoge[i].second);
    if(prev>abs(r-now))return INF;
    prev=abs(r-now);
  }
  if(prev>abs(q-now))return INF;
  return abs(q-now);
}

int main(){
  for(int casenum=1;;casenum++){
    int n;
    if(scanf("%d",&n)<=0)return 0;
    point start=readpt();
    point p[500];
    for(int i=0;i<n;i++){
      p[i]=readpt();
    }
    for(int i=0;i<3*n;i++)p[i]=p[i%n];
    
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
	if(i==j)dist[i][j]=0;
	else{
	  int d=(j-i+n)%n;
	  if(d==1)dist[i][j]=abs(p[j]-p[i]);
	  else{
	    assert(d>=2);
	    vector<pair<point,point> > walls(d-2);
	    for(int k=1;k<d-1;k++){
	      walls[k-1]=make_pair(p[(i+k)%n],p[(i+k+1)%n]);
	    }
	    dist[i][j]=calcdist(p[i],p[j],walls);
	  }
	}
      }
    }
    for(int i=0;i<n;i++){
     for(int d=0;d<n;d++){
	int j=(i+d)%n;
	if(j==i){
	  mindist[i][j]=0;
	}else{
	  mindist[i][j]=dist[i][j];
	  for(int e=0;e<d;e++){
	      int k=(i+e)%n;
	      mindist[i][j]=min(mindist[i][j],mindist[i][k]+dist[k][j]);
	  }
	}
      }
     }
     for(int i=0;i<n;i++)for(int j=0;j<n;j++)printf("%d->%d:(d,md)=(%f,%f)\n",i,j,dist[i][j],mindist[i][j]);

    double ans=INF;
    for(int i=0;i<n;i++){
      for(int d=0;d<=n;d++){
	for(int e=0;e<=n;e++){
	  if(d==0 && e==n)continue;
	  if(d>e)continue;
	  vector<pair<point,point> > iw,fw;
	  for(int t=0;t<max(d-1,0);t++)iw.push_back(make_pair(p[(i+t)%n],p[(i+t+1)%n]));
	  for(int t=0;t<max(n-e-1,0);t++)fw.push_back(make_pair(p[(i-t+n)%n],p[(i-t-1+n)%n]));
	  reverse(fw.begin(),fw.end());
	  ans=min(ans,calcdist(start,p[(i+d)%n],iw)+mindist[(i+d)%n][(i+e)%n]+calcdist(p[(i+d)%n],start,fw));
	}
      }
    }
    for(int i=0;i<n;i++){
      vector<pair<point,point> > walls;
      for(int d=0;d<n;d++)walls.push_back(make_pair(p[(i+d)%n],p[(i+1+d)%n]));
      ans=min(ans,calcdist(start,start,walls));
    }
    printf("Case %d: %.2f\n",casenum,ans);
  }
}
