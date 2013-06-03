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

#define F first
#define S second

struct SubFibonacci {
  int maxElements(vector <int> S);
};

typedef long long ll;
const int K = 50;

int lef[60], rig[60], tmp[60];

char in[100000000 / 8 + 10];

int SubFibonacci::maxElements(vector <int> A) {
  int N = A.size();
  sort(all(A));
  ll max_a = A.back();

  vector<pair<ll, ll> > f(K);
  f[0] = mp(1, 0);
  f[1] = mp(0, 1);
  for (int i = 2; i < K; ++i) {
    f[i] = mp(f[i - 2].F + f[i - 1].F, f[i - 2].S + f[i - 1].S);
  }

  ll bs[60] = {};
  rep (i, N + 1) lef[i] = min(2, i);
  rep (i, N + 1) rig[i] = min(2, N - i);

  for (int i0 = 0; i0 < N; ++i0) {
    for (int f0 = 0; f[f0].F + f[f0].S <= A[i0]; ++f0) {
      for (int i1 = i0 + 1; i1 < N; ++i1) {
        for (int f1 = 0; f[f1].F + f[f1].S <= A[i1]; ++f1) {
          // Determine first two elements
          ll det = f[f0].F * f[f1].S - f[f0].S * f[f1].F;
          if (det == 0) continue;
          ll b0 = +f[f1].S * A[i0] - f[f0].S * A[i1];
          ll b1 = -f[f1].F * A[i0] + f[f0].F * A[i1];
          if (b0 % det != 0 || b1 % det != 0) continue;
          b0 /= det;
          b1 /= det;
          if (b0 <= 0 || b1 <= 0) continue;

          // Generate
          int bs_n = 0;
          bs[bs_n++] = b0;
          bs[bs_n++] = b1;
          for (;;) {
            bs[bs_n] = bs[bs_n - 2] + bs[bs_n - 1];
            if (bs[bs_n] > max_a) break;
            bs_n++;
          }
          rep (i, bs_n) in[bs[i] / 8] |= 1 << (bs[i] % 8);

          rep (iter, 2) {
            if (b0 > b1) {
              in[b0 / 8] ^= 1 << (b0 % 8);
              if (iter == 1) in[b1 / 8] ^= 1 << (b1 % 8);
            } else if (iter == 1) break;

            // Left
            int l = 0;
            tmp[0] = 0;
            rep (i, N) {
              if (in[A[i] / 8] & (1 << (A[i] % 8))) ++l;
              lef[i + 1] = max(lef[i + 1], tmp[i + 1] = l);
            }

            // Right
            rep (i, N) rig[i] = max(rig[i], l - tmp[i]);
          }

          // Reset
          rep (i, bs_n) in[bs[i] / 8] = 0;
        }
      }
    }
  }

  int ans = 0;
  for (int i = 0; i <= N; ++i) ans = max(ans, lef[i] + rig[i]);
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
			int S[]                   = {8, 1, 20, 3, 10};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = SubFibonacci().maxElements(vector <int>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int S[]                   = {19, 47, 50, 58, 77, 99};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = SubFibonacci().maxElements(vector <int>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int S[]                   = {512};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = SubFibonacci().maxElements(vector <int>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int S[]                   = {3, 5, 7, 10, 13, 15, 20, 90};
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = SubFibonacci().maxElements(vector <int>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int S[]                   = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
			int expected__            = 10;

			clock_t start__           = clock();
			int received__            = SubFibonacci().maxElements(vector <int>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 5: {
			int S[]                   = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = SubFibonacci().maxElements(vector <int>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
      case 6: {
        int S[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
			int expected__            = 11;

			clock_t start__           = clock();
			int received__            = SubFibonacci().maxElements(vector <int>(S, S + (sizeof S / sizeof S[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int S[]                   = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SubFibonacci().maxElements(vector <int>(S, S + (sizeof S / sizeof S[0])));
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
