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

const int INF = 987654321;

struct ShoutterDiv1 {
  int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1);
};

vector<int> decode(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1) {
  string c1000 = accumulate(all(s1000), string());
  string c100  = accumulate(all(s100 ), string());
  string c10   = accumulate(all(s10  ), string());
  string c1    = accumulate(all(s1   ), string());

  int N = c1.length();
  vector<int> S(N);
  rep (i, N) S[i] =
      (c1000[i] - '0') * 1000 +
      (c100 [i] - '0') * 100  +
      (c10  [i] - '0') * 10   +
      (c1   [i] - '0') * 1;

  return S;
}

vector<int> doit(vector<int> S, vector<int> T) {
  int N = S.size();
  vector<int> dp(N);

  vector<pair<int, int> > ord(N);
  rep (i, N) ord[i] = mp(S[i], i);
  sort(all(ord));

  rep (i, N) {
    int a = ord[i].second;
    // Done?
    {
      rep (j, i) {
        int b = ord[j].second;
        if (T[b] < S[a]) goto dmp;
      }
      dp[a] = 0;
      continue;
    }
 dmp:
    // Repost
    dp[a] = INF;
    rep (j, i) {
      int b = ord[j].second;
      if (S[b] <= S[a] && S[a] <= T[b]) {
        dp[a] = min(dp[a], dp[b] + 1);
      }
    }
  }

  return dp;
}

int ShoutterDiv1::count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1) {
  vector<int> S = decode(s1000, s100, s10, s1);
  vector<int> T = decode(t1000, t100, t10, t1);
  int N = S.size();

  vector<int> dp[2];
  rep (k, 2) {
    dp[k] = doit(S, T);
    rep (i, N) {
      S[i] *= -1;
      T[i] *= -1;
    }
    S.swap(T);
  }

  int ans = 0;
  rep (i, N) {
    int tmp = dp[0][i] + dp[1][i];
    rep (j, N) {
      if (S[j] <= S[i] && T[i] <= T[j]) tmp = min(tmp, 1 + dp[0][j] + dp[1][j]);
    }
    if (tmp >= INF) return -1;
    ans += tmp;
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
			string s1000[]            = {"22", "2"};
			string s100[]             = {"00", "0"};
			string s10[]              = {"11", "1"};
			string s1[]               = {"21", "4"};
			string t1000[]            = {"22", "2"};
			string t100[]             = {"00", "0"};
			string t10[]              = {"11", "1"};
			string t1[]               = {"43", "6"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s1000[]            = {"00"};
			string s100[]             = {"00"};
			string s10[]              = {"00"};
			string s1[]               = {"13"};
			string t1000[]            = {"00"};
			string t100[]             = {"00"};
			string t10[]              = {"00"};
			string t1[]               = {"24"};
			int expected__            = -1;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s1000[]            = {"0000"};
			string s100[]             = {"0000"};
			string s10[]              = {"0000"};
			string s1[]               = {"1234"};
			string t1000[]            = {"0000"};
			string t100[]             = {"0000"};
			string t10[]              = {"0000"};
			string t1[]               = {"2345"};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s1000[]            = {"0000000000"};
			string s100[]             = {"0000000000"};
			string s10[]              = {"0000000000"};
			string s1[]               = {"7626463146"};
			string t1000[]            = {"0000000000"};
			string t100[]             = {"0000000000"};
			string t10[]              = {"0000000000"};
			string t1[]               = {"9927686479"};
			int expected__            = 18;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s1000[]            = {"00000000000000000000000000000000000000000000000000"};
			string s100[]             = {"00000000000000000000000000000000000000000000000000"};
			string s10[]              = {"50353624751857130208544645495168271486083954769538"};
			string s1[]               = {"85748487990028258641117783760944852941545064635928"};
			string t1000[]            = {"00000000000000000000000000000000000000000000000000"};
			string t100[]             = {"00000000000000000000000000000000000000000000000000"};
			string t10[]              = {"61465744851859252308555855596388482696094965779649"};
			string t1[]               = {"37620749792666153778227385275518278477865684777411"};
			int expected__            = 333;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string s1000[]            = ;
			string s100[]             = ;
			string s10[]              = ;
			string s1[]               = ;
			string t1000[]            = ;
			string t100[]             = ;
			string t10[]              = ;
			string t1[]               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ShoutterDiv1().count(vector <string>(s1000, s1000 + (sizeof s1000 / sizeof s1000[0])), vector <string>(s100, s100 + (sizeof s100 / sizeof s100[0])), vector <string>(s10, s10 + (sizeof s10 / sizeof s10[0])), vector <string>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <string>(t1000, t1000 + (sizeof t1000 / sizeof t1000[0])), vector <string>(t100, t100 + (sizeof t100 / sizeof t100[0])), vector <string>(t10, t10 + (sizeof t10 / sizeof t10[0])), vector <string>(t1, t1 + (sizeof t1 / sizeof t1[0])));
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
