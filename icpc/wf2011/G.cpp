#include <stdio.h>
#include <map>
#include <math.h>
using namespace std;
#define INF 1e12
double l[600];
int n;
map<pair<int,int>,double> memo;

double myasin(double x){return x>1?1:asin(x);}
double mysqrt(double x){return x<0?0:sqrt(x);}

double sol(int p,int q){
  //printf("%d-%d\n",p,q);
  if(q<p){/*printf("sol=0\n");*/return 0;}
  double maxl=0,maxi=0;
  double lsum=0;
  for(int i=p;i<=q;i++){
    if(l[i]>maxl){
      maxl=l[i];
      maxi=i;
    }
    lsum+=l[i];
  }
  if(maxl*2>lsum)return (p==0||q==n-1?0:-INF);
  if(maxl*2==lsum)return 0;
  double s=0;
  for(int i=p;i<=q;i++){
    if(maxi==i)continue;
    s+=myasin(l[i]/maxl);
  }
  if(s>M_PI/2){
    double ub=2/maxl,lb=0;
    for(int z=0;z<50;z++){
      double mid=(ub+lb)/2;
      double t=0;
      for(int i=p;i<=q;i++)t+=myasin(l[i]/2*mid);
      if(t>M_PI)ub=mid; else lb=mid;
    }
    double rho=(ub+lb)/2;
    double ret=0;
    for(int i=p;i<=q;i++){
      ret+=l[i]/2*mysqrt(1/(rho*rho)-(l[i]*l[i])/4);
    }
    //printf("sol=%f\n",ret);
    return ret;
  }else{
    double ub=2/maxl,lb=0;
    for(int z=0;z<50;z++){
      double mid=(ub+lb)/2;
      double t=0;
      for(int i=p;i<=q;i++){
        if(i==maxi)continue;
        t+=myasin(l[i]/2*mid);
      }
      t-=myasin(maxl/2*mid);
      if(t<0)ub=mid; else lb=mid;
    }
    double rho=(ub+lb)/2;
    double ret=0;
    for(int i=p;i<=q;i++){
      if(i==maxi)continue;
      ret+=l[i]/2*mysqrt(1/(rho*rho)-(l[i]*l[i])/4);
    }
    ret-=maxl/2*mysqrt(1/(rho*rho)-(maxl*maxl)/4);
    //printf("sol=%f\n",ret);
    return ret;
  }
}

double saiki(int p,int q){
  if(q<p)return 0;
  if(memo.count(make_pair(p,q))!=0)return memo[make_pair(p,q)];
  
  double maxl=0,maxi=0;
  for(int i=p;i<=q;i++){
    if(l[i]>maxl){
      maxl=l[i];
      maxi=i;
    }
  }
  double ret=max(sol(p,q),saiki(p,maxi-1)+saiki(maxi+1,q));
  memo[make_pair(p,q)]=ret;
  return ret;
}

main(){
  for(int casenum=1;;casenum++){
    scanf("%d",&n);
    if(n==0)return 0;
    for(int i=0;i<n;i++)scanf("%lf",&l[i]);
    memo.clear();
    printf("Case %d: %.12f\n",casenum,saiki(0,n-1));
  }
}
