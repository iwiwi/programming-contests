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

typedef long long ll;

int N;
vector<string> G;
vector<int> na[60];

ll all;

int search(int v, ll b) {
  if (b == all) return 0;
  if (b & (1LL << v)) return search(v + 1, b);

  int tna[2], tna_n = 0;
  rep (i, na[v].size()) if (0 == (b & (1LL << na[v][i]))) tna[tna_n++] = na[v][i];

  b |= 1LL << v;

  if (tna_n == 2) {
    if (G[tna[0]][tna[1]] == 'N') {
      return 1 + search(v + 1, b | (1LL << tna[0]) | (1LL << tna[1]));
    } else {
      return min(1 + search(v + 1, b | (1LL << tna[0])),
                 1 + search(v + 1, b | (1LL << tna[1])));
    }
  } else if (tna_n == 1) {
    return 1 + search(v + 1, b | (1LL << tna[0]));
  } else {
    return 1 + search(v + 1, b);
  }
}

int ChromaticNumber::minColors(vector <string> graph) {
  N = graph.size();
  G = graph;
  rep (v, N) {
    na[v].clear();
    rep (w, N) if (graph[v][w] == 'N' && v != w) na[v].pb(w);
  }

  all = (1LL << N) - 1;
  return search(0, 0);
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

      case 5: {
			string graph[]            =

                {"NYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNNYYYYYYYYYYYYYYY", "YNYYNYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY", "YYNYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYNYY", "YYYNYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYY", "YNYYNYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYY", "YYYYYNYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYY", "YNYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYY", "YYYYYYYNYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYY", "YYYYYYYYNYYYYYYYYYYNYYYYYYYYYYNYYYYYYYYYYYYYYYYYYY", "YYYYYYYYYNNYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYY", "YYYYYYYYYNNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYY", "YYYNYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYY", "YYYYYYYYYYYYNYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYNYYYYY", "YYYYYNYYYYYYYNYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY", "YYYYYYYYYYYYYYNNYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYY", "YYYYYYYYYYYYYYNNYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYY", "YYYYYYYNYYYYYYYYNYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYY", "YYYYYYYYYYYYYYYYYNYYNYYYYYYYYYYYNYYYYYYYYYYYYYYYYY", "YYYYYYYYYYYYYYYYYYNYYYYYYYNYYYYYYYYYYYYYYYYYYYYYNY", "YYYYYYYYNYYYYNYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY", "YYYYYYYYYYYYYYYYYNYYNYYYYYYYYYYYYYYYYYYYNYYYYYYYYY", "YYYYYYYYYYYYNYYYYYYYYNYYYYYYYYYYYYYYNYYYYYYYYYYYYY", "YYYYYYYYYYYYYYYYYYYYYYNYYNYYYYYYYYYYYYYYNYYYYYYYYY", "YYNYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYNYYYY", "YYYYNYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYNYYYYYYYY", "YYYYYYYYYYYYYYYYYYYYYYNYYNYYYYYYYYNYYYYYYYYYYYYYYY", "YYYYYYYYYYYYYYYYYYNYYYYYYYNYYYYYYYYYYYYYYYYYYNYYYY", "YYYYYYYYYYYYYYYNYYYYYYYYYYYNYYYYYYYNYYYYYYYYYYYYYY", "YYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYNYYYYYY", "YYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYNYYYYYYYNYYYYYYYYYY", "YYYYYYYYNYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYNYYYYYY", "YYYYYYYYYYYYYYYYNYYYYYYYYYYYYNYNYYYYYYYYYYYYYYYYYY", "YYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYNYYYYYNYYYYYYYYYYY", "NYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYNYYYYYYYYYY", "NYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYNYYYYYYYYYYYYYYY", "YYYYYYYYYNYYYYYYYYYYYYYYYYYNYYYYYYYNYYYYYYYYYYYYYY", "YYYYYYYYYYYNYYYYYYYYYNYYYYYYYYYYYYYYNYYYYYYYYYYYYY", "YYYYYYNYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYY", "YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYNYYYYYYYNYYY", "YYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYNYYYYYNYYYYYYYYYY", "YYYYYYYYYYYYYYYYYYYYNYNYYYYYYYYYYYYYYYYYNYYYYYYYYY", "YYYNYYYYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYNYYYYYYYY", "YYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYNYYYYY", "YYYYYYYYYYYYYYYYYYYYYYYYYYYYNYNYYYYYYYYYYYYNYYYYYY", "YYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYNYYYYY", "YYYYYYYYYYYYYYYYYYYYYYYNYYNYYYYYYYYYYYYYYYYYYNYYYY", "YYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYYYYYYYNYYY", "YYNYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYY", "YYYYYYYYYYYYYYYYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYYNY", "YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYN"};

			int expected__            = 25;

			clock_t start__           = clock();
			int received__            = ChromaticNumber().minColors(vector <string>(graph, graph + (sizeof graph / sizeof graph[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
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
  while (false) {
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
