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

struct AkariDaisukiDiv1 {
  int countF(string Waai, string Akari, string Daisuki, string S, string F, int k);
};

typedef long long ll;

const ll MOD = 1000000007;

string F;

int len_head_suffix(string s) {
  if (s.length() >= F.length()) s = s.substr(0, F.length() - 1);

  int res = 0;
  for (int i = 0; i <= (int)min(s.length(), F.length()); ++i) {
    if (0 == s.compare(0, i, F, F.length() - i, i)) res = i;
  }
  return res;
}

int len_tail_prefix(string s) {
  if (s.length() >= F.length()) s = s.substr(s.length() - (F.length() - 1));

  int res = 0;
  for (int i = 0; i <= (int)min(s.length(), F.length()); ++i) {
    if (0 == s.compare(s.length() - i, i, F, 0, i)) res = i;
  }
  return res;
}

int countit(string A) {
  int t = 0;
  for (int i = 0; i + F.length() <= A.length(); ++i) {
    if (A.compare(i, F.length(), F) == 0) ++t;
  }
  return t;
}

int AkariDaisukiDiv1::countF(string A, string B, string C, string S, string F, int K) {
  ::F = F;

  int next_head[60];
  int next_tail[60];
  int inc[60][60];

  for (int i = 0; i <= (int)F.length(); ++i) {
    next_head[i] = len_head_suffix(A + F.substr(F.length() - i, i));
    next_tail[i] = len_tail_prefix(F.substr(0, i) + C);
  }

  for (int i = 0; i <= (int)F.length(); ++i) {
    for (int j = 0; j <= (int)F.length(); ++j) {
      string head = F.substr(F.length() - i, i);
      string tail = F.substr(0, j);
      inc[i][j] = countit(A + head) + countit(tail + B + head) + countit(tail + C);
    }
  }

  // naive
  for (; K > 0 && S.length() <= F.length(); --K) {
    S = A + S + B + S + C;
  }

  cout << S << endl;
  ll cnt = countit(S);
  int head = len_head_suffix(S);
  int tail = len_tail_prefix(S);

  for (; K > 0; --K) {
    cnt = (cnt * 2 + inc[head][tail]) % MOD;

    int th = next_head[head];
    int tt = next_tail[tail];
    head = th;
    tail = tt;
  }

  return cnt;
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
			string Waai               = "a";
			string Akari              = "b";
			string Daisuki            = "c";
			string S                  = "x";
			string F                  = "axb";
			int k                     = 2;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string Waai               = "a";
			string Akari              = "b";
			string Daisuki            = "c";
			string S                  = "x";
			string F                  = "abcdefghij";
			int k                     = 1;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string Waai               = "a";
			string Akari              = "a";
			string Daisuki            = "a";
			string S                  = "b";
			string F                  = "aba";
			int k                     = 2;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string Waai               = "a";
			string Akari              = "b";
			string Daisuki            = "c";
			string S                  = "d";
			string F                  = "baadbdcbadbdccccbaaaadbdcbadbdccbaadbdcba";
			int k                     = 58;
			int expected__            = 191690599;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string Waai               = "a";
			string Akari              = "x";
			string Daisuki            = "y";
			string S                  = "b";
			string F                  = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
			int k                     = 49;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string Waai               = "waai";
			string Akari              = "akari";
			string Daisuki            = "daisuki";
			string S                  = "usushio";
			string F                  = "id";
			int k                     = 10000000;
			int expected__            = 127859200;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string Waai               = "vfsebgjfyfgerkqlr";
			string Akari              = "ezbiwls";
			string Daisuki            = "kjerx";
			string S                  = "jbmjvaawoxycfndukrjfg";
			string F                  = "bgjfyfgerkqlrvfsebgjfyfgerkqlrvfsebgjfyfgerkqlrvfs";
			int k                     = 1575724;
			int expected__            = 483599313;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string Waai               = ;
			string Akari              = ;
			string Daisuki            = ;
			string S                  = ;
			string F                  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string Waai               = ;
			string Akari              = ;
			string Daisuki            = ;
			string S                  = ;
			string F                  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string Waai               = ;
			string Akari              = ;
			string Daisuki            = ;
			string S                  = ;
			string F                  = ;
			int k                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = AkariDaisukiDiv1().countF(Waai, Akari, Daisuki, S, F, k);
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
