#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)

const char *one[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
const char *ten[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
const char *hun[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
const char *tho[] = {"", "M", "MM", "MMM"};

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int N;
    scanf("%d", &N);

    vector<pair<string, int> > A(N);
    rep (i, N) {
      int x;
      scanf("%d", &x);

      string s = "";
      s += tho[x / 1000 % 10];
      s += hun[x /  100 % 10];
      s += ten[x /   10 % 10];
      s += one[x /    1 % 10];
      A[i] = make_pair(s, x);
    }
    sort(A.begin(), A.end());

    rep (i, N) {
      if (i) putchar(' ');
      printf("%d", A[i].second);
    }
    puts("");
  }
}
