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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define eb(...) emplace_back(__VA_ARGS__)
#define mp(a, b) make_pair(a, b)

typedef bitset<70010> bs_t;
const size_t T = 70000 / 4 + 10;

int N, S;
int A[70010];

bs_t do_dp_1(const vector<int> &items) {
  bs_t b;
  b[0] = true;
  rep (i, items.size()) b |= b << A[items[i]];
  return b;
}

vector<int> do_dp_2(const vector<int> &items, int x) {
  int n = items.size();
  static bs_t dp[T + 10];

  dp[0].reset();
  dp[0][0] = true;
  rep (i, n) {
    dp[i + 1] = dp[i];
    dp[i + 1] |= dp[i] << A[items[i]];
  }
  if (x < 0 || dp[n][x] == 0) throw "impossible";

  vector<int> ans;
  for (int i = n - 1; i >= 0; --i) {
    int a = A[items[i]];
    if (x >= a && dp[i][x - a]) {
      ans.eb(items[i]);
      x -= a;
    }
  }
  return ans;
}

vector<int> do_dp_rec(const vector<int> &items, int x) {
  if (items.size() <= T) {
    return do_dp_2(items, x);
  } else {
    int n = items.size();
    vector<int> items1(items.begin(), items.begin() + n / 2);
    vector<int> items2(items.begin() + n / 2, items.end());
    bs_t bs1 = do_dp_1(items1);
    bs_t bs2 = do_dp_1(items2);

    for (int x1 = 0; x1 <= x; ++x1) {
      int x2 = x - x1;
      if (bs1[x1] && bs2[x2]) {
        vector<int> ans1 = do_dp_rec(items1, x1);
        vector<int> ans2 = do_dp_rec(items2, x2);
        ans1.insert(ans1.end(), all(ans2));
        return ans1;
      }
    }
    throw "impossible";
  }
}

int main() {
  while (2 == scanf("%d%d", &N, &S)) {
    rep (i, N) scanf("%d", &A[i]);

    int max_root_i = max_element(A, A + N) - A;
    vector<int> items;
    rep (i, N) if (i != max_root_i) items.eb(i);

    vector<int> roots;
    try {
      roots = do_dp_rec(items, S - A[max_root_i]);
    } catch (...) {
      puts("-1");
      continue;
    }
    vector<bool> is_root(N);
    rep (i, roots.size()) is_root[roots[i]] = true;
    is_root[max_root_i] = true;

    vector<pair<int, int> > ins;
    rep (i, N) if (!is_root[i]) ins.eb(A[i], i);
    ins.eb(A[max_root_i], max_root_i);
    sort(all(ins));
    vector<int> chs(N, -1);
    rep (i, ins.size() - 1) chs[ins[i + 1].second] = ins[i].second;

    rep (i, N) {
      int c = chs[i];
      if (c == -1) printf("%d 0\n", A[i]);
      else printf("%d %d %d\n", A[i] - A[c], 1, c + 1);
    }
  }
}
