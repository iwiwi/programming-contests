#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<map>
#define MP make_pair
using namespace std;

int yy,xx;
char board[510][510];
vector<pair<int,int> > pos[26];

bool check(int x1,int y1,int x2,int y2){
	bool ok=true;
	int sx=x2,sy=y2;
	if(x2<x1)swap(x1,x2);
	if(y2<y1)swap(y1,y2);
	for(int i=x1;i<=x2;i++)for(int j=y1;j<=y2;j++){
		if(i==sx && j==sy)continue;
		//printf("(%d %d)%c\n",i,j,board[i][j]);
		if(board[i][j]!='.')ok=false;
	}
	return ok;
}

int main(void){
	scanf("%d %d",&yy,&xx);
	for(int j=0;j<yy;j++){
		char ch[1000];
		scanf("%s",ch);
		for(int i=0;i<xx;i++){
			board[i][j]=ch[i];
			if(ch[i]=='.')continue;
			pos[ch[i]-'A'].push_back(MP(i,j));
		}
	}
	int ans=0;
	while(1){
		bool changed=false;
		for(int i=0;i<26;i++){
			if(pos[i].size()==0)continue;
			int x1=pos[i][0].first;
			int y1=pos[i][0].second;
			int x2=pos[i][1].first;
			int y2=pos[i][1].second;
			bool ok=false;
			//printf("[%c]\n",i+'A');
			if(x1!=x2 && y1!=y2){
				if((check(x1,y2,x1,y1) && check(x1,y2,x2,y2)) || (check(x2,y1,x1,y1) && check(x2,y1,x2,y2)))ok=true;
			}else if(x1==x2){
				if(abs(y1-y2)>=2 && check(x1,(y1+y2)/2,x1,y1) && check(x1,(y1+y2)/2,x2,y2))ok=true;
			}else{
				if(abs(x1-x2)>=2 && check((x1+x2)/2,y1,x1,y1) && check((x1+x2)/2,y1,x2,y2))ok=true;
			}
			if(ok){
				//printf("%c    %d %d %d %d\n",'A'+i,x1,y1,x2,y2);
				board[x1][y1]='.';
				board[x2][y2]='.';
				pos[i].clear();
				ans+=2;
				changed=true;
			}
		}
		if(!changed)break;
	}
	printf("%d\n",ans);
	return 0;
}

