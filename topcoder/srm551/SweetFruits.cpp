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

struct SweetFruits {
  int countTrees(vector <int> sweetness, int maxSweetness);
};

typedef long long ll;
const ll MOD = 1000000007;

inline ll mod(ll a, ll m) { return (a % m + m) % m; }

ll inverse(ll a, ll m) {
  if ((a = mod(a, m)) == 1) return 1;
  return mod((1 - m * inverse(m % a, a)) / a, m);
}



ll cmb[1010][1010];

void init_cmb(int N) {
  cmb[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) cmb[i][j] = (cmb[i-1][j-1] + cmb[i-1][j]) % MOD;
  }
}



typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)
#define INV(x) inverse(x, MOD)
#define NOR(x) ((x) % MOD)

number det(mat_t A) {
  int n = A.size();
  number res = 1;
  for (int i = 0; i < n; i++) {
    int piv = i;
    for (int j = i + 1; j < n; j++)
      if (ABS(A[j][i]) > ABS(A[piv][i])) piv = j;

    if (i != piv) {
      swap(A[i], A[piv]);
      res = NOR(res * -1);
    }

    if (IS0((A[i][i]))) return 0;
    res = NOR(res * A[i][i]);

    for (int j = i + 1; j < n; j++)
      for (int k = n - 1; k >= i; k--)
        A[j][k] = NOR(A[j][k] - NOR(NOR(A[i][k] * A[j][i]) * INV(A[i][i])));
 }
  return res;
}



ll count_tree(int bitter, int truly, int falsely) {
  int n = bitter + truly + falsely;
  vector<int> v;
  rep (i, bitter) v.pb(0);
  rep (i, truly) v.pb(1);
  rep (i, falsely) v.pb(2);

  mat_t A(n, vec_t(n));
  rep (i, n) rep (j, n) if (i != j) A[i][j] = v[i] + v[j] <= 2 ? -1 : 0;
  rep (i, n) A[i][i] = -accumulate(all(A[i]), 0);

  rep (i, n) A[i].pop_back();
  A.pop_back();

  return (det(A) + MOD) % MOD;
}

vector<pair<ll, int> > tmp;
vector<int> swe;

void dfs(int k, ll sum, int falsely) {
  if (k == (int)swe.size()) {
    tmp.pb(mp(sum, falsely));
  } else {
    dfs(k + 1, sum         , falsely + 1);
    dfs(k + 1, sum + swe[k], falsely);
  }
}

int SweetFruits::countTrees(vector <int> sweetness, int maxSweetness) {
  int B = count(all(sweetness), -1);
  sweetness.erase(remove(all(sweetness), -1), sweetness.end());
  int S = sweetness.size();

  ll tree[100];
  init_cmb(100);
  for (int falsely = S; falsely >= 0; --falsely) {
    int truly = S - falsely;
    tree[falsely] = count_tree(B, truly, falsely);
    for (int f = falsely + 1; f <= S; ++f) {
      int t = S - f;
      (tree[falsely] -= cmb[truly][t] * tree[f]) %= MOD;
    }
  }

  int m1 = S / 2, m2 = S - m1;
  vector<int> s1(sweetness.begin(), sweetness.begin() + m1);
  vector<int> s2(sweetness.begin() + m1, sweetness.end());

  tmp.clear();
  vector<pair<ll, int> > e1, e2;
  swe = s1; dfs(0, 0, 0); tmp.swap(e1);
  swe = s2; dfs(0, 0, 0); tmp.swap(e2);

  sort(all(e1)); reverse(all(e1));
  sort(all(e2));
  int cnt[100] = {};
  int i2 = 0;
  ll ans = 0;
  rep (i1, e1.size()) {
    while (i2 < (int)e2.size() && e1[i1].first + e2[i2].first <= maxSweetness) {
      ++cnt[e2[i2].second];
      ++i2;
    }

    for (int k = 0; k <= m2; ++k) ans += cnt[k] * tree[k + e1[i1].second];
    ans %= MOD;
  }

  return (ans + MOD) % MOD;
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
			int sweetness[]           = {1, 2, -1, 3};
			int maxSweetness          = 3;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int sweetness[]           = {1, 2, -1, 3};
			int maxSweetness          = 5;
			int expected__            = 7;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int sweetness[]           = {-1, -1, 2, 5, 5};
			int maxSweetness          = 6;
			int expected__            = 20;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int sweetness[]           = {2, 6, 8, 4, 1, 10, -1, -1, -1, -1};
			int maxSweetness          = 15;
			int expected__            = 17024000;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int sweetness[]           = {1078451, -1, 21580110, 8284711, -1, 4202301, 3427559, 8261270, -1, 16176713, 22915672, 24495540, 19236, 5477666, 12280316, 3305896, 17917887, 564911, 22190488, 21843923, 23389728, 14641920, 9590140, 12909561, 20405638, 100184, 23336457, 12780498, 18859535, 23180993, 10278898, 5753075, 21250919, 17563422, 10934412, 22557980, 24895749, 7593671, 10834579, 5606562};
			int maxSweetness          = 245243285;
			int expected__            = 47225123;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int sweetness[]           = ;
			int maxSweetness          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int sweetness[]           = ;
			int maxSweetness          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int sweetness[]           = ;
			int maxSweetness          = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = SweetFruits().countTrees(vector <int>(sweetness, sweetness + (sizeof sweetness / sizeof sweetness[0])), maxSweetness);
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
