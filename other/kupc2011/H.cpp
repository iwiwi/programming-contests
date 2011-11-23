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

int N;
double save_cost[100010];  // Temp t -> save_cost[i] * t

double solve_half(vector<double> &C) {  // Energy 1 -> hoge
  N = C.size();

  // save_cost
  {
    save_cost[N] = 0.0;

    for (int i = N - 1; i >= 0; --i) {
      // そこを t にして後ろを今までのやつ
      double a = C[i] + save_cost[i + 1];

      // そこをハードコアにして後ろなし
      double b = (N - i) * C[i];

      save_cost[i] = min(a, b);
    }
  }

  double res = 0.0;

  double way_cost = 0.0;
  for (int i = 0; i < N; ++i) {
    // t'=0
    if (i > 0) {
      double t1 = 1 / way_cost;
      double ts1 = t1 * i;
      res = max(res, ts1);
    }

    // t=t'
    double t2 = 1 / (way_cost + save_cost[i]);
    double ts2 = t2 * N;
    res = max(res, ts2);
    
    way_cost += C[i];
  }

  return res;
}

int main() {
  int T, E;
  while (2 == scanf("%d%d", &T, &E)) {
    vector<double> L(T), R(T);
    double C;

    rep (i, T) scanf("%lf", &L[i]); reverse(all(L));
    scanf("%lf", &C);
    rep (i, T) scanf("%lf", &R[i]);

    double lts = solve_half(L);
    double rts = solve_half(R);
    // printf("lts: %f\nrts:%f\n", lts, rts);

    double res = 0.0;

    // 真ん中だけ 1 回
    double ts1 = E / C;
    res = max(res, ts1);
    // printf("ts1: %f\n", ts1);

    // 真ん中に居続けるより外に行きたい
    double ts2a = E / (C / T + 1 / lts + 1 / rts);
    double t2 = ts2a / T;
    double ts2 = t2 * (T + 1);
    
    // double coe = 1 / rts + 1 / lts + 1 / C / T;
    // printf("%f + %f + %f\n", 1 / rts, 1 / lts, 1 / C / T);
    // double ts2 = E / coe;
    // printf("ts2: %f\n", ts2);
    res = max(res, ts2);

    printf("%.10f\n", res);
  }

  return 0;
}
