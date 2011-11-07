#include <stdio.h>
#include <algorithm>
#include <string>
using namespace std;

string s[100010];

long long dp[100010][11];
long long rui[100010][11];
main(){
  for(;;){
    long long a,b,m;
    scanf("%lld%lld%lld",&a,&b,&m);
    if(a==0 && b==0 && m==0)return 0;
    for(long long i=a;i<=b;i++){
      string tmp="";
      int j=i;
      for(;j>0;){
        tmp=tmp+(char)('0'+(j%10));
        j/=10;
      }
      reverse(tmp.begin(),tmp.end());
      s[i-a]=tmp;
    }
    long long n=b-a+1;
    sort(s,s+n);
    for(int l=1;l<=10;l++)dp[0][l]=0;
    dp[0][1]=1;
    rui[0][0]=0;
    for(int l=1;l<=10;l++)rui[0][l]=rui[0][l-1]+dp[0][l];
    for(int i=0;i<n;i++){
      for(int l=1;l<=10;l++)dp[i+1][l]=0;
      for(int l=1;l<=10;l++){
        dp[i+1][l]=(dp[i+1][l]+dp[i][l])%m;
      }
      int nextl=s[i].length();
      dp[i+1][nextl]=(dp[i+1][nextl]+rui[i][nextl])%m;

      rui[i+1][0]=0;
      for(int l=1;l<=10;l++)rui[i+1][l]=rui[i+1][l-1]+dp[i+1][l];
    }
    printf("%lld\n",(rui[n][10]+m-1)%m);
  }
}
