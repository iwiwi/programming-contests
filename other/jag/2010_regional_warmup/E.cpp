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

const double EPS = 1e-10;
typedef complex<double> p_t;
namespace std {
  istream &operator>>(istream &is, p_t &p) {
    is >> p.real() >> p.imag();
    return is;
  }
}

double dot(const p_t &p, const p_t &q) { return real(conj(p) * q); }
double det(const p_t &p, const p_t &q) { return imag(conj(p) * q); }

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

bool on_ls(p_t p, p_t p1, p_t p2) {
  return abs(p1-p)+abs(p2-p)-abs(p1-p2) < EPS;
}

p_t cross_l_l(const p_t &p1, const p_t &d1, const p_t &p2, const p_t &d2) {
  double d = det(d1, d2);
  assert(abs(d) > EPS);
  return p1 + d1 * det(p2 - p1, d2) / d;
}

bool intersect_polygon(p_t a, p_t b, const vector<p_t> &ps) {
  if (a == b) return false;

  int n = ps.size();
  int ai = -1, bi = -1;
  rep (i, n) {
    if (abs(ps[i] - a) < EPS) ai = i;
    if (abs(ps[i] - b) < EPS) bi = i;
  }

  // cout << a << b << endl;
  // printf("ai=%d, bi=%d\n", ai, bi);

  rep (i, n) {
    int j = (i + 1) % n;
    if (i == ai || j == ai || i == bi || j == bi) continue;
    const p_t &p = ps[i], &q = ps[j];

    // cout << p << q << endl;

    if (on_ls(a, p, q)) {
      if (ccw(p, q, b) > 0) return true;
    }
    else if (on_ls(b, p, q)) {
      if (ccw(p, q, a) > 0) return true;
    }
    else if (intersect(a, b, p, q)) return true;
  }

  rep (t, 2) {
    if (ai != -1) {
      const p_t &p = ps[(ai - 1 + n) % n];
      const p_t &q = ps[(ai + 1) % n];

      // if (dot(p - a, q - a) > 0) {

      // }

      // puts("ccw?");
      // cout << p << a << q << endl;
      // cout << " " << ccw(a, q, b) << endl;
      // cout << " " << ccw(a, b, p) << endl;
      // printf("det: %f\ndet: %f\n", det(q - a, b - a), det(b - a, p - a));
      if (ccw(p, a, q) > 0) {
        if (det(q - a, b - a) > 0 && det(b - a, p - a) > 0) return true;
      }
      else {
        if (ccw(a, p, b) > 0 && ccw(a, b, q) > 0);
        else return true;
      }

      // if (ccw(a, q, b) > 0 && ccw(a, b, p) > 0) return true;
    }
    swap(a, b);
    swap(ai, bi);
  }

  return false;
}

p_t perpendicular(p_t p, p_t a, p_t b) {
  p_t d = (b - a) / abs(b - a);
  return a + d * dot(p - a, d);
}

const p_t o = p_t(0, 0);

int N, M[110];
p_t A;
vector<p_t> P[110];

vector<p_t> Q;
double goal[510];

double pot[510];
bool vis[510];

bool reachable(const p_t &a, const p_t &b) {
  // cout << "reachable?:" << a << b << endl;
  rep (i, N) if (intersect_polygon(a, b, P[i])) return false;
  return true;
}

bool on_ray(const p_t &p, const p_t &s, p_t d) {
  // TODO simplify
  // printf("%e %f\n", fabs(det(p - s, d)) , dot(p - s, d));

  //
  p_t v = (p - s) / abs(p - s);
  d /= abs(d);

  if (fabs(det(v, d)) > EPS) return false;
  if (dot(v, d) < -EPS) return false;
  return true;
}

int main() {
  // cerr << perpendicular(p_t(0.5, 0.5), p_t(0.0, 0.0), p_t(100.0, 0.0)) << endl;
  // cerr << perpendicular(p_t(0.5, 0.5), p_t(0.0, 0.0), p_t(0.0, 100.0)) << endl;
  // return 0;

  for (int t = 0; ; ++t) {
    cin >> N;
    if (N == 0) return 0;
    p_t b;
    cin >> b;
    cerr << b << endl;
    A = o - b;

    Q.clear();
    Q.pb(A);
    rep (i, N) {
      int m;
      cin >> m;
      M[i] = m;
      P[i].resize(m);
      rep (j, m) {
        cin >> P[i][j];
        P[i][j] -= b;
        Q.pb(P[i][j]);
      }
    }


    // if (t != 20) continue;
    // printf("%3d %3d ", t, (int)Q.size());
    // if (Q.size() > 400 && (t == 22 || t == 23)) { puts(""); continue; }
    // continue;

    cerr << o << " " << A << endl;


    double mind = 1E30;
    rep (i, Q.size()) if (i > 0) {
      mind = min(mind, abs(Q[i] - A));
    }
    // printf("mind = %f\n", mind);

    // Already safe?
    rep (i, N) {
      if (intersect_polygon(o, A, P[i])) {
        puts("0.0000000000");
        goto done;
      }
    }


    rep (k, Q.size()) {
      const p_t &p = Q[k];
      goal[k] = 1E30;

      // if (p != p_t(-3.0, -3.0)) continue;

      // cerr << Q[k] - A << "=========" << endl;

      // Case 1
      rep (i, N) rep (j, P[i].size()) {
        const p_t &a = P[i][(j + M[i] - 1) % M[i]];
        const p_t &b = P[i][j];
        const p_t &c = P[i][(j + 1) % M[i]];

        // Bad ?
        // if (det(c - b, b) > -EPS && det(b, a - b) > -EPS) continue;
        if (det(c - b, b) > 0 && det(b, a - b) > 0) continue;

        // cerr << a-A << b-A << c-A << endl;

        // Unreachable?
        if (reachable(p, b)) {
          // cerr << a-A << b-A << c-A << endl;
          cerr << "Case 1: " << b - A << endl;
          goal[k] = min(goal[k], abs(b - p));
        }
      }

      // Case 2 & 3
      rep (i, N) rep (j, P[i].size()) {
        const p_t &a = P[i][j];
        p_t h = perpendicular(p, o, a);
        if (abs(h - a) < EPS) continue;

        cerr << " " << a << endl;

        // if (fabs(abs(h - p) - 139.0524489722) < EPS) {
        //   cout << a << endl;
        //   cout << h << endl;
        //   puts("oohohohohoho");
        //   cout << on_ray(h, a, a) << endl;
        //   exit(0);
        // }

        if (on_ray(h, a, a) && reachable(p, h)) {
          // if (k == 1) {
          //   cout << p-A << " " << h-A << endl;
          //   puts("----------------------------------------------------------------------------------------------");
          //   reachable(p, h);
          //   puts("----------------------------------------------------------------------------------------------");
          //   cerr << "Case 2: " << h-A << " " << abs(h - p) << endl;
          //   exit(EXIT_FAILURE);
          // }
          goal[k] = min(goal[k], abs(h - p));
          cerr << "Case 2: " << h-A << endl;
        }
        else {
          cerr << " " << a << endl;

          rep (i2, N) rep (j2, M[i]) {
            const p_t &b = P[i2][j2];
            const p_t &c = P[i2][(j2 + 1) % M[i]];
            if (fabs(det(b - c, a)) < EPS) continue;  // parallel
            p_t x = cross_l_l(a, a, b, c - b);
            cerr << "  " << b << c << endl;
            fprintf(stderr, "  %d, %d, %f, %d\n", on_ls(x, b, c), on_ray(x, a, a), abs(x - a), reachable(p, x));
            if (on_ls(x, b, c) && on_ray(x, a, a) && abs(x - a) > EPS && reachable(p, x)) {
              cerr << "Case 3: " << x - A << endl;
              goal[k] = min(goal[k], abs(x - p));
            }
          }
        }
      }
      fprintf(stderr, "%.f\t", abs(Q[k]-A));
      cerr << Q[k]-A << " " << goal[k] << endl;
    }

    {
      memset(vis, 0, sizeof(vis));
      int K = Q.size();
      rep (i, K) pot[i] = 1E30;
      pot[0] = 0.0;
      double ans = 1E30;
      rep (i, K) {
        int minv = -1;
        rep (v, K) if (!vis[v] && (minv == -1 || pot[v] < pot[minv])) minv = v;

        ans = min(ans, pot[minv] + goal[minv]);

        vis[minv] = true;
        rep (w, K) if (reachable(Q[minv], Q[w])) {
          pot[w] = min(pot[w], pot[minv] + abs(Q[w] - Q[minv]));
        }
      }

      printf("%f\n", ans);
    }

  done:;
    cerr << "\n\n\n\n\n";
  }


  /*
  vector<p_t> ps(4);
  ps[0] = p_t(0, 0);
  ps[1] = p_t(1, 0);
  ps[2] = p_t(1, 1);
  ps[3] = p_t(0, 1);

  cerr << intersect_polygon(p_t(-0.5, 0.5), p_t(1.5, 0.5), ps) << endl;

  cerr << intersect_polygon(p_t(0, 0), p_t(0.5, 0.5), ps) << endl;
  cerr << intersect_polygon(p_t(0, 0), p_t(1, 1), ps) << endl;
  cerr << intersect_polygon(p_t(0, 0), p_t(2, 2), ps) << endl;

  cerr << intersect_polygon(p_t(0, 0), p_t(0.5, 0), ps) << endl;
  cerr << intersect_polygon(p_t(0, 0), p_t(1, 0), ps) << endl;
  cerr << intersect_polygon(p_t(0, 0), p_t(2, 0), ps) << endl; // maybe strange

  cerr << intersect_polygon(p_t(0, 0), p_t(-0.5, -0.5), ps) << endl;
  cerr << intersect_polygon(p_t(0, 0), p_t(-0.5, 0), ps) << endl;
  */



  return 0;
}

