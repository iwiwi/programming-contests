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

char ma[256];

int main() {
  // a, is
  ma['q'] = 'A';
  ma['y'] = 'I';
  ma['i'] = 'S';

  // integer
  ma['d'] = 'N';
  ma['j'] = 'T';
  ma['u'] = 'E';
  ma['w'] = 'G';
  ma['h'] = 'R';

  // the
  ma['x'] = 'H';

  // single
  ma['b'] = 'L';

  // of
  ma['e'] = 'O';
  ma['v'] = 'F';

  // input
  ma['f'] = 'P';
  ma['k'] = 'U';

  // consists
  ma['s'] = 'C';

  // find
  ma['t'] = 'D';

  // number
  ma['c'] = 'M';
  ma['r'] = 'B';

  // index
  ma['n'] = 'X';

  for (int c; (c = getchar()) != EOF; ) {
    if (ma[c]) printf("%c", ma[c]);
    else printf("%c", c);
  }

  return 0;
}

