#include <cstdio>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

typedef long long ll;

long long mulmod(long long a,long long b,long long m){
  if(b==0)return 0;
  if(b%2==1)return (mulmod(a,b-1,m)+a)%m;
  long long c=mulmod(a,b/2,m);
  return (c+c)%m;
}

long long powmod(long long a,long long b,long long m){
  if(b==0)return 1;
  if(b%2==1)return mulmod(powmod(a,b-1,m),a,m);
  long long c=powmod(a,b/2,m);
  return mulmod(c,c,m);
}


const ll MOD2 = (1LL<<60);
const ll MOD5 = 1490116119384765625LL;

int solve(int M, int N) {
  ll s2 = 0;
  ll s5 = 0;

  for (int i = 1; i <= M; ++i) {
    s2 += powmod(i, N, MOD2);
    s2 %= MOD2;
    s5 += powmod(i, N, MOD5);
    s5 %= MOD5;
  }
  
  if (s2 == 0 || s5 == 0) {
    //fprintf(stderr, "%d %d\n", M, N);
    //exit(EXIT_FAILURE);
    return 1;
  }
  
  int ans2 = 0;
  while (s2 % 2 == 0) {
    ++ans2;
    s2 /= 2;
  }
  int ans5 = 0;
  while (s5 % 5 == 0) {
    ++ans5;
    s5 /= 5;
  }
  return min(ans2,ans5);
}

int main() {
  /*
  int ma = 0;
  for (int m = 1; m <= 100; ++m) {
    for (int n = 1; n <= 1000000; ++n) {
      int ans = solve(m, n);
      if (ans > ma) {
        printf("%d (%d %d)\n", ans, m, n);
        ma = ans;
      }
    }
  }
  */
  int M, N;
  
  while (2 == scanf("%d%d", &M, &N)) {
    printf("%d\n", solve(M, N));
  }
  
  return 0;
}
