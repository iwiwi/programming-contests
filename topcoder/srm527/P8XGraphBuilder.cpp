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
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

const int INF = 987654321;

int N;
vector<int> S;
int mem[60][60][60];

int search(int k, int l, int r) {
  if (k == N) return 0;
  if (mem[k][l][r] != -1) return mem[k][l][r];
  if (l == 0) return -INF;


  int res = -INF;
  for (int c = 0; c <= r; ++c) {
    int d = k == 0 ? c : (c + 1);
    res = max(res, S[d] + search(k + 1, l - 1 + c, r - c));
  }
  return mem[k][l][r] = res;
}

struct P8XGraphBuilder {
  int solve(vector <int> scores) {
    N = scores.size() + 1;
    S = scores;
    S.insert(S.begin(), 0);

    memset(mem, -1, sizeof(mem));
    return search(0, 1, N - 1);
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 3, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 0, 0, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { int Arr0[] = {5, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 3, 2, 5, 3, 7, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; verify_case(4, Arg1, solve(Arg0)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  P8XGraphBuilder ___test;
  ___test.run_test(-1);
}
// END CUT HERE
