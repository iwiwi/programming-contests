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

int N;
string S;

int mem[2][1 << 15];

int search(int p, int b) {
  if (__builtin_popcount(b) == 1) {
    return S[__builtin_ctz(b)] == 'A' ? 0 : 1;
  }

  if (mem[p][b] != -1) return mem[p][b];

  for (int l = 0; l < N; ++l) {
    for (int r = l + 1; r <= N; ++r) {
      // [l, r)
      int tb = b;
      for (int i = l; i < r; ++i) {
        if (0 == (b & (1 << i))) goto dmp;
        tb -= (1 << i);
      }
      if (tb == 0) goto dmp;

      if (search(1 - p, tb) == p) {
        return mem[p][b] = p;  // win!!
      }

   dmp:;
    }
  }

  return mem[p][b] = 1 - p;  // lose...
}

struct RowAndCoins {
  string getWinner(string cells) {
    N = cells.length();
    S = cells;
    memset(mem, -1, sizeof(mem));

    if (search(0, (1 << N) - 1) == 0) return "Alice";
    else return "Bob";
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABBB"; string Arg1 = "Alice"; verify_case(0, Arg1, getWinner(Arg0)); }
	void test_case_1() { string Arg0 = "BBBB"; string Arg1 = "Bob"; verify_case(1, Arg1, getWinner(Arg0)); }
	void test_case_2() { string Arg0 = "BA"; string Arg1 = "Alice"; verify_case(2, Arg1, getWinner(Arg0)); }
	void test_case_3() { string Arg0 = "BABBABBB"; string Arg1 = "Bob"; verify_case(3, Arg1, getWinner(Arg0)); }
	void test_case_4() { string Arg0 = "ABABBBABAABBAA"; string Arg1 = "Alice"; verify_case(4, Arg1, getWinner(Arg0)); }
	void test_case_5() { string Arg0 = "BBBAAABBAAABBB"; string Arg1 = "Bob"; verify_case(5, Arg1, getWinner(Arg0)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  RowAndCoins ___test;
  ___test.run_test(-1);

  for (;;) {
    string S(14, 'B');
    for (int i = 1; i + 1 < S.length(); ++i) {
      S[i] = 'A';
    }
    if (___test.getWinner(S) == "Alice") {
      cout << S << endl;
    }
  }

}
// END CUT HERE
