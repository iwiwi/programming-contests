#include <stdio.h>
#include <algorithm>
using namespace std;

char board[50][50];

main(){
	int xsize,ysize,n;
	scanf("%d%d%d ",&ysize,&xsize,&n);
	
	for(int j=0;j<ysize;j++){
		char buf[50];
		gets(buf);
		for(int i=0;i<xsize;i++){
			board[i][j]=buf[i];
		}
	}
	for(int x=0;x<xsize-1;x++){
		for(int y=0;y<ysize;y++){
			char tmp[50][50];
			for(int k=0;k<xsize;k++)for(int l=0;l<ysize;l++)tmp[k][l]=board[k][l];
			swap(tmp[x][y],tmp[x+1][y]);
			//printf("%d %d,%d %d\n",i,j,i+1,j);
			for(;;){
				/*
				for(int j=0;j<ysize;j++){
					for(int i=0;i<xsize;i++){
						printf("%c",tmp[i][j]);
					}
					puts("");
				}
				*/
				for(int i=0;i<xsize;i++){
					char hoge[50];
					int cnt=0;
					for(int j=ysize-1;j>=0;j--)if(tmp[i][j]!='.')hoge[cnt++]=tmp[i][j];
					for(int k=0;k<cnt;k++)tmp[i][ysize-1-k]=hoge[k];
					for(int k=cnt;k<ysize;k++)tmp[i][ysize-1-k]='.';
				}
				bool hoge=false;
				int num[50][50][4];
				for(int i=0;i<xsize;i++)for(int j=0;j<ysize;j++){
					if(i==0)num[i][j][0]=1;
					else num[i][j][0]=(tmp[i-1][j]==tmp[i][j]?num[i-1][j][0]+1:1);
				}
				for(int i=0;i<xsize;i++)for(int j=0;j<ysize;j++){
					if(j==0)num[i][j][1]=1;
					else num[i][j][1]=(tmp[i][j-1]==tmp[i][j]?num[i][j-1][1]+1:1);
				}
				int dx[2]={1,0},dy[2]={0,1};
				for(int i=0;i<xsize;i++)for(int j=0;j<ysize;j++){
					for(int d=0;d<2;d++){
						if(num[i][j][d]>=n){
							for(int k=0;k<n;k++){
								if(tmp[i-dx[d]*k][j-dy[d]*k]!='.')hoge=true;
								tmp[i-dx[d]*k][j-dy[d]*k]='.';
							}
						}
					}
				}
				if(!hoge)break;
			}
			bool zenkesi=true;
			for(int i=0;i<xsize;i++)for(int j=0;j<ysize;j++)zenkesi=zenkesi&&(tmp[i][j]=='.');
			if(zenkesi){
				puts("YES");
				return 0;
			}
		}
	}
	puts("NO");
	return 0;
}