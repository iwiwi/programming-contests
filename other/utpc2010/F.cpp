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

const ll MOD = 1000000;

int N;
string B[1010];

ll dp[1010];

ll match(const string &s, const string &t) {
  bool ty = false, sy1 = false, syx = false;
  ll resx = 1, resy = 1;
  rep (i, s.length()) {
    if (isdigit(t[i])) {
      if (s[i] != 'x' && s[i] != t[i]) return 0;
    }
    else if (t[i] == 'x') {
      if (s[i] == 'x') { resx *= 2; resx %= MOD; }
    }
    else if (t[i] == 'y') {
      ty = true;
      if (s[i] == 'x') { 
        resy *= 2; resy %= MOD;
        syx = true;
      }
      else if (s[i] == '1') {
        sy1 = true;
      }
    }
    else {
      assert(false); // !?
    }
  }

  if (ty) {
    if (!sy1 && !syx) return 0;
    if (!sy1) --resy;
  }
  return resx * resy;
}



int main() {
  vector<string> P[4];
  P[0].pb("0xxxxxxx");
  P[1].pb("110yyyyx"); P[1].pb("10xxxxxx");
  P[2].pb("1110yyyy"); P[2].pb("10yxxxxx"); P[2].pb("10xxxxxx");
  P[3].pb("11110yyy"); P[3].pb("10yyxxxx"); P[3].pb("10xxxxxx"); P[3].pb("10xxxxxx");
  
  while (cin >> N) {
    rep (i, N) cin >> B[i];

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    
    rep (i, N) {
      ll c = dp[i];
      
      rep (j, 4) {
        int pl = P[j].size();
        if (i + pl > N) continue;

        string s = "", t = "";
        rep (k, P[j].size()) {
          s += B[i + k];
          t += P[j][k];
        }

        // cout << s << "\n" << t << "\n = " << match(s, t) << endl;
        
        dp[i + pl] += c * match(s, t);
        dp[i + pl] %= MOD;
      }
    }

    dp[N] %= MOD;
    dp[N] += MOD;
    dp[N] %= MOD;
    cout << dp[N] << endl;
  }
    
  return 0;
}

