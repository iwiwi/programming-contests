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

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

int R, C;
char fld[20][20];
bool vis[20][20];

string ans;
string crr;

int ccvis[20][20];
int ccid;

int cc(int x, int y, int id) {
  if (ccvis[x][y] == id) return 0;
  if (fld[y][x] == '#' || vis[y][x]) return 0;
  ccvis[x][y] = id;
  int res = 1;
  rep (d, 4) res += cc(x + dx[d], y + dy[d], id);
  return res;
}

void saiki(int x, int y) {
  if (fld[y][x] == '#') return;
  if (vis[y][x]) return;

  // pruning
  // if (crr.length() + cc(x, y, ccid++) < ans.length()) {
  //   return;
  // }

  vis[y][x] = true;
  crr += fld[y][x];
  if (crr.length() > ans.length() || (crr.length() == ans.length() && crr > ans)) {
    ans = crr;
  }

  // rep (d, 4) saiki(x + dx[d], y + dy[d]);

  vector<pair<int, int> > ord;
  rep (d, 4) {
    int tx = x + dx[d], ty = y + dy[d];
    int c = cc(tx, ty, ccid++);
    if (crr.length() + c > ans.length() ||
        (crr.length() + c == ans.length() && ans.compare(0, crr.length(), crr) <= 0)) {
      ord.push_back(make_pair(c, d));
    }
  }
  sort(ord.rbegin(), ord.rend());
  rep (i, ord.size()) {
    int d = ord[i].second;
    saiki(x + dx[d], y + dy[d]);
  }

  crr.resize(crr.size() - 1);
  vis[y][x] = false;
}

int main() {
  for (;;) {
    scanf("%d%d", &R, &C);
    if (R == 0 && C == 0) return 0;

    memset(fld, '#', sizeof(fld));
    for (int y = 1; y <= R; ++y) {
      for (int x = 1; x <= C; ++x) {
        scanf(" %c", &fld[y][x]);
      }
    }

    ans = "";
    for (int y = 1; y <= R; ++y) {
      for (int x = 1; x <= C; ++x) {
        saiki(x, y);
      }
    }
    cout << ans << endl;
  }

  return 0;
}
