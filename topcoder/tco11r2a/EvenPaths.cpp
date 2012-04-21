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

struct EvenPaths {
  long long theCount(vector <string> maze, string rooms);
};


// graph preprocessing
vector<vector<ll> > shrink(vector<vector<ll> > adj, int x) {
  int N = adj.size();
  vector<vector<ll> > res(N - 1, vector<ll>(N - 1));

  rep (i, N) if (i != x) {
    rep (j, N) if (j != x) {
      int ti = i > x ? i - 1 : i;
      int tj = j > x ? j - 1 : j;
      res[ti][tj] = adj[i][j] + adj[i][x] * adj[x][j];
    }
  }
  return res;
}

int N;
vector<vector<ll> > adj;

// topological sort
vector<int> ord;
bool vis[60];

void ts(int v) {
  if (vis[v]) return;
  vis[v] = true;
  rep (w, N) if (adj[v][w] > 0) ts(w);
  ord.pb(v);
}


// solve half
vector<ll> doit(vector<int> vs, vector<vector<ll> > adj) {
  int n = vs.size();
  vector<ll> ans(1 << n);

  rep (b, 1 << (n - 1)) {
    int x = 1;
    for (int i = 1; i < n; ++i) {
      if (b & (1 << (i - 1))) continue;  // obstacle!
      rep (j, i) x ^= (((x >> j) & 1) & (adj[vs[j]][vs[i]] & 1)) << i;
    }
    ++ans[x];
  }
  return ans;
}


ll cmb(ll n, ll k) {
  ll res = 1;
  for (int i = 0; i < k; ++i) res = res * (n - i) / (i + 1);
  return res;
}

void zeta(int n, vector<ll> &a) {
  rep (i, n) {
    rep (b, 1 << n) {
      if (0 == (b & (1 << i))) a[b] += a[b | (1 << i)];
    }
  }
}

long long EvenPaths::theCount(vector <string> maze, string rooms) {
  ll total = 1LL << count(all(rooms), '?');

  // preprocess
  rooms[0] = '?';
  rooms[1] = '?';
  int n = maze.size();
  vector<vector<ll> > adj(n, vector<ll>(n));
  rep (i, n) rep (j, n) adj[i][j] = maze[i][j] == 'Y' ? 1 : 0;
  rep (i, rooms.size()) {
    if (rooms[i] == '-') {
      adj = shrink(adj, i);
      rooms.erase(rooms.begin() + i);
      --i;
    }
  }
  ::adj = adj;
  ::N = adj.size();


  // topological sort
  memset(vis, 0, sizeof(vis));
  ord.clear();
  ts(0);
  reverse(all(ord));
  while (!ord.empty() && ord.back() != 1) ord.pop_back();
  if (ord.empty()) return total;

  int z = count(all(rooms), '?') - ord.size();


  // split and list
  int ln = ord.size() / 2, rn = ord.size() - ln;
  vector<int> ls(ord.begin(), ord.begin() + ln), rs(ord.begin() + ln, ord.end());

  reverse(all(rs));

  vector<vector<ll> > rev(N, vector<ll>(N));
  rep (i, N) rep (j, N) rev[i][j] = adj[j][i];

  vector<ll> lc = doit(ls, adj);
  vector<ll> rc = doit(rs, rev);

  vector<ll> mc(1 << rn);
  rep (b, 1 << ln) {
    int tb = 0;
    rep (i, ln) rep (j, rn) tb ^= (((b >> i) & 1) & (adj[ls[i]][rs[j]] & 1)) << j;
    mc[tb] += lc[b];
  }


  // count
  ll ans = 0;

  vector<ll> w2(rn + 1);
  rep (i, rn + 1) {
    w2[i] = i % 2;
    rep (j, i) w2[i] -= w2[j] * cmb(i, j);
  }

  zeta(rn, rc);
  zeta(rn, mc);
  rep (b, 1 << rn) ans += w2[__builtin_popcount(b)] * mc[b] * rc[b];

  cout << total << endl;
  cout << ans << endl;
  return total - ans * (1LL << z);
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
			string maze[]             = {"NYY", "NNN", "NYN"};
			string rooms              = "--?";
			long long expected__      = 1;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string maze[]             = {"NYYNN", "NNNNY", "NYNNN", "YNNNN", "NNNNN"};
			string rooms              = "--???";
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string maze[]             = {"NNNNN", "NNYYN", "YNNNY", "NNNNN", "NNNNN"};
			string rooms              = "--???";
			long long expected__      = 8;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string maze[]             = {"NNYNYNNY", "NNNNNNNN", "NNNNNYYY", "NYNNNNNN", "NNNNNNNN", "NYNYNNNN", "NYNNYNNN", "NNNYYNYN"};
			string rooms              = "----???-";
			long long expected__      = 4;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string maze[]             = {"NYNNNNYYYYYYYNYNYNNN",
"NNNNNNNNNNNNNNNNNNNN",
"NNNNYNYYNYNNNNYNYNYN",
"NNNNNNNNNNNNNNNNYYNN",
"NNNYNNNNNNYYNNYYNNNY",
"NYNNYNYYYYNYNYNYYYNN",
"NNNYYNNNYNYYNNYNYYNY",
"NNNYNNYNYNYNYNYYYYYN",
"NYNYYNNNNNNYYNNYYNNN",
"NNNNNNNNNNYNYNNNYYNN",
"NYNNNNNNNNNYNNNNYNNY",
"NNNNNNNNNNNNNNNNNNNN",
"NNNYNNNNNNNNNNYNNYNN",
"NNNYYNYNNYNNNNNYYYNN",
"NNNNNNNNNNNNNNNNNYNN",
"NYNYNNNNNNNNNNYNNNNN",
"NNNNNNNNNNNNNNNNNNNN",
"NYNNNNNNNNNNNNNNNNNN",
"NYNNNNNNNYNYYNNYYYNN",
"NYNNNNNNNNNNYNYNYYNN"};
			string rooms              = "---??-??--??--?-?---";
			long long expected__      = 136;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string maze[]             = {"NNYNNNNYNYYYNYNNYYNYNNYYNYNNNYYYNNNNYNNNYYNNNNYNNY",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NNNYNNNNNYNNNYNNYNNYNNYYYNYNYNNYYYNYNYYNYYNNNNYNNN",
"NNNNNNNNNYNNNNYNNNNNNNNYNNNNYNNNNNNNNNNYNNNNNNNNYN",
"NYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NYNNYNNNNNNNNNYNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNYNNN",
"NNNYYNNYNNYNNYNYNNNYYNYYNNNNYNNNYNNNNNYYNYNYYNNYYN",
"NYNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNYN",
"NYNYYNNYNYNYNNNNNNNNNNNNNNNNNYNNNNNNNNNYNNNNNYYNNN",
"NNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNYNNYN",
"NYNNYNNYNYNNNNYNNNNNNYNNNNNNNNNNNNNNNNNNNYNNNNNNNN",
"NYNNNNNYNNNNNNNNNNNYNNNYNNNNYNNNNNNNNNNNNNNNNNYNNN",
"NYNNNYNYNYNNNNNNNNYYNYYNNNNYNNNNNNYNNYYNNNNNYNYNYN",
"NNNNYYNNNNNNNNYNNYNYYYNYNNNNNNNYNNYNNNNNYNNNNNNYNN",
"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYN",
"NYNYNYNNNYYNNNYNNNNNYYYNYNNNNYNNNNNNNYNYNYNNNYYNYN",
"NNNNYYNYYYYYNNYNNYNYYNNNNNYNYYNNYNYNNYYYNYYYNNNNYN",
"NNNNNNNNYNNYNNNNNNNNNNNNNNNNYYNNYNYNNNNYNNNNNYNYNN",
"NNNYNYNYYYYYNNNNNNNNYNYNYNNNYNYNYNYNNNNNYYYNYNNYYN",
"NYNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYN",
"NNNYYYNYNYNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNYNNN",
"NNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNYN",
"NNNNNYNNYYYNNNYNNNNYNNNNNNNNNYNNYNYNNYNYNNNNNNNYNN",
"NYNNYNNNNNNNNNYNNNNYNYNNNNNNNNNNNNNNNNNNNYNNNYYNNN",
"NNNNNYNYYYNNNNYNNYNNNNNNNNNNNYNYNNNNNNNNNNNNNYYYNN",
"NNNNYYNYYYYNYNNNYYNYNYYNNNYYNYNNYNNYNYYNYYNYYNYYNY",
"NYNNNNNNNYYNNNNNNNNNNNNYNNNNYYNNNNYNNNYNNYNNNYNNYN",
"NNNYNYNYNYNNNNNNNNNYNYYNNNYNNYNYYNNNNNNNYNNNNYNNYN",
"NYNNNYNNNYNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNYNNN",
"NYNYNNNYNYYNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNYNNNYYNNN",
"NYNNNNNNYNNNNYYYNYNYNNNNNNNNYYNNNNNNNNNNNNNNNYYNNN",
"NNNYYNNNNNYYNNYNNNNNNYNYNNNNYYNNNNYNNNNYNNNNNNYNNN",
"NYNYNYNNNNNYNNNNNNNYNNNNNNNNNNNNNNNNNYYNNYNNNYNNYN",
"NYNNNNNNNYYNNNNYYYNNNNYNYNYNYNNYYNNYNYNNNNNNNNNNYN",
"NNNNYNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNYNNYN",
"NYNYYNNYNYNNNNNYNNNYNYNNYNNNNNNNYNNNNNYNNYNYNNNNNN",
"NYNNNNNNYNNNNYYNNNYNNYYNNYYYYYNNNYNNNNNYNYYNNNNNNY",
"NYNNNYNNNYYNNNNNNNNNNNNYNNNNNNNNNNYNNNNNNNNNNNYNNN",
"NNNNNYNNYYNYNNNNNNNNNYNYNNNNYNNNNNNNNNNNNYNNNNNNNN",
"NNNNNYNYNNYNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNYNNNNNNNN",
"NNNNYNNNYNNNNNNYNNNYNYNYYNNNNYNNNNNNNNNNNYNNNYYNNN",
"NNNNYNNYNYNNNNYNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNYYNYN",
"NYNNYYNNYNNNNNNNNNNYYYNNNNNNNNNNNNNNNNNNNNNYNNNNNN",
"NNNYYNNYYNNNNNYYNNNYNNNNYNYNNNNNNNNNNNNYNNNNNYNNNN",
"NNNNNYNYYNYNNNNNYNNYYYYNYNYYYYYNYNYYNNNNYNNNNYYYYN",
"NNNNNNNYNNNNNNYNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNYN",
"NYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYN",
"NNNYYNNNYYNYNNNNNNNNNYNNNNNNYNNNNNYNNNNNNYNNNNYNNN",
"NYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
"NYNNNNYYYNYYYYNYNNNNNNNNNNNYNYNNNNNNNNNYNYNYNNNNYN"};
			string rooms              = "---??--??-????-??????--?????-?-?-??--?-??--??????-";
			long long expected__      = 2165839872LL;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string maze[]             = ;
			string rooms              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string maze[]             = ;
			string rooms              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string maze[]             = ;
			string rooms              = ;
			long long expected__      = ;

			clock_t start__           = clock();
			long long received__      = EvenPaths().theCount(vector <string>(maze, maze + (sizeof maze / sizeof maze[0])), rooms);
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
