#include <stdio.h>
#include <string.h>

#define N 1000000000LL

long long gcd(long long a,long long b){
  return b?gcd(b,a%b):a;
}

long long doit(long long q,long long p){
  long long g=gcd(p,q);
  p/=g;q/=g;
  //printf("%lld %lld\n",p,q);
  return (N/p-1)*(N/p)/2*p*q+((p+1)*(q+1)-2)/2*(N/p);
}

main(){
  for(;;){
    char buf[30];
    gets(buf);
    if(buf[0]=='#')return 0;
    int l=strlen(buf)-2;
    long long bunbo=1;
    for(int i=0;i<l;i++)bunbo*=10;
    long long n;
    sscanf(buf,"0.%lld",&n);
    printf("%lld\n",doit(10*n+5,10*bunbo)-doit(10*n-5,10*bunbo));
  }
}
