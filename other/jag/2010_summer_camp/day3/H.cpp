#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define INF (1LL<<60)

typedef long long ll;

bool mul_gre(ll a,ll b,ll x){ //a*b>x? (a,b,x>=0)
	if(a==0||b==0)return false;
	return (x/b<a);
}

bool mul_geq(ll a,ll b,ll x){ //a*b>=x? (a,b,x>=0)
	if(a==0||b==0)return (x==0);
	return (x/b<a || (x/b==a && x%b==0));
}

ll greedy_sol(vector<ll> num,ll targ){
	ll ret;
	ll tmp;
	//shita kara kinji
	tmp=0;
	for(int i=num.size()-1;i>=0;i--){
		if(tmp+num[i]<=targ)tmp+=num[i];
	}
	ret=targ-tmp;
	//ue kara kinji
	tmp=0;
	for(int i=num.size()-1;i>=0;i--)tmp+=num[i];
	if(tmp>=targ){
		for(int i=num.size()-1;i>=0;i--){
			if(tmp-num[i]>=targ)tmp-=num[i];
		}
		ret=min(ret,tmp-targ);
	}
	return ret;
}

ll greedy_sol2(vector<ll> num,ll targ,ll k){
	ll ret=INF;
	ll tmp;
	ll hoge[1000];
	ll tukau[1000];
	//shita kara kinji
	ll shitasum=0;
	for(int i=0;i<k;i++)shitasum+=num[i];
	if(shitasum<=targ){
		tmp=0;
		for(int i=num.size()-1;i>=0;i--){
			if(tmp+num[i]<=targ){
				tmp+=num[i];
				tukau[i]=1;
			}else{
				tukau[i]=0;
			}
		}
		
		ll ones=0;
		ll now=0;
		for(int i=num.size()-1;i>=0;i--){
			//1 ni dekiru?
			if(ones==k)hoge[i]=0;
			else{
				ll tmpsum=0;
				for(int j=0;j<k-ones-1;j++)tmpsum+=num[j];
				if(now+num[i]+tmpsum>targ)hoge[i]=0;
				else hoge[i]=1;
			}
			if(hoge[i]==1){now+=num[i];ones++;}
		}
		
		//for(int i=num.size()-1;i>=0;i--)printf("%d",tukau[i]);puts("");
		//for(int i=num.size()-1;i>=0;i--)printf("%d",hoge[i]);puts("");
		//puts("d");
		ret=min(ret,targ-now);
	}
	//ue kara kinji
	ll uesum=0;
	for(int i=num.size()-1;i>=num.size()-k;i--)uesum+=num[i];
	if(uesum>=targ){
		tmp=0;
		for(int i=num.size()-1;i>=0;i--)tmp+=num[i];
		for(int i=num.size()-1;i>=0;i--){
			if(tmp-num[i]>=targ){
				tmp-=num[i];
				tukau[i]=0;
			}else{
				tukau[i]=1;
			}
		}
		ll ones=0,zeroes=0;
		ll now=0;
		for(int i=num.size()-1;i>=0;i--){
			//0 ni dekiru?
			if(zeroes==num.size()-k)hoge[i]=1;
			else{
				ll tmpsum=0;
				for(int j=i-1;j>=i-(k-ones);j--)tmpsum+=num[j];
				if(now+tmpsum<targ)hoge[i]=1;
				else hoge[i]=0;
			}
			if(hoge[i]==1){now+=num[i];ones++;}
			else zeroes++;
		}
		//for(int i=num.size()-1;i>=0;i--)printf("%d",tukau[i]);puts("");
		//for(int i=num.size()-1;i>=0;i--)printf("%d",hoge[i]);puts("");
		//puts("u");
		ret=min(ret,now-targ);
	}
	
	//for(int i=0;i<num.size();i++)printf("%lld ",num[i]);puts("");
	//printf("%lld\n",targ);
	//printf("%lld ko tukau\n",k);
	//printf("ret=%lld\n",ret);
	return ret;	
}

main(){
	ll n,m,a,b,p,q;
	scanf("%lld%lld%lld%lld%lld%lld",&n,&m,&a,&b,&p,&q);
	
	ll ans;
	if(a==1 && b==1){
		ll tmp=m/(p+q);
		if(tmp<=n){
			ans=m%(p+q);
			if(tmp<n)ans=min(ans,(p+q)-(m%(p+q)));
		}else{
			ans=m-n*(p+q);
		}
	}else if(a==1 || b==1){
		if(b==1){swap(a,b);swap(p,q);}
		ll tmp=q;
		vector<ll> qbk;
		for(int i=0;i<n;i++){
			qbk.push_back(tmp);
			if(mul_gre(tmp,b,3*m))break;
			tmp*=b;
		}
		//sort(qbk.begin(),qbk.end());
		ans=INF;
		for(int i=0;i<=qbk.size();i++){
			//printf("i=%d\n",i);
			ans=min(ans,greedy_sol2(qbk,m-p*i,i));
		}
	}else{
		ll tmp1=p,tmp2=q;
		vector<ll> ticket;
		for(int i=0;i<n;i++){
			ticket.push_back(tmp1+tmp2);
			if(mul_gre(tmp1,a,3*m) || mul_gre(tmp2,b,3*m))break;
			tmp1*=a;
			tmp2*=b;
		}
		//sort(ticket.begin(),ticket.end());
		//printf("ticket=");for(int i=0;i<ticket.size();i++)printf("%lld ",ticket[i]);puts("");
		ans=greedy_sol(ticket,m);
	}
	printf("%lld\n",ans);
}