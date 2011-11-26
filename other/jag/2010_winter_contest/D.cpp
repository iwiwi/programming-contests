#include <stdio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define EPS 1e-15

#define D 1e-10

typedef long double ld;

ld px[100],py[100],pz[100];

ld det(int i,int j,int k,int l){
	ld p=px[i]-px[l],q=py[i]-py[l],r=pz[i]-pz[l];
	ld s=px[j]-px[l],t=py[j]-py[l],u=pz[j]-pz[l];
	ld v=px[k]-px[l],w=py[k]-py[l],x=pz[k]-pz[l];
	return p*t*x+q*u*v+r*s*w-p*u*w-q*s*x-r*t*v;
}

ld dot(int i,int j,int k){
	return (px[i]-px[k])*(px[j]-px[k])+(py[i]-py[k])*(py[j]-py[k])+(pz[i]-pz[k])*(pz[j]-pz[k]);
}

main(){
	int n;
	int i,j,k,l;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%Lf%Lf%Lf",&px[i],&py[i],&pz[i]);
		px[i]+=rand()/((ld)RAND_MAX)*D;
		py[i]+=rand()/((ld)RAND_MAX)*D;
		pz[i]+=rand()/((ld)RAND_MAX)*D;
	}
	ld ans=0;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			for(k=j+1;k<n;k++){
				bool posi=false,nega=false;
				for(l=0;l<n;l++){
					if(l==i || l==j || l==k)continue;
					if(det(i,j,k,l)>EPS)posi=true;
					if(det(i,j,k,l)<-EPS)nega=true;
				}
				if(!(posi&&nega)){
					//printf("%d %d %d\n",i,j,k);
					ld pp=dot(i,i,k),qq=dot(j,j,k),pq=dot(i,j,k);
					ld d=pp*qq-pq*pq;
					if(d<0)d=0;
					ld area=sqrt(d)/2.0;
					//printf("%Lf %Lf %Lf --> %Lf\n",pp,qq,pq,area);
					ans+=area;
				}
			}
		}
	}
	printf("%.3Lf\n",ans);
}