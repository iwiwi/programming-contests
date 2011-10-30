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
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

int rad[2000010];

void manacher(const char *text, int n) {
  int i, j, k;
  for (i = 0, j = 0; i < 2*n; i += k, j = max(j-k, 0)) {
    while (i-j >= 0 && i+j+1 < 2*n && text[(i-j)/2] == text[(i+j+1)/2]) ++j;
    rad[i] = j;
    for (k = 1; i-k >= 0 && rad[i]-k >= 0 && rad[i-k] != rad[i]-k; ++k)
      rad[i+k] = min(rad[i-k], rad[i]-k);
  }
}

typedef unsigned long long ull;

int ans[1000010];

bool is_palindrome(const string &s) {
  rep (i, s.length()) if (s[i] != s[s.length() - i - 1]) return false;
  return true;
}

void bruteforce(const string &s) {
  for (int l = 1; l <= s.length(); ++l) {
    int a = 0;
    for (int i = 0; i + l <= s.length(); ++i) {
      if (!is_palindrome(s.substr(i, l))) {
        a = i + 1;
        break;
      }
    }

    // assert(a  == ans[l]);
    printf("%d ", a);
  }
  puts("");
}

int main() {
  int T;
  scanf("%d", &T);

  while (T--) {
    string S;
    cin >> S;

    int L = S.length();
    manacher(S.c_str(), L);

    memset(ans, 0, sizeof(ans));


    // odd-length
    {
      int mid = (L - 1) / 2;
      {
        stack<pair<int, int> > stk;
        for (int i = mid; i >= 0; --i) {
          int r = rad[i * 2] / 2 + 1;
          int lb = r + 1, ub = min(i + 1, L - i);  // [lb, ub]
          // printf("^ [%d, %d]\n", lb, ub);

          while (!stk.empty() && stk.top().first > ub) stk.pop();
          while (!stk.empty() && stk.top().first > lb) stk.pop();

          if (lb <= ub) stk.push(mp(lb, i));

          if (!stk.empty()) {
            int a = ub * 2 - 1;
            int b = 1 + (stk.top().second - ub + 1);
            ans[a] = b;
            // printf("A %d: %d (%d)\n", ub, stk.top().second, stk.top().first);
          }
        }
      }

      {
        queue<pair<int, int> > que;
        for (int i = mid + 1; i < L; ++i) {
          int r = rad[i * 2] / 2 + 1;
          int lb = r + 1, ub = min(i + 1, L - i);  // [lb, ub]
          // printf("v [%d, %d]\n", lb, ub);

          while (!que.empty() && que.front().first > ub) que.pop();
          if (lb <= ub) que.push(mp(lb, i));

          if (!que.empty()) {
            int a = ub * 2 - 1;
            int b = 1 + (que.front().second - ub + 1);
            if (ans[a] == 0) ans[a] = b;
            // printf("B %d: %d (%d)\n", ub, que.front().second, que.front().first);
          }
        }
      }
    }

    // even-length
    {
      int mid = (L - 2) / 2;
      {
        stack<pair<int, int> > stk;
        for (int i = mid; i >= 0; --i) {
          int r = rad[i * 2 + 1] / 2;
          int lb = r + 1, ub = min(i + 1, L - i - 1);  // [lb, ub]
          // printf("A [%d, %d]\n", lb, ub);

          while (!stk.empty() && stk.top().first > ub) stk.pop();
          while (!stk.empty() && stk.top().first > lb) stk.pop();

          if (lb <= ub) stk.push(mp(lb, i));

          if (!stk.empty()) {
            int a = ub * 2;
            int b = 1 + (stk.top().second - ub + 1);
            ans[a] = b;
            // printf("A %d: %d (%d)\n", ub, stk.top().second, stk.top().first);
          }
        }
      }

      {
        queue<pair<int, int> > que;
        for (int i = mid + 1; i < L - 1; ++i) {
          int r = rad[i * 2 + 1] / 2;
          int lb = r + 1, ub = min(i + 1, L - i - 1);  // [lb, ub]
          // printf("B [%d, %d]\n", lb, ub);

          while (!que.empty() && que.front().first > ub) que.pop();
          if (lb <= ub) que.push(mp(lb, i));

          if (!que.empty()) {
            int a = ub * 2;
            int b = 1 + (que.front().second - ub + 1);
            if (ans[a] == 0) ans[a] = b;
            // printf("B %d: %d (%d)\n", ub, que.front().second, que.front().first);
          }
        }
      }
    }

    // for (int i = 1; i <= L; ++i) printf("%d ", ans[i]); puts("");
    // bruteforce(S);

    ull res = 0;
    for (int i = 1; i <= L; ++i) {
      res = res * 100007 + ans[i];
    }
    cout << res << endl;
  }

  return 0;
}

