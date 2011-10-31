#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define iter(c) __typeof((c).begin())


const int MAX_N = 200100;

struct sa_comp {
  int h, *g;
  sa_comp(int h_, int *g_) : h(h_), g(g_) {}
  bool operator() (int a, int b) {
    return a == b ? false : g[a] != g[b] ? g[a] < g[b] : g[a + h] < g[b + h];
  }
};

int g[MAX_N], b[MAX_N];

void construct_sa(const char *s, int n, int *sa) {
  for (int i = 0; i <= n; ++i) {
    sa[i] = i;
    g[i] = s[i];
  }
  b[0] = b[n] = 0;
  sort(sa, sa + n + 1, sa_comp(0, g));
  for (int h = 1; b[n] != n; h *= 2) {
    sa_comp cmp(h, g);
    sort(sa, sa + n + 1, cmp);
    for (int i = 0; i < n; ++i) b[i + 1] = b[i] + cmp(sa[i], sa[i + 1]);
    for (int i = 0; i <= n; ++i) g[sa[i]] = b[i];
  }
}

void construct_lcp(const char *s, int n, int *sa, int *lcp) {
  int h = 0;
  for (int i = 0; i <= n; ++i) b[sa[i]] = i;
  for (int i = 0; i <= n; ++i) {
    if (b[i]) {
      for (int j = sa[b[i] - 1]; j + h < n && i + h < n && s[j + h] == s[i + h]; h++);
      lcp[b[i]] = h;
    }
    else lcp[b[i]] = 0;
    if (h > 0) h--;
  }
}

void manacher(const char *text, int n, int *rad) {
  int i, j, k;
  for (i = 0, j = 0; i < 2 * n; i += k, j = max(j - k, 0)) {
    while (i-j >= 0 && i+j+1 < 2*n && text[(i-j)/2] == text[(i+j+1)/2]) ++j;
    rad[i] = j;
    for (k = 1; i-k >= 0 && rad[i]-k >= 0 && rad[i-k] != rad[i]-k; ++k) {
      rad[i+k] = min(rad[i-k], rad[i]-k);
    }
  }
}

typedef long long ll;

ll sum(int i, ll *bit) {
  ll s = 0;
  for (; i > 0; i -= i & -i) s += bit[i];
  return s;
}
void add(int i, ll v, ll *bit, int n) {
  for (; i <= n; i += i & -i) bit[i] += v;
}




int N;
int sa[MAX_N], lcp[MAX_N];
int srad[MAX_N], trad[MAX_N];

ll sobit0[MAX_N], sobit1[MAX_N], sebit0[MAX_N], sebit1[MAX_N];
ll tobit0[MAX_N], tobit1[MAX_N], tebit0[MAX_N], tebit1[MAX_N];

void update(int h, ll v, map<int, int> &ma, ll *bit0, ll *bit1) {
  if (h == 0) return;
  ma[h] += v;
  add(h, v,     bit0, N);
  add(h, v * h, bit1, N);
}

void truncate(int th, map<int, int> &ma, ll *bit0, ll *bit1) {
  map<int, int>::iterator ite;
  while ((ite = ma.upper_bound(th)) != ma.end()) {
    int h = ite->first;
    int c = ite->second;
    update( h, -c, ma, bit0, bit1);
    update(th, +c, ma, bit0, bit1);
    ma.erase(ite);
  }
}

ll calc(int ra, ll *bit0, ll *bit1) {
  ll a = sum(ra, bit1);
  ll b = ra * (sum(N, bit0) - sum(ra, bit0));
  // printf("(%lld + %lld) ", a, b);
  return a + b;
}



ll solve(string S, string T) {
  string x = S + '$' + T;
  construct_sa(x.c_str(), x.length(), sa);
  construct_lcp(x.c_str(), x.length(), sa, lcp);

  manacher(S.c_str(), S.length(), srad);
  manacher(T.c_str(), T.length(), trad);

  N = x.length();  // enough...

  map<int, int> soma, sema, toma, tema;
  memset(sobit0, 0, sizeof(sobit0)); memset(sobit1, 0, sizeof(sobit1));
  memset(sebit0, 0, sizeof(sebit0)); memset(sebit1, 0, sizeof(sebit1));
  memset(tobit0, 0, sizeof(tobit0)); memset(tobit1, 0, sizeof(tobit1));
  memset(tebit0, 0, sizeof(tebit0)); memset(tebit1, 0, sizeof(tebit1));

  ll ans = 0;

  for (int i = 0; i <= x.length(); ++i) {
    int k = sa[i];

    truncate(lcp[i], soma, sobit0, sobit1); truncate(lcp[i], sema, sebit0, sebit1);
    truncate(lcp[i], toma, tobit0, tobit1); truncate(lcp[i], tema, tebit0, tebit1);

    if (x[k] == '$') continue;
    else if (k < (int)S.length()) {
      int p = k;
      int ora = (srad[p * 2] + 1) / 2;
      int era = p == 0 ? 0 : srad[p * 2 - 1] / 2;

      ans += calc(ora, tobit0, tobit1);
      ans += calc(era, tebit0, tebit1);

      update(ora, 1, soma, sobit0, sobit1);
      update(era, 1, sema, sebit0, sebit1);

      // printf("S %2d %2d (%d, %d) %s\t:", sa[i], lcp[i], ora, era, x.c_str() + sa[i]);
      // printf(" [%lld, %lld]\n", calc(ora, tobit0, tobit1), calc(era, tebit0, tebit1));
    }
    else {
      int p = k - (int)S.length() - 1;
      int ora = (trad[p * 2] + 1) / 2;
      int era = p == 0 ? 0 : trad[p * 2 - 1] / 2;

      ans += calc(ora, sobit0, sobit1);
      ans += calc(era, sebit0, sebit1);

      update(ora, 1, toma, tobit0, tobit1);
      update(era, 1, tema, tebit0, tebit1);
      // printf("T %2d %2d (%d, %d) %s\t:", sa[i], lcp[i], ora, era, x.c_str() + sa[i]);
      // printf(" [%lld, %lld]\n", calc(ora, sobit0, sobit1), calc(era, sebit0, sebit1));
    }
  }

  // printf("hoge: %lld\n", ans);
  return ans;
}


ll naive(string S, string T) {
  ll ans = 0;
  for (int i = 0; i < S.length(); ++i) {
    for (int j = i + 1; j <= S.length(); ++j) {
      for (int k = 0; k < T.length(); ++k) {
        for (int l = k + 1; l <= T.length(); ++l) {
          string s = S.substr(i, j - i);
          string t = T.substr(k, l - k);
          if (s != t) continue;
          reverse(t.begin(), t.end());
          if (s != t) continue;
          ++ans;
        }
      }
    }
  }
  return ans;
}


int main() {
  while (false) {
    int slen = 1 + rand() % 5;
    int tlen = 1 + rand() % 5;
    string S, T;
    rep (i, slen) S += char('A' + rand() % 26);
    rep (i, tlen) T += char('A' + rand() % 26);

    if (solve(S, T) != naive(S, T)) {
      cout << S << endl;
      cout << T << endl;
      cout << "Correct: " << naive(S, T) << endl;
      cout << "Output : " << solve(S, T) << endl;
    }
  }

  string S, T;
  while (cin >> S >> T) {
    ll ans = solve(S, T);
    cout << ans << endl;
    // cout << "Naive: " << naive(S, T) << endl;
  }

  return 0;
}
