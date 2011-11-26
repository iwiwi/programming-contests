#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
using namespace std;

#define INF 1e10
#define EPS 1e-10
vector<pair<double,int> > ev;

double g=9.8;
double v;

vector<double> hoge(double x,double y){
  double a=-(g*x*x)/(2*v*v);
  double b=x;
  double c=-(g*x*x)/(2*v*v)-y;
  double d=b*b-4*a*c;
  vector<double> ret;
  //printf("%f %f %f: \n",a,b,c);
  if(d>EPS){
    double s1=(-b+sqrt(d))/(2*a);
    double s2=(-b-sqrt(d))/(2*a);
    ret.push_back(s1);
    ret.push_back(s2);
    //printf("%f %f\n",s1,s2);
  }
  return ret;
}

void tate(double x,double yb,double yt){
  vector<double> retb,rett;
  retb=hoge(x,yb);
  rett=hoge(x,yt);
  if(rett.size()==2 && retb.size()==2){
    //assert(retb.size()==2);
    ev.push_back(make_pair(retb[0]-EPS,1));
    ev.push_back(make_pair(rett[0]+EPS,-1));
    ev.push_back(make_pair(rett[1]-EPS,1));
    ev.push_back(make_pair(retb[1]+EPS,-1));

    //printf("%lf to %lf\n",retb[0],rett[0]);
    //printf("%lf to %lf\n",rett[1],retb[1]);
  }else if(retb.size()==2){
    ev.push_back(make_pair(retb[0]-EPS,1));
    ev.push_back(make_pair(retb[1]+EPS,-1));
    //printf("%lf to %lf\n",retb[0],retb[1]);
  }
}

void yoko(double y,double xl,double xr){
  vector<double> retl,retr;
  retl=hoge(xl,y);
  retr=hoge(xr,y);
  if(retr.size()==2 && retl.size()==2){
    ev.push_back(make_pair(retr[0]-EPS,1));
    ev.push_back(make_pair(retl[0]+EPS,-1));
    ev.push_back(make_pair(retr[1]-EPS,1));
    ev.push_back(make_pair(retl[1]+EPS,-1));
    //printf("%lf to %lf\n",retr[0],retl[0]);
    //printf("%lf to %lf\n",retr[1],retl[1]);
  }else if(retl.size()==2){
    double t=sqrt(y/((v*v)/(2*g)-y));
    ev.push_back(make_pair(t-EPS,1));
    ev.push_back(make_pair(retl[1]+EPS,-1));
    //printf("%lf to %lf\n",t,retl[1]);
  }
}

main(){
  int n;
  double x,y;
  scanf("%d%lf%lf%lf",&n,&v,&x,&y);
  double xl[100],xr[100],yb[100],yt[100];
  for(int i=0;i<n;i++){
    scanf("%lf%lf%lf%lf",&xl[i],&yb[i],&xr[i],&yt[i]);
    if(xl[i]==0 && yb[i]==0){puts("No");return 0;}
  }
  for(int i=0;i<n;i++){
    if(xr[i]<x){
      tate(xl[i],yb[i],yt[i]);
      tate(xr[i],yb[i],yt[i]);
      yoko(yb[i],xl[i],xr[i]);
      yoko(yt[i],xl[i],xr[i]);
    }else if(xl[i]<x){
      tate(xl[i],yb[i],yt[i]);
      yoko(yb[i],xl[i],x);
      yoko(yt[i],xl[i],x);
    }else if(xl[i]==x){
      tate(xl[i],yb[i],yt[i]);
    }
  }
  tate(x,-1e30,y);
  sort(ev.begin(),ev.end());
  //for(int i=0;i<ev.size();i++)printf("%d at %f\n",ev[i].second,ev[i].first);
  int cnt=0;
  if(ev[0].first>EPS*10 || ev.back().first<-EPS*10){puts("Yes");return 0;}
  double prev=ev[0].first;
  cnt++;
  for(int i=1;i<ev.size();i++){
    double hoge=ev[i].first;
    if(hoge-prev>1e-10 && cnt==0){
      puts("Yes");
      return 0;
    }

    prev=hoge;
    cnt+=ev[i].second;
  }
  puts("No");
  return 0;
}
