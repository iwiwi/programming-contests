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
vector<int> adj[100010];

bool prv[100010];
bool nxt[100010];

int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    rep (v, N) adj[v].clear();
    rep (i, M) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a;
      --b;
      adj[a].pb(b);
    }

    char S[310];
    scanf("%s", S);
    int L = strlen(S);
    reverse(S, S + L);
    vector<bool> enm;
    for (int i = 0; i < L; ) {
      if (S[i] == '"') {
        enm.pb(false);
        i += 1;
      } else if (S[i] == 'w') {
        enm.pb(true);
        if (S[i + 1] == 'w') {
          i += 3;
        } else {
          break; // end with w
        }
      } else {
        enm.pb(false);
        break; // end without w
      }
    }
    reverse(all(enm));

    reverse(S, S + L);
    rep (i, L) if (!isdigit(S[i])) S[i] = ' ';
    int src;
    sscanf(S, "%d", &src);
    --src;

    // printf("src = %d\n", src);
    // rep (i, enm.size()) printf("%d ", (int)enm[i]); puts("");

    memset(prv, 0, sizeof(prv));
    prv[src] = true;

    rep (iter, enm.size()) {
      memset(nxt, 0, sizeof(nxt));
      if (enm[iter]) {
        rep (v, N) rep (i, adj[v].size()) nxt[v] |= prv[adj[v][i]];
      } else {
        int act = count(prv, prv + N, true);
        rep (v, N) {
          int c = 0;
          rep (i, adj[v].size()) c += prv[adj[v][i]];
          nxt[v] = (c < act);
        }
      }
      memcpy(prv, nxt, sizeof(prv));
    }

    printf("%d\n", (int)count(prv, prv + N, true));
  }

  return 0;
}

