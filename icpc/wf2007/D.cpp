#include <stdio.h>
#include <iostream>
using namespace std;

typedef long long ll;

ll gcd(ll a,ll b){
	if(a<0)return gcd(-a,b);
	if(b<0)return gcd(a,-b);
	if(b==0)return a;
	return gcd(b,a%b);
}

main(){
	for(int t=1;;t++){
		ll px[2000],py[2000];
		ll ix[2000],iy[2000];
		ll x[2000],y[2000];
		int n;
		long long m;
		cin >> n >> m;//scanf("%d%lld",&n,&m);
		if(n==0)return 0;
		for(int i=0;i<n;i++)cin >> px[i] >> py[i];//scanf("%lld %lld",&ix[i],&iy[i]);
		px[n]=px[0];py[n]=py[0];
		px[n+1]=px[1];py[n+1]=py[1];
		int cnt=0;
		for(int i=1;i<=n;i++){
			if((px[i+1]-px[i])*(py[i-1]-py[i])!=(px[i-1]-px[i])*(py[i+1]-py[i])){
				ix[cnt]=px[i];
				iy[cnt]=py[i];
				cnt++;
			}
		}
		ix[cnt]=ix[0];
		iy[cnt]=iy[0];
		n=cnt;
		ll g=0;
		for(int i=0;i<n;i++){
			g=gcd(g,ix[i+1]-ix[i]);
			g=gcd(g,iy[i+1]-iy[i]);
		}
		for(int i=0;i<=n;i++){
			x[i]=(ix[i]-ix[0])/g;
			y[i]=(iy[i]-iy[0])/g;
		}
		long long A=0,S=0;
		for(int i=0;i<n;i++){
			A+=(x[i]*y[i+1]-x[i+1]*y[i]);
			S+=gcd(x[i+1]-x[i],y[i+1]-y[i]);
		}
		if(A<0)A=-A;
		//printf("A=%lld S=%lld\n",A,S);
		ll c1=m*(m+1)*(2*m+1)/12;
		ll c2=m*(m+1)/4;
		ll ans;
		if(m%4==0 || m%4==3){
			ans=c1*A+m-c2*S;
		}else{
			ans=c1*A+m-c2*S+(A-S)/2;
		}
		printf("Case %d: ",t);
		cout << ans << endl;
	}
}