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


int main() {
  int N, L;
  while (cin >> N >> L) {
    string line;
    getline(cin, line);

    vector<string> A(L);
    rep (i, L) getline(cin, A[i]);

    getline(cin, line);
    int p = (strchr(line.c_str(), 'o') - line.c_str()) / 2;

    for (int i = L - 1; i >= 0; --i) {
      string a = A[i];
           if (p - 1 >= 0 && a[p * 2 - 1] == '-') --p;
      else if (p + 1  < N && a[p * 2 + 1] == '-') ++p;

      // printf(" %d\n", p);
    }

    printf("%d\n", p + 1);
  }

  return 0;
}

