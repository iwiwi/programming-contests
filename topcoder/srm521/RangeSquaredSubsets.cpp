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

struct RangeSquaredSubsets {
  long long countSubsets(int nlow, int nhigh, vector <int> X, vector <int> Y) {
    int M = X.size();
    rep (i, M) { X[i] *= 2; Y[i] *= 2; }
    nlow *= 2;
    nhigh *= 2;

    vector<ll> bs;

    {
      vector<int> xs, ys;
      rep (i, M) {
        for (int d = -1; d <= 1; ++d) {
          xs.pb(X[i] + d); xs.pb(X[i] + d - nlow);
          ys.pb(Y[i] + d); ys.pb(Y[i] + d - nlow);
        }
      }
      sort(all(xs)); xs.erase(unique(all(xs)), xs.end());
      sort(all(ys)); ys.erase(unique(all(ys)), ys.end());

      rep (xi, xs.size()) rep (yi, ys.size()) {
        ll x = xs[xi], y = ys[yi];
        ll b = 0;
        rep (i, M) {
          b |= ll(x <= X[i] && X[i] <= x + nlow && y <= Y[i] && Y[i] <= y + nlow) << i;
        }
        bs.pb(b);
      }
    }

    rep (iter, 2) {
      vector<int> xs(X);
      sort(all(xs)); xs.erase(unique(all(xs)), xs.end());

      rep (ri, xs.size()) rep (li, ri + 1) {
        ll lx = xs[li], rx = xs[ri];
        ll n = rx - lx;
        if (n < nlow || nhigh < n) continue;

        vector<int> ys;
        rep (i, M) {
          if (X[i] < lx || rx < X[i]) continue;
          ys.pb(Y[i]);
          ys.pb(Y[i] - 1 - n);
        }

        rep (ti, ys.size()) {
          ll ty = ys[ti], by = ty + n;
          ll b = 0;
          rep (i, M) {
            b |= ll(lx <= X[i] && X[i] <= rx && ty <= Y[i] && Y[i] <= by) << i;
          }
          bs.pb(b);
        }
      }

      swap(X, Y);
    }

    bs.erase(remove(all(bs), 0LL), bs.end());
    sort(all(bs)); bs.erase(unique(all(bs)), bs.end());
    return bs.size();
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 5; int Arr2[] = {-5,0,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,0,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 5LL; verify_case(0, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 10; int Arr2[] = {-5,0,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,0,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 5LL; verify_case(1, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 100; int Arr2[] = {-5,0,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0,0,0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 6LL; verify_case(2, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 100000000; int Arr2[] = {-1,-1,-1,0,1,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {-1,0,1,1,-1,0,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 21LL; verify_case(3, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 64; int Arg1 = 108; int Arr2[] = {-56,-234,12,324,-12,53,0,234,1,12,72}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {6,34,2,235,234,234,342,324,234,234,234}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 26LL; verify_case(4, Arg4, countSubsets(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  RangeSquaredSubsets ___test;
  ___test.run_test(-1);
}
// END CUT HERE
