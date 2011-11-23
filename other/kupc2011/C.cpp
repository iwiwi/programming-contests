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

const int INF = 987654321;


int main() {
  set<string> usd;
  char last = 'a';
  for (;;) {
    string my(10, 'a');
    my[0] = last;
    while (usd.count(my)) {
      for (int i = 1; i < 9; ++i) my[i] = 'a' + rand() % 26;
    }
    usd.insert(my);
    printf("?%s\n", my.c_str()); fflush(stdout);

    string op;
    cin >> op;
    if (usd.count(op) || op[0] != my[my.length() - 1]) {
      puts("!OUT");
      return 0;
    }
    usd.insert(op);
    last = op[op.length() - 1];
  }

  return 0;
}
