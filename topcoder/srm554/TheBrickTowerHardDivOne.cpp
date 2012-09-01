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

struct TheBrickTowerHardDivOne {
  int find(int C, int K, long long H);
};

typedef long long ll;
typedef vector<int> vi;

const ll MOD = 1234567891;

typedef long long number;
typedef vector<number> vec_t;
typedef vector<vec_t> mat_t;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define IS0(x) ((x) == 0)
#define INV(x) inverse(x, MOD)
#define NOR(x) ((x) % MOD)

mat_t identity(int n) {
  mat_t A(n, vec_t(n));
  for (int i = 0; i < n; i++) A[i][i] = 1;
  return A;
}

mat_t multiply(const mat_t &A, const mat_t &B) {
  mat_t C(A.size(), vec_t(B[0].size()));
  rep (i, C.size()) rep (k, A[i].size()) rep (j, C[i].size()) {
    C[i][j] = NOR(C[i][j] + A[i][k] * B[k][j]);
  }
  return C;
}

mat_t power(const mat_t &A, long long p) {
  if (p == 0) return identity(A.size());
  if (p == 1) return A;
  mat_t B = power(multiply(A, A), p / 2);
  if (p % 2 == 1) B = multiply(B, A);
  return B;
}



ll C, K, H;

int M;
map<vi, ll> S;
map<vi, int> id;

int L;
mat_t A;

void show(vi v) {
  printf("["); rep (i, 4) printf("%d ", v[i]); puts("]");
}

vi normalize(vi v) {
  int c = 0;
  map<int, int> ma;
  rep (i, 4) if (!ma.count(v[i])) ma[v[i]] = c++;
  rep (i, 4) v[i] = ma[v[i]];
  return v;
}

vi rot(vi v) {
  vi r(4);
  r[0] = v[1];
  r[1] = v[3];
  r[2] = v[0];
  r[3] = v[2];
  return r;
}

vi normalize2(vi v) {
  vi res = normalize(v);
  rep (i, 3) {
    v = rot(v);
    res = min(res, normalize(v));
  }
  return res;
}

int getid(vi v) {
  return id[normalize2(v)];
}

int getidx(vi v, int a) {
  return getid(v) + a * M;
}

int adj(vi v) {
  int ans = 0;
  ans += v[0] == v[1];
  ans += v[0] == v[2];
  ans += v[3] == v[1];
  ans += v[3] == v[2];
  return ans;
}

vi now, base;

void enumerate1(int i, int c, ll p) {
  if (p == 0) return;

  if (i == 4) {
    (S[normalize2(now)] += p) %= MOD;
  } else {
    // used colors
    for (int k = 0; k < c; ++k) {
      now[i] = k;
      enumerate1(i + 1, c, p);
    }
    // new color
    now[i] = c;
    enumerate1(i + 1, c + 1, p * max(0LL, C - c) % MOD);
  }
}

void enumerate2(int i, int c, ll p) {
  if (p == 0) return;

  if (i == 4) {
    int a = adj(now);
    rep (k, 4) a += now[k] == base[k];

    for (int d = K; d - a >= 0; --d) {
      // printf(" %d -> %d: %d, %lld\n", getidx(base, d), getidx(now, d - a), a, p);
      // rep (j, 4) printf(" %d", now[j]); puts("");
      (A[getidx(now, d - a)][getidx(base, d)] += p) %= MOD;
    }
  } else {
    // used colors
    for (int k = 0; k < c; ++k) {
      now[i] = k;
      enumerate2(i + 1, c, p);
    }
    // new color
    now[i] = c;
    enumerate2(i + 1, c + 1, p * max(0LL, C - c) % MOD);
  }
}

int TheBrickTowerHardDivOne::find(int C_, int K_, long long H_) {
  C = C_;
  K = K_;
  H = H_;

  S.clear();
  now.resize(4);
  enumerate1(0, 0, 1);


  printf("%d\n", M);
  id.clear();
  M = 0;
  tr (S, ite) id[ite->first] = M++;

  L = M * (K + 1) + 1;
  A = mat_t(L, vec_t(L));
  vec_t b(L);

  tr(S, ite) {
    base = ite->first;
    // printf("%d: [", id[ite->first]); rep (j, 4) printf("%d ", base[j]); puts("]");
    enumerate2(0, 1 + *max_element(all(base)), 1);

    int a = adj(ite->first);
    if (a > K) continue;
    b[getidx(ite->first, K - a)] = ite->second;
  }
  rep (i, L) A[L - 1][i] = 1;

  // rep (i, L) { rep (j, L) printf("%lld ", A[i][j]); printf(" : %lld\n", b[i]); }

  A = power(A, H);

  ll ans = 0;
  rep (i, L) (ans += (A[L - 1][i] * b[i])) %= MOD;
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
			int C                     = 2;
			int K                     = 0;
			long long H               = 2;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = TheBrickTowerHardDivOne().find(C, K, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int C                     = 1;
			int K                     = 7;
			long long H               = 19;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = TheBrickTowerHardDivOne().find(C, K, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int C                     = 2;
			int K                     = 3;
			long long H               = 1;
			int expected__            = 14;

			clock_t start__           = clock();
			int received__            = TheBrickTowerHardDivOne().find(C, K, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int C                     = 4;
			int K                     = 7;
			long long H               = 47;
			int expected__            = 1008981254;

			clock_t start__           = clock();
			int received__            = TheBrickTowerHardDivOne().find(C, K, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 4: {
			int C                     = ;
			int K                     = ;
			long long H               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBrickTowerHardDivOne().find(C, K, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 5: {
			int C                     = ;
			int K                     = ;
			long long H               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBrickTowerHardDivOne().find(C, K, H);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			int C                     = ;
			int K                     = ;
			long long H               = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = TheBrickTowerHardDivOne().find(C, K, H);
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
