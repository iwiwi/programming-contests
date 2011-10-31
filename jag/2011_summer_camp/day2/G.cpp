#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;

int n,m,W,T;
int uri[10],wei[10];

int num[10],x[10],y[10];
int kai[10][10];

int dist[10][10];

int tim[1200];
int val[1200];

template<class X> X nappu(int W,vector<int> w,vector<X> v){
	int n=w.size();
	X dp[n+1][W+1];
	memset(dp,0,sizeof(dp));
	for(int i=0;i<n;i++){
		for(int j=0;j<=W;j++){
			if(j<w[i]){
				dp[i+1][j]=dp[i][j];
			}else{
				dp[i+1][j]=max(dp[i][j],dp[i+1][j-w[i]]+v[i]);
			}
		}
	}
	return dp[n][W];
}

int main(void){
	scanf("%d %d %d %d",&n,&m,&W,&T);
	map<string,int> ma;
	for(int i=0;i<m;i++){
		char ch[100];
		scanf("%s %d %d",ch,&wei[i],&uri[i]);
		ma[string(ch)]=i;
	}
	for(int i=0;i<n;i++){
		scanf("%d %d %d",&num[i],&x[i],&y[i]);
		for(int j=0;j<num[i];j++){
			char ch[100];
			int q;
			scanf("%s %d",ch,&q);
			int pos=ma[string(ch)];
			kai[i][pos]=uri[pos]-q;
		}
	}
	
	for(int i=0;i<n;i++)dist[0][i+1]=dist[i+1][0]=abs(x[i])+abs(y[i]);
	for(int i=0;i<n;i++)for(int j=0;j<n;j++){
		dist[i+1][j+1]=abs(x[i]-x[j])+abs(y[i]-y[j]);
	}

	vector<int> ww;
	vector<ll> vv;	
	for(int i=1;i<(1<<n);i++){
		vector<int> ve;
		for(int j=0;j<n;j++){
			if((i&(1<<j))!=0)ve.push_back(j);
		}

		int mini=INT_MAX;
		do{
			vector<int> ve2;
			ve2.push_back(0);
			for(int j=0;j<ve.size();j++)ve2.push_back(ve[j]+1);
			ve2.push_back(0);
			int len=0;
			for(int j=0;j<ve2.size()-1;j++){
				len+=dist[ve2[j]][ve2[j+1]];
			}
			mini=min(mini,len);
		}while(next_permutation(ve.begin(),ve.end()));
		tim[i]=mini;
		
		vector<int> w(m),v(m);
		for(int j=0;j<m;j++)w[j]=wei[j];
		for(int j=0;j<ve.size();j++){
			for(int k=0;k<m;k++){
				v[k]=max(v[k],kai[ve[j]][k]);
			}
		}
		val[i]=nappu(W,w,v);
		
		ww.push_back(tim[i]);
		vv.push_back((ll)val[i]);
	}
	
	ll ans=nappu(T,ww,vv);
	printf("%lld\n",ans);

	return 0;
}

