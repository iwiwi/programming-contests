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

struct YamanoteLine {
  long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2);
};

typedef long long ll;
typedef pair<ll, ll> pll;
const ll INF = 1LL << 45;

int N;
vector<pair<ll, pll> > adj[60];

pll add(pll a, pll b) { return mp(a.first + b.first, a.second + b.second); }

pair<bool, ll> check() {
  pll pot[60] = {};

  bool update = false;
  pll update_p;
  rep (iter, N * 2) {
    update = false;

    rep (v, N) rep (i, adj[v].size()) {
      int w = adj[v][i].first;
      pll tp = add(pot[v], adj[v][i].second);
      if (tp.first < pot[w].first) {
        pot[w] = tp;
        update = true;
        update_p = tp;
      }
    }
  }

  if (update) return mp(false, update_p.second);  // negative loop
  else return mp(true, 0);
}

long long YamanoteLine::howMany(int n,
                                vector <int> s1, vector <int> t1, vector <int> l1,
                                vector <int> s2, vector <int> t2, vector <int> l2) {
  N = n;

  // maximize
  ll ma;
  {
    ll lb = 0, ub = INF;
    while (ub - lb > 1) {
      ll L = (lb + ub) / 2;
      rep (i, N) adj[i].clear();

      rep (i, N - 1) adj[i + 1].pb(mp(i, mp(-1, 0)));
      adj[0].pb(mp(N - 1, mp(L - 1, 1)));

      rep (i, s1.size()) adj[t1[i]].pb(mp(s1[i], mp(-l1[i] + (s1[i] > t1[i] ? L : 0), (s1[i] > t1[i]) ? +1 : 0)));
      rep (i, s2.size()) adj[s2[i]].pb(mp(t2[i], mp( l2[i] - (s2[i] > t2[i] ? L : 0), (s2[i] > t2[i]) ? -1 : 0)));

      pair<bool, ll> res = check();
      if (res.first || res.second >= 0) lb = L;
      else ub = L;
    }
    printf("%lld %lld\n", lb, ub);
    ma = lb;
    if (ub == INF) return -1;
  }

  // minimize
  ll mi;
  {
    ll lb = 0, ub = INF;
    while (ub - lb > 1) {
      ll L = (lb + ub) / 2;
      rep (i, N) adj[i].clear();

      rep (i, N - 1) adj[i + 1].pb(mp(i, mp(-1, 0)));
      adj[0].pb(mp(N - 1, mp(L - 1, 1)));

      rep (i, s1.size()) adj[t1[i]].pb(mp(s1[i], mp(-l1[i] + (s1[i] > t1[i] ? L : 0), (s1[i] > t1[i]) ? +1 : 0)));
      rep (i, s2.size()) adj[s2[i]].pb(mp(t2[i], mp( l2[i] - (s2[i] > t2[i] ? L : 0), (s2[i] > t2[i]) ? -1 : 0)));

      pair<bool, ll> res = check();
      if (res.first || res.second < 0) ub = L;
      else lb = L;
    }
    printf("%lld %lld\n", lb, ub);
    mi = ub;
  }

  return max(0LL, ma - mi + 1);
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
			int n                     = 3;
			int s1[]                  = {};
			int t1[]                  = {};
			int l1[]                  = {};
			int s2[]                  = {0,1,2};
			int t2[]                  = {1,2,0};
			int l2[]                  = {1,1,1};
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int n                     = 3;
			int s1[]                  = {};
			int t1[]                  = {};
			int l1[]                  = {};
			int s2[]                  = {0,1,2};
			int t2[]                  = {1,2,0};
			int l2[]                  = {2,2,2};
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int n                     = 3;
			int s1[]                  = {};
			int t1[]                  = {};
			int l1[]                  = {};
			int s2[]                  = {0,1,2};
			int t2[]                  = {2,0,1};
			int l2[]                  = {3,3,3};
			long long expected__      = 2;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int n                     = 4;
			int s1[]                  = {0,1,2,3};
			int t1[]                  = {2,3,0,1};
			int l1[]                  = {3,4,4,3};
			int s2[]                  = {1,3};
			int t2[]                  = {3,1};
			int l2[]                  = {5,5};
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int n                     = 4;
			int s1[]                  = {0,2};
			int t1[]                  = {2,0};
			int l1[]                  = {5,5};
			int s2[]                  = {1,3};
			int t2[]                  = {3,1};
			int l2[]                  = {4,4};
			long long expected__      = 0;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int n                     = 5;
			int s1[]                  = {};
			int t1[]                  = {};
			int l1[]                  = {};
			int s2[]                  = {0,2};
			int t2[]                  = {2,4};
			int l2[]                  = {2,2};
			long long expected__      = -1;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 6: {
			int n                     = 10;
			int s1[]                  = {5,7,2,3,9,4,6,0,4,2};
			int t1[]                  = {0,8,3,9,8,0,8,7,1,7};
			int l1[]                  = {61,54,20,64,25,73,83,79,86,56};
			int s2[]                  = {4,5,4,0,8,3,8,5,5,9};
			int t2[]                  = {5,2,0,1,1,4,7,6,8,3};
			int l2[]                  = {1951,6102,3625,5737,1590,1228,9234,1342,9060,1008};
			long long expected__      = 5726;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

      case 7: {
			int n                     = 6;
			int s1[]                  = {3, 4, 2, 5, 5, 2, 3, 1, 4, 0, 2, 0, 1, 4, 0, 3, 2};
			int t1[]                  = {1, 1, 4, 1, 3, 0, 1, 5, 3, 5, 5, 4, 0, 1, 1, 5, 0};
			int l1[]                  = {8530994, 4587123, 6083110, 3839980, 7162189, 8843968, 8530973, 8013111, 7909353, 9839410, 6830312, 9092310, 10026864, 4587159, 1826302, 4691014, 8843930};
			int s2[]                  = {2, 5, 2, 2, 2, 5, 0, 3, 3, 3, 1, 1, 2, 3, 2, 2, 4, 2, 3, 4, 4};
			int t2[]                  = {3, 1, 3, 1, 1, 2, 5, 0, 4, 2, 2, 5, 1, 1, 3, 5, 5, 5, 5, 1, 2};
			int l2[]                  = {2139308, 3840071, 2139277, 10670316, 10670333, 5022867, 9839475, 6704635, 3943820, 9713845, 1182894, 8013104, 10670249, 8530943, 2139306, 6830304, 747223, 6830223, 4691032, 4587130, 5770075};
			long long expected__      = 36;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
/*      case 8: {
			int n                     = ;
			int s1[]                  = ;
			int t1[]                  = ;
			int l1[]                  = ;
			int s2[]                  = ;
			int t2[]                  = ;
			int l2[]                  = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 9: {
			int n                     = ;
			int s1[]                  = ;
			int t1[]                  = ;
			int l1[]                  = ;
			int s2[]                  = ;
			int t2[]                  = ;
			int l2[]                  = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = YamanoteLine().howMany(n, vector <int>(s1, s1 + (sizeof s1 / sizeof s1[0])), vector <int>(t1, t1 + (sizeof t1 / sizeof t1[0])), vector <int>(l1, l1 + (sizeof l1 / sizeof l1[0])), vector <int>(s2, s2 + (sizeof s2 / sizeof s2[0])), vector <int>(t2, t2 + (sizeof t2 / sizeof t2[0])), vector <int>(l2, l2 + (sizeof l2 / sizeof l2[0])));
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
