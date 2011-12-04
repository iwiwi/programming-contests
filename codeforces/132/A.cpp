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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int rev(int a) {
  bitset<8> bs(a);
  string s = bs.to_string();
  reverse(all(s));
  return bitset<32>(s).to_ulong();
}

int main() {
  string line;
  getline(cin, line);
  rep (i, line.length()) {
    int p = i == 0 ? 0 : line[i - 1];
    int c = line[i];
    int x = (rev(p) - rev(c) + 256) % 256;;
    printf("%d\n", x);
  }

  return 0;
}

