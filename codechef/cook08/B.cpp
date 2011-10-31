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

int N, M, K;
pair<int, int> ord[10010];

vector<int> adj[10010];

vector<int> crr;
int cnt[10010];

void search(int i) {
  if (i == N) {
    vector<int> tmp = crr;
    sort(all(tmp));
    rep (i, tmp.size()) {
      if (i) putchar(' ');
      printf("%d", tmp[i]);
    }
    puts("");
    if (--K == 0) throw 0;
    return;
  }

  int v = ord[i].second;
  if (cnt[v] == (int)crr.size()) {
    crr.push_back(v);
    rep (j, adj[v].size()) ++cnt[adj[v][j]];

    search(i + 1);
    crr.pop_back();
    rep (j, adj[v].size()) --cnt[adj[v][j]];
  }

  search(i + 1);
}


int main() {
  int cases;
  scanf("%d", &cases);
  rep (ca, cases) {
    scanf("%d%d%d", &N, &M, &K);

    rep (i, N) {
      scanf("%d", &ord[i].first);
      ord[i].second = i;
    }
    sort(ord, ord + N);
    reverse(ord, ord + N);

    rep (i, N) adj[i].clear();
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      adj[a].pb(b);
      adj[b].pb(a);
    }

    try {
      crr.clear();
      memset(cnt, 0, sizeof(cnt));
      search(0);
    } catch (...) {}
    puts("");
  }

  return 0;
}

