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

const double pth = 43.2 / 180.0 * M_PI;
const double px = cos(pth);
const double pz = sin(pth);

const double R = (1 + 1 / 365.24) * 360.0 / 180.0 * M_PI;


bool solve(double a, double b, double rot) {
  double hoge;
  // !printf("rot: %f\n", modf(rot / M_PI, &hoge) * M_PI);

  double z = sin(b);
  double t = cos(b);
  double x = t * cos(a);
  double y = t * sin(a);

  //fprintf(stderr, "%f %f %f\n", x, y, z);

  double dot = px * x + pz * z;
  double hx = px * dot;
  double hz = pz * dot;

  //fprintf(stderr ,"%f %f\n", hx, hz);

  double Y = y;
  double Z = hypot(x - hx, z - hz) * (z < hz ? -1.0 : 1.0);

  //fprintf(stderr, "%f %f\n", Y, Z);

  // double TY = Y * cos(R * T) - Z * sin(R * T);
  double TZ = Y * sin(rot) + Z * cos(rot);

  //fprintf(stderr, "%f\n", TZ);

  double tz = hz + TZ * cos(pth);

  //!fprintf(stderr, "%f\n", tz);
  
  return tz > 0;
}

long gepoch(int y, int m, int d) {
  y += 4800;
  if (m < 3) --y, m += 12;
  return 365L*y+y/4-y/100+y/400+(153*m-457)/5+d-32045;
}




int main() {
  {
    //solve(0.0, M_PI / 2.0, M_PI / 2);
    //solve(0.0, 0.0, M_PI / 2);
    //solve(M_PI / 2.0, 0.0, M_PI / 2);
    //return 0;
  }


  
  bool first = true;
  
  int mon, day, h, m;
  while (4 == scanf("%d/%d %d:%d", &mon, &day, &h, &m)) {
    if (!first) puts("");
    first = false;
    
    double T = gepoch(2012, mon, day) - gepoch(2012, 1, 1);
    T += (h * 60.0 + m) / (24.0 * 60.0);
    // printf("T=%f\n", T);

    

    int N;
    scanf("%d", &N);
    rep (i, N) {
      string name;
      int M;
      cin >> name >> M;

      bool ok = true;

      rep (i, M) {
        double a, b;
        cin >> a >> b;
        ok &= solve(a / 180.0 * M_PI, b / 180.0 * M_PI, T * R);
      }

      if (ok) cout << name << endl;
    }
  }
  
  return 0;
}

