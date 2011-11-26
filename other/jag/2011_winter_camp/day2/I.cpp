#include <stdio.h>
#include <math.h>

double p[10010][20];
double re[10010][20];

main(){
	int T,n;
	scanf("%d%d",&T,&n);
	double q[20];
	for(int i=0;i<n;i++)scanf("%lf",&q[i]);
	
	
	for(int i=0;i<=T;i++){
		for(int j=0;j<n;j++){
			scanf("%lf",&p[i][j]);
		}
	}
	double v[20];
	for(int i=0;i<n;i++)v[i]=p[0][i]*q[i];
	double vp=0;
	for(int i=0;i<n;i++)vp+=v[i];
	double w[20];
	for(int i=0;i<n;i++)w[i]=v[i]/vp;
	
	for(int t=1;t<=T;t++)for(int i=0;i<n;i++)re[t][i]=(p[t-1][i]-p[t][i])/p[t][i];
	double mu[20]={0};
	for(int i=0;i<n;i++){
		for(int t=1;t<=T;t++)mu[i]+=re[t][i];
		mu[i]/=T;
	}
	double mup=0;
	for(int i=0;i<n;i++)mup+=w[i]*mu[i];
	double sigma[20];
	for(int i=0;i<n;i++){
		sigma[i]=0;
		for(int t=1;t<=T;t++)sigma[i]+=(re[t][i]-mu[i])*(re[t][i]-mu[i]);
		sigma[i]/=T;
		sigma[i]=sigma[i]<0?0:sqrt(sigma[i]);
	}
	double cov[20][20];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cov[i][j]=0;
			for(int t=1;t<=T;t++)cov[i][j]+=(re[t][i]-mu[i])*(re[t][j]-mu[j]);
			cov[i][j]/=T;
		}
	}
	double sigmap=0;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)sigmap+=w[i]*cov[i][j]*w[j];
	sigmap=sigmap<0?0:sqrt(sigmap);
	double VaR=-vp*(mup-1.644854*sigmap);
	printf("%f\n",VaR);
	return 0;
}