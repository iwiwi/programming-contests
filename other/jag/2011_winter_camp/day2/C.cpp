#include <stdio.h>
#include <algorithm>
#define EPS 1e-10
using namespace std;

void calc(bool stay[22],double r[22]){
	r[0]=1;
	for(int k=1;k<=21;k++){
		r[k]=0;
		for(int d=1;d<=6;d++){
			if(k-d>=0 && !stay[k-d])r[k]+=r[k-d];
		}
		r[k]/=6;
	}
}

main(){
	double x;
	scanf("%lf",&x);
	double e[50][50];
	double misegaAnikatu[50][50];
	for(int i=0;i<30;i++){
		for(int j=0;j<30;j++){
			double dp[22];
			bool stay[22];
			for(int k=21;k>=0;k--){
				double e_stop=((k>=i || i>21)?1:-1)+((k>=j || j>21)?x:-x);
				double e_go=0;
				for(int d=1;d<=6;d++){
					if(k+d>21)e_go+=(i<=21?-1:1)+(j<=21?-x:x);
					else e_go+=dp[k+d];
				}
				e_go/=6;
				dp[k]=max(e_stop,e_go);
				if(e_go>e_stop-EPS)stay[k]=false;
				else stay[k]=true;
			}
			double tmp[22];
			calc(stay,tmp);
			if(i>21)misegaAnikatu[i][j]=0;
			else{
				misegaAnikatu[i][j]=0;
				for(int k=0;k<=21;k++){
					if(stay[k] && k>=i)misegaAnikatu[i][j]+=tmp[k];
				}
			}
			e[i][j]=dp[0];
			//printf("%f ",misegaAnikatu[i][j]);
		}
		//puts("");
	}
	double dp[22];
	bool stay[22];
	double bprob[22];
	for(int k=21;k>=0;k--){
		double e_stop=-e[k][k];
		double e_go=0;
		for(int d=1;d<=6;d++){
			if(k+d>21)e_go-=(x+1);
			else e_go+=dp[k+d];
		}
		e_go/=6;
		dp[k]=max(e_stop,e_go);
		if(e_go>e_stop-EPS)stay[k]=false;
		else stay[k]=true;
	}
	//for(int i=0;i<=21;i++)printf("%d",(int)stay[i]);puts("");
	calc(stay,bprob);
	//for(int i=0;i<=21;i++)printf("%f ",bprob[i]);puts("");
	double bover=1;
	for(int l=0;l<=21;l++)if(stay[l])bover-=bprob[l];
	double finalanswer=0;
	for(int l=22;l>=0;l--){
		if(l<=21 && !stay[l])continue;
		double p=(l==22?bover:bprob[l]);
		//printf("B=%d: %f\n",l,p);
		double dpdp[22];
		for(int k=21;k>=0;k--){
			double e_stop=1-misegaAnikatu[k][l];
			double e_go=0;
			for(int d=1;d<=6;d++){
				if(k+d>21)e_go+=0;
				else e_go+=dpdp[k+d];
			}
			e_go/=6;
			dpdp[k]=max(e_stop,e_go);
		}
		finalanswer+=p*dpdp[0];
	}
	printf("%.6f\n",finalanswer);
}