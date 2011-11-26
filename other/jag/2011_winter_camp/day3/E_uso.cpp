#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
double r[8];
double myacos(double x){
	if(x>=1)return 0;
	return acos(x);
}
double calc(double t,int m){
	double s=0;
	double ret=0;
	for(int i=0;i<m-1;i++){
		double theta=myacos(t/(r[i]*r[i+1]));
		ret+=(sin(theta)*r[i]*r[i+1])/2;
		s+=theta;
	}
	if(s>2*M_PI)return -1;
	ret-=(sin(s)*r[m-1]*r[0])/2;
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
			if(!hoge){
				//for(int i=0;i<m;i++)printf("%lf ",r[i]);puts("");
				double ub=1e9;
				for(int i=0;i<m-1;i++)ub=min(ub,r[i]*r[i+1]);
				double lb=-ub;
				//for(int x=-100;x<=100;x++)printf("%lf\n",calc(ub*(double)x/100.0,m));
				
				for(int t=0;t<30;t++){
					double p=(2*lb+ub)/3;
					double q=(lb+2*ub)/3;
					double ap=calc(p,m),aq=calc(q,m);
					if(ap>aq)ub=q;
					else lb=p;
				}
				ans=max(ans,calc(ub,m));
				
				//puts("");
			}
			sort(r+m,r+n);
			reverse(r+m,r+n);
		}while(next_permutation(r,r+n));
	}
	printf("%.10f\n",ans);
}