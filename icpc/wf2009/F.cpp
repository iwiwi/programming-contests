#include <stdio.h>
#include <complex>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef complex<int> point;

namespace std{
  bool operator < (const point& a,const point& b){
    return real(a)-real(b)!=0?real(a)<real(b):imag(a)<imag(b);
  }
}

int n;
double margin;
point p[20];

int grpcnt;
int grp[20];

double ans;

int dot(point p,point q){return real(conj(p)*q);}
int det(point p,point q){return imag(conj(p)*q);}
double myabs(point p){return sqrt((double)real(p)*real(p)+(double)imag(p)*imag(p));}

int ccw(point a,point b,point c){
  b-=a;c-=a;
  if(det(b,c)>0)return 1;
  if(det(b,c)<0)return -1;
  if(dot(b,c)<0)return 2;
  if(myabs(b)<myabs(c)-(1e-9))return -2;
  return 0;
}

vector<point> convexhull(vector<point> p){
  if(p.size()<=2)return p;
  int n=p.size(),k=0;
  sort(p.begin(),p.end());
  vector<point> ch(2*n);
  for(int i=0;i<n;ch[k++]=p[i++])
    while(k>=2 && ccw(ch[k-2],ch[k-1],p[i])<=0)k--;
  for(int i=n-2,t=k+1;i>=0;ch[k++]=p[i--])
    while(k>=t && ccw(ch[k-2],ch[k-1],p[i])<=0)k--;
  ch.resize(k-1);
  return ch;
}

double now;

double hoge[2012];

void saiki(int pos){
  //for(int i=0;i<n;i++)printf("%d",grp[i]);printf("\n");

  if(pos==n){
    //for(int i=0;i<n;i++)printf("%d",grp[i]);printf(": %f\n",now);
    ans=min(ans,now);
  }else{
    if(grp[pos]!=-1){saiki(pos+1);return;}
    int emp[10],empcnt=0;
    for(int i=pos+1;i<n;i++){
      if(grp[i]==-1)emp[empcnt++]=i;
    }
    for(int b=0;b<(1<<empcnt);b++){
      int c=0;
      grp[pos]=grpcnt;
      c+=(1<<pos);
      for(int k=0;k<empcnt;k++){
        if((b>>k)&1){
          grp[emp[k]]=grpcnt;
          c+=(1<<emp[k]);
        }
      }
      grpcnt++;
      
      now+=hoge[c];

      saiki(pos+1);

      now-=hoge[c];

      grp[pos]=-1;
      for(int k=0;k<empcnt;k++){
        if((b>>k)&1)grp[emp[k]]=-1;
      }
      grpcnt--;
    }
  }
}

point readpt(){int x,y;scanf("%d%d",&x,&y);return point(x,y);}

int main(){
  for(int casenum=1;;casenum++){
    scanf("%d%lf",&n,&margin);
    if(n==0 && margin==0)return 0;
    for(int i=0;i<n;i++)p[i]=readpt();

    for(int b=1;b<(1<<n);b++){
      vector<point> pts;
      for(int i=0;i<n;i++)if((b>>i)&1)pts.push_back(p[i]);
      vector<point> ret=convexhull(pts);
      hoge[b]=0;
      for(int i=0;i<(int)ret.size();i++)hoge[b]+=myabs(ret[i]-ret[(i+1)%ret.size()]);
      hoge[b]+=margin*2*M_PI;
    }
    //puts("hoge");
    ans=1e9;
    now=0;
    for(int i=0;i<n;i++)grp[i]=-1;
    saiki(0);
    printf("Case %d: length = %.2f\n",casenum,ans);
  }
}
