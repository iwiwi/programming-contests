#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <complex>
using namespace std;
#define EPS 1e-10

typedef complex<double> point;

vector<point> crosscc(point c,double r,point d,double s){
  double di=abs(c-d);
  if(di>r+s || di<fabs(r-s))return vector<point>();
  double l=((r*r-s*s)/di+di)/2.0,n=sqrt(r*r-l*l);
  point e=c+(d-c)*l/di,p=(d-c)*n/di*point(0,-1);
  vector<point> ret(2);
  ret[0]=e+p;
  ret[1]=e-p;
  return ret;
}

double integral_1(double x1,double x2){
  if(x1>1-EPS)return 0;
  if(x2<-1+EPS)return 0;
  if(x2>1)x2=1;
  if(x1<-1)x1=-1;
  double theta1=acos(x1),theta2=acos(x2);
  return ((theta1-theta2)+cos(theta2)*sin(theta2)-cos(theta1)*sin(theta1))/2;
}

double integral_x(double x1,double x2){
  if(x1>1-EPS)return 0;
  if(x2<-1+EPS)return 0;
  if(x2>1)x2=1;
  if(x1<-1)x1=-1;
  double theta1=acos(x1),theta2=acos(x2);
  return (pow(sin(theta1),3)-pow(sin(theta2),3))/3;
}

double integral_y(double x1,double x2){
  if(x1>1-EPS)return 0;
  if(x2<-1+EPS)return 0;
  if(x2>1)x2=1;
  if(x1<-1)x1=-1;
  //double theta1=acos(x1),theta2=acos(x2);
  return (x2-x1)/2-(pow(x2,3)-pow(x1,3))/6;
}

main(){
  for(;;){
    double r;
    double R;
    int n;
    if(scanf("%lf%lf%d",&r,&R,&n)<=0)return 0;
    double cx[210],cy[210];
    point c[210];
    for(int i=0;i<n;i++){
      scanf("%lf%lf",&cx[i],&cy[i]);
      c[i]=point(cx[i],cy[i]);
    }
    vector<double> cutx;
    cutx.push_back(R);
    cutx.push_back(-R);
    for(int i=0;i<n;i++){
      cutx.push_back(cx[i]+r);
      cutx.push_back(cx[i]-r);
    }
    for(int i=0;i<n;i++){
      for(int j=0;j<i;j++){
        vector<point> ret=crosscc(c[i],r,c[j],r);
        for(int k=0;k<(int)ret.size();k++)cutx.push_back(real(ret[k]));
      }
    }
    sort(cutx.begin(),cutx.end());
    double sum1=M_PI*R*R,sumx=0,sumy=0;
    for(int k=0;k<(int)cutx.size()-1;k++){
      if(cutx[k+1]-cutx[k]<EPS)continue;
      double x=(cutx[k]+cutx[k+1])/2;
      pair<double,pair<int,int> > ev[500];
      int cnt2=0;
      for(int i=0;i<n;i++){
        if(fabs(x-cx[i])<r){
          double y1=cy[i]-sqrt(r*r-(x-cx[i])*(x-cx[i]));
          double y2=cy[i]+sqrt(r*r-(x-cx[i])*(x-cx[i]));
          ev[cnt2++]=make_pair(y1,make_pair(i,1));
          ev[cnt2++]=make_pair(y2,make_pair(i,-1));
        }
      }
      sort(ev,ev+cnt2);
      //printf("kukan %lf to %lf\n",cutx[k],cutx[k+1]);
      int cnt=0;
      for(int p=0;p<cnt2;p++){
        //printf("%lf: %d %d\n",ev[p].first,ev[p].second.first,ev[p].second.second);
        if((cnt==0 && ev[p].second.second==1)||
           (cnt==1 && ev[p].second.second==-1)){
          int i=ev[p].second.first;
          double x1=(cutx[k]-cx[i])/r;
          double x2=(cutx[k+1]-cx[i])/r;
          double i1=integral_1(x1,x2);
          double ix=integral_x(x1,x2);
          double iy=integral_y(x1,x2);
          double sita1=(cutx[k+1]-cutx[k])*cy[i];
          double sitax=(cutx[k+1]+cutx[k])*(cutx[k+1]-cutx[k])*cy[i]/2;
          double sitay=(cutx[k+1]-cutx[k])*cy[i]*cy[i]/2;
          
          if(ev[p].second.second==1){
            sum1+=-(i1*r*r)+sita1;
            sumx+=-(ix*r*r*r+i1*r*r*cx[i])+sitax;
            sumy+=-(-iy*r*r*r+i1*r*r*cy[i])+sitay;
          }else{
            sum1-=(i1*r*r)+sita1;
            sumx-=(ix*r*r*r+i1*r*r*cx[i])+sitax;
            sumy-=(iy*r*r*r+i1*r*r*cy[i])+sitay;
          }
        }
        cnt+=ev[p].second.second;
      }
    }
    double gx=sumx/sum1;
    double gy=sumy/sum1;
    
    bool haitteru=true;
    for(int i=0;i<n;i++){
      if(abs(point(gx,gy)-c[i])<r-EPS)haitteru=false;
    }
    if(!haitteru)puts("No");
    else printf("Yes %.4f %.4f\n",gx,gy);
    
    //printf("%f %f\n",gx,gy);
  }
}
