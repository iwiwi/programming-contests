#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <climits>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define mp make_pair
#define pb push_back

typedef long long ll;

const int target[2] = { 24, 2 };

int N;
ll R;
char name[10];
ll A[10];
int name2id[256];

bool usd[10];

string res[2] = "";

ll gcd(ll a, ll b) {
  if (b == 0) return a;
  else gcd(b, a % b);
}

pair<pair<pair<int, int>, string>, pair<string, string> > ans;

void done(int shafts, int gear) {
  string s = "";
  rep (i, 2) rep (j, res[i].length()) if (isalpha(res[i][j])) s += res[i][j];
  // cout << shafts << " " << gear << " " << s << endl;
  
  ans = min(ans, mp(mp(mp(shafts, gear), s), mp(res[0], res[1])));
}

void search(int step, int shafts, int gear) {
  // compute and check!!
  string &r = res[step];
  {
    ll mul = R, div = 1;

    for (int i = 1; i + 1 < (int)r.length(); ) {
      if (r[i + 1] == '-') {
	mul *= -A[name2id[int(r[i])]];
	div *= +A[name2id[int(r[i + 2])]];
	
	i += 2;
      } else {
	i += 1;
      }
    }
    
    if (mul % div == 0 && mul / div == target[step]) {
      if (step == 0) {
	rep (cut, r.length()) {
	  if (r[cut] == '-') continue;

	  res[1] = r.substr(0, cut + 1);
	  search(step + 1, shafts, gear);
	}
      } else {
	done(shafts, gear);
      }
    }
  }

  // next one!
  rep (i, N) if (!usd[i]) {
    usd[i] = true;

    // A-B
    if (r.length() > 1) {
      r += string("-") + name[i];
      search(step, shafts + 1, gear + 1);
      r = r.substr(0, r.length() - 2);
    }

    // AB
    if (r.length() <= 1 || !isalpha(r[r.length() - 2])) {
      r += name[i];
      search(step, shafts, gear + 1);
      r = r.substr(0, r.length() - 1);
    }
    
    usd[i] = false;
  }
}

int main() {
  for (int ca = 1; ; ++ca) {
    cin >> N >> R;
    if (N == 0) return 0;
    
    rep (i, N) {
      string s;
      cin >> s >> A[i];
      name[i] = s[0];
      name2id[int(s[0])] = i;
    }

    memset(usd, 0, sizeof(usd));

    res[0] = "*";
    ans.first.first.first = INT_MAX;
    search(0, 1, 0);

    if (ca > 1) cout << endl;
    cout << "Trial " << ca;
    if (ans.first.first.first == INT_MAX) cout << " IS IMPOSSIBLE" << endl;
    else {
      cout << endl;
      cout << "Minutes: " << ans.second.first  << endl;
      cout << "Hours:   " << ans.second.second << endl;
    }
  }
}
