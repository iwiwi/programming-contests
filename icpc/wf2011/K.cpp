#include <stdio.h>
#include <math.h>
#include <complex>

using namespace std;

#define INF 1010101010

typedef complex<int> point;

point readpt(){
  int x,y;
  scanf("%d%d",&x,&y);
  return point(x,y);
}

double myabs(point p){
  return sqrt((double)p.real()*p.real()+(double)p.imag()*p.imag());
}

int dot(point p,point q){return real(conj(p)*q);}
int det(point p,point q){return imag(conj(p)*q);}
main(){
  for(int casenum=1;;casenum++){
    int n;
    scanf("%d",&n);
    if(n==0)return 0;
    point p[110];
    for(int i=0;i<n;i++)p[i]=readpt();
    double ans=INF;
    for(int i=0;i<n;i++){
      for(int j=0;j<i;j++){
        int mini=INF,maxi=-INF;
        for(int k=0;k<n;k++){
          mini=min(mini,det(p[j]-p[i],p[k]-p[i]));
          maxi=max(maxi,det(p[j]-p[i],p[k]-p[i]));
        }
        ans=min(ans,(maxi-mini)/myabs(p[j]-p[i]));
      }
    }
    printf("Case %d: %.2f\n",casenum,ans+0.005-1e-12);
  }
}
