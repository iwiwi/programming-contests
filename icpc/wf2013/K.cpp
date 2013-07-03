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

const char *name[] = {"Pre", "In", "Post"};

string S[3];
int L;

int ch[3][2];
map<vector<int>, pair<bool, vector<string> > > mem;

pair<bool, vector<string> > search(const vector<int> &a) {
  if (mem.count(a)) return mem[a];

  int l = a[3];
  if (l == 0) return mp(true, vector<string>(3, ""));
  int n[3] = {a[4], a[5], a[6]};

  pair<bool, vector<string> > res;
  for (char c = 'A'; c <= 'Z'; ++c) {
    vector<int> la(7), ra(7);
    for (int ll = 0; ll <= l - 1; ++ll) {
      int rl = l - 1 - ll;
      la[3] = ll;
      ra[3] = rl;
      rep (i, 3) {
        la[4 + i] = ch[n[i]][0];
        ra[4 + i] = ch[n[i]][1];
        char tc;
        if (n[i] == 0) { la[i] = a[i] + 1; ra[i] = a[i] + 1 + ll; tc = S[i][a[i]]; }
        if (n[i] == 1) { la[i] = a[i];     ra[i] = a[i] + 1 + ll; tc = S[i][a[i] + ll]; }
        if (n[i] == 2) { la[i] = a[i];     ra[i] = a[i]     + ll; tc = S[i][a[i] + ll + rl]; }
        if (tc != c) goto dmp;
      }

      {
        pair<bool, vector<string> > lp = search(la);
        pair<bool, vector<string> > rp = search(ra);
        if (!lp.first || !rp.first) goto dmp;
        vector<string> ss(3);
        ss[0] = c + lp.second[0] + rp.second[0];
        ss[1] = lp.second[1] + c + rp.second[1];
        ss[2] = lp.second[2] + rp.second[2] + c;
        if (res.first == false) res = mp(true, ss);
        else res.second = min(res.second, ss);
      }

     dmp:;
    }
  }

  return mem[a] = res;
}

int main() {
  while (cin >> S[0] >> S[1] >> S[2]) {
    L = S[0].length();
    bool already = false;

    rep (b, 1 << (2 * 6)) {
      int cnt[4] = {};
      rep (i, 3) rep (j, 2) {
        ch[i][j] = (b >> (((2 - i) * 2 + (1 - j)) * 2)) % 4;
        ++cnt[ch[i][j]];
      }
      if (cnt[0] != 2 || cnt[1] != 2 || cnt[2] != 2) continue;

      {
        mem.clear();
        vector<int> a(7);
        a[3] = L;
        a[4] = 0; a[5] = 1; a[6] = 2;
        pair<bool, vector<string> > r = search(a);
        if (r.first) {
          if (already) cout << endl;
          already = true;
          rep (i, 3) rep (j, 2) cout << name[ch[i][j]] << (mp(i, j) == mp(2, 1) ? '\n' : ' ');
          rep (i, 3) cout << r.second[i] << endl;
        }
      }
    }
  }

  return 0;
}

