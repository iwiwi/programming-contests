#include <cstdio>
#include <utility>
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define T first
#define F second

typedef long long ll;
typedef pair<ll, ll> pll;


const ll MOD = 1000000007;

char S[1000010];
int p;

void show(const char *msg, pll a) {
  printf("%s (%lld, %lld)\n", msg, a.T, a.F);
}

pll expression();
pll term();
pll factor();

pll expression() {
  pll a = term();
  while (S[p] == '|') {
    ++p;
    pll b = term();
    a = mp((a.T * b.T + a.T * b.F + a.F * b.T) % MOD,
	   (a.F * b.F) % MOD);
  }
  return a;
}

pll term() {
  pll a = factor();
  while (S[p] == '&') {
    ++p;
    pll b = factor();
    a = mp((a.T * b.T) % MOD,
	   (a.T * b.F + a.F * b.T + a.F * b.F) % MOD);
  }
  return a;
}

pll variable() {
  char c = S[p++];
  assert(c == 'x');
  assert(isdigit(S[p]));
  while (isdigit(S[p])) ++p;
  return mp(1, 1);
}

pll factor() {
  if (S[p] == 'x') {
    return variable();
  } else if (S[p] == '~') {
    ++p;
    pll a = factor();
    return mp(a.F, a.T);
  } else {
    assert(S[p] == '(');
    ++p;
    pll a = expression();
    assert(S[p] == ')');
    ++p;
    return mp(a.T, a.F);
  }
}

int main() {
  while (1 == scanf("%s", S)) {
    p = 0;

    pll r = expression();
    int l = strlen(S);
    assert(l == p);
    
    cout << (r.T + MOD) % MOD << endl;
  }
  
  return 0;
}
