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

int N, M;
vector<int> adj[40];

int cc_size, best, ans;

int deg[40], val[40], det[40][2];
int crr, rem;

void search(int k) {
  if (crr + rem < best) return;

  if (k == cc_size) {
    if (crr < best) return;

    if (crr > best) {
      best = crr;
      ans = 0;
    }
    ++ans;
    return;
  }

  // Find the best target to branch
  int tv = -1, ts = -1000000;
  rep (v, N) {
    if (val[v] != -1) continue;
    int s = max(det[v][0], det[v][1]) * 2 > deg[v] ? 1000000 : -(deg[v] - (det[v][0] + det[v][1]));

    if (s > ts) {
      tv = v;
      ts = s;
    }
  }
  int v = tv;

  // Determine the order of colors to branch
  int cs[2];
  if (det[v][0] < det[v][1]) { cs[0] = 0; cs[1] = 1; }
  else                       { cs[0] = 1; cs[1] = 0; }

  rep (ci, 2) {
    int c = cs[ci];
    if (det[v][c] * 2 > deg[v]) continue;  // Prune

    val[v] = c;
    for (int w : adj[v]) {
      ++det[w][c];
      if (val[w] != -1) {
        crr += !!(val[v] != val[w]);
        --rem;
      }
    }

    search(k + 1);

    for (int w : adj[v]) {
      --det[w][c];
      if (val[w] != -1) {
        crr -= !!(val[v] != val[w]);
        ++rem;
      }
    }
    val[v] = -1;
  }
}

int main() {
  for (string S; cin >> S; ) {
    map<char, int> ma;
    rep (i, S.length()) if (isalpha(S[i])) ma[S[i]] = 0;
    N = 0;
    for (auto &i : ma) i.second = N++;
    rep (v, N) adj[v].clear();

    M = 0;
    for (int i = 0; i < (int)S.length(); i += 4) {
      int a = ma[S[i]];
      int b = ma[S[i + 2]];
      if (a == b) continue;
      adj[a].emplace_back(b);
      adj[b].emplace_back(a);
      ++M;
    }

    // Connected component decomposition
    int total_ans = 1;

    vector<bool> done(N);
    rep (s, N) {
      if (done[s]) continue;
      vector<int> cc;

      queue<int> que;
      que.push(s);
      done[s] = true;
      while (!que.empty()) {
        int x = que.front();
        que.pop();
        cc.push_back(x);

        for (int w : adj[x]) {
          if (done[w]) continue;
          que.push(w);
          done[w] = true;
        }
      }
      // fprintf(stderr, " %d\n", (int)cc.size());

      // Solve this CC
      sort(all(cc));
      cc_size = cc.size();

      rep (v, N) {
        val[v] = binary_search(all(cc), v) ? -1 : -2;  // only vertices in this CC
        deg[v] = adj[v].size();
        det[v][0] = det[v][1] = 0;
      }
      best = ans = 0;

      crr = 0;
      rem = M;
      search(0);

      total_ans *= ans;
      // fprintf(stderr, " CC: %d\n", ans);
    }


    printf("%d\n", total_ans);
  }

  return 0;
}
