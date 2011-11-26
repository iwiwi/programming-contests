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

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};
const char *ds = "URDL";

int H, W;
char fld[60][60];

int P;
int fbd[20][20];
int fbl[20];

int nxt[20][20][4];

int main() {
  while (2 == scanf("%d%d", &H, &W)) {
    memset(fld, '#', sizeof(fld));
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        scanf(" %c", &fld[y][x]);
      }
    }

    scanf("%d", &P);
    rep (i, P) {
      char buf[256];
      scanf("%s", buf);
      fbl[i] = strlen(buf);
      rep (j, fbl[i]) fbd[i][j] = strchr(ds, buf[j]) - ds;
    }

    rep (i, P) {
      rep (j, fbl[i]) {
        rep (d, 4) {
          if (fbd[i][j] == d) nxt[i][j][d] = j + 1;
          else {
            for (int t = j; t >= 1; --t) {
              if (fbd[i][t - 1] != d) goto dmp;
              for (int s = 2; t - s >= 0; ++s) {
                if (fbd[i][t - s] != fbd[i][j + 1 - s]) goto dmp;
              }
              nxt[i][j][d] = t;
              goto done;
            dmp:;
            }
            nxt[i][j][d] = 0;
          done:;
          }
        }
      }
    }

    /*
    rep (i, P) {
      printf("[%d]\n", i);
      rep (j, fbl[i]) {
        rep (d, 4) printf(" %d", nxt[i][j][d]);
        puts("");
      }
    }
    */

    int sx, sy;
    sx = sy = -1;
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        if (fld[y][x] == 'S') {
          sx = x;
          sy = y;
          fld[y][x] = '.';
        }
      }
    }

    map<pair<pair<int, int>, vector<int> >, int> mem;
    queue<pair<pair<int, int> , vector<int> > > que;
    pair<pair<int, int>, vector<int> > s = mp(mp(sx, sy), vector<int>(P));

    que.push(s);
    mem[s] = 0;
    
    while (!que.empty()) {
      int x = que.front().first.first;
      int y = que.front().first.second;
      vector<int> p = que.front().second;
      int c = mem[que.front()];
      que.pop();

      if (fld[y][x] == 'G') {
        printf("%d\n", c);
        goto done2;
      }

      rep (d, 4) {
        int tx = x + dx[d];
        int ty = y + dy[d];
        if (fld[ty][tx] == '#') continue;
        
        vector<int> tp = p;
        rep (i, P) {
          tp[i] = nxt[i][p[i]][d];
          if (tp[i] == fbl[i]) goto ng;
        }
        
        s = mp(mp(tx, ty), tp);
        if (mem.count(s)) continue;

        que.push(s);
        mem[s] = c + 1;
        
      ng:;
      }
    }

    puts("-1");
  done2:;
  }
  
  return 0;
}

