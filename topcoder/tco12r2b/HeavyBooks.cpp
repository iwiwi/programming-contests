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

struct HeavyBooks {
  vector <int> findWeight(vector <int> books, vector <int> moves);
};

const int INF = 987654321;

pair<int, int> dp[60][60];

vector <int> HeavyBooks::findWeight(vector <int> books, vector <int> moves) {
  int B = books.size();
  sort(all(books));

  vector<int> have[2];
  int N = min(moves[0], (int)books.size());
  have[1].resize(N);
  rep (i, N) have[1][i] = i;

  for (int i = 1; i < (int)moves.size(); ++i) {
    vector<int> &my = have[i % 2];
    vector<int> &op = have[1 - i % 2];

    sort(all(my));
    reverse(all(my));
    int m = min(moves[i], (int)my.size());
    vector<int> give(my.begin(), my.begin() + m);
    my.erase(my.begin(), my.begin() + m);
    op.insert(op.end(), all(give));
  }
  rep (i, 2) { rep (j, have[i].size()) printf("%d ", have[i][j]); puts(""); }

  vector<int> sgn(N);
  rep (i, 2) rep (j, have[i].size()) sgn[have[i][j]] = i == 0 ? -1 : +1;

  dp[0][0] = mp(0, 0);
  for (int j = 1; j <= N; ++j) dp[0][j] = mp(-INF, -INF);
  rep (i, B) {
    for (int j = 0; j <= N; ++j) dp[i + 1][j] = dp[i][j];

    for (int j = 0; j < N; ++j) {
      dp[i + 1][j + 1] = max(dp[i + 1][j + 1], mp(dp[i][j].first  + sgn[j] * books[i],
                                                  dp[i][j].second +          books[i]));
    }
  }

  vector<int> res(2);
  res[0] = (dp[B][N].second - dp[B][N].first) / 2;
  res[1] = (dp[B][N].second + dp[B][N].first) / 2;
  return res;
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
			int books[]               = {5,2,3,1};
			int moves[]               = {3,2,1,1,1};
			int expected__[]          = {3, 7 };

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int books[]               = {10, 100, 1000};
			int moves[]               = {2, 3};
			int expected__[]          = {110, 0 };

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int books[]               = {155870,565381};
			int moves[]               = {1,1,1};
			int expected__[]          = {0, 565381 };

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int books[]               = {500,500,500,500};
			int moves[]               = {4,1,1,3,2};
			int expected__[]          = {500, 1500 };

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int books[]               = {1,1,1,1,1000000};
			int moves[]               = {1};
			int expected__[]          = {0, 1000000 };

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			int books[]               = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
			int moves[]               = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
			int expected__[]          = {110, 100 };

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int books[]               = ;
			int moves[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			int books[]               = ;
			int moves[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			int books[]               = ;
			int moves[]               = ;
			int expected__[]          = ;

			clock_t start__           = clock();
			vector <int> received__   = HeavyBooks().findWeight(vector <int>(books, books + (sizeof books / sizeof books[0])), vector <int>(moves, moves + (sizeof moves / sizeof moves[0])));
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
