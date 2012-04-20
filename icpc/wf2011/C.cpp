#include <stdio.h>


int board[300][300];
int chk[300][300];

int tate,yoko;

int e,v,f;

int htoi(char c){
  if(c>='0' && c<='9')return c-'0';
  if(c>='a' && c<='f')return (c-'a')+10;
}

void saiki(int p,int q){
  if(p<0 || p>=tate || q<0 || q>=yoko)return;
     if(board[p][q]==0)return;
     if(chk[p][q]==1)return;
     chk[p][q]=1;
     v++;
     if(p<tate-1 && board[p+1][q]==1)e++;//{e++;printf("tate %d %d\n",p,q);}
     if(q<yoko-1 && board[p][q+1]==1)e++;//{e++;printf("yoko %d %d\n",p,q);}
     if(p<tate-1 && q<yoko-1 && board[p+1][q]==1 && board[p][q+1]==1 && board[p+1][q+1]==1)f++;
     saiki(p-1,q);
     saiki(p+1,q);
     saiki(p,q-1);
     saiki(p,q+1);
}

main(){
  for(int casenum=1;;casenum++){
    scanf("%d%d ",&tate,&yoko);
    if(tate==0 && yoko==0)return 0;
    for(int i=0;i<tate;i++){
      char buf[60];
      gets(buf);
      for(int j=0;j<yoko;j++){
        int d=htoi(buf[j]);
        board[i][4*j+0]=(d>>3)&1;
        board[i][4*j+1]=(d>>2)&1;
        board[i][4*j+2]=(d>>1)&1;
        board[i][4*j+3]=(d>>0)&1;
      }
    }
    yoko*=4;
    int cnt[6]={};
    for(int i=0;i<tate;i++)for(int j=0;j<yoko;j++)chk[i][j]=0;
    for(int i=0;i<tate;i++)for(int j=0;j<yoko;j++){
        if(board[i][j]==1 && chk[i][j]==0){
          v=0;e=0;f=0;
          saiki(i,j);
          //printf("%d %d: v=%d e=%d f=%d\n",i,j,v,e,f);
          int ana=1-v+e-f;
          cnt[ana]++;
        }
      }
    printf("Case %d: ",casenum);
    for(int i=0;i<cnt[1];i++)printf("A");
    for(int i=0;i<cnt[5];i++)printf("D");
    for(int i=0;i<cnt[3];i++)printf("J");
    for(int i=0;i<cnt[2];i++)printf("K");
    for(int i=0;i<cnt[4];i++)printf("S");
    for(int i=0;i<cnt[0];i++)printf("W");
    puts("");
  }
}
