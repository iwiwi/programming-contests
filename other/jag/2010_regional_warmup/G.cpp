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

vector<double> quadratic(double a, double b, double c) {
  vector<double> res;
  if (fabs(a) < EPS) {
    if (fabs(b) > EPS) res.push_back(-c / b);
    else if (fabs(c) < EPS) return vector<double>(3, -1); // P“™Ž®
  }
  else {
    double d = b * b - 4 * a * c;
    if (d > EPS) {
      if (b > 0) res.push_back((-b - sqrt(d)) / (2 * a));
      else res.push_back((-b + sqrt(d)) / (2 * a));
      res.push_back(c / a / res[0]);
    }
    else if (d > -EPS) res.push_back(-b / (2 * a));
  }
  return res;
}

int N;
int M[60], L[60];
p_t P[60][110];
double T[60][110], B[60][110], E[60][110];

map<double, int> vs[60];

int num_v = 0;
vector<int> par;
vector<vector<int> > adj;
vector<vector<double> > wgh;

int v_id(int i, double t) {
  if (vs[i].count(t)) return vs[i][t];
  else {
    par.pb(num_v);
    return vs[i][t] = num_v++;
  }
}

int find(int v) {
  if (par[v] == v) return v;
  else return par[v] = find(par[v]);
}

void merge(int v, int w) {
  v = find(v);
  w = find(w);
  par[v] = w;
}

#define X(p) (p).real()
#define Y(p) (p).imag()

vector<double> mem;

double saiki(int v) {
  v = find(v);
  if (mem[v] >= 0.0) return mem[v];

  double res = 0.0;
  rep (i, adj[v].size()) if (adj[v][i] != v) {
    res = max(res, wgh[v][i] + saiki(adj[v][i]));
  }
  return mem[v] = res;
}

int main() {
  for (int ca = 1; ; ++ca) {
    scanf("%d", &N);
    if (N == 0) return 0;
    p_t C;
    scanf("%lf%lf", &C.real(), &C.imag());
    rep (i, N) {
      scanf("%d", &M[i]);
      rep (j, M[i]) {
        scanf("%lf%lf%lf", &P[i][j].real(), &P[i][j].imag(), &T[i][j]);
        P[i][j] -= C;
      }
      scanf("%d", &L[i]);
      rep (j, L[i]) {
        scanf("%lf%lf", &B[i][j], &E[i][j]);
      }
      P[i][M[i]] = P[i][M[i] - 1];
      T[i][M[i]] = 1010;
      ++M[i];
    }

    num_v = 0;
    par.clear();

    // Trivial events
    rep (i, N) {
      vs[i].clear();
      rep (j, M[i]) v_id(i, T[i][j]);
      rep (j, L[i]) {
        v_id(i, B[i][j]);
        v_id(i, E[i][j]);
      }
    }

    // Intersection events
    rep (i1, N) rep (j1, M[i1] - 1) {
      rep (i2, i1) rep (j2, M[i2] - 1) {
        double tb = max(T[i1][j1], T[i2][j2]);
        double te = min(T[i1][j1 + 1], T[i2][j2 + 1]);
        if (te < tb) continue;

        p_t v1 = (P[i1][j1 + 1] - P[i1][j1]) / (T[i1][j1 + 1] - T[i1][j1]);
        p_t v2 = (P[i2][j2 + 1] - P[i2][j2]) / (T[i2][j2 + 1] - T[i2][j2]);
        p_t p1 = P[i1][j1] - v1 * T[i1][j1];
        p_t p2 = P[i2][j2] - v2 * T[i2][j2];

        double a = X(v1) * Y(v2) - Y(v1) * X(v2);
        double b = (X(v1) * Y(p2) + Y(v2) * X(p1)) - (Y(v1) * X(p2) + X(v2) * Y(p1));
        double c = X(p1) * Y(p2) - Y(p1) * X(p2);

        vector<double> ts = quadratic(a, b, c);
        rep (i, ts.size()) {
          double t = ts[i];
          if (t < T[i1][j1] || T[i1][j1 + 1] < t) continue;
          if (t < T[i2][j2] || T[i2][j2 + 1] < t) continue;
          if (dot(p1 + v1 * t, p2 + v2 * t) < 0) continue;
          merge(v_id(i1, t), v_id(i2, t));
        }
      }
    }

    // Parallel events
    rep (i1, N) rep (j1, M[i1] - 1) {
      rep (i2, i1) rep (j2, M[i2] - 1) {
        double tb = max(T[i1][j1], T[i2][j2]);
        double te = min(T[i1][j1 + 1], T[i2][j2 + 1]);
        if (te < tb) continue;

        p_t v1 = (P[i1][j1 + 1] - P[i1][j1]) / (T[i1][j1 + 1] - T[i1][j1]);
        p_t v2 = (P[i2][j2 + 1] - P[i2][j2]) / (T[i2][j2 + 1] - T[i2][j2]);
        p_t p1 = P[i1][j1] - v1 * T[i1][j1];
        p_t p2 = P[i2][j2] - v2 * T[i2][j2];

        if (abs(v1) > EPS && abs(v2) > EPS && fabs(det(v1, v2)) / abs(v1) / abs(v2) > EPS) continue;

        p_t q1b = p1 + v1 * tb, q1e = p1 + v1 * te;
        p_t q2b = p2 + v2 * tb, q2e = p2 + v2 * te;
        if (fabs(det(q1b, q2b)) / abs(q1b) / abs(q2b) > EPS || dot(q1b, q2b) < 0) continue;
        if (fabs(det(q1e, q2e)) / abs(q1e) / abs(q2e) > EPS || dot(q1e, q2e) < 0) continue;

        vector<double> ts;
        for (iter(vs[i1]) ite = vs[i1].lower_bound(tb - EPS); ite != vs[i1].end() && ite->first < te + EPS; ++ite) ts.pb(ite->first);
        for (iter(vs[i2]) ite = vs[i2].lower_bound(tb - EPS); ite != vs[i2].end() && ite->first < te + EPS; ++ite) ts.pb(ite->first);
        sort(all(ts));
        ts.erase(unique(all(ts)), ts.end());
        rep (k, ts.size()) merge(v_id(i1, ts[k]), v_id(i2, ts[k]));
      }
    }

    // Merge almost same vertices (necessary?)
    rep (i, N) {
      vector<pair<double, int> > ts;
      tr (vs[i], ite) ts.pb(*ite);
      rep (j, ts.size() - 1) if (ts[j + 1].first - ts[j].first < EPS) merge(ts[j].second, ts[j + 1].second);
    }

    // Edges
    adj.clear();
    wgh.clear();
    adj.resize(num_v);
    wgh.resize(num_v);
    rep (i, N) {
      iter(vs[i]) ite1 = vs[i].begin();
      while (ite1 != vs[i].end()) {
        iter(vs[i]) ite2 = ite1;
        ++ite2;
        if (ite2 == vs[i].end()) break;

        int v = find(ite1->second);
        int w = find(ite2->second);

        double t1 = ite1->first;
        double t2 = ite2->first;

        if (v != w) {
          double s = 0.0;
          rep (j, L[i]) {
            double tb = max(t1, B[i][j]);
            double te = min(t2, E[i][j]);
            s += max(0.0, te - tb);
          }
          adj[v].pb(w);
          wgh[v].pb(s);
        }
        ++ite1;
      }
    }

    // Compute answer
    double ans = 0.0;
    mem.clear();
    mem.resize(num_v, -1.0);
    rep (i, N) ans = max(ans, saiki(find(vs[i][0.0])));
    printf("%.20f\n", ans);
  }

  return 0;
}

