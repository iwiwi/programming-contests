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

struct SetAndSet {
  long long countandset(vector <int> A);
};

typedef long long ll;

int B, N;
ll Z[30];

ll ans;

void search(int b, int c, const vector<ll> &zs) {
  if (b == B) {
    ll z = 0;
    rep (i, zs.size()) z |= zs[i];
    int o = N - __builtin_popcountll(z);
    ll t = 1LL << (o + zs.size());
    ans += (c % 2 == 1 ? -1 : 1) * t;
  } else {
    search(b + 1, c, zs);

    ll z = Z[b];
    vector<ll> tzs;
    rep (i, zs.size()) {
      if (zs[i] & z) z |= zs[i];
      else tzs.pb(zs[i]);
    }
    tzs.pb(z);

    search(b + 1, c + 1, tzs);
  }
}

long long SetAndSet::countandset(vector <int> A) {
  N = A.size();

  B = 0;
  rep (b, 20) {
    Z[B] = 0;
    rep (i, N) if (0 == ((A[i] >> b) & 1)) Z[B] |= 1LL << i;
    if (Z[B]) ++B;
  }

  ans = 0;
  search(0, 0, vector<ll>());
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
			int A[]                   = {1,2};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = SetAndSet().countandset(vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int A[]                   = {1,2,3,4};
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = SetAndSet().countandset(vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int A[]                   = {1,2,3,4,5};
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = SetAndSet().countandset(vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int A[]                   = {6,6,6};
			long long expected__      = 6;

			clock_t start__           = clock();
			long long received__      = SetAndSet().countandset(vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int A[]                   = {13,10,4,15,4,8,4,2,4,14,0};
			long long expected__      = 1728;

			clock_t start__           = clock();
			long long received__      = SetAndSet().countandset(vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int A[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SetAndSet().countandset(vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int A[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SetAndSet().countandset(vector <int>(A, A + (sizeof A / sizeof A[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int A[]                   = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SetAndSet().countandset(vector <int>(A, A + (sizeof A / sizeof A[0])));
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
