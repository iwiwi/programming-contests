#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back

typedef long long ll;

const int A = 26;

int N, M;
string S[20];

int P;
vector<string> pfx;
int nxt[110][30];
int end[110];
ll mem[30][110][(1 << 10) + 10];

ll search(int k, int p, int b) {
  b |= end[p];
  // if (k == N) printf("end %d = %d\n", p, b);
  if (k == N) return b == (1 << M) - 1 ? 1 : 0;
  if (mem[k][p][b] != -1) return mem[k][p][b];

  ll res = 0;
  rep (a, A) res += search(k + 1, nxt[p][a], b);
  return mem[k][p][b] = res;
}

vector<string> ans;
string crr;

void restore(int k, int p, int b) {
  b |= end[p];

  if (k == N) {
    if (b == (1 << M) - 1) ans.pb(crr);
    return;
  }
  
  if (mem[k][p][b] == 0) return;
  
  rep (a, A) {
    crr[k] = 'a' + a;
    restore(k + 1, nxt[p][a], b);
  }
}

int main() {
  for (int ca = 1; ; ++ca) {
    cin >> N >> M;
    if (N == 0 && M == 0) return 0;
    rep (i, M) cin >> S[i];

    pfx.clear();
    pfx.pb(string(""));
    rep (i, M) rep (j, S[i].length() + 1) pfx.pb(S[i].substr(0, j));
    sort(pfx.begin(), pfx.end());
    pfx.erase(unique(pfx.begin(), pfx.end()), pfx.end());
    P = pfx.size();

    memset(end, 0, sizeof(end));
    rep (i, P) {
      rep (a, A) {
        string s = pfx[i] + char('a' + a);
        while (!binary_search(pfx.begin(), pfx.end(), s)) {
          s = s.substr(1);
        }
        nxt[i][a] = find(pfx.begin(), pfx.end(), s) - pfx.begin();
      }
      const string &p = pfx[i];
      rep (j, M) {
        const string &q = S[j];
        if (q.length() <= p.length() && 
            p.compare(p.length() - q.length(), q.length(), q) == 0) {
          end[i] |= 1 << j;
        }
      }
      // printf("%s: %d\n", p.c_str(), end[i]);
    }    

    memset(mem, -1, sizeof(mem));
    ll res = search(0, 0, 0);
    printf("Case %d: %lld suspects\n", ca, res);
    if (res <= 42) {
      ans.clear();
      crr = string(N, '-');
      restore(0, 0, 0);
      sort(ans.begin(), ans.end());
      rep (i, ans.size()) printf("%s\n", ans[i].c_str());
    }
  }
}
