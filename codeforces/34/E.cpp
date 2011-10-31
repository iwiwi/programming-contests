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

const double EPS = 1E-10;

int main() {
  int N, T;
  while (2 == scanf("%d%d", &N, &T)) {
    double X[20], V[20], M[20];
    rep (i, N) scanf("%lf%lf%lf", X + i, V + i, M + i);

    vector<pair<double, int> > ord(N);
    rep (i, N) ord[i] = mp(X[i], i);
    sort(all(ord));
    
    double t = 0;
    while (t < T - EPS) {
      double dt = T - t;
      rep (k, N - 1) {
        int i = ord[k].second, j = ord[k + 1].second;
        
        double dx = X[j] - X[i];
        double v = V[i] - V[j];
        if (v > EPS) dt = min(dt, dx / v);
      }
      
      t += dt;
      rep (i, N) X[i] += V[i] * dt;

      rep (k, N - 1) {
        int i = ord[k].second, j = ord[k + 1].second;
        
        if (X[i] < X[j] - EPS) continue;
        double m1 = M[i], m2 = M[j];
        double v1 = V[i], v2 = V[j];
        double tv1 = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
        double tv2 = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);
        V[i] = tv1;
        V[j] = tv2;
      }
    }

    rep (i, N) printf("%.10f\n", X[i]);
  }
  
  return 0;
}

