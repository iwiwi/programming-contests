#include <stdio.h>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define EPS 1e-10
#define INF 1e12

double x[21000];
double r[21000];
double g[21000];
double d[21000];

pair<double,int> ev[2100000];
int evsize;

main(){
  int n;
  double s;
  double vmin,vmax;
  scanf("%d%lf%lf%lf",&n,&s,&vmin,&vmax);
  for(int i=0;i<n;i++){
    scanf("%lf%lf%lf%lf",&x[i],&r[i],&g[i],&d[i]);
  }
  evsize=0;
  for(int i=0;i<n;i++){
    double tn=d[i],tp=d[i]+r[i];
    double tmax=x[i]/vmin,tmin=x[i]/vmax;
    for(;;){
      if(tn>tmax+EPS)break;
      if(tn>tmin-EPS)ev[evsize++]=make_pair(x[i]/tn-EPS,1);
      tn+=r[i]+g[i];
      if(tp>tmax+EPS)break;
      if(tp>tmin-EPS)ev[evsize++]=make_pair(x[i]/tp+EPS,-1);
      tp+=r[i]+g[i];
    }
  }
  ev[evsize++]=make_pair(vmin-EPS,0);
  ev[evsize++]=make_pair(vmax+EPS,0);
  sort(ev,ev+evsize);
  int pos0=0,pos1=evsize-1;
  //for(;ev[pos0].second!=0;pos0++);
  //for(;ev[pos1].second!=0;pos1--);
  int cnt=0;
  int ans=-999999;
  double ansv=0;
  for(int i=pos0;i<pos1;i++){
    cnt+=ev[i].second;
    double v0=ev[i].first,v1=ev[i+1].first;
    // if(v1<vmin-EPS)continue;
    if(cnt>=ans){
      ans=cnt;
      ansv=max(ansv,v1);
    }
    //if(v1>vmax+EPS)break;
  }
  ansv-=EPS;
  vector<int> kaeru;
  for(int i=0;i<n;i++){
    double t=x[i]/ansv;
    double tn=d[i],tp=d[i]+r[i];
    for(;;){
      if(t<tn+3*EPS)break;
      tn+=r[i]+g[i];
      if(t<tp-3*EPS){kaeru.push_back(i);break;}
      tp+=r[i]+g[i];
    }
  }
  printf("%.10f\n",ansv);
  printf("%d\n",kaeru.size());
  if(kaeru.size()>=1){
    for(int i=0;i<kaeru.size();i++){
      if(i>0)printf(" ");
      printf("%d",kaeru[i]+1);
    }
    puts("");
  }
}
