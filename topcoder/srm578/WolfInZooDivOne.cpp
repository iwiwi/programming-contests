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

typedef long long ll;
const ll MOD = 1000000007;

struct WolfInZooDivOne {
  int count(int N, vector <string> L, vector <string> R);
};

int N, M;
vector<pair<int, int> > I;

ll mem[310][310];

ll search(int k, int i0) {
  if (k == N) return 1;
  if (mem[k][i0] != -1) return mem[k][i0];

  ll res = 0;

  // Don't place
  res += search(k + 1, i0);

  // Place
  {
    int tk = k + 1;
    for (int ti1 = 0; ti1 < i0; ++ti1) tk = max(tk, I[ti1].second);

    int ti0 = i0;
    while (ti0 < M && I[ti0].first <= k) ++ti0;

    res += search(tk, ti0);
  }

  res %= MOD;
  return mem[k][i0] = res;
}

int WolfInZooDivOne::count(int N_, vector <string> L, vector <string> R) {
  N = N_;
  {
    string sl = accumulate(all(L), string()), sr = accumulate(all(R), string());
    stringstream ssl(sl), ssr(sr);
    I.clear();
    for (int l, r; (ssl >> l) && (ssr >> r); ) I.pb(mp(l, r + 1));
    sort(all(I));
    M = I.size();
  }

  memset(mem, -1, sizeof(mem));
  return search(0, 0);
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
			int N                     = 5;
			string L[]                = {"0"};
			string R[]                = {"4"};
			int expected__            = 16;

			clock_t start__           = clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 5;
			string L[]                = {"0 1"};
			string R[]                = {"2 4"};
			int expected__            = 21;

			clock_t start__           = clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 10;
			string L[]                = {"0 4 2 7"};
			string R[]                = {"3 9 5 9"};
			int expected__            = 225;

			clock_t start__           = clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 100;
			string L[]                = {"0 2 2 7 10 1","3 16 22 30 33 38"," 42 44 49 51 57 60 62"," 65 69 72 74 77 7","8 81 84 88 91 93 96"};
			string R[]                = {"41 5 13 22 12 13 ","33 41 80 47 40 ","4","8 96 57 66 ","80 60 71 79"," 70 77 ","99"," 83 85 93 88 89 97 97 98"};
			int expected__            = 6419882;

			clock_t start__           = clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int N                     = ;
			string L[]                = ;
			string R[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int N                     = ;
			string L[]                = ;
			string R[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int N                     = ;
			string L[]                = ;
			string R[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = WolfInZooDivOne().count(N, vector <string>(L, L + (sizeof L / sizeof L[0])), vector <string>(R, R + (sizeof R / sizeof R[0])));
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
