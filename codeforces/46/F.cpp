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



const int MAX_N = 1010;

struct union_find {
int par[MAX_N], rank[MAX_N];

void init(int n) {
  for (int i = 0; i < n; i++) {
    par[i] = i;
    rank[i] = 0;
  }
}

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}

void unite(int x, int y) {
  x = root(x);
  y = root(y);
  if (x == y) return;

  if (rank[x] < rank[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rank[x] == rank[y]) rank[x]++;
  }
}

bool find(int x, int y) {
  return root(x) == root(y);
}
};


int N, M, K;
int E[1010][2];

int owner[2][1010];
int room[2][1010];
vector<int> key[2][1010];
union_find uf[2];

map<string, int> name2id;
int readname() {
  string name;
  cin >> name;
  if (name2id.count(name)) return name2id[name];
  else {
    int id = name2id.size();
    return name2id[name] = id;
  }
}

int main() {
  while (3 == scanf("%d%d%d", &N, &M, &K)) {
    rep (i, M) {
      scanf("%d%d", &E[i][0], &E[i][1]);
      --E[i][0];
      --E[i][1];
    }

    name2id.clear();
    rep (d, 2) {
      rep (i, K) {
        int k = readname(), t;
        scanf("%d%d", &room[d][k], &t);
        --room[d][k];
        key[d][k].resize(t);
        rep (j, t) {
          scanf("%d", &key[d][k][j]);
          --key[d][k][j];
          owner[d][key[d][k][j]] = k;
        }
      }

      uf[d].init(N);

      bool up;
      do {
        up = false;
        rep (i, M) {
          if (uf[d].find(E[i][0], E[i][1])) continue;

          rep (j, 2) {
            if (uf[d].find(room[d][owner[d][i]], E[i][j])) {
              // Open the door!!
              uf[d].unite(E[i][0], E[i][1]);
              // printf("[%d] %d-%d\n", i, E[i][0], E[i][1]);
              up = true;
              break;
            }
          }
        }
      } while (up);

      // rep (i, N) printf("%d ", uf[d].root(i)); puts("");
    }

    rep (i, K) {
      rep (d, 2) {
        if (!uf[d].find(room[0][i], room[1][i])) goto ng;
      }
    }

    rep (p, N) if (uf[0].par[p] == p) {
      vector<int> v[2];
      rep (d, 2) {
        rep (i, K) {
          if (uf[d].find(room[d][i], p)) {
            v[d].insert(v[d].end(), all(key[d][i]));
          }
        }
        sort(all(v[d]));
      }
      if (v[0] != v[1]) goto ng;
    }
    puts("YES");
    continue;
  ng:
    puts("NO");
  }

  return 0;
}

