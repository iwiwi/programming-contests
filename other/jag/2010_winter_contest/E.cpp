/*
#include <stdio.h>

char board[20][20];
int xsize,ysize;

main(){
	scanf("%d%d",&xsize,&ysize);
	int i,j,k,l;
	int sx,sy;
	for(j=0;j<ysize;j++){
		char buf[100];
		gets(buf);
		for(i=0;i<xsize;i++){
			board[i][j]=buf[i];
			if(board[i][j]=='@')sx=i,sy=j,board[i][j]='.';
		}
	}
	
}
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <

main(){
	srand(time(NULL)+getpid());
	puts()
}