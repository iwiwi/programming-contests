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
#include <climits>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

int pop_pre[1 << 20];

void init_pop(int n) {  // n bits
  for (int b = 1; b < 1 << n; ++b) {
    pop_pre[b] = pop_pre[b & (b - 1)] + 1;
  }
}

inline int pop(int b) {
  return pop_pre[b];
}



int N, A[20];
int K;

ll sum[1 << 16];
int crr[10][10];

int &get(pair<int, int> p) { return crr[p.first][p.second]; }

vector<int> along[10][10];
int G;
vector<pair<int, int> > group[20];
vector<pair<int, int> > fre[20];
vector<int> ord;

ll S;
int three;

void add(int i, int j, int g) {
  along[i][j].pb(g);
  group[g].pb(mp(i, j));
}

void search(int o, int k, int b) {
  if (o == G) throw 0;  // done
  int g = ord[o];

  if (k == (int)fre[g].size()) {
    if (o == 0) {
      S = 0;
      rep (i, N) S += crr[group[g][i].first][group[g][i].second];
      // printf("S = %lld, b = %d\n", S, b);

      ll goal = S * G;
      // printf("goal = %lld\n", goal);
      rep (i, N) goal -= along[group[g][i].first][group[g][i].second].size() * ll(get(group[g][i]));
      // printf("goal = %lld, sum = %lld\n", goal, sum[b]);
      goal -= 2 * sum[b];
      // printf("b=%d\n", b);
      // rep (i, K) if (b & (1 << i)) printf(" %d", A[i]); puts("");
      // printf("goal = %lld, three = %d\n", goal, three);

      if (N == 4) {
        int sub = b;
        do {
          if (pop(sub) == three) {
            if (sum[sub] == goal) {
              // printf(" sub %x -> %lld\n", sub, goal);
              goto done;
            }
          }

          sub = (sub - 1) & b;
        } while (sub != b);

        // puts("NG");

        if (S == 15) {
          if (crr[0][0] == 2 && crr[0][1] == 7 && crr[0][2] == 6) {
            ///printf("NG (%d) vvv\n", o); rep (i, N) rep (j, N) printf("%d%c", crr[i][j], j == N - 1 ? '\n' : ' '); puts("^^^");
            // exit(0);
          }
        }

        return;  // bad S!!!!!
     done:
        // puts("OK");
        // search(o + 1, 0, b);
        ;
      }
    } else {
      ll s = 0;
      rep (i, N) s += crr[group[g][i].first][group[g][i].second];
      if (s != S){
        // printf("NG (%d) vvv\n", o); rep (i, N) rep (j, N) printf("%d%c", crr[i][j], j == N - 1 ? '\n' : ' '); puts("^^^");
        return;
      }
    }
    search(o + 1, 0, b);
    return;
  }
  else {
    int prv = INT_MIN;
    rep (q, K) if (b & (1 << q)) {
      if (prv == A[q]) continue;

      get(fre[g][k]) = A[q];

      if (N == 4) {
        if (fre[g][k] == mp(0, 3) && get(mp(0, 0)) > get(mp(0, 3))) continue;
        if (fre[g][k] == mp(3, 0) && get(mp(0, 0)) > get(mp(3, 0))) continue;
        if (fre[g][k] == mp(3, 3) && get(mp(0, 0)) > get(mp(3, 3))) continue;
        if (fre[g][k] == mp(1, 0) && get(mp(0, 1)) > get(mp(1, 0))) continue;
      }

      // printf("%d %d <- %d\n", fre[g][k].first, fre[g][k].second, A[q]);
      search(o, k + 1, b - (1 << q));
      get(fre[g][k]) = INT_MIN;

      prv = A[q];
    }
  }
}

int main() {
  init_pop(16);

  while (1 == scanf("%d", &N)) {
    K = N * N;
    rep (i, K) scanf("%d", &A[i]);

    rep (b, 1 << K) {
      sum[b] = 0;
      rep (i, K) if (b & (1 << i)) sum[b] += A[i];
    }

    G = N + N + 2;
    rep (i, G) group[i].clear();
    rep (i, N) rep (j, N) along[i][j].clear();
    rep (i, N) rep (j, N) add(i, j, i);
    rep (j, N) rep (i, N) add(i, j, N + j);
    rep (i, N) add(i, i, N + N);
    rep (i, N) add(i, N - i - 1, N + N + 1);


    // decide the order
    memset(crr, -1, sizeof(crr));
    ord.resize(G);
    vector<bool> usd(G);
    rep (i, G) {
      int best_f = INT_MAX, best_g = -1;
      rep (g, G) if (!usd[g]) {
        int f = 0;
        rep (i, N) if (crr[group[g][i].first][group[g][i].second] == -1) ++f;
        if (f < best_f) {
          best_f = f;
          best_g = g;
        }
      }

      usd[best_g] = true;
      ord[i] = best_g;
      fre[best_g].clear();
      rep (i, N) {
        int a = group[best_g][i].first;
        int b = group[best_g][i].second;
        if (crr[a][b] == -1) {
          fre[best_g].pb(mp(a, b));
          crr[a][b] = 0;
        }
      }
    }

    // two weight
    three = 0;
    rep (i, N) rep (j, N) {
      if (cpresent(group[ord[0]], mp(i, j))) continue;
        // printf("%d %d: %d\n", i, j, (int)along[i][j].size());
      if (along[i][j].size() == 3) ++three;
    }

    // rep (i, G) { int g = ord[i]; rep (j, fre[g].size()) printf("(%d,%d) ", fre[g][j].first, fre[g][j].second);  puts("");   }

    try {
      rep (i, N) rep (j, N) crr[i][j] = -100;
      search(0, 0, (1 << K) - 1);
      *(int*)0 = 0;
    } catch (...) {
      printf("%d\n", int(S));
      rep (i, N) rep (j, N) printf("%d%c", crr[i][j], j == N - 1 ? '\n' : ' ');
    }
  }

  return 0;
}

