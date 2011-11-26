#include <stdio.h>
#include <algorithm>

typedef long long ll;

ll myabs(ll x){
	return x>0?x:-x;
}

ll gcd(ll a,ll b){
	if(b==0)return a;
	return gcd(b,a%b);
}

main(){
	ll m,n,a,b,c,d;
	scanf("%lld%lld%lld%lld%lld%lld",&m,&n,&a,&b,&c,&d);
	ll g=m*n;
	g=gcd(g,myabs(a*d-b*c));
	g=gcd(g,m*b);
	g=gcd(g,a*n);
	g=gcd(g,m*d);
	g=gcd(g,c*n);
	printf("%lld\n",(m*n)/g-1);
}