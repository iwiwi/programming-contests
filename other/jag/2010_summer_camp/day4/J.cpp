#include <stdio.h>
#include <algorithm>
#define P 10007
typedef long long ll;

int dp[35][20][20][20][35];
int f[33];
int siz;

int bitcount(int n){
	if(n==0)return 0;
	return bitcount(n/2)+n%2;
}

int cnt(int flg,int exx[32],int exy[32]){
	int x=0,y=0,z=0,w=0;
	int brd[32][32];
	int excnt=0;
	for(int i=0;i<siz;i++)if(exx[i])excnt++;
	for(int i=0;i<siz;i++)for(int j=0;j<siz;j++){
		brd[i][j]=0;
		if(i==j && (flg&1))brd[i][j]=1;
		if(i+j==siz-1 && (flg&2))brd[i][j]=1;
	}
	for(int i=0;i<siz;i++)for(int j=0;j<siz;j++){
		if(exx[i] || exy[j])continue;
		if(brd[i][j])x++;
	}
	for(int i=0;i<siz;i++)for(int j=0;j<siz;j++)for(int k=0;k<i;k++){
		if(exx[i] || exy[j] || exx[k])continue;
		if(brd[i][j] && brd[k][j])y++;
	}
	for(int i=0;i<siz;i++)for(int j=0;j<siz;j++)for(int l=0;l<j;l++){
		if(exx[i] || exy[j] || exy[l])continue;
		if(brd[i][j] && brd[i][l])z++;
	}
	for(int i=0;i<siz;i++)for(int j=0;j<siz;j++)for(int k=0;k<i;k++)for(int l=0;l<j;l++){
		if(exx[i] || exy[j] || exx[k] || exy[l])continue;
		if(brd[i][j] && brd[i][l] &&  brd[k][j] && brd[k][l])w++;
	}
	/*
	for(int i=0;i<siz;i++){
			for(int j=0;j<siz;j++)printf("%d ",brd[i][j]);puts("");
	}
	*/
	//printf("%d %d %d %d(%d)\n",x,y,z,w,siz-excnt);
	int a=x-2*y-2*z+4*w,b=y-2*w,c=z-2*w,d=w;
	a=(a%P+P)%P;
	b=(b%P+P)%P;
	c=(c%P+P)%P;
	d=(d%P+P)%P;
	printf("%d %d %d %d(%d): %d\n",a,b,c,d,siz-excnt,dp[a][b][c][d][siz-excnt]);
	return dp[a][b][c][d][siz-excnt];
}

main(){
	for(int n=0;n<=32;n++)f[n]=n?(f[n-1]*n)%P:1;
	
	for(int n=0;n<=32;n++){
		for(int a=0;a<=32;a++){
			for(int b=0;b<=16;b++){
				for(int c=0;c<=16;c++){
					for(int d=0;d<=16;d++){
						if(n<a+b+2*c+2*d)continue;
						int e=n-(a+b+2*c+2*d);
						if(a>0)dp[a][b][c][d][n]=(e*(e>0?dp[a-1][b][c][d][n-1]:0)+(a-1)*(a>1?dp[a-2][b][c][d][n-1]:0)+b*(b>0?dp[a-1][b-1][c][d][n-1]:0)+2*c*(c>0?dp[a][b][c-1][d][n-1]:0)+2*d*(d>0?dp[a-1][b+1][c][d-1][n-1]:0))%P;
						else if(b>0)dp[a][b][c][d][n]=(e*(e>0?dp[a+1][b-1][c][d][n-1]:0)+(b-1)*(b>1?dp[a+1][b-2][c][d][n-1]:0)+2*c*(c?dp[a+2][b-1][c-1][d][n-1]:0)+2*d*(d?dp[a+1][b][c][d-1][n-1]:0))%P;
						else if(c>0)dp[a][b][c][d][n]=(e*(e>0?dp[a][b][c-1][d][n-1]:0)+2*(c-1)*(c>1?dp[a+1][b][c-2][d][n-1]:0)+2*d*(d?dp[a][b+1][c-1][d-1][n-1]:0))%P;
						else if(d>0)dp[a][b][c][d][n]=(e*(e>0?dp[a][b][c+1][d-1][n-1]:0)+2*(d-1)*(d>1?dp[a][b+1][c+1][d-2][n-1]:0))%P;
						else dp[a][b][c][d][n]=f[n];
					}
				}
			}
		}
	}
	
	int k;
	int px[10],py[10];
	scanf("%d%d",&siz,&k);
	for(int i=0;i<k;i++){
		scanf("%d%d",&px[i],&py[i]);
	}

	int ans=0;	
	for(int b=0;b<(1<<k);b++){
		int exx[32]={0},exy[32]={0};
		bool ng=false;
		for(int i=0;i<k;i++){
			if((b>>i)&1){
				if(exx[px[i]]==1 || exy[py[i]]==1)ng=true;
				exx[px[i]]=1;
				exy[py[i]]=1;
			}
		}
		int c=cnt(0,exx,exy)-cnt(1,exx,exy)-cnt(2,exx,exy)+cnt(3,exx,exy);
		if(bitcount(b)%2==1)c=-c;
		c=(c%P+P)%P;
		ans+=c;ans%=P;
	}
	printf("%d\n",ans);
	return 0;
}