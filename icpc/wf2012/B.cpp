#include <stdio.h>
#include <math.h>
#include <string.h>
double b[50];
int n;

double integ(double x){
  double ret=0;
  for(int i=0;i<=2*n;i++){
    ret+=b[i]*pow(x,i+1)/(double)(i+1);
    //printf("%lf = %lf\n",x,ret);
  }
  return M_PI*ret;
}

int main(){
  for(int casenum=1;;casenum++){
    if(scanf("%d",&n)<=0)return 0;
    double a[50];
    for(int i=0;i<=n;i++)scanf("%lf",&a[i]);
    memset(b,0,sizeof(b));
    for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)b[i+j]+=a[i]*a[j];
    //for(int i=0;i<=2*n;i++)printf("%lf ",b[i]);puts("");
    double xlow,xhigh,inc;
    scanf("%lf%lf%lf",&xlow,&xhigh,&inc);
    double v=integ(xhigh)-integ(xlow);
    printf("Case %d: %.2f\n",casenum,v);
    if(v<inc)printf("insufficient volume\n");
    else{
      
      for(int i=1;i<=8 && i*inc<v;i++){
	double lb=xlow,ub=xhigh;
	for(int t=0;t<50;t++){
	  double mid=(ub+lb)/2;
	  if(integ(mid)-integ(xlow)<i*inc)lb=mid;
	  else ub=mid;
	}
	if(i>1)printf(" ");
	printf("%.2f",(ub+lb)/2-xlow);
      }
      puts("");
    }
  }
}
