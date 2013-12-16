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
#include <tuple>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define eb emplace_back
#define mp make_pair

typedef long long ll;
const ll INF = 150000000000000;

double get_time_sec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

class JumpingOnPoints {
 public:
  long long sumOfDistances(int N, int S, vector <int> params);
};

int N;

struct point_t {
  int x, y, p, t;
  ll d;
} ps[60010];

inline int ABS(int x) { return x >= 0 ? x : -x; }

/*
#define UPDATE(X) {                                         \
    point_t &q = ps[i + (X)];                               \
    bool b = (ABS(q.x - cx) <= cp) | (ABS(q.y - cy) <= cp); \
    int t = max(q.t, ct);                                   \
    ll d = cd + t;                                          \
    q.d = (b & (d < q.d)) ? d : q.d;                        \
  }
*/

#define UPDATE(X) {                                         \
    point_t &q = ps[i + (X)];                               \
    if ((ABS(q.x - cx) <= cp) || (ABS(q.y - cy) <= cp)) {   \
      int t = max(q.t, ct);                                 \
      ll d = cd + t;                                        \
      q.d = d < q.d ? d : q.d;                              \
    }                                                       \
  }

long long JumpingOnPoints::sumOfDistances(int N, int S, vector <int> params) {
  double time_start = get_time_sec();
  int original_N = N;

  ps[0].x = params[0];
  ps[0].y = params[4];
  ps[0].p = params[8];
  ps[0].t = params[12];
  for (int i = 1; i < N; i++) {
    ps[i].x = (ps[i - 1].x * (ll)params[1] + params[2]) % params[3];
    ps[i].y = (ps[i - 1].y * (ll)params[5] + params[6]) % params[7];
    ps[i].p = (ps[i - 1].p * (ll)params[9] + params[10]) % params[11];
    ps[i].t = (ps[i - 1].t * (ll)params[13] + params[14]) % params[15];
  }

  rep (i, N) ps[i].d = INF;
  ps[S].d = 0;

  while (N > 0) {
    if (get_time_sec() - time_start > 9.8) break;

    int ci = -1;
    ll cd = INF;
    rep (i, N) {
      ll d = ps[i].d;
      bool b = cd <= d;
      ci = b ? ci : i;
      cd = b ? cd : d;
    }
    if (ci == -1) break;

    int cx = ps[ci].x, cy = ps[ci].y, cp = ps[ci].p, ct = ps[ci].t;
    {
      int i = 0;
      for (; i + 8 <= N; i += 8) {
        UPDATE(0);
        UPDATE(1);
        UPDATE(2);
        UPDATE(3);
        UPDATE(4);
        UPDATE(5);
        UPDATE(6);
        UPDATE(7);
      }
      for (; i < N; ++i) {
        UPDATE(0);
      }
    }

    swap(ps[ci], ps[N - 1]);
    --N;
  }

  ll ans = 0;
  rep (i, original_N) ans += ps[i].d;
  return ans;
}















// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
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
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}

	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) {
		std::cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;

		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl;
			std::cerr << "    Received: " << received << std::endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int N                     = 2;
			int S                     = 0;
			int params[]              = {0, 0, 5, 100, 0, 0, 5, 100, 0, 0, 10, 100, 1, 1, 0, 100};
			long long expected__      = 150000000000000LL;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 3;
			int S                     = 1;
			int params[]              = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
			long long expected__      = 18;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 4;
			int S                     = 0;
			int params[]              = {0, 1, 1, 100, 0, 1, 1, 100, 1, 1, 0, 100, 0, 0, 1, 2};
			long long expected__      = 6;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 60000;
			int S                     = 0;
			int params[]              = {0, 1, 1, 1000000000, 0, 1, 1, 1000000000, 1, 1, 0, 1000000000, 999999999, 1, 0, 1000000000};
			long long expected__      = 1799969998200030000LL;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 6;
			int S                     = 0;
			int params[]              = {0, 1, 5, 15, 0, 1, 5, 10, 0, 0, 0, 1,1,1,1,3};
			long long expected__      = 8;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 1000;
			int S                     = 286;
			int params[]              = {11111, 11111, 111111, 11111111, 12121, 12111, 13131, 11111111, 13, 14444, 44312, 222211, 13131, 328655, 11373, 999999993};
			long long expected__      = 738940004832LL;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int S                     = ;
			int params[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int S                     = ;
			int params[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int S                     = ;
			int params[]              = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = JumpingOnPoints().sumOfDistances(N, S, vector <int>(params, params + (sizeof params / sizeof params[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
