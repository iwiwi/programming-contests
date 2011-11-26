#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back

int N, transit_time, start_v, goal_v;
int A[50010];
vector<int> S[50010], T[50010];
map<string, int> name2id;

int readid() {
  char buf[256];
  scanf("%s", buf);
  string name(buf);

  if (name2id.count(name)) return name2id[name];
  else {
    int id = name2id.size();
    return name2id[name] = id;
  }
}

typedef pair<int, int> pii;
typedef pair<pair<int, int>, bool> ppiib;

vector<ppiib> v2stat[100010];
bool vis[100010];

int main() {
  // input
  scanf("%d%d", &N, &transit_time);
  start_v = readid();
  goal_v = readid();
  rep (k, N) {
    scanf("%d", A + k);
    S[k].resize(A[k]);
    T[k].resize(A[k] - 1);
    rep (p, A[k]) S[k][p] = readid();
    rep (p, A[k] - 1) scanf("%d", &T[k][p]);
  }

  // v2stat
  rep (k, N) {
    rep (p, A[k]) {
      int v = S[k][p];
      v2stat[v].pb(mp(mp(k, p), false));
      v2stat[v].pb(mp(mp(k, p), true));
    }
  }

  // initialize
  multimap<pii, ppiib> que;
  map<ppiib, pii> mem;
  rep (i, v2stat[start_v].size()) {
    const ppiib &kpr = v2stat[start_v][i];
    que.insert(mp(mp(0, 0), kpr));
    mem[kpr] = mp(0, 0);
  }

  while (!que.empty()) {
    pii c = que.begin()->first;                // cost
    int k = que.begin()->second.first.first;   // rosen
    int p = que.begin()->second.first.second;  // pos
    bool r = que.begin()->second.second;       // reverse
    que.erase(que.begin());
    if (c > mem[mp(mp(k, p), r)]) continue;

    // printf("%d %d %d\n", k, p, r);

    int v = S[k][p];
    if (v == goal_v) {
      printf("%d %d\n", c.first, c.second);
      return 0;
    }

    // continue
    int tp = p + (r ? 1 : -1);
    if (0 <= tp && tp < A[k]) {
      pii tc = mp(c.first + (r ? T[k][p] : T[k][p - 1]), c.second);
      ppiib tkpr = mp(mp(k, tp), r);
      if (mem.count(tkpr) == 0 || tc < mem[tkpr]) {
        mem[tkpr] = tc;
        que.insert(mp(tc, tkpr));
      }
    }

    // transit
    if (!vis[v]) {
      vis[v] = true;
      pii tc = mp(c.first + transit_time, c.second + 1);
      rep (i, v2stat[v].size()) {
        const ppiib &tkpr = v2stat[v][i];
        if (mem.count(tkpr) == 0 || tc < mem[tkpr]) {
          mem[tkpr] = tc;
          que.insert(mp(tc, tkpr));
        }
      }
    }
 }

  puts("-1");
  return 0;
}
