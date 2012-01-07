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

typedef long long ll;

struct MagicMatchesGame {
  long long minimumArea(vector <int> matches, vector <int> red, vector <int> blue);
};


typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)
#define INV(x) (x)
#define NOR(x) ((x) % 2)

int rank(mat_t A) {
  int n = A[0].size(), m = A.size(), i, j, k, r = 0;
  for (i = 0; i < n && r < m; i++) {
    int piv = r;
    for (j = r + 1; j < m; j++)
      if (ABS(A[j][i]) > ABS(A[piv][i])) piv = j;
    swap(A[r], A[piv]);

    if (IS0((A[r][i]))) continue;

    for (j = r + 1; j < m; j++)
      for (k = n - 1; k >= i; k--)
        A[j][k] = NOR(A[j][k] - NOR(NOR(A[r][k] * A[j][i]) * INV(A[r][i])));

    r++;
  }
  return r;
}

const int Z = 20;

vector<int> R, B;
double D;

bool cmp(int i, int j) {
  return R[i] + D * B[i] < R[j] + D * B[j];
}

long long MagicMatchesGame::minimumArea(vector <int> matches, vector <int> red, vector <int> blue) {
  int N = matches.size();
  R = red;
  B = blue;

  vector<double> ds;
  rep (i, N) rep (j, i) {
    if (B[i] == B[j]) continue;
    ds.pb((R[j] - R[i]) / double(B[i] - B[j]));
  }
  ds.pb(-1E10);
  ds.pb(+1E10);
  sort(all(ds));
  ds.erase(unique(all(ds)), ds.end());

  pair<int, ll> res = mp(INT_MIN, 0);
  map<vector<int>, int> rank_mem;

  rep (i, ds.size() - 1) {
    D = (ds[i] + ds[i + 1]) / 2.0;

    vector<int> ord(N);
    rep (i, N) ord[i] = i;
    sort(all(ord), cmp);

    vector<int> sel;
    rep (j, ord.size()) {
      sel.pb(ord[j]);
      int r;

      if (rank_mem.count(sel)) r = rank_mem[sel];
      else {
        mat_t A;
        rep (k, sel.size()) {
          A.pb(vec_t(Z));
          rep (z, Z) A.back()[z] = 1 & (matches[sel[k]] >> z);
        }
        r = rank_mem[sel] = rank(A);
      }
      if (r < sel.size()) sel.pop_back();
    }

    ll rs = 0, bs = 0;
    rep (j, sel.size()) {
      rs += R[sel[j]];
      bs += B[sel[j]];
    }

    res = max(res, mp((int)sel.size(), -rs * bs));
  }

  return -res.second;
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
			int matches[]             = {1,1};
			int red[]                 = {5,6};
			int blue[]                = {5,4};
			long long expected__      = 24;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int matches[]             = {1,2,3};
			int red[]                 = {4,5,6};
			int blue[]                = {9,8,7};
			long long expected__      = 153;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int matches[]             = {1,2,3,4,5,6,7};
			int red[]                 = {20,11,12,23,21,52,65};
			int blue[]                = {23,10,31,18,13,10,13};
			long long expected__      = 2255;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int matches[]             = {1037, 2220, 6908, 4179, 4243, 4396, 679, 179, 163, 818, 9767, 5199, 3973, 2065, 8060};
			int red[]                 = {724, 123, 178, 262, 628, 981, 882, 814, 752, 495, 906, 904, 265, 329, 470};
			int blue[]                = {664, 134, 254, 798, 290, 753, 941, 264, 200, 369, 547, 628, 120, 833, 928};
			long long expected__      = 42628758;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int matches[]             = {10095, 16913, 10198, 12528, 15264, 19224, 16442, 14595, 12060, 11858, 17900, 19304, 10619, 15818, 11670};
			int red[]                 = {9419, 9448, 9722, 9030, 9591, 9451, 9871, 9124, 9012, 9047, 9024, 9984, 9163, 9852, 9203};
			int blue[]                = {9706, 9436, 9454, 9585, 9592, 9145, 9356, 9797, 9523, 9032, 9178, 9472, 9594, 9637, 9256};
			long long expected__      = 17324432487LL;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int matches[]             = {1000000};
			int red[]                 = {10000};
			int blue[]                = {10000};
			long long expected__      = 100000000;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int matches[]             = ;
			int red[]                 = ;
			int blue[]                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int matches[]             = ;
			int red[]                 = ;
			int blue[]                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int matches[]             = ;
			int red[]                 = ;
			int blue[]                = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = MagicMatchesGame().minimumArea(vector <int>(matches, matches + (sizeof matches / sizeof matches[0])), vector <int>(red, red + (sizeof red / sizeof red[0])), vector <int>(blue, blue + (sizeof blue / sizeof blue[0])));
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
