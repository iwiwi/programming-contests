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

vector<string> lines;
vector<vector<int> > linei;

#define CHK(a, b, c) if (b < a || c < b) return false

vector<int> get(int i) {
  if (i >= (int)linei.size()) return vector<int>();
  else return linei[i];
}

bool isA() {
  CHK(2, linei.size(), 101);
  rep (i, linei.size() - 1) {
    const vector<int> &line = linei[i];
    if (line.size() != 4) return false;
    rep (i, 4) if (line[i] < 1 || 1000000000 < line[i]) return false;
  }
  const vector<int> &line = linei.back();
  if (line[0] == 0 && line[1] == 0 && line[2] == 0 && line[3] == 0) return true;
  else return false;
}

/*
bool isD() {
  int i;
  for (;;) {
    vector<int> line = get(i++);
    if (line.size() != 4) return false;
    int N = line[0];
    int P = line[1];
    int Q = line[2];
    int D = line[3];
    if (N == 0 && P == 0 && Q == 0 && D == 0) return true;

    CHK(1, N, 1000);
    CHK(1, P, 1000);
    CHK(1, Q, 100000);
    CHK(1, D, 100000);

    int prvd = 0;
    rep (j, N) {
      line = get(i++);
      if (line.size() != 3) return false;
      int d = line[0];
      int a = line[1];
      int b = line[2];
      CHK(prvd + 1, d, D - 1);
      CHK(1, a, 100000);
      CHK(1, b, 100000);
    }
  }
}
*/

bool isG() {
  CHK(2, linei.size(), 21);
  rep (i, linei.size() - 1) {
    const vector<int> &line = linei[i];
    if (line.size() != 4) return false;
    int N = line[0];
    int M = line[1];
    int A = line[2];
    int B = line[3];
    CHK(1, N, 100000);
    CHK(1, M, 100000);
    CHK(1, A, N);
    CHK(1, B, N);
  }
  const vector<int> &line = linei.back();
  if (line[0] == 0 && line[1] == 0 && line[2] == 0 && line[3] == 0) return true;
  else return false;
}

int main() {
  for (;;) {
    lines.clear();
    for (;;) {
      string line;
      getline(cin, line);
      if (line == "@@@@@@@@@@@@@@@@@@@@") return 0;
      else if (line == "@@@@@@@@@@") break;
      else lines.pb(line);
    }
    int N = lines.size();

    if (lines.back() == "#") {
      puts("B");
      continue;
    }

    linei.clear();
    linei.resize(N);
    rep (i, N) {
      stringstream ss(lines[i]);
      for (int t; ss >> t; ) linei[i].pb(t);
    }

    if (linei[0].size() == 1) {
      // E
      puts("E");
    }
    else if (linei[0].size() == 2) {
      // C
      puts("C");
    }
    else if (linei[0].size() == 3) {
      // F
      puts("F");
    }
    else if (linei[0].size() == 4) {
      if (linei[1].size() == 3) {
        // D
        puts("D");
      }
      else {
        // A, G
        bool a = isA();
        bool g = isG();
        if (a && g) puts("?");
        else if (a) puts("A");
        else if (g) puts("G");
        else puts("?");  // !?!?!?!?!?
      }
    }
  }

  return 0;
}

