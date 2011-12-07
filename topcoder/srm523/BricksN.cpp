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
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;
const ll MOD = 1000000007;

ll hor[60];
int K;

ll mem[60][60];
ll search(int w, int h) {
  if (h == 0) return 1;
  if (w == 0) return 1;
  if (mem[w][h] != -1) return mem[w][h];

  ll res = search(w - 1, h);
  for (int tw = 1; tw <= w; ++tw) {
    ll t = hor[tw];
    t = t * search(tw, h - 1) % MOD;
    if (w - tw - 1 >= 1) t = t * search(w - tw - 1, h) % MOD;

    res += t;
    res %= MOD;
  }

  return mem[w][h] = res;
}

struct BricksN {
  int countStructures(int W, int H, int K_) {
    K = K_;

    hor[0] = 1;
    for (int w = 1; w <= W; ++w) {
      hor[w] = 0;
      for (int i = 1; i <= K && w - i >= 0; ++i) {
        hor[w] += hor[w - i];
        hor[w] %= MOD;
      }
    }

    memset(mem, -1, sizeof(mem));
    return search(W, H);
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 3; int Arg3 = 13; verify_case(0, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 3; int Arg3 = 83; verify_case(1, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 5; int Arg2 = 1; int Arg3 = 6; verify_case(2, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 3; int Arg3 = 288535435; verify_case(3, Arg3, countStructures(Arg0, Arg1, Arg2)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  BricksN ___test;
  ___test.run_test(-1);
}
// END CUT HERE
