//kore ha matomo ni hamatta orz

#include <stdio.h>
#include <utility>
#include <algorithm>

using namespace std;

pair<int,int> pos[1000010][2];
int tate[1000][2],yoko[1000][2],d1[2],d2[2];

main(){
	for(int i=1;i<=1000000;i++)pos[i][0]=pos[i][1]=make_pair(-1,-1);
	int n;
	int win[2];
	int m;
	scanf("%d%d%d%d",&n,&win[0],&win[1],&m);
	for(int p=0;p<2;p++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				int tmp;
				scanf("%d",&tmp);
				pos[tmp][p]=make_pair(i,j);
			}
		}
	}
	int lines[2]={0,0};
	for(int i=0;i<m;i++){
		int num;
		scanf("%d",&num);
		for(int p=0;p<2;p++){
			if(pos[num][p]!=make_pair(-1,-1)){
				int x=pos[num][p].first,y=pos[num][p].second;
				if(n!=1)tate[x][p]++;if(tate[x][p]==n)lines[p]++;
				if(n!=1)yoko[y][p]++;if(yoko[y][p]==n)lines[p]++;
				if(n!=1)if(x==y){d1[p]++;if(d1[p]==n)lines[p]++;}
				if(x+y==n-1){d2[p]++;if(d2[p]==n)lines[p]++;}
			}
		}
		bool usagi=(lines[0]>=win[0]);
		bool neko=(lines[1]>=win[1]);
		if(usagi&&(!neko)){puts("USAGI");return 0;}
		if(neko&&(!usagi)){puts("NEKO");return 0;}
		if(usagi&&neko){puts("DRAW");return 0;}
	}
	puts("DRAW");
	return 0;
}