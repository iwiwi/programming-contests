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
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct MapGuessing {
  long long countPatterns(string goal, vector <string> code);
};

typedef long long ll;

long long MapGuessing::countPatterns(string G, vector <string> code) {
  int L = G.length();
  string C = accumulate(all(code), string());
  vector<ll> ms;

  for (int s = 0; s < L; ++s) {
    string now(L, '-'), ok;
    int p = s;

    rep (i, C.length() + 1) {
      if (p < 0 || L <= p) goto dmp1;

      rep (j, L) if (now[j] != '-' && now[j] != G[j]) goto dmp2;
      ok = now;
   dmp2:

      if (i < (int)C.length()) {
        switch (C[i]) {
          case '<': --p; break;
          case '>': ++p; break;
          case '0': now[p] = '0'; break;
          case '1': now[p] = '1'; break;
        }
      }
    }

    if (!ok.empty()) {
      ll m = 0;
      rep (j, L) m |= ll(ok[j] != '-') << j;
      ms.pb(m);
    }
    cout << ok << endl;
 dmp1:;
  }

  int M = ms.size();

  ll res = 0;
  rep (i, M) {
    vector<ll> ts;
    int r = 0;
    rep (j, i) {
      if (ms[i] & ms[j]) ts.pb(ms[j]);
      else ++r;
    }
    int k = ts.size();

    rep (b, 1 << k) {
      ll m = ms[i];
      rep (j, k) if (b & (1 << j)) m &= ts[j];
      res += (__builtin_parity(b) ? -1 : +1) * (1LL << __builtin_popcountll(m));
    }
    if (k == 0 && r > 0) res -= 1;
  }
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
			string goal               = "000";
			string code[]             = {"0"};
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string goal               = "001";
			string code[]             = {"0>1"};
			long long expected__      = 5;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string goal               = "000";
			string code[]             = {"1>1>1"};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string goal               = "11001";
			string code[]             = {">><<<<><<"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string goal               = "1000101011";
			string code[]             = {"1<<0>>0>1"};
			long long expected__      = 22;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string goal               = "00000010000000000000000000000000";
			string code[]             = {"><>>0<0<>>1>0><>", "<<0>>0<>><0>0>>><><", ">>>0<>", ">0><>>>>0<<><>>0>>>0<0>>0>"};
			long long expected__      = 13601;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string goal               = "11100011010111111010100100110001101";
			string code[]             = {"11111111111111111111"
,"1<><><><><><><><><>1"
,"1<>000>000><0<><0<>1"
,"1<0<><>0><0<00>00<>1"
,"1<>00<>000><0<0<0<>1"
,"1<><>0>0><0<0<><0<>1"
,"1<000<>0><0<0<><0<>1"
,"1<><><><><><><><><>1"
,"1<>000><000<>000><>1"
,"1<>0><><0<><>0><><>1"
,"1<>000><000<>000><>1"
,"1<><>0><><0<><>0><>1"
,"1<>000><000<>000><>1"
,"1<><><><><><><><><>1"
,"11111111111111111111"};
			long long expected__      = 90;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string goal               = ;
			string code[]             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string goal               = ;
			string code[]             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string goal               = ;
			string code[]             = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MapGuessing().countPatterns(goal, vector <string>(code, code + (sizeof code / sizeof code[0])));
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
