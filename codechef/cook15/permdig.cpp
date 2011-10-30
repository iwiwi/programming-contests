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

map<vector<int>, ll> mem[100][2];
int B;
string C;
int L;

ll search(int k, int c, vector<int> &v) {
  iter(mem[k][c]) ite = mem[k][c].find(v);
  if (ite != mem[k][c].end()) return ite->second;

  // printf("k = %d, c = %d: ", k, c);rep (i, 2) { rep (d, B) printf("%d ", v[i * B + d]); printf(" / "); };puts("");

  if (k == L) {
    if (c == 0 && count(all(v), 0) == 2 * B - (v[0] ? 1 : 0) - (v[B] ? 1 : 0)) return 1;
    else return 0;
  }

  int d = C[k] - '0';

  bool z[2] = {true, true};
  rep (i, 2) rep (d, B) if (v[i * B + d] != 0) z[i] = false;

  ll res = 0;
  rep (a, B) {
    if (v[a] == 0 && !(a == 0 && z[0])) continue;

    rep (b, B) {
      if (v[B + b] == 0 && !(b == 0 && z[1])) continue;

      if ((a + b + c) % B != d) continue;

      if (!(a == 0 && z[0])) --v[a];
      if (!(b == 0 && z[1])) --v[B + b];

      res += search(k + 1, (a + b + c) / B, v);

      if (!(a == 0 && z[0])) ++v[a];
      if (!(b == 0 && z[1])) ++v[B + b];
    }
  }


  return mem[k][c][v] = res;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    cin >> B;

    vector<int> cnt(B * 2);
    rep (i, 2) {
      string s;
      cin >> s;
      rep (j, s.length()) ++cnt[B * i + (s[j] - '0')];
    }

    cin >> C;
    reverse(all(C));
    L = C.length();

    rep (i, L) rep (c, 2) mem[i][c].clear();
    printf("%lld\n", search(0, 0, cnt));
  }

  return 0;
}

