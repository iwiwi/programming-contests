#include <stdio.h>
#include <complex>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

#define EPS 1e-9

typedef complex<double> point;

double D;
double d[4];
point p[4];
bool success;

vector<point> cckoten(point a,point b,double r,double s){
  vector<point> ret;
  double di=abs(a-b);
  if(di>r+s || di<fabs(r-s))return ret;
  double l=((r*r-s*s)/di+di)/2.0,n=sqrt(r*r-l*l);
  point e=a+(b-a)*l/di,p=(b-a)*n/di*point(0.0,-1.0);
  ret.push_back(e+p);
  ret.push_back(e-p);
  return ret;
}

void saiki(int i){
  if(i==4){
    bool ok=true;
    for(int j=0;j<4;j++)if(abs(p[j])>D-d[j]+EPS)ok=false;
    for(int k=0;k<4;k++)for(int l=0;l<k;l++)if(abs(p[k]-p[l])<d[k]+d[l]-EPS)ok=false;
    if(ok){
      //puts("[");
      //for(int k=0;k<4;k++)printf("circle(%f,%f,%f,%f)\n",real(p[k]),imag(p[k])));
      success=true;
    }
    return;
  }
  for(int j=0;j<i;j++){
    vector<point> ret=cckoten(0,p[j],D-d[i],d[j]+d[i]);
    for(int t=0;t<ret.size();t++){p[i]=ret[t];saiki(i+1);}
  }
  for(int k=0;k<i;k++){
    for(int l=0;l<k;l++){
      vector<point> ret=cckoten(p[k],p[l],d[k]+d[i],d[l]+d[i]);
      for(int t=0;t<ret.size();t++){p[i]=ret[t];saiki(i+1);}
    }
  }
}

main(){
  for(int casenum=1;;casenum++){
    double tmp[4];
    for(int k=0;k<4;k++){
      scanf("%lf",&tmp[k]);
      if(tmp[k]==0)return 0;
    }
    int perm[4]={0,1,2,3};
    double ans=tmp[0]+tmp[1]+tmp[2]+tmp[3];
    do{
      if(perm[0]<perm[1])continue;
      for(int i=0;i<4;i++)d[i]=tmp[perm[i]];
      double ub=d[0]+d[1]+d[2]+d[3],lb=0;
      for(int i=0;i<4;i++)for(int j=0;j<i;j++)lb=max(lb,d[i]+d[j]);
      for(int t=0;t<50;t++){
        double mid=(ub+lb)/2;
        D=mid;
        p[0]=point(mid-d[0],0);
        success=false;
        saiki(1);
        if(success)ub=mid; else lb=mid;
      }
      ans=min(ans,ub);
      //fprintf(stderr, "%.15f\n",ub);
    }while(next_permutation(perm,perm+4));
    printf("Case %d: %.f\n",casenum,ans);
  }
}
