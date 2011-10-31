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

const ll MOD = 1000000009;



const int MAX_NODES = 110;
const int A = 4;

int alphabet2id(int a) {
  switch (a) {
    case 'A': return 0;
    case 'C': return 1;
    case 'G': return 2;
    case 'T': return 3;
    default: assert(false);
  }
}


struct node_t {
  node_t *parent, *fail, *next[A];
  // MODIFY HERE!
  int max_suffix_cover;
  int dp[1010][20];
};

node_t nodes[MAX_NODES], *root;
int num_nodes;

node_t *new_node() {
  node_t *p = &nodes[num_nodes++];
  p->parent = p->fail = NULL;
  rep (i, A) p->next[i] = NULL;
  // MODIFY HERE!
  p->max_suffix_cover = 0;
  memset(p->dp, 0, sizeof(p->dp));
  return p;
}

void construct(const vector<string> &words) {
  num_nodes = 0;
  root = new_node();
  rep (i, words.size()) {
    const string &w = words[i];
    node_t *p = root;
    rep (j, w.length()) {
      node_t *&q = p->next[alphabet2id(w[j])];
      if (!q) q = new_node();
      q->parent = p;
      p = q;
    }
    // MODIFY HERE!
    p->max_suffix_cover = max(p->max_suffix_cover, (int)w.length());
  }

  queue<node_t*> que;
  que.push(root);
  while (!que.empty()) {
    node_t *p = que.front();
    que.pop();
    rep (i, A) {
      node_t *&q = p->next[i];
      if (!q) q = p->fail ? p->fail->next[i] : root;
      else {
        node_t *r = p->fail;
        while (r && !r->next[i]) r = r->fail;
        q->fail = r ? r->next[i] : root;
        que.push(q);
        // MODIFY HERE!
        q->max_suffix_cover = max(q->max_suffix_cover, q->fail->max_suffix_cover);
      }
    }
  }
}


char id2alphabet(int i) {
  return "ACGT"[i];
}

string get_prefix(node_t *p) {
  string s = "";
  while (p->parent != NULL) {
    node_t *q = p->parent;
    rep (i, A) {
      if (q->next[i] == p) {
        s += id2alphabet(i);
        break;
      }
    }
    p = q;
  }
  reverse(all(s));
  return s;
}

void print_all() {
  rep (v, num_nodes) {
    node_t *p = &nodes[v];
    cout << v << ": " << get_prefix(p) << endl;
    rep (i, A) cout << " " << id2alphabet(i) << " -> " << get_prefix(p->next[i]) << endl;
    cout << endl;
  }
}



int main() {
  int N, M;
  while (cin >> N >> M) {
    vector<string> S(M);
    rep (i, M) cin >> S[i];

    construct(S);

    int L = 0;
    rep (i, M) L = max(L, (int)S[i].length());

    print_all();

    root->dp[0][0] = 1;
    rep (n, N) {
      rep (v, num_nodes) {
        node_t &p = nodes[v];
        rep (l, L + 1) {
          rep (a, 4) {
            node_t &tp = *p.next[a];
            int tl = l + 1;
            if (tl <= tp.max_suffix_cover) tl = 0;
            if (tl > L) continue;
            tp.dp[n + 1][tl] += p.dp[n][l];
            tp.dp[n + 1][tl] %= MOD;
          }
        }
      }
    }

    ll ans = 0;
    rep (v, num_nodes) {
      ans += nodes[v].dp[N][0];
      ans %= MOD;
    }
    cout << ans << endl;
  }

  return 0;
}

