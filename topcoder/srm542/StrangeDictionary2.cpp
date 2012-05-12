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

struct StrangeDictionary2 {
  vector <double> getProbabilities(vector <string> words);
};

int N, L;
vector<string> W;
vector<double> mem[(1 << 16) + 10];

const vector<double> &search(int b) {
  if (!mem[b].empty()) return mem[b];

  if (0 == (b & (b - 1))) {
    mem[b].resize(N);
    mem[b][__builtin_ctz(b)] = 1.0;
    return mem[b];
  }

  mem[b].resize(N);
  int d = 0;
  rep (p, L) {
    int c = INT_MAX, tb = 0;
    rep (i, N) if (b & (1 << i)) {
      int tc = W[i][p];
      if (tc < c) { c = tc; tb = 0; }
      if (tc == c) tb |= 1 << i;
    }

    if (tb == b) continue;
    const vector<double> &t = search(tb);
    rep (i, N) mem[b][i] += t[i];
    ++d;
  }
  rep (i, N) mem[b][i] /= d;
  return mem[b];
}

vector <double> StrangeDictionary2::getProbabilities(vector <string> words) {
  W = words;
  N = words.size();
  L = words[0].length();

  rep (b, 1 << N) mem[b].clear();
  return search((1 << N) - 1);
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

	static const double MAX_DOUBLE_ERROR = 1e-9; static bool topcoder_fequ(double expected, double result) { if (isnan(expected)) { return isnan(result); } else if (isinf(expected)) { if (expected > 0) { return result > 0 && isinf(result); } else { return result < 0 && isinf(result); } } else if (isnan(result) || isinf(result)) { return false; } else if (fabs(result - expected) < MAX_DOUBLE_ERROR) { return true; } else { double mmin = min(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); double mmax = max(expected * (1.0 - MAX_DOUBLE_ERROR), expected * (1.0 + MAX_DOUBLE_ERROR)); return result > mmin && result < mmax; } }
	double moj_relative_error(double expected, double result) { if (isnan(expected) || isinf(expected) || isnan(result) || isinf(result) || expected == 0) return 0; return fabs(result-expected) / fabs(expected); }
	static bool topcoder_fequ(const vector<double> &a, const vector<double> &b) { if (a.size() != b.size()) return false; for (size_t i=0; i<a.size(); ++i) if (!topcoder_fequ(a[i], b[i])) return false; return true; }
	double moj_relative_error(const vector<double> &expected, const vector<double> &result) { double ret = 0.0; for (size_t i=0; i<expected.size(); ++i) { ret = max(ret, moj_relative_error(expected[i], result[i])); } return ret; }

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <double> &expected, const vector <double> &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (topcoder_fequ(expected, received)) {
			verdict = "PASSED";
			double rerr = moj_relative_error(expected, received);
			if (rerr > 0) {
				sprintf(buf, "relative error %.3e", rerr);
				info.push_back(buf);
			}
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
			string words[]            = {"hardesttestever"};
			double expected__[]       = {1.0 };

			clock_t start__           = clock();
			vector <double> received__ = StrangeDictionary2().getProbabilities(vector <string>(words, words + (sizeof words / sizeof words[0])));
			return verify_case(casenum__, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string words[]            = {"ab", "ba"};
			double expected__[]       = {0.5, 0.5 };

			clock_t start__           = clock();
			vector <double> received__ = StrangeDictionary2().getProbabilities(vector <string>(words, words + (sizeof words / sizeof words[0])));
			return verify_case(casenum__, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string words[]            = {"aza", "aab", "bba"};
			double expected__[]       = {0.3333333333333333, 0.5, 0.16666666666666666 };

			clock_t start__           = clock();
			vector <double> received__ = StrangeDictionary2().getProbabilities(vector <string>(words, words + (sizeof words / sizeof words[0])));
			return verify_case(casenum__, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string words[]            = {"abababab", "babababa", "acacacac", "cacacaca", "bcbcbcbc", "cbcbcbcb"};
			double expected__[]       = {0.5, 0.5, 0.0, 0.0, 0.0, 0.0 };

			clock_t start__           = clock();
			vector <double> received__ = StrangeDictionary2().getProbabilities(vector <string>(words, words + (sizeof words / sizeof words[0])));
			return verify_case(casenum__, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			string words[]            = ;
			double expected__[]       = ;

			clock_t start__           = clock();
			vector <double> received__ = StrangeDictionary2().getProbabilities(vector <string>(words, words + (sizeof words / sizeof words[0])));
			return verify_case(casenum__, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 5: {
			string words[]            = ;
			double expected__[]       = ;

			clock_t start__           = clock();
			vector <double> received__ = StrangeDictionary2().getProbabilities(vector <string>(words, words + (sizeof words / sizeof words[0])));
			return verify_case(casenum__, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			string words[]            = ;
			double expected__[]       = ;

			clock_t start__           = clock();
			vector <double> received__ = StrangeDictionary2().getProbabilities(vector <string>(words, words + (sizeof words / sizeof words[0])));
			return verify_case(casenum__, vector <double>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
