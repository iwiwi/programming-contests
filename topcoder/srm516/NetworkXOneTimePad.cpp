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

struct NetworkXOneTimePad {
  int crack(vector <string> plaintexts, vector <string> ciphertexts);
};



int NetworkXOneTimePad::crack(vector <string> plaintexts, vector <string> ciphertexts) {
  int P = plaintexts.size();
  int C = ciphertexts.size();
  int L = plaintexts[0].length();

  int ans = 0;
  rep (p0, P) {
    rep (c, C) {
      string tp = "";
      rep (i, L) {
        if (ciphertexts[0][i] == plaintexts[p0][i]) tp += ciphertexts[c][i];
        else tp += '0' + ('1' - ciphertexts[c][i]);
      }
      if (!cpresent(plaintexts, tp)) goto ng;
    }
    ++ans;
 ng:;
  }

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
			string plaintexts[]       = {"110", "001"};
			string ciphertexts[]      = {"101", "010"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = NetworkXOneTimePad().crack(vector <string>(plaintexts, plaintexts + (sizeof plaintexts / sizeof plaintexts[0])), vector <string>(ciphertexts, ciphertexts + (sizeof ciphertexts / sizeof ciphertexts[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string plaintexts[]       = {"00", "01", "10", "11"};
			string ciphertexts[]      = {"00", "01", "10", "11"};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = NetworkXOneTimePad().crack(vector <string>(plaintexts, plaintexts + (sizeof plaintexts / sizeof plaintexts[0])), vector <string>(ciphertexts, ciphertexts + (sizeof ciphertexts / sizeof ciphertexts[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string plaintexts[]       = {"01", "10"};
			string ciphertexts[]      = {"00"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = NetworkXOneTimePad().crack(vector <string>(plaintexts, plaintexts + (sizeof plaintexts / sizeof plaintexts[0])), vector <string>(ciphertexts, ciphertexts + (sizeof ciphertexts / sizeof ciphertexts[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string plaintexts[]       = {"000", "111", "010", "101", "110", "001"};
			string ciphertexts[]      = {"011", "100"};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = NetworkXOneTimePad().crack(vector <string>(plaintexts, plaintexts + (sizeof plaintexts / sizeof plaintexts[0])), vector <string>(ciphertexts, ciphertexts + (sizeof ciphertexts / sizeof ciphertexts[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string plaintexts[]       = ;
			string ciphertexts[]      = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NetworkXOneTimePad().crack(vector <string>(plaintexts, plaintexts + (sizeof plaintexts / sizeof plaintexts[0])), vector <string>(ciphertexts, ciphertexts + (sizeof ciphertexts / sizeof ciphertexts[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			string plaintexts[]       = ;
			string ciphertexts[]      = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NetworkXOneTimePad().crack(vector <string>(plaintexts, plaintexts + (sizeof plaintexts / sizeof plaintexts[0])), vector <string>(ciphertexts, ciphertexts + (sizeof ciphertexts / sizeof ciphertexts[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string plaintexts[]       = ;
			string ciphertexts[]      = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = NetworkXOneTimePad().crack(vector <string>(plaintexts, plaintexts + (sizeof plaintexts / sizeof plaintexts[0])), vector <string>(ciphertexts, ciphertexts + (sizeof ciphertexts / sizeof ciphertexts[0])));
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
