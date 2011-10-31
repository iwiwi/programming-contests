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


bool add1(string &s) {
  int c = 1;
  rep (i, s.length()) {
    int j = s.length() - i - 1;
    int d = s[j] - '0';
    s[j] = '0' + (c xor d);
    c = c and d;
  }
  if (c) return false;
  return true;
}

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    vector<pair<int, int> > A(N);
    rep (i, N) {
      scanf("%d", &A[i].first);
      A[i].second = i;
    }
    sort(all(A));

    string s = "";
    vector<string> ans(N);
    
    rep (i, N) {
      int l = A[i].first;
      s.resize(l, '0');
      ans[A[i].second] = s;
      if (i + 1 < N && !add1(s)) goto ng;
    }
    puts("YES");
    rep (i, N) puts(ans[i].c_str());
    continue;
  ng:
    puts("NO");
  }
  
  return 0;
}

