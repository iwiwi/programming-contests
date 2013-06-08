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

struct YetAnotherANDProblem {
  string test(vector <int> X, int K, vector <int> queries);
};

typedef long long ll;

string YetAnotherANDProblem::test(vector <int> X, int K, vector <int> queries) {
  int N = X.size();

  vector<int> ts;
  for (ll k = min(3LL, (1LL << (K - 1)) + 1); k <= (1LL << K); ++k) {
    if (k > N) break;

    for (int m = (1 << k) - 1; m < (1 << N); ) {
      int t = -1;
      rep (i, N) if (m & (1 << i)) t &= X[i];
      ts.pb(t);

      int x = m & -m;
      int y = m + x;
      m = ((m & ~y) / x >> 1) | y;
    }
  }
  sort(all(ts));

  string ans;
  rep (i, queries.size()) ans += binary_search(all(ts), queries[i]) ? '+' : '-';

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

	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) {
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
			cerr << "    Expected: \"" << expected << "\"" << endl;
			cerr << "    Received: \"" << received << "\"" << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int X[]                   = {10, 14, 7};
			int K                     = 1;
			int queries[]             = {10, 14, 2, 4};
			string expected__         = "+-+-";

			clock_t start__           = clock();
			string received__         = YetAnotherANDProblem().test(vector <int>(X, X + (sizeof X / sizeof X[0])), K, vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int X[]                   = {30, 29, 27, 23, 15};
			int K                     = 2;
			int queries[]             = {28, 9, 16, 0, 12};
			string expected__         = "-++-+";

			clock_t start__           = clock();
			string received__         = YetAnotherANDProblem().test(vector <int>(X, X + (sizeof X / sizeof X[0])), K, vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int X[]                   = {5, 5, 5, 5, 5};
			int K                     = 50;
			int queries[]             = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			string expected__         = "-----+----";

			clock_t start__           = clock();
			string received__         = YetAnotherANDProblem().test(vector <int>(X, X + (sizeof X / sizeof X[0])), K, vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int X[]                   = {71258, 1257, 2592588, 2885851, 999928, 123456, 59881, 99999};
			int K                     = 4;
			int queries[]             = {72, 91, 10, 0, 27, 64, 8};
			string expected__         = "+--+-++";

			clock_t start__           = clock();
			string received__         = YetAnotherANDProblem().test(vector <int>(X, X + (sizeof X / sizeof X[0])), K, vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int X[]                   = ;
			int K                     = ;
			int queries[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = YetAnotherANDProblem().test(vector <int>(X, X + (sizeof X / sizeof X[0])), K, vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int X[]                   = ;
			int K                     = ;
			int queries[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = YetAnotherANDProblem().test(vector <int>(X, X + (sizeof X / sizeof X[0])), K, vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int X[]                   = ;
			int K                     = ;
			int queries[]             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = YetAnotherANDProblem().test(vector <int>(X, X + (sizeof X / sizeof X[0])), K, vector <int>(queries, queries + (sizeof queries / sizeof queries[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


string naive(vector<int> X, int K, vector<int> queries) {
  int N = X.size();
  map<int, ll> A;
  rep (i, N) ++A[X[i]];

  rep (k, K) {
    map<int, ll> B;
    tr (A, i1) tr (A, i2) {
      if (i1->first < i2->first) {
        int a = i1->first & i2->first;
        B[a] += i1->second * i2->second;
      } else if (i1->first == i2->first) {
        ll t = i1->second * (i1->second - 1) / 2;
        if (t) B[i1->first] += t;
      }
    }
    B.swap(A);
  }

  vector<int> ts;
  tr (A, ite) ts.pb(ite->first);

  string ans;
  rep (i, queries.size()) ans += binary_search(all(ts), queries[i]) ? '+' : '-';
  return ans;
}

int main(int argc, char *argv[]) {


	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}


  const int N = 10;
  while (1) {
    vector<int> X(N);
    rep (i, N) X[i] = 1 + rand() % 1000; //000000;
    int K = 1 + rand() % 50;

    vector<int> Q(50);
    rep (i, Q.size()) Q[i] = 1 + rand() % 1000; //00000;

    rep (i, N) printf("%d%c", X[i], i == N - 1 ? '\n' : ',');
    printf("%d\n", K);
    rep (i, Q.size()) printf("%d%c", Q[i], i + 1 == (int)Q.size() ? '\n' : ',');

    string ans = YetAnotherANDProblem().test(X, K, Q);
    cout << "PASSED: " << ans << endl;
  }
}
// END CUT HERE
