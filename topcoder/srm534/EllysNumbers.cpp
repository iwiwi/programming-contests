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

struct EllysNumbers {
  long long getSubsets(long long n, vector <string> special);
};

typedef long long ll;

vector<pair<int, int> > factorize(int n) {
  vector<pair<int, int> > res;
  for (int i = 2; i * i <= n; i++) {
    int c = 0;
    for (; n % i == 0; n /= i) c++;
    if (c > 0) res.push_back(make_pair(i, c));
  }
  if (n != 1) res.push_back(make_pair(n, 1));
  return res;
}


vector<ll> S;

int ord(ll n, int d) {
  int o = 0;
  while (n % d == 0) {
    n /= d;
    ++o;
  }
  return o;
}

long long EllysNumbers::getSubsets(long long n, vector <string> special) {
  vector<int> fs;

  S.clear();
  stringstream ss(accumulate(all(special), string()));
  for (int s; ss >> s; ) {
    if (n % s != 0) continue;

    vector<pair<int, int> > f = factorize(s);
    rep (i, f.size()) {
      if (ord(n, f[i].first) != f[i].second) goto dmp;
      fs.pb(f[i].first);
    }
    S.pb(s);
 dmp:;
  }

  {
    ll t = n;
    rep (i, fs.size()) while (t % fs[i] == 0) t /= fs[i];
    if (t != 1) return 0;
  }

  sort(all(fs));
  fs.erase(unique(all(fs)), fs.end());
  int F = fs.size();

  vector<ll> dp(1 << F);
  dp[0] = 1;
  rep (i, S.size()) {
    ll s = S[i];
    int f = 0;
    rep (j, F) if (s % fs[j] == 0) f |= 1 << j;

    rep (b, 1 << F) if ((b & f) == 0) dp[b | f] += dp[b];
  }

  return dp[(1 << F) - 1];
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

	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) {
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
			long long n               = 12;
			string special[]          = {"4 2 5 6 3"};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long n               = 42;
			string special[]          = {"1 2 3 4 5 6 7 13 14 21 42"};
			long long expected__      = 10;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long n               = 1337;
			string special[]          = {"1 13 42 666 2674"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long n               = 1073741824;
			string special[]          = {"1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 1",
 "6384 32768 65536 131072 262144 524288 1048576 2097",
 "152 4194304 8388608 16777216 33554432 67108864 134",
 "217728 268435456 536870912"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long n               = 7420738134810LL;
			string special[]          = {"435 625199055 4199 33263 17 222870 284870433 72093",
 "2379 7 11 31 247110827 23 1771 81809 851968487 13 ",
 "476379795 1001 5 435274114 38264554 7429 239906525",
 " 3 227183706 887045414 606786670 3795 797605175 29",
 " 30 747186719 19 2 562347843 74 2294 588002688 743",
 "6429 703 591740547 36657492 37 444178205 1002001 2",
 "17626404"};
			long long expected__      = 110;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			long long n               = ;
			string special[]          = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			long long n               = ;
			string special[]          = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			long long n               = ;
			string special[]          = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EllysNumbers().getSubsets(n, vector <string>(special, special + (sizeof special / sizeof special[0])));
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
