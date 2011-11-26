#include<stdio.h>
#include<algorithm>
using namespace std;

#define ZERO 45000

typedef long long ll;

bool dp[110][90000]; //k/2‚Ìƒgƒ‹ƒN‚ª‚Â‚­‚ê‚é‚©
ll s[110];

main(void){
	ll n,l,m,r;
	scanf("%lld %lld %lld %lld",&n,&l,&m,&r);
	m*=2;
	r*=2;
	for(int i=0;i<n;i++){
		scanf("%lld",&s[i]);
	}
	
	dp[0][ZERO]=true;
	
	for(int i=0;i<n;i++){
		ll cnt;
		
		cnt=0;
		for(int k=-2*m;k<=2*m;k++){
			if(k-2*r*s[i]>=-2*m && dp[i][k-2*r*s[i]+ZERO])cnt++;
			if(k-2*l*s[i]-1>=-2*m && dp[i][k-2*l*s[i]-1+ZERO])cnt--;
			if(cnt>0)dp[i+1][k+ZERO]=1;
		}

		cnt=0;
		for(int k=2*m;k>=-2*m;k--){
			if(k+2*r*s[i]<=2*m && dp[i][k+2*r*s[i]+ZERO])cnt++;
			if(k+2*l*s[i]+1<=2*m && dp[i][k+2*l*s[i]+1+ZERO])cnt--;
			if(cnt>0)dp[i+1][k+ZERO]=1;
		}
	}
	
	for(int k=-2*m;k<=2*m;k++){
		if(dp[n][k+ZERO]){
			puts("Yes");
			return 0;
		}
	}
	puts("No");
	return 0;
}
