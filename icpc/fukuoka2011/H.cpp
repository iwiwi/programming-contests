#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define OWAKON (-2)
#define mod(x) ((((x)%2011)+2011)%2011)
#define HERE(x) (x)[r1][c1][r2][c2]
//-2 is owakon

int vexpr[21][81][21][81];
int vterm[21][81][21][81];
int vfactor[21][81][21][81];
int vpowexpr[21][81][21][81];
int vprimary[21][81][21][81];
int vfraction[21][81][21][81];
int basel[21][81][21][81];

int rows,cols;

char board[21][81];

int inv[2022];

int fexpr(int r1,int c1,int r2,int c2);
int fterm(int r1,int c1,int r2,int c2);
int ffactor(int r1,int c1,int r2,int c2);
int fpowexpr(int r1,int c1,int r2,int c2);
int fprimary(int r1,int c1,int r2,int c2);
int ffraction(int r1,int c1,int r2,int c2);


bool allsp(int r1, int c1, int r2, int c2) {
  for (int i = r1; i < r2; ++i) {
    for (int j = c1; j < c2; ++j) {
      if (board[i][j] != '.') return false;
    }
  }
  return true;
}

bool allsp_col(int r1, int r2, int c1) {
  return allsp(r1, c1, r2, c1 + 1);
}

bool allsp_row(int c1, int c2, int r1) {
  return allsp(r1, c1, r1 + 1, c2);
}

void shrink(int &r1, int &c1, int &r2, int &c2) {
  while (r1 < r2) {
    if (allsp_row(c1, c2, r1)) ++r1;
    else break;
  }
  while (r1 < r2) {
    if (allsp_row(c1, c2, r2 - 1)) --r2;
    else break;
  }
  while (c1 < c2) {
    if (allsp_col(r1, r2, c1)) ++c1;
    else break;
  }
  while (c1 < c2) {
    if (allsp_col(r1, r2, c2 - 1)) --c2;
    else break;
  }
}

int fdigit(int r1,int c1,int r2,int c2){
  shrink(r1,c1,r2,c2);
  //printf("fdigit %d %d %d %d %c\n",r1,c1,r2,c2,board[r1][c1]);

  if(r2-r1==1 && c2-c1==1 && isdigit(board[r1][c1]))return (board[r1][c1]-'0');
  return OWAKON;
}

int fexpr(int r1,int c1,int r2,int c2){
  shrink(r1, c1, r2, c2);
  if(HERE(vexpr)!=-1)return HERE(vexpr);
  if(fterm(r1,c1,r2,c2)!=OWAKON){
    return HERE(vexpr)=fterm(r1,c1,r2,c2);
  }
  for(int j=c1+1;j<c2-1;j++){
    for(int i=r1;i<r2;i++){
      if(board[i][j]=='+' || board[i][j]=='-'){
	if(allsp_col(r1,r2,j-1) && allsp_col(r1,r2,j+1) &&
	   allsp_col(r1,i,j) && allsp_col(i+1,r2,j)){
	  int ret1=fexpr(r1,c1,r2,j-1);
	  int ret2=fterm(r1,j+2,r2,c2);
	  if(ret1!=OWAKON && ret2!=OWAKON){
	    //printf("(%d %d %d %d) %c (%d %d %d %d)\n",r1,c1,r2,j-1,board[i][j],r1,j+2,r2,c2);
	    if(board[i][j]=='+')return HERE(vexpr)=mod(ret1+ret2);
	    else return HERE(vexpr)=mod(ret1-ret2);
	  }
	}
      }
    }
  }
  return HERE(vexpr)=OWAKON;
}

int fterm(int r1,int c1,int r2,int c2){
  shrink(r1, c1, r2, c2);
  if(HERE(vterm)!=-1)return HERE(vterm);
  if(ffactor(r1,c1,r2,c2)!=OWAKON){
    return HERE(vterm)=ffactor(r1,c1,r2,c2);
  }
  for(int j=c1+1;j<c2-1;j++){
    for(int i=r1;i<r2;i++){
      if(board[i][j]=='*'){
	if(allsp_col(r1,r2,j-1) && allsp_col(r1,r2,j+1) &&
	   allsp_col(r1,i,j) && allsp_col(i+1,r2,j)){
	  int ret1=fterm(r1,c1,r2,j-1);
	  int ret2=ffactor(r1,j+2,r2,c2);
	  if(ret1!=OWAKON && ret2!=OWAKON){
	    return HERE(vterm)=mod(ret1*ret2);
	  }
	}
      }
    }
  }
  return -2;
}

int ffactor(int r1,int c1,int r2,int c2){
  shrink(r1, c1, r2, c2);
  if(HERE(vfactor)!=-1)return HERE(vfactor);
  if(fpowexpr(r1,c1,r2,c2)!=OWAKON){
    return HERE(vfactor)=fpowexpr(r1,c1,r2,c2);
  }
  if(ffraction(r1,c1,r2,c2)!=OWAKON){
    return HERE(vfactor)=ffraction(r1,c1,r2,c2);
  }
  if(c2-c1>=3){
    for(int i=r1;i<r2;i++){
      if(board[i][c1]=='-'){
	if(allsp_col(r1,i,c1) && allsp_col(i+1,r2,c1) && allsp_col(r1,r2,c1+1)){
	  int ret=ffactor(r1,c1+2,r2,c2);
	  if(ret!=OWAKON){
	    return HERE(vfactor)=mod(-ret);
	  }
	}
      }
    }
  }
  return -2;
}

int mypow(int x,int d){
  int ret=1;
  if(d==0)return 1;
  if(d%2==1)return mod(mypow(x,d-1)*x);
  ret=mypow(x,d/2);
  return mod(ret*ret);
  //for(int i=0;i<d;i++)ret=mod(ret*x);
}

int fpowexpr(int r1,int c1,int r2,int c2){
  shrink(r1, c1, r2, c2);
  if(HERE(vpowexpr)!=-1)return HERE(vpowexpr);
  if(fprimary(r1,c1,r2,c2)!=OWAKON){
    return HERE(vpowexpr)=fprimary(r1,c1,r2,c2);
  }
  for(int i=r1;i<r2;i++){
    if(fdigit(i,c2-1,i+1,c2)!=OWAKON){
      if(allsp_col(r1,i,c2-1) && allsp_col(i+1,r2,c2-1)){
	int d=fdigit(i,c2-1,i+1,c2);
	int ret=fprimary(r1,c1,r2,c2-1);
	if(ret!=OWAKON){
	  return HERE(vpowexpr)=mypow(ret,d);
	}
      }
    }
  }
  return -2;
}

int fprimary(int r1,int c1,int r2,int c2){
  shrink(r1, c1, r2, c2);
  if(HERE(vprimary)!=-1)return HERE(vprimary);
  if(fdigit(r1,c1,r2,c2)!=OWAKON){
    return HERE(vprimary)=fdigit(r1,c1,r2,c2);
  }
  if(c2-c1>=5){
    for(int i=r1;i<r2;i++){
      if(board[i][c1]=='(' && board[i][c2-1]==')'){
	if(allsp_col(r1,i,c1) && allsp_col(i+1,r2,c1) && allsp_col(r1,i,c2-1) && allsp_col(i+1,r2,c2-1) && allsp_col(r1,r2,c1+1) && allsp_col(r1,r2,c2-2)){
	  int ret=fexpr(r1,c1+2,r2,c2-2);
	  if(ret!=OWAKON)return HERE(vprimary)=ret;
	}
      }
    }
  }
  return OWAKON;
}


int ffraction(int r1,int c1,int r2,int c2){
  shrink(r1, c1, r2, c2);
  if(HERE(vfraction)!=-1)return HERE(vfraction);

  for(int i=r1+1;i<r2-1;i++){
    bool allhyphen=true;
    for(int j=c1;j<c2;j++)if(board[i][j]!='-')allhyphen=false;
    if(allhyphen){
      int ret1=fexpr(r1,c1,i,c2);
      int ret2=fexpr(i+1,c1,r2,c2);
      if(ret1!=OWAKON && ret2!=OWAKON)return HERE(vfraction)=mod(ret1*inv[ret2]);
    }
  }
  return OWAKON;
}

int main(){
  for(int i=1;i<2011;i++)inv[i]=mypow(i,2009);
  for(;;){
    scanf("%d ",&rows);
    if(rows==0)return 0;
    for(int i=0;i<rows;i++){
      gets(board[i]);
    }
    cols=strlen(board[0]);
    memset(vexpr,-1,sizeof(vexpr));
    memset(vterm,-1,sizeof(vexpr));
    memset(vfactor,-1,sizeof(vexpr));
    memset(vpowexpr,-1,sizeof(vexpr));
    memset(vprimary,-1,sizeof(vexpr));
    memset(vfraction,-1,sizeof(vexpr));
    printf("%d\n",fexpr(0,0,rows,cols));
  }
}
