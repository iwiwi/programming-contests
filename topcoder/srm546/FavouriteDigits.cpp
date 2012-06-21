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

struct FavouriteDigits {
  long long findNext(long long N, int digit1, int count1, int digit2, int count2);
};

typedef long long ll;

int D1, D2;

ll doit(string S, int k, int h, int c1, int c2) {
  int L = S.length();
  int p = L - 1;
  while (c2-- > 0) S[p--] = '0' + D2;
  while (c1-- > 0) S[p--] = '0' + D1;
  while (k < p)    S[p--] = '0';
  S[k] = '0' + h;

  stringstream ss(S);
  ll res;
  ss >> res;
  return res;
}

long long FavouriteDigits::findNext(long long N, int digit1, int count1, int digit2, int count2) {
  if (digit1 > digit2) {
    swap(digit1, digit2);
    swap(count1, count2);
  }
  D1 = digit1;
  D2 = digit2;

  string S;
  stringstream ss;
  ss << N;
  S = ss.str();
  int L = S.length();

  if (count(all(S), '0' + digit1) >= count1 && count(all(S), '0' + digit2) >= count2) {
    return N;
  }

  bool retry = false;
  for (;;) {
    for (int k = L - 1; k >= 0; --k) {
      if (retry && k > 0) continue;

      int r = L - k - 1;  // free

      int c1 = 0, c2 = 0;
      rep (i, k) {
        if (S[i] == '0' + digit1) ++c1;
        if (S[i] == '0' + digit2) ++c2;
      }

      // printf("%d: %d %d + %d / d = %d\n", k, c1, c2, r);

      //    =   |   >  |  free
      // S[k-1] | S[k] | S[k+1], ...
      int d = S[k] - '0';
      if (9 > d && D1 != d + 1 && D2 != d + 1 && max(0, count1 - c1) + max(0, count2 - c2)       <= r) {
        return doit(S, k, d + 1,  max(0, count1 - c1),       max(0, count2 - c2));
      }
      if (digit1 > d && max(0, count1 - (c1 + 1)) + max(0, count2 - c2)       <= r) {
        return doit(S, k, digit1, max(0, count1 - (c1 + 1)), max(0, count2 - c2));
      }
      if (digit2 > d && max(0, count1 - c1)       + max(0, count2 - (c2 + 1)) <= r) {
        return doit(S, k, digit2, max(0, count1 - c1),       max(0, count2 - (c2 + 1)));
      }
    }

    S = '0' + S;
    L += 1;
    retry = true;
  }
}

ll naive(ll n, int d1, int c1, int d2, int c2) {
  for (;;) {
    stringstream ss;
    ss << n;
    string s = ss.str();
    if (count(all(s), '0' + d1) >= c1 && count(all(s), '0' + d2) >= c2) {
      return n;
    }
    ++n;
  }
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
			long long N               = 47;
			int digit1                = 1;
			int count1                = 0;
			int digit2                = 2;
			int count2                = 0;
			long long expected__      = 47;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			long long N               = 47;
			int digit1                = 5;
			int count1                = 0;
			int digit2                = 9;
			int count2                = 1;
			long long expected__      = 49;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			long long N               = 47;
			int digit1                = 5;
			int count1                = 0;
			int digit2                = 3;
			int count2                = 1;
			long long expected__      = 53;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			long long N               = 47;
			int digit1                = 2;
			int count1                = 1;
			int digit2                = 0;
			int count2                = 2;
			long long expected__      = 200;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			long long N               = 123456789012345LL;
			int digit1                = 1;
			int count1                = 2;
			int digit2                = 2;
			int count2                = 4;
			long long expected__      = 123456789012422LL;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			long long N               = 92;
			int digit1                = 1;
			int count1                = 1;
			int digit2                = 0;
			int count2                = 0;
			long long expected__      = 100;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			long long N               = 1687926652;
			int digit1                = 6;
			int count1                = 1;
			int digit2                = 0;
			int count2                = 2;
			long long expected__      = 1687926700;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}


        /*      case 7: {
			long long N               = ;
			int digit1                = ;
			int count1                = ;
			int digit2                = ;
			int count2                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			long long N               = ;
			int digit1                = ;
			int count1                = ;
			int digit2                = ;
			int count2                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = FavouriteDigits().findNext(N, digit1, count1, digit2, count2);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

#include <glog/logging.h>

int main(int argc, char *argv[]) {
  rep (iter, 1000000) {
    if (iter % 1000 == 0) printf("%d\n", iter);

    ll n = rand() * (ll)rand() % 1000000000000000LL;
    int d1 = rand() % 10;
    int c1 = rand() % 3;
    int d2 = rand() % 10;
    int c2 = rand() % 5;
    if (d1 == d2) continue;

    CHECK_EQ(naive(n, d1, c1, d2, c2), FavouriteDigits().findNext(n, d1, c1, d2, c2))
        << n << " " << d1 << " " << c1 << " " << d2 << " " << c2;
  }

	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
