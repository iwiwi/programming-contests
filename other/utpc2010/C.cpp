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

const int H = 12;
const int W = 6;

char fld[20][20];

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int cid[20][20];

int saiki(int x, int y, int c, int id) {
  if (fld[y][x] != c) return 0;
  if (cid[y][x] != -1) return 0;

  cid[y][x] = id;
  int res = 1;
  rep (d, 4) res += saiki(x + dx[d], y + dy[d], c, id);
  return res;
}

int main() {
  memset(fld, '.', sizeof(fld));
  for (int y = 1; y <= H; ++y) {
    for (int x = 1; x <= W; ++x) scanf(" %c", &fld[y][x]);
  }

  for (int iter = 0;; ++iter) {
    memset(cid, -1, sizeof(cid));

    int cs[500];
    int cn = 0;
    
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        if (fld[y][x] == '.' || fld[y][x] == 'O') continue;
        if (cid[y][x] != -1) continue;
        
        cs[cn] = saiki(x, y, fld[y][x], cn);
        cn++;
      }
    }

    bool del = false;
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        if (fld[y][x] == '.');
        else if (fld[y][x] == 'O') {
          rep (d, 4) {
            int id = cid[y + dy[d]][x + dx[d]];
            if (id >= 0 && cs[id] >= 4) {
              fld[y][x] = '.';
              del = true;
            }
          }
        }
        else {
          if (cs[cid[y][x]] >= 4) {
            fld[y][x] = '.';
            del = true;
          }
        }
      }
    }

    if (!del) {
      printf("%d\n", iter);
      break;
    }

    for (int x = 1; x <= W; ++x) {
      int ty = H;
      for (int y = H; y >= 1; --y) {
        if (fld[y][x] != '.') fld[ty--][x] = fld[y][x];
      }
      while (ty >= 1) fld[ty--][x] = '.';
    }

    /*
    for (int y = 1; y <= H; ++y) {
      for (int x = 1; x <= W; ++x) {
        printf("%c", fld[y][x]);
      }
      puts("");
    }
    break;
    */
  }
  
  return 0;
}

