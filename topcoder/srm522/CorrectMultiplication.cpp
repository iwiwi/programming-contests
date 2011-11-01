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

struct CorrectMultiplication {
  ll A, B, C;
  ll g(ll x, ll y, ll a, ll b, ll c) {
    return abs(a-x)+abs(b-y)+abs(x*y-c);
  }
  ll f(ll x, ll a, ll b, ll c) {
    ll left=1, right=1000000000, mid1, mid2;
    while(left+1 < right) {
      mid1 = (left*2 + right)/3;
      mid2 = (left + right*2)/3;
      if (mid2==mid1)mid2++;
      ll v1=g(x, mid1, a,b,c);
      ll v2=g(x,mid2,a,b,c);
      if(v1 <= v2) right = mid2;
      else left = mid1 + 1;
    }
    return min(min(g(x,left,a,b,c),g(x,left+1,a,b,c)),g(x,right,a,b,c));
  }
  ll dreamoon(int a, int b, int c) {
    int i;
    ll an = 10000000000000000LL;
    for (i  = 1; i <= 60000; ++i) {
      an = min(an, f(i, a, b, c));
      an = min(an, f(i, b, a, c));
    }
    return an;
  }


  ll myabs(ll x) {
    if (x < 0) return -x;
    else return x;
  }

  long long getMinimum(int a, int b, int c) {
    if (a < b) swap(a, b);

    ll maxB = floor(sqrt(c) + 100000);

    ll ans = ll(a - 1) + ll(b - 1) + ll(c - 1);

    for (ll B = 1; B <= maxB; ++B) {
      ll minA = max(1LL, c / B - 10);
      ll maxA = c / B + 10;
      for (ll A = minA; A <= maxA; ++A) {
        ll C = A * B;
        ans = min(ans, myabs(A - a) + myabs(B - b) + myabs(C - c));
      }
    }

    return ans;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 19; int Arg1 = 28; int Arg2 = 522; long long Arg3 = 2LL; verify_case(0, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 30; int Arg2 = 500; long long Arg3 = 11LL; verify_case(1, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 11111; int Arg1 = 11111; int Arg2 = 123454321; long long Arg3 = 0LL; verify_case(2, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 100; int Arg2 = 10; long long Arg3 = 1089LL; verify_case(3, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 399; int Arg1 = 522; int Arg2 = 199999; long long Arg3 = 24LL; verify_case(4, Arg3, getMinimum(Arg0, Arg1, Arg2)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  CorrectMultiplication ___test;
  ___test.run_test(-1);

  srand(time(NULL));
  for (;;) {
    int a = 1 + rand() % 1000000000;
    int b = 1 + rand() % 1000000000;
    int c = 1 + rand() % 1000000000;
    ll ans = ___test.getMinimum(a, b, c);
    ll tmp = ___test.dreamoon(a, b, c);
    if (ans != tmp) {
      printf("%d %d %d: %lld %lld\n", a, b, c, ans, tmp);
    }
  }
}
// END CUT HERE
