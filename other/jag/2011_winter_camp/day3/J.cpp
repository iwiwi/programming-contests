#include <stdio.h>
#include <algorithm>
using namespace std;

#define P 1000000007
#define modP(x) ((((x)%P)+P)%P)

typedef long long ll;

ll bi[1010][1010];

ll pm[1010][1010];

ll p[1010][1010];

ll a[1010][1010];

ll x[1010][1010];

ll g[1010][1010];

ll df[1010];

ll pw[1010][1010];

ll gcd(ll a,ll b){
	if(b==0)return a;
	return gcd(b,a%b);
}

ll fnc(ll l,ll m){
	if(l%2==1)return p[m][l];
	else if(m==0)return 1;
	else if(m%2==0)return (df[m-1]*pw[l][m/2])%P;
	else return 0;
}

ll modinv(ll x){
	if(x==1)return 1;
	ll m=P%x;
	return (P-modinv(m)*(P/x)%P);
}

main(){
	ll n;
	ll hoge,piyo,fuga;
	ll k;
	scanf("%lld%lld%lld%lld",&n,&hoge,&piyo,&fuga);
	k=hoge-piyo+fuga;
	if(k<0)k=-k;
	df[0]=df[1]=1;for(ll i=2;i<=1000;i++)df[i]=(df[i-2]*i)%P;
	for(ll i=0;i<=1000;i++)for(ll j=0;j<=1000;j++)pw[i][j]=(j==0?1:(pw[i][j-1]*i)%P);
	for(ll i=0;i<=1000;i++)for(ll j=0;j<=i;j++)bi[i][j]=(j==0||j==i?1:(bi[i-1][j-1]+bi[i-1][j])%P);
	for(ll i=0;i<=1000;i++)for(ll j=0;j<=i;j++)pm[i][j]=(j==0?1:(pm[i][j-1]*(i+1-j))%P);
	for(ll i=0;i<=1000;i++)for(ll j=0;j<=1000;j++){
		if(i==0 || i==1)p[i][j]=1;
		else p[i][j]=((((i-1)*j)%P*p[i-2][j])%P+p[i-1][j])%P;
	}
	
	for(ll nd=0;nd<=n;nd++){
		for(ll i=1;i<=n;i++){
			if(nd==0)a[nd][i]=1;
			else{
				a[nd][i]=0;
				for(ll l=i;l<=nd;l+=i){
					if(l/gcd(l,k)!=i)continue;
					a[nd][i]+=(pm[nd-1][l-1]*a[nd-l][i])%P;
					a[nd][i]%=P;
				}
			}
		}
	}
	
	for(ll i=0;i<=n;i++){
		for(ll nd=0;nd<=n;nd++){
			if(nd==0)x[nd][i]=1;
			else if(i==0)x[nd][i]=0;
			else{
				x[nd][i]=0;
				for(ll q=0;;q++){
					if(q*i>nd)break;
					x[nd][i]+=(((bi[nd][q*i]*a[q*i][i])%P*x[nd-q*i][i-1])%P*fnc(i,q))%P;
					x[nd][i]%=P;
				}
			}
		}
	}
	if(hoge==0 && piyo==0 && fuga==0){
		ll ans=x[n][n];
		for(ll i=1;i<=n;i++){
			ans=(ans*modinv(i))%P;
		}
		for(ll i=1;i<=n;i++){
			ans=(ans*n)%P;
		}
		printf("%lld\n",ans);
	}else{
		printf("%lld\n",x[n][n]);
	}
}