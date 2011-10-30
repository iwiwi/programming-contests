#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define P 97654321
#define modp(x) ((((x)%P)+P)%P)

long long powmod(long long a,long long b,long long m){
  if(b==0)return 1;
  if(b%2==1)return (powmod(a,b-1,m)*a)%m;
  long long c=powmod(a,b/2,m);
  return (c*c)%m;
}


main(){
  int n;
  long long m;
  for(;scanf("%d%lld",&n,&m)>0;){
    int a[n];
    for(int i=0;i<n;i++)a[i]=i;
    long long ans=0;
    long long ord=0;
    do{
      for(int b=0;b<(1<<n);b++){
        long long hoge=1;
        int chk[1<<n];
        memset(chk,0,sizeof(chk));
        for(int v=0;v<(1<<n);v++){
          if(chk[v]==0){
            int w=v;
            for(;;){
              //printf("%d ",w);
              chk[w]=1;
              int fw=0;
              for(int i=0;i<n;i++){
                int bit=((w^b)>>i)&1;
                int pos=a[i];
                fw+=(bit<<pos);
              }
              w=fw;
              if(w==v)break;
            }
            //puts("");
            hoge=modp(hoge*m);
          }
        }
        ans=modp(ans+hoge);
        ord++;
      }
    }while(next_permutation(a,a+n));
    ans=modp(ans*powmod(ord,P-2,P));
    printf("%lld\n",ans);
  }
}
