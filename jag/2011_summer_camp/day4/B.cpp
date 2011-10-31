#include <stdio.h>
#include <algorithm>
using namespace std;
main(){
  char board[8][10];
  for(int i=0;i<8;i++){
    gets(board[i]);
  }
  char pl='o',op='x';
  int pass=0;
  for(;;){
    int dx[8]={1,1,1,0,-1,-1,-1,0};
    int dy[8]={1,0,-1,-1,-1,0,1,1};
    int m=0,mi=-1,mj=-1;
    for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
        if(board[i][j]!='.')continue;
        int cnt=0;
        for(int d=0;d<8;d++){
          int px=i,py=j;
          int tmp=0;
          for(;;){
            px+=dx[d];
            py+=dy[d];
            if(px<0 || px>=8 || py<0 || py>=8 || board[px][py]=='.'){
                tmp=0;break;
            }
            if(board[px][py]==pl)break;
            if(board[px][py]==op)tmp++;
          }
          cnt+=tmp;
        }
          if((pl=='o' && cnt>m) || (pl=='x' && cnt>=m)){
            m=cnt;
            mi=i;
            mj=j;
          }
      }
    }
      if(m==0){
        pass++;
        if(pass==2)break;
      }else{
        pass=0;
        board[mi][mj]=pl;
        for(int d=0;d<8;d++){
          int px=mi,py=mj;
          int tmp=0;
          for(;;){
            px+=dx[d];
            py+=dy[d];
            if(px<0 || px>=8 || py<0 || py>=8 || board[px][py]=='.'){
                tmp=0;break;
            }
            if(board[px][py]==pl)break;
            if(board[px][py]==op)tmp++;
          }
            if(tmp>0){
              for(int i=1;i<=tmp;i++)board[mi+dx[d]*i][mj+dy[d]*i]=pl;
            }
        }
          //for(int i=0;i<8;i++)puts(board[i]);
          //puts("");
      }
      swap(pl,op);
   }
      for(int i=0;i<8;i++)puts(board[i]);
}
