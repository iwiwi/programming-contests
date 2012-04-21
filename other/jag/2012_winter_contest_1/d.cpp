#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;

map<pair<int,int>,int> hijimei;

int sigma[40000];
int tau[40000];
int g;

int n;

pair<int,int> transf(int r,int c){
  int rr,cc;
  if(g==0){rr=r;cc=c;}
  if(g==1){rr=c;cc=n-1-r;}
  if(g==2){rr=n-1-r;cc=n-1-c;}
  if(g==3){rr=n-1-c;cc=r;}
  if(g==4){rr=r;cc=n-1-c;}
  if(g==5){rr=c;cc=r;}
  if(g==6){rr=n-1-r;cc=c;}
  if(g==7){rr=n-1-c;cc=n-1-r;}
  return make_pair(sigma[rr],tau[cc]);
}

main(){
  int q;
  scanf("%d%d",&n,&q);
  int aa,bb,cc,dd,ee,ff,gg;
  scanf("%d%d%d%d%d%d%d ",&aa,&bb,&cc,&dd,&ee,&ff,&gg);dd--;ee--;ff--;gg--;
  for(int i=0;i<n;i++)sigma[i]=tau[i]=i;
  for(int i=0;i<q;i++){
    char buf[10];
    scanf("%s",&buf);
    if(strcmp(buf,"WR")==0){
      int r,c,v;
      scanf("%d%d%d ",&r,&c,&v);r--;c--;
      hijimei[transf(r,c)]=v;
    }
    if(strcmp(buf,"CP")==0){
      int r1,c1,r2,c2;
      scanf("%d%d%d%d ",&r1,&c1,&r2,&c2);r1--;c1--;r2--;c2--;
      int v;
      pair<int,int> hoge1=transf(r1,c1),hoge2=transf(r2,c2);
      if(hijimei.count(hoge1)==1){
	v=hijimei[hoge1];
      }else{
	v=((long long)(hoge1.first+1)*aa+(long long)(hoge1.second+1)*bb)%cc;
      }
      hijimei[hoge2]=v;
    }
    if(strcmp(buf,"SR")==0){
      int r1,r2;
      scanf("%d%d ",&r1,&r2);r1--;r2--;
      if(g==0 || g==4)swap(sigma[r1],sigma[r2]);
      if(g==1 || g==7)swap(tau[n-1-r1],tau[n-1-r2]);
      if(g==2 || g==6)swap(sigma[n-1-r1],sigma[n-1-r2]);
      if(g==3 || g==5)swap(tau[r1],tau[r2]);
    }
    if(strcmp(buf,"SC")==0){
      int c1,c2;
      scanf("%d%d ",&c1,&c2);c1--;c2--;
      if(g==0 || g==6)swap(tau[c1],tau[c2]);
      if(g==1 || g==5)swap(sigma[c1],sigma[c2]);
      if(g==2 || g==4)swap(tau[n-1-c1],tau[n-1-c2]);
      if(g==3 || g==7)swap(sigma[n-1-c1],sigma[n-1-c2]);
    }
    if(strcmp(buf,"RL")==0){
      int arr[8]={1,2,3,0,5,6,7,4};
      g=arr[g];
    }
    if(strcmp(buf,"RR")==0){
      int arr[8]={3,0,1,2,7,4,5,6};
      g=arr[g];
    }
    if(strcmp(buf,"RH")==0){
      int arr[8]={6,5,4,7,2,1,0,3};
      g=arr[g];
    }
    if(strcmp(buf,"RV")==0){
      int arr[8]={4,7,6,5,0,3,2,1};
      g=arr[g];
    }
  }
  /*
  for(int r=0;r<n;r++){
    for(int c=0;c<n;c++){
      int brc;
      pair<int,int> hoge=transf(r,c);
      if(hijimei.count(hoge)==1)brc=hijimei[hoge];
      else brc=((long long)(hoge.first+1)*a+(long long)(hoge.second+1)*b)%c;
      printf("%d ",brc);
    }
    puts("");
  }
  */
  long long h=314159265;
  for(int ridx=dd;ridx<=ee;ridx++){
    for(int cidx=ff;cidx<=gg;cidx++){
      int brc;
      pair<int,int> hoge=transf(ridx,cidx);
      if(hijimei.count(hoge)==1)brc=hijimei[hoge];
      else brc=((long long)(hoge.first+1)*aa+(long long)(hoge.second+1)*bb)%cc;
      h=(31*h+brc)%1000000007;
    }
  }
  printf("%lld\n",h);
}
