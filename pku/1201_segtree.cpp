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

const int MAX_N = 100000;

int n;
bool flg[4 * MAX_N];
int sum[4 * MAX_N];

void init(int n_) {
  for (n = 1; n < n_; n *= 2);
  memset(flg, 0, sizeof(flg));
  memset(sum, 0, sizeof(sum));
}

int query_sum(int a, int b, int k = 0, int l = 0, int r = 0) { // [a, b)
  if (k == 0) r = n;
  if (r <= a || b <= l) return 0;
  if (a <= l && r <= b) return sum[k];
  else {
    int vl = query_sum(a, b, k * 2 + 1, l, (l + r) / 2);
    int vr = query_sum(a, b, k * 2 + 2, (l + r) / 2, r);
    return vl + vr;
  }
}

// returns sum of [l, r) (not to be confused with [a, b))
int query_add(int a, int b, int &v, int k = 0, int l = 0, int r = 0) { // [a, b) += v (right-most places)
  if (k == 0) r = n;
  if (r <= a || b <= l) return sum[k];
  if (a <= l && r <= b && (v == 0 || flg[k])) return sum[k];

  if (r - l == 1) {
    flg[k] = true;
    --v;
    return sum[k] = 1;
  }
  else {
    int vr = query_add(a, b, v, k * 2 + 2, (l + r) / 2, r);
    int vl = query_add(a, b, v, k * 2 + 1, l, (l + r) / 2);
    sum[k] = vl + vr;
    flg[k] = (sum[k] == r - l);
    return sum[k];
  }
}

int N;
pair<int, pair<int, int> > A[50010];

int main() {
  scanf("%d", &N);
  rep (i, N) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    ++b;
    A[i] = mp(b, mp(a, c));
  }
  sort(A, A + N);

  init(50010);
  rep (i, N) {
    int a = A[i].second.first;
    int b = A[i].first;
    int c = A[i].second.second;

    int s = query_sum(a, b);
    // printf("[%d, %d): %d : %d\n", a, b, c, s);
    if (s < c) {
      int v = c - s;
      query_add(a, b, v);
    }
  }

  printf("%d\n", query_sum(0, 50010));

  return 0;
}
