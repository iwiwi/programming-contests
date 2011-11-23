#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <map>
#include <climits>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second

int M, mat[20][20];

int mem[1 << 15][15];
int search(int b, int k) {
  if (b == 0) return 0;
  if (mem[b][k] != -1) return mem[b][k];

  int tmp = INT_MAX;
  rep (i, M) if (b & (1 << i)) {
    tmp = min(tmp, mat[k][i] + search(b - (1 << i), i));
  }
  return mem[b][k] = tmp;
}

int main() {
  for (;;) {
    vector<string> T;
    {
      int N;
      scanf("%d", &N);
      if (N == 0) return 0;
      
      vector<string> S(N);
      rep (i, N) cin >> S[i];
      
      rep (i, N) {
	string s = S[i];
	rep (j, N) if (i != j && S[j].find(s) != string::npos) goto contained;
	T.push_back(s);
      contained:;
      }
    }
    
    M = T.size();
    rep (i, M) {
      rep (j, M) if (i != j) {
	mat[i][j] = T[j].length();
	for (int k = 0; k <= (int)min(T[i].length(), T[j].length()); ++k) {
	  if (T[i].substr(T[i].length() - k) == T[j].substr(0, k)) {
	    mat[i][j] = T[j].length() - k;
	  }
	}
	// printf("%s->%s: %d\n", T[i].c_str(), T[j].c_str(), mat[i][j]);
      }
    }

    memset(mem, -1, sizeof(mem));
    int ans = INT_MAX;
    rep (i, M) {
      int tmp = T[i].length() + search((1 << M) - 1 - (1 << i), i);
      ans = min(ans, tmp);
    }
    printf("%d\n", ans);
  }
}
