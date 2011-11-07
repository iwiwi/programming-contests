#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <climits>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair

typedef vector<int> poly_t;
const int L = 60;
const poly_t POLY_MAX(L, INT_MAX);

poly_t parse(string s) {
  poly_t res(L);

  rep (i, s.length()) if (s[i] == '+') s[i] = ' ';
  stringstream ss(s);
  for (string t; ss >> t;) {
    string a, b;
    bool x = false;
    rep (i, t.length()) if (t[i] == 'x') {
      a = t.substr(0, i);
      b = t.substr(i + 1);
      x = true;
    }
    // cout << "!" << t << ": " <<  a << "/" << b << endl;
    int d = 1, c = 1;

    if (x == false) {
      d = 0;
      c = atoi(t.c_str());
    }
    else {
      if (!b.empty()) d = atoi(b.substr(1).c_str());
      if (!a.empty()) c = atoi(a.c_str());
    }

    res[L - d - 1] = c;
    // printf("%d x^ %d\n", c, d);
  }
  // puts("");

  return res;
}

bool is_zero(const poly_t &p) {
  rep (i, L) if (p[i] != 0) return false;
  return true;
}

bool is_less(const poly_t &a, const poly_t &b) {
  rep (i, L) {
    if (a[i] < b[i]) return true;
    if (a[i] > b[i]) return false;
  }
  return false;
}

poly_t mynegate(poly_t p) {
  rep (i, L) p[i] *= -1;
  return p;
}

poly_t add(poly_t a, poly_t b) {
  poly_t p(L);
  rep (i, L) p[i] = a[i] + b[i];
  return p;
}

void output(poly_t ans) {
  bool first = true;
  rep (i, L) {
    if (ans[i] == 0) continue;

    if (first) first = false;
    else putchar('+');

    if (i == L - 1) printf("%d", ans[i]);
    else {
      if (ans[i] != 1) printf("%d", ans[i]);
      putchar('x');
      int d = L - i - 1;
      if (d > 1) printf("^%d", d);
    }
  }
  if (first) puts("0");
  else puts("");
}


const int MAX_V = 60;
struct e_t {
  int to;
  poly_t cap;
  int rev;
};

int V, S, T;
vector<e_t> adj[MAX_V];

void add_edge(int i, int j, poly_t c) {
  adj[i].push_back((e_t){j, c, adj[j].size()});
  adj[j].push_back((e_t){i, poly_t(L), adj[i].size() - 1});
}

int prvv[MAX_V], prve[MAX_V];

poly_t max_flow() {
  poly_t f(L);
  for (;;) {
    memset(prvv, -1, sizeof(prvv));
    queue<int> que;
    prvv[S] = -2;
    que.push(S);

    while (!que.empty() && prvv[T] == -1) {
      int v = que.front();
      que.pop();
      rep (i, adj[v].size()) {
        e_t &e = adj[v][i];
        if (prvv[e.to] == -1 && !is_zero(e.cap)) {
          prvv[e.to] = v;
          prve[e.to] = i;
          que.push(e.to);
        }
      }
    }

    if (prvv[T] == -1) return f;

    poly_t a = POLY_MAX;
    for (int i = T; i != S; i = prvv[i]) {
      poly_t &b = adj[prvv[i]][prve[i]].cap;
      if (is_less(b, a)) a = b;
    }
    for (int i = T; i != S; i = prvv[i]) {
      e_t &e = adj[prvv[i]][prve[i]];
      e.cap = add(e.cap, mynegate(a));
      adj[i][e.rev].cap = add(adj[i][e.rev].cap, a);
    }

    /// printf("aug: "); output(a);
    f = add(f, a);
  }
  return f;
}

int main() {
  for (;;) {
    int N, M;
    cin >> N >> M;
    if (N == 0 && M == 0) return 0;

    V = N;
    S = 0;
    T = N - 1;
    rep (i, N) adj[i].clear();

    rep (i, M) {
      int a, b;
      string s;
      cin >> a >> b >> s;
      --a;
      --b;
      add_edge(a, b, parse(s));
      add_edge(b, a, parse(s));
      // output(parse(s));
    }

    poly_t ans = max_flow();
    output(ans);
  }
}
