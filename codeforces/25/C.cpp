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

int N;
int mat[310][310];


int main() {
  while (1 == scanf("%d", &N)) {
    rep (i, N) rep (j, N) scanf("%d", &mat[i][j]);

    int M;
    scanf("%d", &M);
    rep (k, M) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      --a; --b;

      ll res = 0;
      rep (i, N) rep (j, i) {
        int l1 = mat[i][j];
        int l2 = mat[i][a] + c + mat[b][j];
        int l3 = mat[i][b] + c + mat[a][j];
        int l = min(l1, min(l2, l3));
        res += l;
        mat[i][j] = mat[j][i] = l;
      }

      if (k) cout << " ";
      cout << res;
    }
    cout << endl;
  }
  
  return 0;
}
