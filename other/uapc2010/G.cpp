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


enum { TOP, FRONT, RIGHT, BACK, LEFT, BOTTOM };
#define ROTATE_X TOP, BACK, BOTTOM, FRONT
#define ROTATE_Y TOP, LEFT, BOTTOM, RIGHT
#define ROTATE_Z BACK, LEFT, FRONT, RIGHT
 
void rotate(vector<int> &p, int a, int b, int c, int d) {
  swap(p[a], p[b]); swap(p[b], p[c]); swap(p[c], p[d]);
}

typedef pair<pair<int, int>, vector<int> > s_t;

int H, W, fld[20][20];
multimap<int, s_t> que;
map<s_t, int> pot;

void push(int x, int y, const vector<int> &p, int c) {
  if (x < 0 || W <= x || y < 0 || H <= y) return;
  // printf(" -> %d %d\n", x, y);
  
  c += fld[y][x] * p[BOTTOM];
  s_t s = mp(mp(x, y), p);
  if (pot.count(s) && c >= pot[s]) return;

  // puts("  hoge");
  
  que.insert(mp(c, s));
  pot[s] = c;
}


int main() {
  for (;;) {
    scanf("%d%d", &H, &W);
    if (!(W|H)) return 0;
    
    rep (y, H) rep (x, W) scanf("%d", &fld[y][x]);
    
    int sx, sy, gx, gy;
    scanf("%d%d%d%d", &sy, &sx, &gy, &gx);

    vector<int> p(6);
    p[TOP]   = 1; p[BOTTOM] = 6;
    p[FRONT] = 2; p[BACK]   = 5;
    p[RIGHT] = 3; p[LEFT]   = 4;

    que.clear();
    pot.clear();
    
    s_t s = mp(mp(sx, sy), p);
    que.insert(mp(0, s));
    pot[s] = 0;

    while (!que.empty()) {
      int c = que.begin()->first;
      s = que.begin()->second;
      que.erase(que.begin());
      if (c > pot[s]) continue;

      int x = s.first.first;
      int y = s.first.second;
      //printf(" %d %d\n", x, y);

      if (x == gx && y == gy) {
        printf("%d\n", c);
        break;
      }
      
      vector<int> &p = s.second, q;

      q = p;
      rotate(q, ROTATE_Y);
      push(x + 1, y, q, c);

      rotate(q, ROTATE_Y);
      rotate(q, ROTATE_Y);
      push(x - 1, y, q, c);

      q = p;
      rotate(q, ROTATE_X);
      push(x, y + 1, q, c);

      rotate(q, ROTATE_X);
      rotate(q, ROTATE_X);
      push(x, y - 1, q, c);
    }
  }
  
  return 0;
}

