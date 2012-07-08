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
#include <complex>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct MaximalTriangle {
  int howMany(int n, int z);
};

typedef long long ll;
typedef complex<double> p_t;
const double EPS = 1E-10;

double det(const p_t &p, const p_t &q) { return imag(conj(p) * q); }

double heron(double a, double b, double c) {
  double s = (a + b + c) / 2.0;
  return sqrt(s * (s - a) * (s - b) * (s - c));
}

double area(const p_t &a, const p_t &b) {
  return fabs(det(a, b)) / 2.0;
}

int N, Z;
p_t P[500];
double A[500][500], B[500];

ll trivial[500], dp[500];
double S;

void solve(int K) {
  dp[1] = 1;
  for (int k = 2; k <= K; ++k) {
    if (A[k][k / 2] < S) {
      dp[k] = trivial[k];
      continue;
    }

    ll ans = 0;
    for (int i = 1; i < (k + 1) / 2; ++i) {
      if (A[k][i] >= S) break;
      (ans += dp[i] * dp[k - i]) %= Z;
    }
    (ans *= 2) %= Z;
    if (k % 2 == 0 && A[k][k / 2] < S) (ans += dp[k / 2] * dp[k / 2]) %= Z;
    dp[k] = ans;
  }
}

int MaximalTriangle::howMany(int n, int z) {
  N = n;
  Z = z;
  rep (i, N) P[i] = polar(1.0, 2 * M_PI * i / N);

  double total = N * area(P[0], P[1]);

  trivial[1] = 1;
  for (int k = 2; k < N; ++k) {
    trivial[k] = 0;
    for (int i = 1; i < k; ++i) {
      A[k][i] = area(P[k] - P[0], P[i] - P[0]) + EPS;
      (trivial[k] += trivial[i] * trivial[k - i]) %= Z;
    }
    B[k] = k * area(P[0], P[1]) - area(P[0], P[k]);
  }

  map<vector<int>, int> ma;
  for (int a = 1; a < N; ++a) {
    for (int b = 1; a + b < N; ++b) {
      vector<int> v(3);
      v[0] = a;
      v[1] = b;
      v[2] = N - a - b;
      sort(all(v));
      ma[v] += N - a - b;
    }
  }

  ll ans = 0;
  tr (ma, ite) {
    const vector<int> &v = ite->first;
    S = heron(abs(P[v[0]] - P[0]), abs(P[v[1]] - P[0]), abs(P[v[2]] - P[0]));
    if (S * (N - 2) < total - EPS) continue;

    solve(v[2]);

    ll t = ite->second;
    rep (i, 3) (t *= dp[v[i]]) %= Z;
    (ans += t) %= Z;
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
			int n                     = 4;
			int z                     = 1000000000;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 5;
			int z                     = 100;
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 6;
			int z                     = 1000003;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 10;
			int z                     = 1000000000;
			int expected__            = 1010;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 15;
			int z                     = 1000000000;
			int expected__            = 714340;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 100;
			int z                     = 987654321;
			int expected__            = 308571232;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 6: {
			int n                     = 444;
			int z                     = 1000000000;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 7: {
			int n                     = ;
			int z                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int n                     = ;
			int z                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = MaximalTriangle().howMany(n, z);
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
