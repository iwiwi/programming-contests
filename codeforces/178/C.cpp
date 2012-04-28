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

typedef long long ll;

int H, M, N;
int G, group[1000010];
int grnk[1000010], gsiz[1000010];
int ginv[1000010];  // rnk -> h

map<int, int> hsh;
map<int, int> pos;

vector<set<int> > fre;

int main() {
  while (3 == scanf("%d%d%d", &H, &M, &N)) {
    memset(group, -1, sizeof(group));
    G = 0;
    rep (i, H) if (group[i] == -1) {
      int t = i, r = 0;
      do {
        group[t] = G;
        grnk[t] = r;
        ginv[r] = t;
        ++r;
        t = (t + M) % H;
      } while (t != i);
      gsiz[G] = r;
      ++G;
    }

    // rep (i, H) printf("%d: %d-%d\n", i, group[i], grnk[i]);

    fre.clear();
    fre.resize(G);
    rep (h, H) fre[group[h]].insert(grnk[h]);
    hsh.clear();
    pos.clear();

    ll res = 0;
    rep (iter, N) {
      char c;
      int id;
      scanf(" %c%d", &c, &id);

      if (c == '+') {
        int h;
        scanf("%d", &h);
        int g = group[h];

        set<int>::iterator ite = fre[g].lower_bound(grnk[h]);
        if (ite == fre[g].end()) ite = fre[g].lower_bound(0);
        int r = *ite;

        int dummy = (r - grnk[h] + gsiz[g]) % gsiz[g];
        res += dummy;
        // cout << iter << ": " << dummy << endl;

        hsh[id] = h;
        pos[id] = ginv[r];
        fre[g].erase(ite);
      } else {
        int h = hsh[id];
        int p = pos[id];
        int g = group[h];
        fre[g].insert(grnk[p]);
      }
    }

    cout << res << endl;
  }


  return 0;
}

