#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <complex>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#define EPS 1e-9
#define INF 1e9
typedef complex<double> point;
int n;
point pt,pp;
double vt,vp;

point readp(){
  double x,y;
  scanf("%lf%lf",&x,&y);
  return point(x,y);
}

//double dot(point p,point q){return real(conj(p)*q);}
//double det(point p,point q){return imag(conj(p)*q);}
/*
double myabs(point p){
  return sqrt(p.real()*p.real()+p.imag()*p.imag());
}
*/
double sol1(vector<point> p,int ip){
  //puts("sol1");
  //for(int i=0;i<=n;i++){
  //  cout << p[i] << (i==ip?"kokokara start":"")<< endl;
  // }
  double len1=0,len2=0;
  for(int i=0;i<ip;i++)len1+=abs(p[i]-p[i+1]);
  for(int i=ip;i<n;i++)len2+=abs(p[i]-p[i+1]);
  double lb=0,ub=len2;
  for(int z=0;z<100;z++){
    double mid=(z==0?ub:(lb+ub)/2);
    //printf("try to stop at %f\n",mid);
    double len;
    len=0;
    point hoge;
    for(int i=ip;i<n;i++){
      double d=abs(p[i]-p[i+1]);
      if(len+d<mid-EPS){
	len+=d;
      }else{
	hoge=(mid-len)/d*(p[i+1]-p[i])+p[i];
	break;
      }
    }
    //cout << "hoge=" << hoge << endl;
    len=0;
    bool ok=false;
    for(int i=ip-1;i>=0;i--){
      double lb2=0,ub2=1;
      double d=abs(p[i+1]-p[i]);
      for(int zz=0;zz<100;zz++){
	double mid2=(lb2+ub2)/2;
	point piyo=p[i+1]+(p[i]-p[i+1])*mid2;
	if(abs(piyo-pp)/vp>EPS+(len+d*mid2)/vt)lb2=mid2;
	else ub2=mid2;
      }
      double lb3=0,ub3=1;
      for(int zz=0;zz<100;zz++){
	double mid3=(lb3+ub3)/2;
	point piyo=p[i+1]+(p[i]-p[i+1])*mid3;
	if(abs(piyo-hoge)/vp>EPS+(mid-len-d*mid3)/vt)ub3=mid3;
	else lb3=mid3;
      }
      if(abs(p[i]-pp)/vp>EPS+(len+d)/vt)lb2=2;
      if(abs(p[i+1]-hoge)/vp>EPS+(mid-len)/vt)lb3=-1;
      //cout << i+1 << "-->" <<i << ":" << lb2 << " " << lb3 <<endl; 
      if(lb2<EPS+lb3){
	ok=true;
      }
      len+=d;
    }
    if(z>0){
      if(ok)ub=mid;
      else lb=mid;
    }else{
      if(!ok)return INF;
    }
    //puts(ok?"success":"failed");
  }
  return lb/vt;
}

double sol2(vector<point> p,int ip){
  double len1=0,len2=0;
  for(int i=0;i<ip;i++)len1+=abs(p[i]-p[i+1]);
  for(int i=ip;i<n;i++)len2+=abs(p[i]-p[i+1]);
  double lb=0,ub=len2;
  double dist;
  for(int z=0;z<100;z++){
    double mid=(z==0?ub:(lb+ub)/2);
    double len=0;
    point hoge;
    for(int i=ip;i<n;i++){
      double d=abs(p[i]-p[i+1]);
      if(len+d<mid-EPS){
	len+=d;
      }else{
	hoge=(mid-len)/d*(p[i+1]-p[i])+p[i];
	break;
      }
    }
    dist=abs(hoge-pp);
    if(z>0){
      if(dist/vp>EPS+mid/vt)lb=mid;
      else ub=mid;
    }else{
      if(dist/vp>EPS+mid/vt)return INF;
    }
  }
  return max(dist/vp,len1/vt);
}

double sol3(vector<point> p,int ip){
  double len1=0,len2=0;
  for(int i=0;i<ip;i++)len1+=abs(p[i]-p[i+1]);
  for(int i=ip;i<n;i++)len2+=abs(p[i]-p[i+1]);
  return max(len1/vt,len2/vt);
}

main(){
  scanf("%d",&n);
  vector<point> p(n+1);
  long long x[n],y[n];
  for(int i=0;i<n;i++)scanf("%lld%lld",&x[i],&y[i]);
  long long xt,yt;
  scanf("%lld%lld",&xt,&yt);
  //pt=readp();
  scanf("%lf",&vt);
  pp=readp();
  scanf("%lf",&vp);
  int ip=-1;
  if(x[0]==xt && y[0]==yt){
    for(int i=0;i<n;i++)p[i]=point((double)x[i],(double)y[i]);
    ip=0;
    n--;
  }else{
    for(int i=0;i<n-1;i++){
      //cout << p[i] << "-" << p[i+1] << "; "<< pt << endl;
      //if(det(p[i]-pt,p[i+1]-pt)==0 && dot(p[i]-pt,p[i+1]-pt)<=0){
      if((x[i]-xt)*(y[i+1]-yt)-(x[i+1]-xt)*(y[i]-yt)==0 && (x[i]-xt)*(x[i+1]-xt)+(y[i]-yt)*(y[i+1]-yt)<=0){
	for(int j=0;j<=i;j++)p[j]=point((double)x[j],(double)y[j]);
	if(x[i+1]==xt && y[i+1]==yt){
	  for(int j=i+1;j<n;j++)p[j]=point((double)x[j],(double)y[j]);
	  n--;
	}else{
	  p[i+1]=point((double)xt,(double)yt);
	  for(int j=i+1;j<n;j++)p[j+1]=point((double)x[j],(double)y[j]);
	}
	ip=i+1;
	break;
      }
    }
  }
  if(abs(pp-point((double)xt,(double)yt))<EPS){puts("0.0");return 0;}
  assert(ip!=-1);
  vector<point> q=p;
  reverse(q.begin(),q.end());
  double ans=1e9;
  //printf("%f %f %f %f %f\n",sol1(p,ip),sol1(q,n-ip),sol2(p,ip),sol2(q,n-ip),sol3(p,ip));
  
  ans=min(ans,sol1(p,ip));
  ans=min(ans,sol1(q,n-ip));
  ans=min(ans,sol2(p,ip));
  ans=min(ans,sol2(q,n-ip));
  ans=min(ans,sol3(p,ip));
  printf("%.10f\n",ans);
  
}
