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

typedef long long ll;

const int K = 26;
const int INF = 987654321;

int cost[30][30];

int main() {
  string A, B;
  while (cin >> A >> B) {
    rep (i, K) rep (j, K) cost[i][j] = i == j ? 0 : INF;
    
    int N;
    scanf("%d", &N);
    rep (i, N) {
      string s, t;
      int c;
      cin >> s >> t >> c;
      int a = s[0] - 'a';
      int b = t[0] - 'a';
      cost[a][b] = min(c, cost[a][b]);
    }

    if (A.length() != B.length()) {
      cout << -1 << endl;
      continue;
    }

    rep (k, K) rep (i, K) rep (j, K) cost[i][j] = min(cost[i][j], cost[i][k] + cost[k][j]);

    int L = A.length();
    string ans = "";
    ll totc = 0;
    rep (i, L) {
      int a = A[i] - 'a';
      int b = B[i] - 'a';
      int minc = INF, mind = -1;
      rep (d, K) {
        int c = cost[a][d] + cost[b][d];
        if (c < minc) {
          minc = c;
          mind = d;
        }
      }
      if (minc >= INF) {
        goto ng;
      }
      totc += minc;
      ans += 'a' + mind;
    }
    cout << totc << endl;
    cout << ans << endl;
    continue;
  ng:
    cout << -1 << endl;
  }
  
  return 0;
}

