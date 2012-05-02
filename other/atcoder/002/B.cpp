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


int gepoch(int y, int m, int d) {
  y += 4800;
  if (m < 3) --y, m += 12;
  return 365L*y+y/4-y/100+y/400+(153*m-457)/5+d-32045;
}

void ymd(int gep, int &y, int &m, int &d) {
  for (y = 0; gep >= gepoch(y + 1, 1, 1); y++);
  for (m = 1; m < 12 && gep >= gepoch(y, m + 1, 1); m++);
  for (d = 1; gep > gepoch(y, m, d); d++);
}


int main() {
  int y, m, d;
  while (3 == scanf("%d/%d/%d", &y, &m, &d)) {
    int g = gepoch(y, m, d);
    while (y % m != 0 || y / m % d != 0) {
      ++g;
      ymd(g, y, m, d);
    }
    printf("%04d/%02d/%02d\n", y, m, d);
  }


  return 0;
}

