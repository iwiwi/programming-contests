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

struct WebsiteRank2 {
  long long countVotes(vector <string> votes, string website);
};

typedef long long ll;

long long WebsiteRank2::countVotes(vector <string> votes, string website) {
  int N = votes.size();

  map<string, int> id;
  rep (i, N) {
    stringstream sin(votes[i]);
    string ss;
    sin >> ss;
    id[ss] = i;
  }

  ll score[60] = {};
  bool mat[60][60] = {};
  rep (i, N) {
    stringstream sin(votes[i]);
    string ss;
    sin >> ss;

    score[i] = 1;
    for (string ts; sin >> ts; ) {
      if (id.count(ts)) {
        mat[id[ts]][id[ss]] = true;
      } else {
        ++score[i];
      }
    }
  }

  bool adj[60][60];
  rep (i, N) rep (j, N) adj[i][j] = mat[i][j];
  rep (k, N) rep (i, N) rep (j, N) adj[i][j] |= adj[i][k] && adj[k][j];

  bool done[60] = {};
  rep (iter, N) {
    rep (i, N) {
      if (done[i]) goto dmp;
      rep (j, N) if (adj[j][i] && !adj[i][j] && !done[j]) goto dmp;

      { // OK
        rep (j, N) if (mat[j][i] && !adj[i][j]) score[i] += score[j];
        done[i] = true;
        break;
      }
   dmp:;
    }
  }

  if (id.count(website) == 0) return 1;
  else return score[id[website]];
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
			string votes[]            = {"C A B"};
			string website            = "C";
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string votes[]            = {"A B C D", "B C D", "C D"};
			string website            = "A";
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string votes[]            = {"A"};
			string website            = "A";
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string votes[]            = {"A B", "B A"};
			string website            = "A";
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string votes[]            = {"A B C D E F", "B A", "C B", "D B"};
			string website            = "A";
			long long expected__      = 3;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string votes[]            = {"MYSITE OTHERSITE ANOTHERSITE THIRDSITE"};
			string website            = "MYSITE";
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string votes[]            = ;
			string website            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string votes[]            = ;
			string website            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string votes[]            = ;
			string website            = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = WebsiteRank2().countVotes(vector <string>(votes, votes + (sizeof votes / sizeof votes[0])), website);
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
