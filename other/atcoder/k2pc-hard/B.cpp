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
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

struct node {
  bool ng;
  node *ch[2];
  node() : ng(false) {
    ch[0] = ch[1] = NULL;
  }
};

int K, N;

ll search(node *n, int k) {
  if (n == NULL) return (1LL << (k + 1)) - 1;
  else if (n->ng) return 0;
  else return 1 + search(n->ch[0], k - 1) + search(n->ch[1], k - 1);
}

int main() {
  while (2 == scanf("%d%d", &K, &N)) {
    node root;

    rep (i, N) {
      int p;
      ll q;
      scanf("%d%lld", &p, &q);
      --q;

      node *n = &root;
      ll j = 0;
      for (int i = 0; i < p; ++i) {
        ll t = q / (1LL << (p - i - 1));
        int k = t - j * 2;
        if (n->ch[k] == NULL) n->ch[k] = new node();
        n = n->ch[k];
        j = t;
      }
      n->ng = true;
    }

    printf("%lld\n", search(&root, K));
  }

  return 0;
}

