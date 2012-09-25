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

struct ProductQuery {
  int theInput(int N, vector <int> Qfrom, vector <int> Qto, vector <int> output);
};

typedef long long ll;
const ll MOD = 1000000007;

int N, M;
int F[110], O[110];

map<pair<int, int>, ll> mem;

ll search(int i, int z) {
  if (i == N) return 1;
  if (mem.count(mp(i, z))) return mem[mp(i, z)];

  ll res;
  if (F[i] != -1) {
    bool zero = F[i] <= z;

    if (O[i] == 0) {
      res = search(i + 1, i);
      if (zero) res += (M - 1) * search(i + 1, z);
    } else {
      if (zero) res = 0;
      else res = search(i + 1, z);
    }
  } else {
    res = search(i + 1, i) + (M - 1) * search(i + 1, z);
  }

  return mem[mp(i, z)] = res % MOD;
}

ll solve(int N, int M, vector<int> F, vector<int> T, vector<int> O) {
  int inv[20];
  for (int i = 1; i < M; ++i) rep (j, M) if (i * j % M == 1) inv[i] = j;

  for (;;) {
    rep (i, F.size()) rep (j, F.size()) if (i != j) {
      if (F[i] <= F[j] && T[i] == T[j]) {
        if (F[i] == F[j]) {
          if (O[i] != O[j]) return 0;
          F.erase(F.begin() + i); T.erase(T.begin() + i); O.erase(O.begin() + i);
        } else {
          if (O[j] == 0) {
            if (O[i] != 0) return 0;
            F.erase(F.begin() + i); T.erase(T.begin() + i); O.erase(O.begin() + i);
          }
          else {
            T[i] = F[j] - 1;
            O[i] = (O[i] * inv[O[j]]) % M;
          }
        }
        goto upd;
      }
    }
    break;
 upd:;
  }

  ::N = N;
  ::M = M;
  memset(::F, -1, sizeof(::F));
  rep (i, F.size()) {
    ::F[T[i]] = F[i];
    ::O[T[i]] = O[i];
  }

  mem.clear();
  return search(0, -1);
}

int ProductQuery::theInput(int N, vector <int> Qfrom, vector <int> Qto, vector <int> output) {
  int K = Qfrom.size();
  ll ans = 1;
  int ms[2] = {2, 5};
  rep (i, 2) {
    int m = ms[i];
    vector<int> O(K);
    rep (j, K) O[j] = output[j] % m;
    (ans *= solve(N, m, Qfrom, Qto, O)) %= MOD;
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
			int N                     = 3;
			int Qfrom[]               = {0};
			int Qto[]                 = {0};
			int output[]              = {5};
			int expected__            = 100;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int N                     = 5;
			int Qfrom[]               = {0, 2, 0};
			int Qto[]                 = {1, 4, 4};
			int output[]              = {3, 4, 6};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int N                     = 3;
			int Qfrom[]               = {0, 1};
			int Qto[]                 = {1, 2};
			int output[]              = {5, 8};
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int N                     = 8;
			int Qfrom[]               = {2, 0, 3, 6};
			int Qto[]                 = {3, 7, 4, 6};
			int output[]              = {2, 0, 6, 7};
			int expected__            = 118080;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int N                     = 20;
			int Qfrom[]               = {9, 6, 2, 3, 1, 3, 12, 3, 4, 6, 10, 18, 10, 11, 15, 5};
			int Qto[]                 = {12, 12, 4, 13, 7, 14, 17, 10, 5, 13, 11, 19, 17, 14, 17, 8};
			int output[]              = {7, 5, 7, 5, 0, 5, 8, 5, 3, 5, 3, 9, 4, 1, 6, 5};
			int expected__            = 276398080;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int N                     = 58;
			int Qfrom[]               = {5, 5};
			int Qto[]                 = {8, 8};
			int output[]              = {1, 2};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int N                     = ;
			int Qfrom[]               = ;
			int Qto[]                 = ;
			int output[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int N                     = ;
			int Qfrom[]               = ;
			int Qto[]                 = ;
			int output[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int N                     = ;
			int Qfrom[]               = ;
			int Qto[]                 = ;
			int output[]              = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ProductQuery().theInput(N, vector <int>(Qfrom, Qfrom + (sizeof Qfrom / sizeof Qfrom[0])), vector <int>(Qto, Qto + (sizeof Qto / sizeof Qto[0])), vector <int>(output, output + (sizeof output / sizeof output[0])));
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
