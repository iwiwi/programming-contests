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



struct Rumor {
  int getMinimum(string knowledge, vector <string> graph) {
    int N = knowledge.size();
    int ans = INT_MAX;

    int G[20] = {};
    rep (i, N) {
      rep (j, N) if (graph[i][j] == 'Y') {
        // graph[i][j] is 'Y' if and only if rabbit i will spread rumors to rabbit j.
        G[j] |= 1 << i;
      }
    }

    int L = N * 2 + 3;

    rep (b, 1 << N) {
      bool know[20][2] = {};
      bool done[20][2] = {};
      int tell[2];
      rep (i, N) if (knowledge[i] == 'Y') {
        know[i][0] = know[i][1] = true;
      }

      int d;
      for (d = 0; d <= L; ++d) {
        rep (i, N) if (!know[i][0] || !know[i][1]) goto notyet;
        break;
     notyet:

        tell[0] = tell[1] = 0;
        rep (i, N) {
          bool k0 = know[i][0];
          bool k1 = know[i][1];

          int t = -1;
          if (k0 && k1) {
            rep (j, 2) {
              int tt = (1 & (b >> i)) ^ j;
              if (done[i][tt] == false) {
                t = tt;
                break;
              }
            }
          }
          else if (k0) t = 0;
          else if (k1) t = 1;

          if (t != -1 && done[i][t] == false) {
            tell[t] |= 1 << i;
            done[i][t] = true;
            // printf("%d, %d: %d\n", d, i, t);
          }
        }

        rep (i, N) {
          rep (t, 2) {
            know[i][t] |= (tell[t] & G[i]) ? true : false;
          }
        }
      }
      if (d <= L) ans = min(ans, d);
    }

    if (ans == INT_MAX) return -1;
    return ans;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "YNN"; string Arr1[] = {"NYN"
,"NNY"
,"NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "YNNY"; string Arr1[] = {"NYYN"
,"YNNY"
,"YNNY"
,"NYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "YYYY"; string Arr1[] = {"NYNN"
,"YNYN"
,"NYNY"
,"NNYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "YYYYYN"; string Arr1[] = {"NYYYYN"
,"YNYYYN"
,"YYNYYN"
,"YYYNYN"
,"YYYYNN"
,"NNNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "NNNY"; string Arr1[] = {"NNNN"
,"YNNN"
,"YNNN"
,"NYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(4, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_5() { string Arg0 =  "NNNNNNNYYY"; string Arr1[] = {"NYNNYNNYNN"
,"NNYNYNNNNY"
,"YYNNNYNNNN"
,"YNNNYNYNNN"
,"NNYNNYNNYN"
,"NNNNYNNNYY"
,"NYNYNYNNNN"
,"NNNNNNYNYY"
,"NNNYNNNYNY"
,"NYYNNNNYNN"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(5, Arg2, getMinimum(Arg0, Arg1)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  Rumor ___test;
  ___test.run_test(-1);
}
// END CUT HERE
