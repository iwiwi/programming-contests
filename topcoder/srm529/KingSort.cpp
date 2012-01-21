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

struct KingSort {
  vector <string> getSortedList(vector <string> kings);
};

int parse_roman(string s) {
  const char *TOKENS[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
  const int VALUES[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  int res = 0, p = 0;
  rep (i, sizeof(TOKENS) / sizeof(TOKENS[0])) {
    const char *t = TOKENS[i];
    int tl = strlen(t);
    while (s.compare(p, tl, t) == 0) {
      p += tl;
      res += VALUES[i];
    }
  }
  assert(p == (int)s.length());
  return res;
}


vector <string> KingSort::getSortedList(vector <string> kings) {
  vector<pair<pair<string, int>, string> > vs(kings.size());
  rep (i, kings.size()) {
    string s = kings[i];
    string a = s.substr(0, s.find(' '));
    string b = s.substr(s.find(' ') + 1);
    vs[i] = mp(mp(a, parse_roman(b)), s);
  }
  sort(all(vs));
  vector<string> res(kings.size());
  rep (i, vs.size()) res[i] = vs[i].second;
  return res;
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

	template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }
	template<> ostream& operator<<(ostream &os, const vector<string> &v) { os << "{"; for (vector<string>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " \"" << *vi << "\""; } os << " }"; return os; }

	int verify_case(int casenum, const vector <string> &expected, const vector <string> &received, clock_t elapsed) {
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
			string kings[]            = {"Louis IX", "Louis VIII"};
			string expected__[]       = {"Louis VIII", "Louis IX" };

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			string kings[]            = {"Louis IX", "Philippe II"};
			string expected__[]       = {"Louis IX", "Philippe II" };

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			string kings[]            = {"Richard III", "Richard I", "Richard II"};
			string expected__[]       = {"Richard I", "Richard II", "Richard III" };

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			string kings[]            = {"John X", "John I", "John L", "John V"};
			string expected__[]       = {"John I", "John V", "John X", "John L" };

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			string kings[]            = {"Philippe VI", "Jean II", "Charles V", "Charles VI", "Charles VII", "Louis XI"};
			string expected__[]       = {"Charles V", "Charles VI", "Charles VII", "Jean II", "Louis XI", "Philippe VI" };

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 5: {
			string kings[]            = {"Philippe II", "Philip II"};
			string expected__[]       = {"Philip II", "Philippe II" };

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string kings[]            = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			string kings[]            = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 8: {
			string kings[]            = ;
			string expected__[]       = ;

			clock_t start__           = clock();
			vector <string> received__ = KingSort().getSortedList(vector <string>(kings, kings + (sizeof kings / sizeof kings[0])));
			return verify_case(casenum__, vector <string>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
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
