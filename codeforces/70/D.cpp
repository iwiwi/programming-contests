#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;
typedef map<int, int>::iterator ite_t;

bool is_upper(const ite_t &l, int x1, int y1, const ite_t &r) {
  ll x0 = l->first, y0 = l->second;
  ll x2 = r->first, y2 = r->second;
  return y1 * (x2 - x0) > y0 * (x2 - x0) + (y2 - y0) * (x1 - x0);
}

void delete_right(map<int, int> &hull, ite_t &ite) {
  for (;;) {
    ite_t nxt1 = ite; ++nxt1;
    if (nxt1 == hull.end()) return;

    ite_t nxt2 = nxt1; ++nxt2;
    if (nxt2 == hull.end()) return;

    if (is_upper(ite, nxt1->first, nxt1->second, nxt2)) break;
    hull.erase(nxt1);
  }
}

void delete_left(map<int, int> &hull, ite_t &ite) {
  for (;;) {
    if (ite == hull.begin()) return;
    ite_t nxt1 = ite; --nxt1;

    if (nxt1 == hull.begin()) return;
    ite_t nxt2 = nxt1; --nxt2;

    if (is_upper(nxt2, nxt1->first, nxt1->second, ite)) break;
    hull.erase(nxt1);
  }
}

bool process(map<int, int> &hull, int x, int y, bool insert) {
  bool out = false;
  if (hull.empty()) out = true;
  else {
    ite_t ite = hull.lower_bound(x);
    if (ite == hull.end()) out = true;
    else if (ite->first == x) out = y > ite->second;
    else if (ite == hull.begin()) out = true;
    else {
      ite_t prv = ite; --prv;
      out = is_upper(prv, x, y, ite);
    }
  }

  if (out && insert) {
    hull[x] = y;
    ite_t ite = hull.find(x);
    delete_left(hull, ite);
    delete_right(hull, ite);
  }
  return out;
}

map<int, int> uphull, lohull;

void insert(int x, int y) {
  process(uphull, x, +y, true);
  process(lohull, x, -y, true);
}

bool is_outside(int x, int y) {
  return process(uphull, x, +y, false) || process(lohull, x, -y, false);
}

int main() {
  int Q;
  scanf("%d", &Q);

  map<int, int> uphull, lohull;
  rep (q, Q) {
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y);

    if (t == 1) insert(x, y);
    else {
      if (is_outside(x, y)) puts("NO");
      else puts("YES");
    }
  }

  return 0;
}

