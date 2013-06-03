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
#include <climits>
#include <numeric>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct PickAndDelete {
  int count(vector <string> S);
};

typedef long long ll;
const ll MOD = 1000000007;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}

ll pa[410][210];
ll dp[210][410];

int PickAndDelete::count(vector <string> S_) {
  stringstream ss(accumulate(all(S_), string()));
  vector<int> S;
  for (int x; ss >> x; ) S.pb(x);
  sort(all(S));
  int N = S.size();

  vector<pair<int, int> > R;
  R.pb(mp(0, 1));
  if (S[0] > 1) R.pb(mp(1, S[0]));
  rep (i, N) {
    if (i > 0) {
      if (S[i - 1] == S[i]) continue;
      if (S[i] - S[i - 1] > 1) {
        R.pb(mp(S[i - 1] + 1, S[i]));
      }
    }
    R.pb(mp(S[i], S[i] + 1));
  }
  int J = R.size();
  // rep (j, J) printf("%d: [%d, %d)\n", j, R[j].first, R[j].second);

  rep (j, J) {
    pa[j][0] = 1;
    ll c = R[j].second - R[j].first;
    for (int n = 1; n <= N; ++n) {
      pa[j][n] = pa[j][n - 1] * c % MOD * inverse(n, MOD) % MOD;
    }
  }

  memset(dp, 0, sizeof(dp));
  rep (j, J) dp[0][j] = 1;

  rep (i, N) {
    for (int j = 1; j < J; ++j) {
      dp[i + 1][j] = dp[i + 1][j - 1];
      for (int b = i; b >= 0; --b) {
        if (R[j].first > S[b]) continue;  // Too big
        int n = i - b + 1;
        (dp[i + 1][j] += dp[b][j - 1] * pa[j][n]) %= MOD;
      }
    }
  }

  ll ans = dp[N][J - 1];
  rep (i, N) (ans *= (i + 1)) %= MOD;
  return ans;
}











// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}

		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}

		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}

	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;

		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl;
			cerr << "    Received: " << received << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string S[]                = {"1 2"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S[]                = {"2 2 2 2 2 2 2 2 2"};
			int expected__            = 512;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S[]                = {"5", " 1 ", "2"};
			int expected__            = 34;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S[]                = {"3 ", "14159 265", "3589 7", " 932"};
			int expected__            = 353127147;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 4: {
        string S[]                ={"100000000", "99999999", "99999998", "99999997", "99999996", "99999995", "99999994", "99999993", "99999992", "99999991", "99999990", "99999989", "99999988", "99999987", "99999986", "99999985", "99999984", "99999983", "99999982", "99999981", "99999980", "99999979", "99999978", "99999977", "99999976", "99999975", "99999974", "99999973", "99999972", "99999971", "99999970", "99999969", "99999968", "99999967", "99999966", "99999965", "99999964", "99999963", "99999962", "99999961", "99999960", "99999959", "99999958", "99999957", "99999956", "99999955", "99999954", "99999953", "99999952", "99999951"};
 ;
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 5: {
			string S[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string S[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = PickAndDelete().count(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
