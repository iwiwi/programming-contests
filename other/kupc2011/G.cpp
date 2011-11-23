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

int N, K;
bool ans[10010];

vector<int> gen_rand(int n) {
  vector<int> res;
  do {
    rep (i, n) {
      if (ans[i]) continue;
      if ((rand() >> 10) & 1) res.pb(i);
    }
  } while (res.empty());
  return res;
}

pair<vector<int>, vector<int> > gen_half(const vector<int> &v) {
  int k = v.size() / 2;
  return mp(vector<int>(v.begin(), v.begin() + k),
            vector<int>(v.begin() + k, v.end()));
            
}

bool tmp[10010];
bool ask(const vector<int> &v) {
  memset(tmp, 0, sizeof(tmp));
  rep (i, v.size()) tmp[v[i]] = true;
  printf("?");
  rep (i, N) printf("%d", tmp[i] ? 1 : 0);
  puts("");
  fflush(stdout);

  int r;
  scanf("%d", &r);
  return r == 1;
}

void solve(int n, int k) {
  N = n;
  K = k;
  memset(ans, 0, sizeof(ans));

  rep (i, k) {
    vector<int> se;
    do {
      se = gen_rand(n);
    } while (ask(se) == false);

    while (se.size() > 1) {
      pair<vector<int>, vector<int> > p = gen_half(se);
      if (ask(p.first)) se = p.first;
      else se = p.second;
    }

    ans[se[0]] = true;
  }

  vector<int> res;
  rep (i, N) if (ans[i]) res.pb(i);
  printf("!");
  rep (i, res.size()) {
    if (i) putchar(' ');
    printf("%d", res[i] + 1);
  }
  puts("");
  return;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  solve(n, k);
}
