#include <stdio.h>


typedef long double ld;

ld p[1010][1010];

main(){
	int n,m,k;
	ld f=1;
	for(n=0;n<=1000;n++)for(m=n+1;m<=1000;m++)p[n][m]=1;
	for(n=1;n<=1000;n++){
		f/=n;
		for(m=1;m<=n;m++){
			if(m==1)p[n][m]=f;
			else{
				p[n][m]=0;
				ld pr;
				for(k=0;n-k*m>=0;k++){
					if(k==0)pr=1; else pr/=(k*m);
					p[n][m]+=pr*p[n-k*m][m-1];
				}
			}
			//printf("%.3Lf ",p[n][m]);
		}
		//puts("");
	}
	scanf("%d%d",&n,&m);
	printf("%.8Lf\n",p[n][m]);
}