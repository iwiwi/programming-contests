#include <stdio.h>
#include <complex>
#include <algorithm>
#include <utility>
#include <vector>
#include <math.h>
using namespace std;

#define EPS 1e-9

typedef complex<double> point;

int n,r;

point readpt(){
  double x,y;
  scanf("%lf%lf",&x,&y);
  return point(x,y);
}

main(){
  for(;;){
    int n;
    double R;
    scanf("%d%lf",&n,&R);
    if(n==0 && R==0)return 0;
    point c[200];
    double r[200];
    for(int i=0;i<n;i++){
      c[i]=readpt();//*point(cos(1),sin(1));
      scanf("%lf",&r[i]);
    }
    bool dekasugi=false;
    for(int i=0;i<n;i++)if(r[i]>=R)dekasugi=true;
    if(dekasugi){puts("0.0");continue;}
    int nochan=0;
    double ans=2*M_PI*R;
    //printf("plus %f\n",2*M_PI*R);
    for(int i=0;i<n;i++){
      int cnt=0;
      vector<pair<double,int> > ev;
      for(int j=0;j<n;j++){
	if(i==j){cnt++;continue;}

	double a=abs(c[j]-c[i]);
	double b=R-r[i];
	double x=R-r[j];
	double hoge=(a*a+b*b-x*x)/(2*a*b);
	if(hoge<-1+EPS)cnt++;
	else if(hoge<1-EPS){
	  double theta=acos(hoge);
	  double t1=arg(c[j]-c[i])+theta,t2=arg(c[j]-c[i])-theta;
	  while(t1>M_PI)t1-=2*M_PI;
	  while(t1<-M_PI)t1+=2*M_PI;
	  while(t2>M_PI)t2-=2*M_PI;
	  while(t2<-M_PI)t2+=2*M_PI;
	  if(t1<t2)cnt++;
	  ev.push_back(make_pair(t1,-1));
	  ev.push_back(make_pair(t2,+1));
	}
      }
      sort(ev.begin(),ev.end());
      //printf("initial cnt=%d\n",cnt);
      //printf("ev.size()=%d\n",(int)ev.size());
      //for(int k=0;k<ev.size();k++)printf("%f %d\n",ev[k].first,ev[k].second);
      if(ev.size()==0){
	//printf("%d\n",cnt);
	//if(cnt==n)printf("plus %f\n",2*M_PI*(R-r[i]));
	if(cnt==n)ans+=2*M_PI*(R-r[i]);
	else nochan++;
      }else{
	int maxcnt=cnt;
	if(cnt==n)ans+=(ev[0].first-(-M_PI))*(R-r[i]);
	for(int k=0;k<ev.size();k++){
	  cnt+=ev[k].second;
	  maxcnt=max(maxcnt,cnt);
	  if(cnt==n){
	    double tugi=(k==ev.size()-1?M_PI:ev[k+1].first);
	    ans+=(tugi-ev[k].first)*(R-r[i]);
	  }
	}
	if(maxcnt<n)nochan++;
      }
    }
    if(nochan==n)puts("0.0");
    else printf("%.12f\n",ans);
  }
}
