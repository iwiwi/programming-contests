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

struct EllysString {
  int theMin(vector <string> s, vector <string> t);
};

const int A = 26;

int L;
int S[3000], T[3000];

int mem[3000][30][30];

int search(int p, int s0 = A, int t0 = A) {
  if (p == L) return 0;

  if (s0 == A) s0 = S[p];
  if (t0 == A) t0 = T[p];

  if (mem[p][s0][t0] != -1) return mem[p][s0][t0];

  int res = (s0 == t0 ? 0 : 1) + search(p + 1);

  if (p + 1 < L) {
    int s1 = S[p + 1], t1 = T[p + 1];
    if (s1 == t0) res = min(res, 1 + search(p + 1, s0, t1));
    if (s0 == t1) res = min(res, 1 + search(p + 1, s1, t0));
  }

  return mem[p][s0][t0] = res;
}

int EllysString::theMin(vector <string> s, vector <string> t) {
  string ss = accumulate(all(s), string());
  string ts = accumulate(all(t), string());
  L = ss.length();
  rep (i, L) {
    S[i] = ss[i] - 'a';
    T[i] = ts[i] - 'a';
  }

  memset(mem, -1, sizeof(mem));
  return search(0);
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
			string s[]                = {"usagi"};
			string t[]                = {"unagi"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string s[]                = {"unagi"};
			string t[]                = {"nugai"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string s[]                = {"ellys", "string"};
			string t[]                = {"e", "ll", "ysst", "ring"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string s[]                = {"fox"};
			string t[]                = {"xfo"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string s[]                = {"salmon"};
			string t[]                = {"camlon"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string s[]                = {"boajxuidva"};
			string t[]                = {"jcayduvida"};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			string s[]                = {"vykdnujyezbcbmnatipqfuxqmgkvtn"};
			string t[]                = {"qokbqyujeqcbwsinatupqfoegmvkdz"};
			int expected__            = 22;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 7: {
			string s[]                = ;
			string t[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string s[]                = ;
			string t[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			string s[]                = ;
			string t[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EllysString().theMin(vector <string>(s, s + (sizeof s / sizeof s[0])), vector <string>(t, t + (sizeof t / sizeof t[0])));
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
