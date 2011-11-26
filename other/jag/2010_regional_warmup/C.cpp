#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX 987654321

char mapp[200][200];
int convert[300];

int dp[1100][(1<<12)];
int sum[1100];
int psum[(1<<12)];
int por[12];

vector<int> dama;

int main(void){
	freopen("C.txt","r",stdin);
	while(1){
		int i,j,k;
		int init,maxi,y,x,T,S,P,n;
		scanf("%d %d",&init,&maxi);
		if(init==0 && maxi==0)break;
		scanf("%d %d",&y,&x);
		for(j=0;j<y;j++){
			char ch[200];
			scanf("%s",ch);
			for(i=0;i<x;i++)mapp[i][j]=ch[i];
		}
		scanf("%d",&T);
		for(i=0;i<T;i++){
			char ch[10];
			int a;
			scanf("%s %d",ch,&a);
			convert[ch[0]]=a;
		}
		scanf("%d",&S);
		int px=0,py=0;
		dama.clear();
		dama.push_back(convert[mapp[px][py]]);
		for(i=0;i<S;i++){
			char ch[10];
			int a;
			scanf("%s %d",ch,&a);
			int dx,dy;
			if(ch[0]=='D'){dx=0;dy=1;}
			if(ch[0]=='U'){dx=0;dy=-1;}
			if(ch[0]=='L'){dx=-1;dy=0;}
			if(ch[0]=='R'){dx=1;dy=0;}
			for(j=0;j<a;j++){
				px+=dx;py+=dy;
				dama.push_back(convert[mapp[px][py]]);
			}
		}
		n=dama.size();
		scanf("%d",&P);
		for(i=0;i<P;i++){
			scanf("%d",&por[i]);
		}
		sum[0]=dama[0];
		for(i=1;i<n;i++){
			sum[i]=sum[i-1]+dama[i];
		}
		for(i=0;i<(1<<P);i++){
			psum[i]=0;
			for(j=0;j<P;j++){
				if((i&(1<<j))!=0)psum[i]+=por[j];
			}
		}
		for(i=0;i<=n;i++)for(j=0;j<(1<<P);j++)dp[i][j]=MAX;
		dp[0][0]=0;
		for(i=0;i<n;i++){
			for(j=0;j<(1<<P);j++){
				if(dp[i][j]==MAX)continue;
				int hp=init+psum[j]-dp[i][j];
				if(i>0)hp-=sum[i-1];
				for(k=0;k<P;k++){
					if((j&(1<<k))!=0)continue;
					dp[i][j^(1<<k)]=min(dp[i][j^(1<<k)],dp[i][j]+max(hp+por[k]-maxi,0));
				}
				if(hp>dama[i]){
					dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
				}
			}
		}
		int yes=0;
		for(j=0;j<(1<<P);j++){
			if(dp[n][j]!=MAX)yes=1;
		}
		if(yes==1)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
