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

struct ChromaticNumber {
  int minColors(vector <string> graph);
};



// adj: 隣接行列をビットマスクで
int chromatic_number(const vector<int> &adj) {
  int n = adj.size();
  vector<int> dp1(1 << n), dp2(1 << n);
  dp1[0] = dp2[0] = 1;
  rep (i, n) rep (j, 1 << i) {
    dp2[j | 1 << i] = -dp2[j];
    dp1[j | 1 << i] = dp1[j] + dp1[j & ~adj[i]];
  }
  for (int q = 1; q < n; ++q) {
    int r = 0;
    rep (i, 1 << n) {
      dp2[i] *= dp1[i];
      r += dp2[i];
    }
    if (r != 0) return q;
  }
  return n;
}

namespace ZoRGaN {
int n, maxcol;
int w[2000], col[2000];
vector<string> a;

void dfs(int u) {
  w[u] = 1;
  for (int i = 0, ok;; i++) {
    ok = 1;
    for (int j = 0; j < n && ok; j++) {
      if (w[j] && a[u][j] == 'Y' && col[j] == i) ok = 0;
    }
    if (ok) {
      col[u] = i;
      maxcol = max(maxcol, i + 1);
      break;
    }
  }
  int p[n];
  for (int i = 0; i < n; i++) p[i] = i;
  random_shuffle(p, p + n);
  for (int i = 0; i < n; i++) {
    if (!w[p[i]] && a[u][p[i]] == 'Y') {
      dfs(p[i]);
    }
  }
}

int minColors(vector<string> s) {
  puts("It's me!!");

  n = s.size();
  a = s;
  memset(w, 0, sizeof(w));
  maxcol = 0;
  for (int i = 0; i < n; i++) {
    if (!w[i]) dfs(i);
  }
  return maxcol;
}
}



int ChromaticNumber::minColors(vector <string> graph) {
  return ZoRGaN::minColors(graph);


  int N = graph.size();

  int col[60];
  rep (v, N) col[v] = -1;

  int ans = 0;
  rep (v, N) {
    if (col[v] != -1) continue;
    col[v] = v;
    ++ans;

    vector<int> na;
    rep (w, N) if (graph[v][w] == 'N' && col[w] == -1) na.pb(w);

    if (na.size() >= 1) {
      if (na.size() == 2) {
        if (graph[na[0]][na[1]] == 'N') {
          col[na[0]] = col[na[1]] = v;
        } else {
          col[na[0]] = v;
        }
      } else {
        col[na[0]] = v;
      }
    }
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
			string graph[]            = {"N"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string graph[]            = {"NYY",
 "YNN",
 "YNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string graph[]            = {"NYNN",
 "YNNN",
 "NNNY",
 "NNYN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string graph[]            = {"NYNY",
 "YNYY",
 "NYNN",
 "YYNN"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string graph[]            = {"NYYYYYYY",
 "YNYYYYYY",
 "YYNYYYYY",
 "YYYNYYYY",
 "YYYYNYYY",
 "YYYYYNYY",
 "YYYYYYNY",
 "YYYYYYYN"};
			int expected__            = 8;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>

struct __bench__ {
  double start;
  char msg[100];
  __bench__(const char* format, ...)
  __attribute__((format(printf, 2, 3)))
  {
    va_list args;
    va_start(args, format);
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);

    start = sec();
  }
  ~__bench__() {
    fprintf(stderr, "%s: %.6f sec\n", msg, sec() - start);
  }
  double sec() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
  }
  operator bool() { return false; }
};

#define benchmark(...) if(__bench__ __b__ = __bench__(__VA_ARGS__));else


int main(int argc, char *argv[]) {
  const int N = 20;
  while (true) {
    vector<string> adj(N, string(N, 'N'));
    rep (i, N) {
      while (count(all(adj[i]), 'Y') < N - 3) {
        int j = rand() % (N - 1);
        if (j >= i) ++j;
        adj[i][j] = adj[j][i] = 'Y';
      }
    }

    rep (i, N) cout << adj[i] << endl;

    vector<int> bs(N);
    rep (i, N) rep (j, N) bs[i] |= (adj[i][j] == 'Y') << j;

    int my = ChromaticNumber().minColors(adj);

    int op;
    benchmark("opponent") op = ZoRGaN::minColors(adj);

    int ans = chromatic_number(bs);
    printf("N=%d, my=%d, exact=%d\n", N, my, ans);
    printf("N=%d, my=%d, out=%d\n", N, my, op);

    assert(op <= my);

    // assert(out == ans);
  }

	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
