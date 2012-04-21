#include <stdio.h>
#include <string.h>
#include <utility>
#include <algorithm>
using namespace std;

#define MAX 101010

int tame[MAX*9][2];
int p10[10];

int ansm,ansa,ansn,ansb;
void update(int m,int a,int n,int b,int key){
  if(m<=8){
    if(a*p10[m]+(b-a)*p10[n]+b==key)return;
  }
  bool gre;
  if(m>ansm)gre=true;
  else if(m<ansm)gre=false;
  else if(a>ansa)gre=true;
  else if(a<ansa)gre=false;
  else{
    if(n>ansn){
      if(b>ansa)gre=true; else gre=false;
    }
    if(n<ansn){
      if(a>ansb)gre=true; else gre=false;
    }
    if(n==ansn){
      if(b>ansb)gre=true; else gre=false;
    }
  }
  //printf("%d %d %d %d %s %d %d %d %d\n",m,a,n,b,gre?">":"<=",ansm,ansa,ansn,ansb);
  if(!gre){
    ansm=m;
    ansa=a;
    ansn=n;
    ansb=b;
  }
}

//long long loopcnt;

void doit(int key,int a,int b){
  //printf("key=%d a=%d b=%d\n",key,a,b);
  int anscnt=0;
  memset(tame,-1,sizeof(int)*2*key);
  int a10m=a%key;
  int ba10m=((b-a)%key+key)%key;
  for(int m=1;m<=key/9/8+15;m++){
    //loopcnt++;
    a10m=(a10m*10)%key;
    //printf("a*10^m=%d\n",a10m);
    if(tame[a10m][0]!=-1){
      anscnt++;
      update(m,a,tame[a10m][0],b,key);
      if(anscnt==2)break;
    }
    if(tame[a10m][1]!=-1){
      anscnt++;
      update(m,a,tame[a10m][1],b,key);
      if(anscnt==2)break;
    }
    ba10m=(ba10m*10)%key;
    int neg=((-ba10m+b)%key+key)%key;
    //printf("store %d\n",neg);
    if(b-a>0){
      if(tame[neg][0]==-1)tame[neg][0]=m;
      else if(tame[neg][1]==-1)tame[neg][1]=m;
    }else{
      tame[neg][1]=tame[neg][0];
      tame[neg][0]=m;
    }
  }
}

main(){
  
  p10[0]=1;
  for(int i=1;i<=9;i++)p10[i]=p10[i-1]*10;
  //doit(27,1,9);
  
  for(;;){
    int k;
    scanf("%d",&k);
    if(k==0)return 0;
    //loopcnt=0;
    k*=9;
    ansm=10101010;ansa=1;ansn=5050505;ansb=0;//initialize
    for(int a=1;a<=9;a++){
      for(int b=0;b<=9;b++){
       if(a==b)continue;
       doit(k,a,b);
      }
    }
    // printf("loopcnt=%lld\n",loopcnt);
    printf("%d: %d %d %d %d\n",k/9,ansm-ansn,ansa,ansn,ansb);
  }
  
}
