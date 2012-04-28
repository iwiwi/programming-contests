#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back
void chkmin(int &a, int b) { a = min(a, b); }

typedef long long ll;

int ncp, nroad, ncm, confdist, startisect, endisect, startdir;
pair<int, int> eid[200][2];

bool is_cho[110];
vector<pair<int, int> > tov[110];
vector<int> dir[110], len[110];
vector<int> cnf[110];
vector<int> rid[110];

vector<int> route;

int crr_v, crr_d;
int cho_v, cho_d;
vector<bool> cho_usd;
int hound_dist;

int inv(int d) { return (d + 180) % 360; }

void back() {
  do {
    rep (i, tov[crr_v].size()) {
      if (rid[crr_v][i] == route.back()) {
        pair<int, int> p = tov[crr_v][i];
        hound_dist += len[crr_v][i];
        // printf(" back (%d) %d\n", route.back(), len[crr_v][i]);
        crr_v = p.first;
        crr_d = p.second;
        route.pop_back();
        goto found;
      }
    }
    assert(false);
  found:;
  } while (!is_cho[crr_v]);
  cho_d = 0;
}

bool is_right(int cd, int nd) {
  while (nd < cd) nd += 360;
  if (nd < cd + 180) return true;
  else return false;
}

int main() {
  for (int ca = 1; ; ++ca) {
    cin >> ncp >> nroad >> ncm >> confdist >> startisect >> endisect >> startdir;
    if (!(ncp | nroad | ncm | confdist | startisect | endisect | startdir)) return 0;

    for (int v = 1; v <= 100; ++v) {
      is_cho[v] = false;
      tov[v].clear();
      dir[v].clear();
      len[v].clear();
    }

    rep (i, ncp) { int v; cin >> v; is_cho[v] = true; }
    rep (i, nroad) {
      int v, w, vd, wd, l;
      cin >> v >> w >> vd >> wd >> l;
      eid[i][0] = mp(v, tov[v].size());
      eid[i][1] = mp(w, tov[w].size());
      tov[v].pb(mp(w, inv(wd))); dir[v].pb(vd); len[v].pb(l); cnf[v].pb(INT_MAX); rid[v].pb(i);
      tov[w].pb(mp(v, inv(vd))); dir[w].pb(wd); len[w].pb(l); cnf[w].pb(INT_MAX); rid[w].pb(i);
    }
    rep (i, ncm) {
      int v, e, d;
      cin >> v >> e >> d;
      --e;
      pair<int, int> p0 = eid[e][0], p1 = eid[e][1];
      chkmin(cnf[p0.first][p0.second], d);
      chkmin(cnf[p1.first][p1.second], d);
    }

    // |crr_v| ni ite, |crr_d| wo muiteiru
    crr_v = startisect;
    crr_d = startdir;

    cho_v = -1;
    cho_d = 0;
    cho_usd.clear();

    route.clear();
    hound_dist = 0;

    for (int turn = 0; ; ++turn) {
      // printf("%d %d (%d)\n", crr_v, crr_d, hound_dist);
      // printf(" route: ");
      // rep (i, route.size()) printf("%d ", route[i]);
      // puts("");

      if (crr_v == endisect) break;

      if (is_cho[crr_v]) {
        if (cho_v != -1) {
          // back();
        } else {
          cho_v = crr_v;
          cho_d = 0;
          cho_usd = vector<bool>(tov[crr_v].size());
        }
      }

      if (turn > 0 && tov[crr_v].size() == 1) {
        back();
      }

      // Choose next!
      vector<bool> tmp_usd;
      if (is_cho[crr_v]) tmp_usd = cho_usd;
      else {
        tmp_usd.resize(tov[crr_v].size());
        rep (i, tov[crr_v].size()) if (dir[crr_v][i] == inv(crr_d)) tmp_usd[i] = true;
      }

      int nxt_i = -1;
      pair<int, int> nxt_d = mp(INT_MAX, true);
      rep (i, tov[crr_v].size()) {
        if (tmp_usd[i]) continue;
        pair<int, int> d = mp(abs(dir[crr_v][i] - crr_d), is_right(crr_d, dir[crr_v][i]) ? -1 : 1);
        // printf(" nxt? %d: %d %d\n", tov[crr_v][i].first, d.first, d.second);
        if (d < nxt_d) {
          nxt_d = d;
          nxt_i = i;
        }
      }
      assert(nxt_i != -1);
      if (is_cho[crr_v]) cho_usd[nxt_i] = true;

      // printf("poyo len=%d\n", hound_dist);

      // confirmatino point?
      if (cho_v != -1 && confdist < cho_d + min(len[crr_v][nxt_i], cnf[crr_v][nxt_i])) {
        // TOO FAR FROM CHOOSEPOINT!!!
        // puts("far");
        // printf("puyo len=%d\n", hound_dist);
        hound_dist += (confdist - cho_d) * 2;
        // printf("puyo len=%d\n", hound_dist);
        if (is_cho[crr_v]) crr_d = inv(dir[crr_v][nxt_i]);
        else back();
      }
      else {
        if (cho_v != -1 && cnf[crr_v][nxt_i] < INT_MAX) {
          // conguratulation!!! confirmation!!!
          cho_v = -1;
        }
        route.pb(rid[crr_v][nxt_i]);
        pair<int, int> p = tov[crr_v][nxt_i];

        // printf("len=%d\n", hound_dist);
        hound_dist += len[crr_v][nxt_i];
        if (cho_v != -1) cho_d += len[crr_v][nxt_i];
        // printf("len=%d\n", hound_dist);
        crr_v = p.first;
        crr_d = p.second;

        if (cho_v != -1 && is_cho[crr_v]) {
          back();
        }
      }
    }

    printf("Case %d:\n", ca);
    int hare_dist = 0;
    rep (i, route.size()) {
      pair<int, int> p = eid[route[i]][0];
      hare_dist += len[p.first][p.second];
    }
    printf("   Length of hare's route is %d\n", hare_dist);
    printf("   Length of hound's search is %d\n", hound_dist);
    printf("   Route:");
    rep (i, route.size()) printf(" %d", route[i] + 1);
    puts("");
    puts("");
  }
}
