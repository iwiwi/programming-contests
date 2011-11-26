#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <climits>
using namespace std;

#define pb push_back
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

const int CANNOT_END  = -10000000;
const int IN_LOOP     = -20000000;   // but cannot end...

string W[110], R[110];
int L[110];
vector<int> fadj[110], radj[110];
bool adj[110][110];

int memL[110][110][20], memR[110][110][20];
int depL[110][110][20], depR[110][110][20];

bool is_palindrome(string s, int from) {
  int l = s.length();
  for (int i = 0; from + i < l; ++i) {
    if (s[from + i] != s[l - i - 1]) return false;
  }
  return true;
}


int searchR(int wl, int wr, int le, int d = 0);

// L: (..le...) .... : wl
// R: (.. : wr) ????
int searchL(int wl, int wr, int le, int d = 0) {
  // printf("%*sL: %d %d %d\n", d, "", wl, wr, le);

  if (memL[wl][wr][le] == -2) return IN_LOOP - depL[wl][wr][le];
  if (memL[wl][wr][le] >= 0) return memL[wl][wr][le];
  memL[wl][wr][le] = -2;
  depL[wl][wr][le] = d;

  bool in_loop = false;
  int res = INT_MIN, loop_d = d;
  if (is_palindrome(W[wl], le) && adj[wl][wr]) res = L[wl] - le;  // end

  rep (i, radj[wr].size()) {
    int twr = radj[wr][i];

    int now = min(L[wl] - le, L[twr]);
    if (W[wl].compare(le, now, R[twr], 0, now) != 0) continue;

    int r;
    if (now == L[wl] - le) r = searchR(wl, twr, now, d + 1);
    else                   r = searchL(wl, twr, le + now, d + 1);

    if (r == CANNOT_END) {
      continue;
    } else if (r <= IN_LOOP) {
      int td = IN_LOOP - r;
      if (td <= d) {
        in_loop = true;
        loop_d = min(loop_d, td);
      }
    } else {
      res = max(res, 2 * now + r);
    }
  }

  if (res >= 0 && in_loop) throw 0;  // LOOP & CAN END !!!!!!!!!
  else {
    if (res < 0) res = CANNOT_END;
    if (in_loop) res = IN_LOOP - loop_d;
    // printf("%*sL: %d %d %d [%d]\n", d, "", wl, wr, le, res);
    return memL[wl][wr][le] = res;
  }
}

int searchR(int wl, int wr, int le, int d) {
  // printf("%*sR: %d %d %d\n", d, "", wl, wr, le);

  if (memR[wl][wr][le] == -2) return IN_LOOP - depR[wl][wr][le];
  if (memR[wl][wr][le] >= 0) return memR[wl][wr][le];
  memR[wl][wr][le] = -2;
  depR[wl][wr][le] = d;

  bool in_loop = false;
  int res = INT_MIN, loop_d = d;
  if (is_palindrome(R[wr], le) && adj[wl][wr]) res = L[wr] - le;  // end;

  rep (i, fadj[wl].size()) {
    int twl = fadj[wl][i];

    int now = min(L[wr] - le, L[twl]);
    if (R[wr].compare(le, now, W[twl], 0, now) != 0) continue;

    int r;
    if (now == L[wr] - le) r = searchL(twl, wr, now, d + 1);
    else                   r = searchR(twl, wr, le + now, d + 1);

    if (r == CANNOT_END) {
      continue;
    } else if (r <= IN_LOOP) {
      int td = IN_LOOP - r;
      if (td <= d) {
        in_loop = true;
        loop_d = min(loop_d, td);
      }
    }
    else {
      res = max(res, 2 * now + r);
    }
  }

  if (res >= 0 && in_loop) throw 0;  // LOOP & CAN END !!!!!!!!!
  else {
    if (res < 0) res = CANNOT_END;
    if (in_loop) res = IN_LOOP - loop_d;
    // printf("%*sR: %d %d %d [%d]\n", d, "", wl, wr, le, res);
    return memR[wl][wr][le] = res;
  }
}

int main() {
  int N, M;
  while (cin >> N >> M) {
    rep (i, N) {
      cin >> W[i];
      L[i] = W[i].length();

      R[i] = W[i];
      reverse(R[i].begin(), R[i].end());
    }

    rep (i, N) fadj[i].clear(), radj[i].clear();
    rep (i, M) {
      int a, b;
      cin >> a >> b;
      --a; --b;
      fadj[a].pb(b);
      radj[b].pb(a);
    }

    // DUMMY STRING!!
    int start_w = N++;
    W[start_w] = R[start_w] = "";
    L[start_w] = 0;
    fadj[start_w].clear(); radj[start_w].clear();
    rep (i, N - 1) fadj[start_w].pb(i), radj[start_w].pb(i);

    // adjacency matrix
    memset(adj, 0, sizeof(adj));
    rep (i, N) rep (j, fadj[i].size()) adj[i][fadj[i][j]] = true;
    // specially adjacent!!!!!?!?!!?
    rep (i, N) adj[i][start_w] = adj[start_w][i] = true;

    memset(memL, -1, sizeof(memL));
    memset(memR, -1, sizeof(memR));
    try {
      int res = 0;
      res = max(res, searchL(start_w, start_w, 0));
      printf("%d\n", res);
    } catch (...) {
      puts("-1");
    }
  }

  return 0;
}
