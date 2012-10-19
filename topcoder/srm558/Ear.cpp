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

struct Ear {
  long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY);
};

typedef long long ll;

vector<ll> parse(vector<string> vs) {
  stringstream ss(accumulate(all(vs), string()));
  vector<ll> res;
  for (ll t; ss >> t; ) res.pb(t);
  return res;
}

ll det(ll x1, ll y1, ll x2, ll y2) {
  return x1 * y2 - y1 * x2;
}

ll solve(ll px, ll py, ll qx, ll qy, vector<ll> rx) {
  if (py <= qy) return 0;
  // py > qy

  ll cnt_q = 0, cnt_pq = 0;
  rep (i, rx.size()) {
    ll x = rx[i];

    if (x > px && det(px - x, py, qx - x, qy) > 0) {
      ++cnt_pq;
    }
    else if (x > qx) {
      ++cnt_q;
    }
  }

  ll res1 = cnt_q * cnt_pq;
  ll res2 = cnt_pq * (cnt_pq - 1) / 2;
  return res1 + res2;
}

long long Ear::getCount(vector <string> redX,
                        vector <string> blueX,
                        vector <string> blueY) {
  vector<ll> RX1 = parse(redX);
  vector<ll> BX1 = parse(blueX);
  vector<ll> BY = parse(blueY);
  int RN = RX1.size();
  int BN = BX1.size();

  vector<ll> RX2(RN); rep (i, RN) RX2[i] = RX1[i] * -1;
  vector<ll> BX2(BN); rep (i, BN) BX2[i] = BX1[i] * -1;

  ll ans = 0;
  rep (pi, BN) rep (qi, BN) {
    ll rc = solve(BX1[pi], BY[pi], BX1[qi], BY[qi], RX1);
    ll lc = solve(BX2[pi], BY[pi], BX2[qi], BY[qi], RX2);
    ans += rc * lc;
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
			string redX[]             = {"3 2 8 7"};
			string blueX[]            = {"5 4"};
			string blueY[]            = {"2 4"};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string redX[]             = {"3 2 8 7"};
			string blueX[]            = {"2 8"};
			string blueY[]            = {"3 4"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string redX[]             = {"1 2 6 9"};
			string blueX[]            = {"3 6 8 5"};
			string blueY[]            = {"1 5 4 3"};
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string redX[]             = {"10000"};
			string blueX[]            = {"10000 9999"};
			string blueY[]            = {"10000 9999"};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string redX[]             = {"100 2", "00", " 39", "9", " 800 900 9", "99"};
			string blueX[]            = {"15", "0 250 ", "349"};
			string blueY[]            = {"2 3 1"};
			long long expected__      = 12;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string redX[]             = {"1", " ", "2", " ", "3", " ", "4 5 6", " 7 8 9"};
			string blueX[]            = {"4", " ", "5", " ", "6", " 7 ", "8"};
			string blueY[]            = {"1", " 2 ", "3 4", " 5"};
			long long expected__      = 204;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string redX[]             = ;
			string blueX[]            = ;
			string blueY[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string redX[]             = ;
			string blueX[]            = ;
			string blueY[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string redX[]             = ;
			string blueX[]            = ;
			string blueY[]            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = Ear().getCount(vector <string>(redX, redX + (sizeof redX / sizeof redX[0])), vector <string>(blueX, blueX + (sizeof blueX / sizeof blueX[0])), vector <string>(blueY, blueY + (sizeof blueY / sizeof blueY[0])));
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
