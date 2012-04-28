#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
#define EPS 1e-8

bool isequal(double a,double b){
  if(fabs(a-b)<EPS)return true;
  else return false;
}

double mydist(double x0,double y0,double x1,double y1){
  return sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
}

double x[200],h[200],b[200];

int main(){

  for(int casenum=1;;casenum++){
    int n;
    scanf("%d",&n);
    if(n==0)break;
    vector<double> pos;
    vector<double> x0,y0,x1,y1,len;
    for(int i=0;i<n;i++){
      scanf("%lf %lf %lf",&x[i],&h[i],&b[i]);
      x0.push_back(x[i]-(double)b[i]/2);
      y0.push_back(0);
      x1.push_back(x[i]);
      y1.push_back(h[i]);

      x0.push_back(x[i]);
      y0.push_back(h[i]);
      x1.push_back(x[i]+(double)b[i]/2);
      y1.push_back(0);

      pos.push_back(x[i]-(double)b[i]/2);
      pos.push_back(x[i]);
      pos.push_back(x[i]+(double)b[i]/2);
    }
    n*=2;
    for(int i=0;i<n;i++){
      len.push_back(mydist(x0[i],y0[i],x1[i],y1[i]));
    }
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
        double a,b,c,d;
        a=(y1[i]-y0[i])/(x1[i]-x0[i]);
        b=-a*x0[i]+y0[i];
        c=(y1[j]-y0[j])/(x1[j]-x0[j]);
        d=-c*x0[j]+y0[j];
        if(isequal(a,c))continue;
        double x=(d-b)/(a-c);
        pos.push_back(x);
      }
    }
    sort(pos.begin(),pos.end());
    pos.erase(unique(pos.begin(),pos.end()),pos.end());
    
    double ans=0;
    for(int i=0;i+1<pos.size();i++){
      double x=((double)pos[i]+pos[i+1])/2;
      double maxiy=0;
      int maxipos=-1;
      for(int j=0;j<n;j++){
        if(!(x0[j]-EPS<x && x<x1[j]+EPS))continue;
        double a=(y1[j]-y0[j])/(x1[j]-x0[j]);
        double y=a*(x-x0[j])+y0[j];
        if(maxiy<y){
          maxiy=y;
          maxipos=j;
        }
      }
      if(maxipos==-1)continue;
      ans+=len[maxipos]*(pos[i+1]-pos[i])/(x1[maxipos]-x0[maxipos]);
    }
    printf("Case %d: %lld\n\n",casenum,(ll)round(ans+EPS));
  }

  return 0;
}
