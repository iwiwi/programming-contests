#include <stdio.h>

char board[200][200];

long long hoge[200][200][4];

long long dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};

main(){
  for(;;){
    long long xsize,ysize,l;
    scanf("%lld%lld%lld ",&ysize,&xsize,&l);
    if(xsize==0)return 0;
    for(long long  i=0;i<=xsize+1;i++)for(long long  j=0;j<=ysize+1;j++)board[i][j]='#';
    long long  ix,iy,id;
    for(long long  j=1;j<=ysize;j++){
      char buf[200];
      gets(buf);
      for(long long  i=1;i<=xsize;i++){
        board[i][j]=buf[i-1];
        if(board[i][j]=='E'){ix=i;iy=j;id=0;board[i][j]='.';}
        if(board[i][j]=='S'){ix=i;iy=j;id=1;board[i][j]='.';}
        if(board[i][j]=='W'){ix=i;iy=j;id=2;board[i][j]='.';}
        if(board[i][j]=='N'){ix=i;iy=j;id=3;board[i][j]='.';}
      }
    }
    for(long long  i=1;i<=xsize;i++)for(long long  j=0;j<=ysize;j++)for(long long  d=0;d<4;d++)hoge[i][j][d]=-1;
    hoge[ix][iy][id]=0;
    long long  cnt=0;
    for(;;){
      while(board[ix+dx[id]][iy+dy[id]]=='#')id=(id+1)%4;
      ix+=dx[id];
      iy+=dy[id];
      cnt++;
      if(cnt==l){
        printf("%lld %lld %c\n",iy,ix,"ESWN"[id]);
        break;
      }
      if(hoge[ix][iy][id]==-1)hoge[ix][iy][id]=cnt;
      else {
        long long m=cnt-hoge[ix][iy][id];
        long long nokori=l-cnt;
        long long r=nokori%m;
        for(long long x=1;x<=xsize;x++){
          for(long long y=1;y<=ysize;y++){
            for(long long d=0;d<4;d++){
              if(hoge[x][y][d]==hoge[ix][iy][id]+r){
                printf("%lld %lld %c\n",y,x,"ESWN"[d]);
                goto owata;
              }
            }
          }
        }
      }
    }
 owata:
    ;
  }
}
