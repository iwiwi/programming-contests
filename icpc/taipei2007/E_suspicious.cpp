#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <cstring>
#include <climits>
#include <sstream>
#include <stack>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second

#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

ll X1[30], Y1[30], X2[30], Y2[30];

ll pot[900][210][4][2];

inline ll ABS(ll x) {
  if (x < 0) return -x;
  else return x;
}

void chkmax(ll &a, ll b) {
  a = max(a, b);
}

int main() {
  int C;
  cin >> C;

  while (C--) {
    ll T;
    int E;
    cin >> T >> E;

    rep (i, E) cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];

    vector<pii> P;
    map<pii, map<int, pii> > adj;

    rep (i, E) {
      if (X1[i] != X2[i]) {
        vector<pii> ps;
        rep (j, E) {
          if (Y1[j] == Y2[j]) continue;

          if ((X1[i] - X1[j]) * (X2[i] - X1[j]) <= 0 &&
              (Y1[j] - Y1[i]) * (Y2[j] - Y1[i]) <= 0) {
            P.pb(mp(X1[j], Y1[i]));
            ps.pb(mp(X1[j], Y1[i]));
          }
        }
        sort(ps.begin(), ps.end()); ps.erase(unique(ps.begin(), ps.end()), ps.end());

        int n = ps.size();
        rep (i, n) {
          if (i - 1 >= 0) adj[ps[i]][2] = ps[i - 1];
          if (i + 1 <  n) adj[ps[i]][0] = ps[i + 1];
        }
      } else {
        vector<pii> ps;
        rep (j, E) {
          if (X1[j] == X2[j]) continue;

          if ((Y1[i] - Y1[j]) * (Y2[i] - Y1[j]) <= 0 &&
              (X1[j] - X1[i]) * (X2[j] - X1[i]) <= 0) {
            P.pb(mp(X1[i], Y1[j]));
            ps.pb(mp(X1[i], Y1[j]));
          }
        }
        sort(ps.begin(), ps.end()); ps.erase(unique(ps.begin(), ps.end()), ps.end());

        int n = ps.size();
        rep (i, n) {
          if (i - 1 >= 0) adj[ps[i]][3] = ps[i - 1];
          if (i + 1 <  n) adj[ps[i]][1] = ps[i + 1];
        }
      }
    }
    sort(P.begin(), P.end());
    P.erase(unique(P.begin(), P.end()), P.end());

    int N = P.size();
    map<pii, int> pid;
    rep (i, N) pid[P[i]] = i;

    int adj2[210][4];
    rep (i, N) {
      rep (j, 4) adj2[i][j] = -1;
      tr (adj[P[i]], ite) adj2[i][ite->first] = pid[ite->second];

      // printf("(%lld, %lld):\n", P[i].F, P[i].S);
      // rep (j, 4) {
      //   if (adj2[i][j] == -1) puts(" -1");
      //   else printf(" (%lld, %lld)\n", P[adj2[i][j]].F, P[adj2[i][j]].S);
      // }
    }

    vector<int> adj3[210][4];
    rep (i, N) {
      rep (d, 4) {
        int v = adj2[i][d];
        while (v != -1) {
          adj3[i][d].pb(v);
          v = adj2[v][d];
        }
      }
    }

    int M = N * 4 + 10;
    ll ans = 0;

    rep (si, N) {
      rep (sd, 4) {
        rep (k, M) rep (i, N) rep (d, 4) rep (b, 2) pot[k][i][d][b] = -(ll(1) << 60);
        pot[0][si][sd][true] = 0;

        rep (k, M) {
          if (k > 0) {
            rep (i, N) rep (d, 4) {
              for (int dd = -1; dd <= 1; ++dd) {
                chkmax(pot[k][i][(d + dd + 4) % 4][true], pot[k - 1][i][d][false]);
              }
            }
            // printf(" %d, (%lld, %lld), %d: %lld\n", k, P[si].F, P[si].S, sd, pot[k][si][sd][true]);
          }

          rep (i, N) rep (d, 4) rep (j, adj3[i][d].size()) {
            int t = adj3[i][d][j];
            chkmax(pot[k][t][d][false], pot[k][i][d][true] + ABS(P[t].F - P[i].F) + ABS(P[t].S - P[i].S));
          }
        }

        // only normal loop
        for (int k = 1; k < M; ++k) {
          ll len = pot[k][si][sd][true];
          if (len < 0) continue;
          ans = max(ans, len * (T / k));
        }
      }
    }

    cout << ans << endl;
  }

  return 0;
}
