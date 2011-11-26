#include <stdio.h>
#include <utility>
using namespace std;
#define P 1000000007
typedef long long ll;

#define fs first
#define sn second

pair<pair<ll,ll>, pair<ll,ll> > fibmat(ll n){
	if(n==0)return make_pair(make_pair(1,0),make_pair(0,1));
	pair<pair<ll,ll>, pair<ll,ll> > t=fibmat(n/2);
	pair<pair<ll,ll>, pair<ll,ll> > s,u;
	pair<pair<ll,ll>, pair<ll,ll> > f=make_pair(make_pair(1,1),make_pair(1,0));
	s.fs.fs=(t.fs.fs*t.fs.fs+t.fs.sn*t.sn.fs)%P;
	s.fs.sn=(t.fs.fs*t.fs.sn+t.fs.sn*t.sn.sn)%P;
	s.sn.fs=(t.sn.fs*t.fs.fs+t.sn.sn*t.sn.fs)%P;
	s.sn.sn=(t.sn.fs*t.fs.sn+t.sn.sn*t.sn.sn)%P;
	if(n%2==0)return s;
	else{
		u.fs.fs=(s.fs.fs*f.fs.fs+s.fs.sn*f.sn.fs)%P;
		u.fs.sn=(s.fs.fs*f.fs.sn+s.fs.sn*f.sn.sn)%P;
		u.sn.fs=(s.sn.fs*f.fs.fs+s.sn.sn*f.sn.fs)%P;
		u.sn.sn=(s.sn.fs*f.fs.sn+s.sn.sn*f.sn.sn)%P;
		return u;
	}
}

ll fib(ll n){
	return fibmat(n).fs.sn;
}

ll sol(ll K){
	K--;
	ll k;
	ll lb=0,ub=1000000001;
	while(ub-lb>1){
		ll mid=(ub+lb)/2;
		if(mid*mid<=K)lb=mid;
		else ub=mid;
	}
	k=lb;
	//printf("k=%lld\n",k);
	ll p,q;
	
	if(k%2==1){
		ll l=K-k*k;
		if(k+(k+1)/2<=l){p=k+2+2*(l-k-(k+1)/2);q=2*k+4-p;}
		else if(k<=l){p=2*k+2-2*(l-k);q=2*k+4-p;}
		else if((k+1)/2<=l){p=k+3+2*(l-(k+1)/2);q=2*k+3-p;}
		else if(0<=l){p=2*k+1-2*l;q=2*k+3-p;}
	}else{
		ll l=K-k*k;
		if(k+k/2+1<=l){p=k+3+2*(l-k-k/2-1);q=2*k+4-p;}
		else if(k<=l){p=2*k+2-2*(l-k);q=2*k+4-p;}
		else if(k/2<=l){p=k+2+2*(l-k/2);q=2*k+3-p;}
		else if(0<=l){p=2*k+1-2*l;q=2*k+3-p;}
	}
	//printf("%lld %lld\n",p,q);
	return (fib(p)*fib(q))%P;

}
	

main(){
	ll K;
	//for(ll i=1;i<=100;i++)printf("%lld\n",sol(i));
	scanf("%lld",&K);
	printf("%lld\n",sol(K));
}