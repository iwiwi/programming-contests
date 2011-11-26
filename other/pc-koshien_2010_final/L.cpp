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

#include <complex>
typedef complex<double> p_t;
const double EPS = 1E-10;

double dot(const p_t &p, const p_t &q) { return real(conj(p) * q); }
double det(const p_t &p, const p_t &q) { return imag(conj(p) * q); }

double dist_l_p(const p_t &p, const p_t &a, const p_t &u) {
  return abs(det(p - a, u)) / abs(u);
}

double dist_ls_p(const p_t &p, const p_t &a, const p_t &b) {
  if (dot(b - a, p - a) < EPS) return abs(p - a);
  if (dot(a - b, p - b) < EPS) return abs(p - b);
  return dist_l_p(p, a, b - a);
}
int ccw(p_t a, p_t b, p_t c) {
  b -= a; c -= a;
  if (det(b, c) > EPS) return 1;          // ccw
  if (det(b, c) < -EPS) return -1;        // cw
  if (dot(b, c) < -EPS) return 2;         // c-a-b
  if (norm(b) < norm(c) - EPS) return -2; // a-b-c
  return 0;                               // a-c-b, b==c
}

bool intersect(p_t p1, p_t p2, p_t p3, p_t p4) {
  return ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0
         && ccw(p3, p4, p1) * ccw(p3, p4, p2) <=0 ;
}

bool contain(const vector<p_t> &po, const p_t &p) {
  bool in = false;
  for (int i = 0; i < po.size(); i++) {
    p_t a = po[i] - p, b = po[(i + 1) % po.size()] - p;
    if (imag(a) > imag(b)) swap(a, b);
    if (imag(a) < EPS && EPS < imag(b) && det(a, b) < -EPS) in = !in;
    if (fabs(det(a, b)) < EPS && dot(a, b) < EPS) return true; // 辺上
  }
  return in;
}

bool intersect_po_po(const vector<p_t> &ps, const vector<p_t> &qs) {
  int nps = ps.size(), nqs = qs.size();
  rep (i, nps) rep (j, nqs) {
    if (intersect(ps[i], ps[(i + 1) % nps], qs[j], qs[(j + 1) % nqs])) return true;
  }
  rep (i, nps) if (contain(qs, ps[i])) return true;
  rep (j, nqs) if (contain(ps, qs[j])) return true;

  // !?!??!?!?!?!?!?!?!?
  rep (i, nps) rep (j, nqs) if (abs(ps[i] - qs[j]) < 0.01) return true;
  rep (i, nps) rep (j, nqs) if (dist_ls_p(qs[j], ps[i], ps[(i + 1) % nps]) < 0.01) return true;
  rep (i, nps) rep (j, nqs) if (dist_ls_p(ps[i], qs[j], qs[(j + 1) % nqs]) < 0.01) return true;

  return false;
}

int main() {
  for (;;) {
    int N, D;
    scanf("%d%d", &N, &D);
    if (N == 0 && D == 0) return 0;

    p_t P[110], Q[110], R[110];
    vector<p_t> A[110];
    rep (i, N) {
      A[i].resize(3);
      rep (j, 3) scanf("%lf%lf", &A[i][j].real(), &A[i][j].imag());
      rep (j, 3) {
        if (fabs(abs(A[i][j] - A[i][(j + 1) % 3]) - abs(A[i][j] - A[i][(j + 2) % 3])) < EPS) {
          P[i] = A[i][(j + 1) % 3];
          Q[i] = A[i][(j + 2) % 3];
          R[i] = A[i][j];
        }
      }
    }

    bool adj[110][110];
    memset(adj, 0, sizeof(adj));
    rep (i, N) adj[i][i] = true;

    rep (i, N) {
      const p_t &p = P[i];
      const p_t &q = Q[i];
      const p_t &r = R[i];

      p_t v = q - p;
      v /= abs(v);
      v *= polar(1.0, M_PI / 2.0);
      v *= D;
      if (dot(v, r - p) < -EPS) v *= -1;

      vector<p_t> beam;
      beam.pb(p);
      beam.pb(q);
      beam.pb(q + v);
      beam.pb(p + v);
      // rep (j, beam.size()) cout << beam[j]; cout << endl;

      rep (j, N) if (i != j) {
        adj[i][j] = intersect_po_po(beam, A[j]);
      }
    }

    rep (k, N) rep (i, N) rep (j, N) adj[i][j] |= adj[i][k] & adj[k][j];

    bool done[110] = {0};
    int ans = 0;
    rep (i, N) {
      if (done[i]) continue;
      int indeg = 0;
      rep (j, N) if (adj[i][j] && adj[j][i]) {
        done[j] = true;
        rep (k, N) if (adj[k][j] && !adj[j][k]) ++indeg;
      }
      if (indeg == 0) ++ans;
    }
    printf("%d\n", ans);
  }

  return 0;
}

