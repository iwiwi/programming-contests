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

struct ElevenMultiples {
  int countMultiples(vector <string> pieces);
};

typedef long long ll;

const ll MOD = 1000000007;

int N, G, K;
int L[60], D[60];

int mem2[2][51][51][51][51];

ll countit(bool g, int gg, int gk, int kg, int kk) {
  if (gg == 0 && gk == 0 && kg == 0 && kk == 0) return 1;

  if (mem2[g][gg][gk][kg][kk] != -1) return mem2[g][gg][gk][kg][kk];

  ll res = 0;
  if (g == true) {
    if (gg) res += gg * countit( g, gg - 1, gk, kg, kk);
    if (kg) res += kg * countit(!g, gg, gk, kg - 1, kk);
  } else {  // g == false
    if (gk) res += gk * countit( g, gg, gk - 1, kg, kk);
    if (kk) res += kk * countit(!g, gg, gk, kg, kk - 1);
  }
  res %= MOD;
  return mem2[g][gg][gk][kg][kk] = res;
}


int mem[2][60][60][20];

inline int mod11(int x) { return (x % 11 + 11) % 11; }

int ElevenMultiples::countMultiples(vector <string> pieces) {
  N = pieces.size();
  rep (i, N) {
    string p = pieces[i];
    L[i] = p.length() % 2;
    D[i] = 0;

    reverse(all(p));
    rep (j, p.length()) D[i] += (j % 2 == 0 ? +1 : -1) * (p[j] - '0');
    D[i] %= 11;
  }

  G = K = 0;
  rep (i, N) {
    if (L[i] % 2 == 0) ++G;
    else ++K;
  }

  memset(mem, -1, sizeof(mem));
  memset(mem2, -1, sizeof(mem2));
  for (int k = N; k >= 0; --k) {
    for (int gg = 0; gg <= G; ++gg) {
      for (int kg = 0; kg <= K; ++kg) {
        rep (d, 11) {
          int &VAL = mem[k % 2][gg][kg][d];

          if (k == N) {
            if (d == 0) VAL = countit(true, gg, G - gg, kg, K - kg);
            else VAL = 0;
          }
          else {
            ll res = 0;

            // place gu-place
            {
              int tgg = gg, tkg = kg;
              if (L[k] == 0) tgg += 1;
              else tkg += 1;
              res += mem[(k + 1) % 2][tgg][tkg][mod11(d + D[k])];
            }
            // place ki-place
            {
              res += mem[(k + 1) % 2][gg][kg][mod11(d - D[k])];
            }

            res %= MOD;
            VAL = res;
          }
        }
      }
    }
  }
  return mem[0][0][0][0];
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
			string pieces[]           = {"58", "2012", "123"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string pieces[]           = {"1", "1111", "1", "11"};
			int expected__            = 24;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string pieces[]           = {"43925486943738659795389387498953274"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string pieces[]           = {"983", "4654", "98", "3269", "861", "30981"};
			int expected__            = 96;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string pieces[]           = {"193", "8819", "40676", "97625892", "5719", "45515667", "32598836", "70559374", "38756", "724",
"93391", "942068", "506", "901150", "874", "895567", "7560480", "7427691", "799450", "85127"};
			int expected__            = 537147821;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string pieces[]           = {"687045939630", "997856158148599044", "2014910234712225061", "9658113323175370226", "1584118137",
"67925153345598920", "6960366756", "863413844386808834", "799302243562410012", "44481835751",
"8004606814733183", "19623906615609", "23859998326058162", "461385591582", "9261878982390119",
"1569373294276", "318106951168934", "65389049931", "12791173342", "507877942026",
"3947173045690", "472425746178910", "524552931853595", "40771812249667850232", "563988469071932",
"28147819070", "797007158858587", "5716177008624223", "387565700495309324", "4716621063133318"}
;
			int expected__            = 814880650;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string pieces[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string pieces[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string pieces[]           = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ElevenMultiples().countMultiples(vector <string>(pieces, pieces + (sizeof pieces / sizeof pieces[0])));
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
