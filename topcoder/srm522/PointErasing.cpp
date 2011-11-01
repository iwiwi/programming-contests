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
#include <bitset>
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

struct PointErasing {
  vector <int> getOutcomes(vector<int> Y) {
    int N = Y.size();
    int min_y = *min_element(all(Y));
    int max_y = *max_element(all(Y));

    if (min_y == max_y) return vector<int>(1, N);

    int lef_i = N, rig_i = 0;
    rep (i, N) {
      if (Y[i] == min_y || Y[i] == max_y) {
        lef_i = min(lef_i, i);
        rig_i = max(rig_i, i);
      }
    }

    int base = 0;
    vector<int> tar;
    rep (i, N) {
      if (i < lef_i && Y[0] == Y[i]) tar.pb(i);
      else if (i > rig_i && Y[N - 1] == Y[i]) tar.pb(i);
      else if (Y[i] == min_y || Y[i] == max_y) ++base;
    }
    int M = tar.size();

    printf("always: %d\n", base);
    rep (i, tar.size()) printf("%d ", tar[i]); puts("");

    vector<int> skip[60];
    rep (ri, N) {
      rep (li, ri) {  // [li, ri]
        int b = M, e = -1;  // [b, e]

        rep (k, M) {
          int x = tar[k], y = Y[x];
          if ((x - li) * (x - ri) < 0 && (y - Y[li]) * ll(y - Y[ri]) < 0) {
            b = min(b, k);
            e = max(e, k);
          }
        }

        if (b > e) continue;
        skip[b].pb(e + 1);
      }
    }


    rep (i, M) {
      printf("%d: ", i);
      rep (j, skip[i].size()) printf(" %d", skip[i][j]);
      puts("");

    }


    ll dp[60] = {0};
    dp[M] = 1;

    for (int i = M - 1; i >= 0; --i) {
      sort(all(skip[i]));
      skip[i].erase(unique(all(skip[i])), skip[i].end());
      int sz = skip[i].size();
      rep (j, sz) {
        for (int k = i + 1; k < skip[i][j]; ++k) {
          rep (l, skip[k].size()) {
            skip[i].push_back(max(skip[i][j], skip[k][l]));
          }
        }
      }
      sort(all(skip[i]));
      skip[i].erase(unique(all(skip[i])), skip[i].end());

      dp[i] = dp[i + 1] << 1;
      rep (j, skip[i].size()) {
        dp[i] |= dp[skip[i][j]];
      }
    }

    rep (i, M) {
      printf("%d: ", i);
      cout << bitset<32>(dp[i] >> 32) << bitset<32>(dp[i]) << " --- ";
      rep (j, skip[i].size()) printf(" %d", skip[i][j]);
      puts("");

    }

    vector<int> res;
    rep (i, M + 1) if ((dp[0] >> i) & 1) res.pb(base + i);
    return res;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arr0[] = { 1, 2, 1, 1, 0, 4, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getOutcomes(Arg0)); }
	void test_case_1() { int Arr0[] = { 0, 0, 4, 4, 8, 8, 4, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getOutcomes(Arg0)); }
	void test_case_2() { int Arr0[] = { 522 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getOutcomes(Arg0)); }
	void test_case_3() { int Arr0[] = { 19, 19, 19, 19, 19, 19 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getOutcomes(Arg0)); }
	void test_case_4() { int Arr0[] = { 0, 1, 2, 3, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getOutcomes(Arg0)); }
	void test_case_5() { int Arr0[] = { 7, 8, 8, 7, 6, 7, 9, 3, 5, 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 4, 5 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, getOutcomes(Arg0)); }
	void test_case_6() { int Arr0[] = { 3, 2, 3, 3, 4, 3, 4, 3, 3, 1, 5, 3 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 5, 6, 7, 9 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(6, Arg1, getOutcomes(Arg0)); }
	void test_case_7() { int Arr0[] = { 5, 5, 4, 4, 5, 8, 5, 5, 5, 5, 5, 9, 2, 0, 9, 4, 5, 5, 3, 4, 4, 4, 4, 7, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 7, 8, 10, 11, 12, 13, 15, 16, 17 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(7, Arg1, getOutcomes(Arg0)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  PointErasing ___test;
  ___test.run_test(-1);
}
// END CUT HERE
