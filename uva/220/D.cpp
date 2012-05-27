#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

typedef unsigned long long ull;

struct node_t {
  node_t *ch[2];
  bool end;
  ull ans;

  node_t() : end(false) {
    ch[0] = ch[1] = NULL;
  }
};

int N, M;

ull dfs(node_t *n, int k) {
  if (n == NULL) return 1ULL << (M - k);
  
  ull s;
  if (k == M) s = 1;
  else s = dfs(n->ch[0], k + 1) + dfs(n->ch[1], k + 1);

  if (n->end) {
    n->ans = s;
    return 0;
  } else {
    return s;
  }
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d%d", &N, &M);
    if (N == 0 && M == 0) return 0;

    node_t *root = new node_t;
    root->end = true;
    
    rep (i, N) {
      string S;
      cin >> S;

      node_t *n = root;
      int k = S.length() - 1;
      rep (i, k) {
        int c = S[i] - '0';
        if (n->ch[c] == NULL) n->ch[c] = new node_t;
        n = n->ch[c];
      }
      n->end = true;
    }

    dfs(root, 0);

    int K;
    cin >> K;
    rep (i, K) {
      string S;
      cin >> S;

      node_t *n = root;
      int k = S.length() - 1;
      rep (i, k) {
        int c = S[i] - '0';
        if (n->ch[c] == NULL) n->ch[c] = new node_t;
        n = n->ch[c];
      }
      cout << n->ans << endl;
    }
    cout << endl;
  }
}
