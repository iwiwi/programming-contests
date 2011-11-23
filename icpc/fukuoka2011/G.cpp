#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <map>
#include <climits>
#include <cstring>
#include <cctype>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef long long ll;

const int INF = 87654321;

int W, H;
char fld[20][20];

int K;
vector<int> px, py;

map<ll, int> mem[20][20];

int search(int x, int y, const vector<int> &c) {
  if (x == W) return search(0, y + 1, c);
  if (y == H) {
    if (count(c.begin(), c.end(), 0) == (int)c.size()) return 0;
    else return INF;
  }

  ll e = 0;
  rep (i, c.size()) e = e * 10 + c[i];

  // printf("(%d, %d):", x, y); rep (i, K) printf(" %d", c[i]); puts("");
			    
  map<ll, int>::iterator ite = mem[y][x].find(e);
  if (ite != mem[y][x].end()) return ite->second;

  int tmp = INF;
  
  rep (d, 2) {
    if (d == 1 && fld[y][x] == '.') continue;

    vector<int> tc = c;
    if (d == 1) {
      bool b = false;
      rep (i, K) {
	if (max(abs(px[i] - x), abs(py[i] - y)) <= 1) {
	  b = true;
	  --tc[i];
	}
      }
      if (b == false) goto ng;
    }

    rep (i, K) {
      if (tc[i] < 0) goto ng;  // No-chance
      
      int fx = min(px[i] + 1, W - 1);
      int fy = min(py[i] + 1, H - 1);
      if (x == fx && y == fy && tc[i] > 0) {
	goto ng;  // Prune!
      }
    }

    tmp = min(tmp, d + search(x + 1, y, tc));
  ng:;
  }

  return mem[y][x][e] = tmp;
}

int main() {
  for (;;) {
    scanf("%d%d", &H, &W);
    if (H == 0 && W == 0) return 0;
    
    px.clear();
    py.clear();

    vector<int> sc;
    rep (y, H) {
      scanf("%s", fld[y]);

      rep (x, W) {
	if (isdigit(fld[y][x])) {
	  px.pb(x);
	  py.pb(y);
	  sc.pb(fld[y][x] - '0');
	}
      }
    }
    K = sc.size();
    
    rep (y, H) rep (x, W) mem[y][x].clear();
    printf("%d\n", search(0, 0, sc));
  }
}
