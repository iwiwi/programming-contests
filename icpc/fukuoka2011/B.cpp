#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)

const int dx[8]={1,1,1,0,-1,-1,-1,0};
const int dy[8]={1,0,-1,-1,-1,0,1,1};


int main() {
  for (;;) {
    int W, H;
    char fld[30][30];
    scanf("%d%d", &H, &W);
    if (W == 0 && H == 0) return 0;
    rep (y, H) scanf("%s", fld[y]);

    vector<string> strs;
    rep (sy, H) rep (sx, W) {
      rep (d, 8) {
	string s = "";
	int x = sx, y = sy;
	bool vis[30][30] = {};
	for (;;) {
	  if (vis[y][x]) break;
	  assert(0 <= y && y < H);
	  assert(0 <= x && x < W);
	  s += fld[y][x];
	  vis[y][x] = true;

	  x = (x + dx[d] + W) % W;
	  y = (y + dy[d] + H) % H;
	}
	strs.push_back(s);
      }
    }
    sort(strs.begin(), strs.end());

    string ans = "";
    rep (i, strs.size() - 1) {
      string a = strs[i], b = strs[i + 1];
      string s = "";
      rep (j, min(a.length(), b.length())) {
	if (a[j] != b[j]) break;
	s += a[j];
      }
      // cout << a << " " << b << ": " << s << endl;
      if (s.length() > ans.length() || (s.length() == ans.length() && s < ans)) {
	ans = s;
      }
    }
    
    if (ans.length() < 2) cout << 0 << endl;
    else cout << ans << endl;
  }
}
