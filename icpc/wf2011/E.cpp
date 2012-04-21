#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define M 1000

int cs[2*M+10][2*M+10];
int rui[2*M+10][2*M+10];

int cnt(int i,int j){
  return rui[min(2*M,max(0,i))][min(2*M,max(0,j))];
}

main(){
  for(int casenum=1;;casenum++){
    int tate,yoko;
    int n;
    int qnum;
    scanf("%d%d%d%d",&yoko,&tate,&n,&qnum);
    if(yoko==0 && tate==0)return 0;
    for(int i=0;i<=2*M;i++)for(int j=0;j<=2*M;j++)cs[i][j]=0;//memset(cs,0,sizeof(cs));
    for(int i=0;i<n;i++){
      int cp,cq;
      scanf("%d%d",&cq,&cp);cp--;cq--;
      cs[cp+cq][cp-cq+M]=1;
    }
    for(int i=0;i<=2*M;i++){
      for(int j=0;j<=2*M;j++){
        if(i==0 || j==0)rui[i][j]=0;
        else rui[i][j]=rui[i-1][j]+rui[i][j-1]-rui[i-1][j-1]+cs[i-1][j-1];
      }
    }
    printf("Case %d:\n",casenum);
    for(int i=0;i<qnum;i++){
      int d;
      scanf("%d",&d);
      int maxi=-1,mp,mq;
      for(int p=0;p<tate;p++){
        for(int q=0;q<yoko;q++){
          int kosu=cnt(p+q+d+1,p-q+M+d+1)-cnt(p+q+d+1,p-q+M-d)-cnt(p+q-d,p-q+M+d+1)+cnt(p+q-d,p-q+M-d);
          if(kosu>maxi){
            maxi=kosu;
            mp=p;
            mq=q;
          }
        }
      }
      printf("%d (%d,%d)\n",maxi,mq+1,mp+1);
    }
  }
}
