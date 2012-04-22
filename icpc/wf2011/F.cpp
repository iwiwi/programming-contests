#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <climits>
#include <iostream>
#include <cassert>
#include <cstring>
#include <queue>

using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back
#define mp make_pair

#define F first
#define S second

typedef long long ll;
typedef pair<ll, ll> pll;
typedef map<ll, ll>::iterator ite_t;

int N;
ll C, D;

ll d[1000010], p[1000010], r[1000010], g[1000010];
pair<ll, int> ord[1000010];




map<ll, ll> que;

ll det(pll v, pll w) {
  return v.F * w.S - v.S * w.F;
}

pll sub(pll a, pll b) {
  return mp(a.F - b.F, a.S - b.S);
}

ll calc(pll p, ll x) {
  return -p.F * x + p.S;
}

double get(ll a) {
  ite_t i1 = que.lower_bound(a);
  if (i1 == que.end()) return -1E30;
  if (i1->F == a) return i1->S;
  if (i1 == que.begin()) return -1E30;
  ite_t i2 = i1--;
  return (double(a - i1->F) * i2->S + double(i2->F - a) * i1->S) / double(i2->F - i1->F);
}

bool relax(ite_t q) {
  ite_t p1, p2;
  if (q == que.end() || ++(p1 = q) == que.end() || ++(p2 = p1) == que.end()) {
    return false;
  }

  if (det(sub(*p2, *p1), sub(*q, *p1)) >= 0) {
    que.erase(p1);
    return true;
  } else {
    return false;
  }
}

void push(ll a, ll b) {
  if (get(a) >= b) return;
  que[a] = b;

  for (ite_t i = que.lower_bound(a);;) if (!relax(i)) break;

  ite_t i = que.lower_bound(a);
  if (i != que.begin() && --i != que.begin()) {
    for (--i; ; --i) {
      if (!relax(i) || i == que.begin()) break;
    }
  }
}

ll query(ll x) {
  ll y = calc(*--que.end(), x);
  while (que.size() >= 2) {
    ll ty = calc(*(----que.end()), x);
    if (ty >= y) {
      y = ty;
      que.erase(--que.end());
    }
    else break;
  }
  return y;
}




int main() {
  for (int ca = 1;; ++ca) {
    scanf("%d%lld%lld", &N, &C, &D);
    if (N == 0 && C == 0 && D == 0) return 0;

    rep (i, N) {
      scanf("%lld%lld%lld%lld", &d[i], &p[i], &r[i], &g[i]);
      ord[i] = mp(d[i], i);
    }
    sort(ord, ord + N);

    que.clear();
    push(0, C);

    rep (iter, N) {
      int i = ord[iter].second;

      ll y = query(d[i]);

      if (y < p[i]) continue;

      ll a = -g[i];
      ll b = y - p[i] + r[i] - g[i] * (d[i] + 1);
      push(a, b);
    }

    printf("Case %d: %lld\n", ca, query(D + 1));
  }
}

