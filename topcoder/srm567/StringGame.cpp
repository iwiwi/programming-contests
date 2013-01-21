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

struct StringGame {
  vector <int> getWinningStrings(vector <string> S);
};



vector <int> StringGame::getWinningStrings(vector <string> S) {
  int N = S.size();

  int C[60][30] = {};
  rep (i, N) rep (j, 26) C[i][j] = count(all(S[i]), 'a' + j);

  vector<int> ans;
  rep (i, N) {
    vector<bool> usd(30);
    vector<bool> alive(N, true);
    alive[i] = false;

    // cout << S[i] << endl;
    for (;;) {
      rep (j, 26) if (!usd[j]) {
        rep (k, N) if (alive[k] && C[k][j] > C[i][j]) goto lose;
        usd[j] = true;
        rep (k, N) if (alive[k] && C[k][j] < C[i][j]) alive[k] = false;
        goto done;
     lose:;
      }
      break;
   done:;
    }

    if (count(all(alive), true) == 0) ans.pb(i);
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

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, clock_t elapsed) {
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
			string S[]                = {"a", "b", "c", "d"};
			int expected__[]          = {0, 1, 2, 3 };

			clock_t start__           = clock();
			vector <int> received__   = StringGame().getWinningStrings(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string S[]                = {"aabbcc", "aaabbb", "aaaccc"};
			int expected__[]          = {1, 2 };

			clock_t start__           = clock();
			vector <int> received__   = StringGame().getWinningStrings(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string S[]                = {"ab", "ba"};
			int expected__[]          = { };

			clock_t start__           = clock();
			vector <int> received__   = StringGame().getWinningStrings(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string S[]                = {"xaocxsss", "oooxsoas", "xaooosss", "xaocssss", "coxaosxx"};
			int expected__[]          = {1, 3, 4 };

			clock_t start__           = clock();
			vector <int> received__   = StringGame().getWinningStrings(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string S[]                = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = StringGame().getWinningStrings(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			string S[]                = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = StringGame().getWinningStrings(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string S[]                = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = StringGame().getWinningStrings(vector <string>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}



int main(int argc, char *argv[]) {
  for (;;) {
    const int L = 50;
    const int N = 50;
    vector<string> S(N);
    rep (i, L) {
      S[i] = string(L, 'a');
      rep (j, L) S[i][j] = 'a' + rand() % 26;
    }

    vector<int> ans = StringGame().getWinningStrings(S);


    rep (i, N) cout << S[i] << ",";
    cout << endl;
    break;
  }


	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
