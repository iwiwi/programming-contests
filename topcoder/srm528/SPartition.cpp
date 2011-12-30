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

struct SPartition {
  long long getCount(string s);
};

typedef long long ll;

string S;
int L;
vector<ll> cnt[30];

void search(int i, int l, int b) {
  if (i == L) {
    // cout << i << " " << l << " " << bitset<20>(b) << endl;
    ++cnt[l][b];
  }
  else {
    int d = S[i] == 'o' ? 1 : 0;
    if (l == 0) {
      search(i + 1, 1, d);
      search(i + 1, 1, d);
    } else {
      search(i + 1, l + 1, b | (d << l));
      if ((b & 1) == d) search(i + 1, l - 1, b >> 1);
    }
  }
}

void enumerate(string s) {
  S = s;
  L = s.length();
  for (int i = 0; i <= L; ++i) {
    cnt[i].clear();
    cnt[i].resize(1 << i);
  }

  search(0, 0, 0);
}


vector<ll> cntL[30], cntR[30];

long long SPartition::getCount(string s) {
  int l = s.length();
  int m = l / 2;

  string ls = s.substr(0, m);
  enumerate(s.substr(0, m));
  for (int i = 0; i <= m; ++i) cntL[i].swap(cnt[i]);

  string rs = s.substr(m);
  reverse(all(rs));
  enumerate(rs);
  for (int i = 0; i <= m; ++i) cntR[i].swap(cnt[i]);

  ll ans = 0;
  for (int k = 0; k <= m; ++k) {
    rep (lb, 1 << k) {
      int rb = 0;
      rep (i, k) rb = (rb << 1) | ((lb >> i) & 1);

      cntL[k][lb] /= 2;
      cntR[k][rb] /= 2;
      // cout << k << " " << bitset<5>(lb) << " " << bitset<5>(rb) << " : " << cntL[k][lb] << " " << cntR[k][rb] << endl;

      ll t = cntL[k][lb] * cntR[k][rb];
      // if (k == 0) t *= 2;
      ans += t;
    }
  }

  return ans * 2;
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
			string s                  = "oxox";
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s                  = "oooxxx";
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s                  = "xoxxox";
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s                  = "xo";
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s                  = "ooooxoox";
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string s                  = "ooxxoxox";
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			string s                  = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			string s                  = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string s                  = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = SPartition().getCount(s);
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
