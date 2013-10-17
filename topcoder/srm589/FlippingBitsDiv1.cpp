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
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define eb emplace_back
#define mp make_pair

class FlippingBitsDiv1 {
 public:
  int getmin(vector <string> S, int M);
};

int cnt1[310][2];

int solve1(const string &B, int M) {
  int N = B.length();
  int K = N / M;

  int ans = INT_MAX;
  rep (b, 1 << K) {
    int p = 0, tmp = 0;
    rep (i, M) cnt1[i][0] = cnt1[i][1] = 0;

    rep (k, K) {
      int f = (b >> k) & 1;
      if (k > 0 && f != p) ++tmp;
      p = f;
      rep (i, M) ++cnt1[i][f ^ (B[k * M + i] - '0')];
    }
    if (p) ++tmp;
    for (int i = K * M; i < N; ++i) ++cnt1[i - K * M][B[i] - '0'];

    rep (i, M) tmp += min(cnt1[i][0], cnt1[i][1]);
    ans = min(ans, tmp);
  }

  return ans;
}

int solve2(const string &B, int M) {
  int N = B.length();
  int K = N / M;

  int ans = INT_MAX;
  rep (b, 1 << M) {
    int s = 0;
    for (int i = K * M; i < N; ++i) s += ((b >> (i % M)) & 1) ^ (B[i] - '0');

    int dp[2] = {s, s + 1};
    for (int k = K - 1; k >= 0; --k) {
      int tmp[2] = {0, 0};
      rep (f, 2) rep (i, M) tmp[f] += f ^ ((b >> i) & 1) ^ (B[k * M + i] - '0');
      tmp[0] += min(dp[0], dp[1] + 1);
      tmp[1] += min(dp[1], dp[0] + 1);
      dp[0] = tmp[0];
      dp[1] = tmp[1];
    }
    ans = min({ans, dp[0], dp[1]});
  }
  return ans;
}

int FlippingBitsDiv1::getmin(vector <string> S, int M) {
  string B = accumulate(all(S), string());
  int N = B.length();

  if (N / M <= 18) return solve1(B, M);
  else return solve2(B, M);
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

	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) {
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
			string S[]                = {"00111000"};
			int M                     = 1;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string S[]                = {"101100001101"};
			int M                     = 3;
			int expected__            = 2;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string S[]                = {"11111111"};
			int M                     = 4;
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string S[]                = {"1101001000"};
			int M                     = 8;
			int expected__            = 1;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string S[]                = {"1","10","11","100","101","110"};
			int M                     = 5;
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string S[]                = {"1001011000101010001111111110111011011100110001001"};
			int M                     = 2;
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string S[]                = ;
			int M                     = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = FlippingBitsDiv1().getmin(vector <string>(S, S + (sizeof S / sizeof S[0])), M);
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
