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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

void count_buckets(const int *s, int n, int k, bool end, int *b) {
  for (int i = 0; i <= k; ++i) b[i] = 0;
  for (int i = 0; i < n; ++i) ++b[s[i]];
  int c = 0;
  for (int i = 0; i <= k; ++i) {
    c += b[i];
    b[i] = end ? c : c - b[i];
  }
}

void induce_sa(const int *s, int n, int k, const bool *t, int *sa, int *b) {
  // Induce L-type suffixes
  count_buckets(s, n, k, false, b);
  for (int i = 0; i < n; ++i) {
    int j = sa[i] - 1;
    if (j >= 0 && !t[j]) sa[b[s[j]]++] = j;
  }
  // Induce S-type suffixes
  count_buckets(s, n, k, true, b);
  for (int i = n - 1; i >= 0; --i) {
    int j = sa[i] - 1;
    if (j >= 0 && t[j]) sa[--b[s[j]]] = j;
  }
}

bool is_lms(int i, const bool *t) {
  return i > 0 && t[i] && !t[i - 1];
}

void construct_sa(const int *s, int n, int k, int *sa) {
  bool *t = new bool[n];
  t[n - 1] = true;
  t[n - 2] = false;
  for (int i = n - 3; i >= 0; --i) {
    t[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && t[i + 1]);
  }

  // Stage 1: Sort the LMS-substrings & generate the sub-problem
  int *b = new int[k + 10];
  count_buckets(s, n, k, true, b);
  for (int i = 0; i < n; ++i) sa[i] = -1;
  for (int i = 1; i < n; ++i) if (is_lms(i, t)) sa[--b[s[i]]] = i;
  induce_sa(s, n, k, t, sa, b);

  int n1 = 0;
  for (int i = 0; i < n; ++i) if (is_lms(sa[i], t)) sa[n1++] = sa[i];
  for (int i = n1; i < n; ++i) sa[i] = -1;
  int k1 = 0, prv = -1;
  for (int i = 0; i < n1; ++i) {
    int crr = sa[i];
    for (int j = 0; ; ++j) {
      if (prv == -1 || s[crr + j] != s[prv + j] || t[crr + j] != t[prv + j]) {
        ++k1;
        break;
      }
      else if (j > 0 && (is_lms(crr + j, t) || is_lms(prv + j, t))) break;
    }
    sa[n1 + crr / 2] = k1 - 1;
    prv = crr;
  }
  for (int i = n - 1, j = n - 1; i >= n1; --i) {
    if (sa[i] >= 0) sa[j--] = sa[i];
  }

  // Stage 2: Recurse and solve the sub-problem
  int *sa1 = sa, *s1 = sa + n - n1;
  if (k1 < n1) {
    construct_sa(s1, n1, k1, sa1);
  } else {
    for (int i = 0; i < n1; ++i) sa1[s1[i]] = i;
  }

  // Stage 3: Induced-sort and construct the SA
  count_buckets(s, n, k, true, b);
  for (int i = 1, j = 0; i < n; ++i) {
    if (is_lms(i, t)) s1[j++] = i;
  }
  for (int i = 0; i < n1; ++i) sa[i] = s1[sa1[i]];
  for (int i = n1; i < n; ++i) sa[i] = -1;
  for (int i = n1 - 1; i >= 0; --i) {
    int j = sa[i];
    sa[i] = -1;
    sa[--b[s[j]]] = j;
  }
  induce_sa(s, n, k, t, sa, b);

  delete [] t;
  delete [] b;
}

void construct_sa(const unsigned char *s, int *sa) {
  int n = strlen((const char*)s);
  int *si = new int[n + 1];
  for (int i = 0; i <= n; ++i) si[i] = s[i];
  construct_sa(si, n + 1, 255, sa);
}

const int MAX_N = 200010;

int g[MAX_N], b[MAX_N];

void construct_lcp(const char *s, int n, int *sa, int *lcp) {
  int h = 0;
  for (int i = 0; i <= n; i++) b[sa[i]] = i;
  for (int i = 0; i <= n; i++) {
    if (b[i]) {
      for (int j = sa[b[i] - 1]; j + h < n && i + h < n && s[j + h] == s[i + h]; h++);
      lcp[b[i]] = h;
    }
    else lcp[b[i]] = -1;
    if (h > 0) h--;
  }
}


int sa[200010], lcp[200010];

ll solve(const char *S, int X) {
  int L = strlen(S);

  memset(lcp, 0, sizeof(lcp));
  construct_sa((const unsigned char*)S, sa);
  construct_lcp(S, L, sa, lcp);

  ll ans = 0;
  for (int i = 1; i <= L; ++i) {
    int p = sa[i];
    int l = lcp[i];
    // printf("%s %d\n", S + p, l);

    if (p < X) ans += (X - p) - l;
    if (p > X) ans += (L - p) - l;
  }
  return ans;
}

int main() {
  string A, B;
  while (cin >> A >> B) {
    int al = A.length(), bl = B.length();
    ll a = solve((A + "$").c_str(), al);
    ll b = solve((B + "$").c_str(), bl);
    ll c = solve((A + "$" + B).c_str(), al);
    ll d = a + b - c;
    // printf(" %lld %lld %lld\n", a, b, c);
    cout << c - d << endl;
  }

  return 0;
}

