#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;
#define PI 3.1415926535897932
double r[8];
double myacos(double x){
	assert(fabs(x)<1.1);
	if(x>=1)return 0;
	if(x<=-1)return PI;
	return acos(x);
}
double mysqrt(double x){
	assert(x>-0.1);
	if(x<=0)return 0;
	return sqrt(x);
}

double calc(double t,int m){
	double s=0;
	double ret=0;
	for(int i=0;i<m;i++){
		double theta=myacos(t/(r[i]*r[(i+1)%m]));
		ret+=(sin(theta)*r[i]*r[(i+1)%m])/2;
		//s+=theta;
	}
	//ret-=(sin(s)*r[m-1]*r[0])/2;
	return ret;
}


main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%lf",&r[i]);
	double ans=0;
	for(int m=3;m<=n;m++){
		sort(r,r+n);
		do{
			bool hoge=false;
			for(int i=1;i<m;i++)if(r[i]<r[0])hoge=true;
			//for(int i=0;i<m;i++)printf("%lf ",r[i]);puts("");
			double ub=1e9;
			for(int i=0;i<m;i++)ub=min(ub,r[i]*r[(i+1)%m]);
			double lb=-ub;
			//for(int x=0;x<=100;x++)printf("%lf\n",calc(ub*(double)x/100.0,m));
			double s=0;
			for(int i=0;i<m;i++)s+=myacos(ub/(r[i]*r[(i+1)%m]));
			if(!hoge && s<PI*2){
				for(int t=0;t<50;t++){
					double mid=(lb+ub)/2;
					double s=0;
					for(int i=0;i<m;i++)s+=myacos(mid/(r[i]*r[(i+1)%m]));
					//for(int i=0;i<m;i++)printf("acos(%lf) ",mid*r[i]*r[(i+1)%m]);printf(": %lf\n",s);
					if(s>PI*2)lb=mid;
					else ub=mid;
				}
				//printf("ub=%lf\n",ub);
				ans=max(ans,calc(ub,m));
				//puts("");
			}
			sort(r+m,r+n);
			reverse(r+m,r+n);
		}while(next_permutation(r,r+n));
	}
	printf("%.10f\n",ans);
}