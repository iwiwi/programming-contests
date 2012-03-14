#include <cstdio>
#include <utility>
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>
#include <stack>
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

enum bnf { EXP_B, EXP_E,
	   TER_B, TER_E,
	   FAC_B, FAC_E };
const pll F_NOT = mp(0, 0);
const pll F_EXP = mp(1, 0);

stack<pair<bnf, pll> > stk;

pll variable() {
  char c = S[p++];
  assert(c == 'x');
  assert(isdigit(S[p]));
  while (isdigit(S[p])) ++p;
  return mp(1, 1);
}

int main() {
  while (1 == scanf("%s", S)) {
    p = 0;

    stk.push(mp(EXP_B, mp(0, 1)));
    pll b;
    while (!stk.empty()) {
      bnf t = stk.top().first;
      pll a = stk.top().second;
      stk.pop();

      // printf("%d (%c): %d a = (%lld, %lld), b = (%lld, %lld)\n", p, S[p], t, a.T, a.F, b.T, b.F);
      
      if (t == EXP_B) {
	stk.push(mp(EXP_E, a));
	stk.push(mp(TER_B, mp(1, 0)));
      }
      else if (t == EXP_E) {
	a = mp((a.T * b.T + a.T * b.F + a.F * b.T) % MOD,
	       (a.F * b.F) % MOD);
	if (S[p] == '|') { ++p; stk.push(mp(EXP_B, a)); }
	else b = a;
      }
      else if (t == TER_B) {
	stk.push(mp(TER_E, a));
	stk.push(mp(FAC_B, mp(-1, -1)));
      }
      else if (t == TER_E) {
	a = mp((a.T * b.T) % MOD,
	       (a.T * b.F + a.F * b.T + a.F * b.F) % MOD);
	if (S[p] == '&') { ++p; stk.push(mp(TER_B, a)); }
	else b = a;
      }
      else if (t == FAC_B) {
	if (S[p] == 'x') {
	  b = variable();
	} else if (S[p] == '~') {
	  ++p;
	  stk.push(mp(FAC_E, F_NOT));
	  stk.push(mp(FAC_B, mp(-1, -1)));
	} else {
	  assert(S[p] == '(');
	  ++p;
	  stk.push(mp(FAC_E, F_EXP));
	  stk.push(mp(EXP_B, mp(0, 1)));
	}
      }
      else {
	if (a == F_NOT) {
	  b = mp(b.F, b.T);
	} else {
	  assert(S[p] == ')');
	  ++p;
	}
      }
    }

    // printf("!!! %lld %lld\n", b.T, b.F);
    
    cout << (b.T + MOD) % MOD << endl;
  }
  
  return 0;
}
