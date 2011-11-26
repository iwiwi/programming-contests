#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back

int H, W;
char fld[60][60];
bool vis[60][60];

enum {TOP, FRONT, RIGHT, BACK, LEFT, BOTTOM};
#define ROTATE_X TOP, FRONT, BOTTOM, BACK
#define ROTATE_Y TOP, RIGHT, BOTTOM, LEFT
#define ROTATE_Z BACK, LEFT, FRONT, RIGHT

void rotate(vector<char> &p, int a, int b, int c, int d) {
  swap(p[a], p[b]);
  swap(p[b], p[c]);
  swap(p[c], p[d]);
}

void saiki(int x, int y, vector<char> &p) {
  if (vis[y][x]) return;
  if (fld[y][x] == '.') return;
  p[BOTTOM] = fld[y][x];
  vis[y][x] = true;

  {
    rotate(p, ROTATE_X);
    saiki(x, y - 1, p);
    rotate(p, ROTATE_X); rotate(p, ROTATE_X); rotate(p, ROTATE_X);
  }
  {
    rotate(p, ROTATE_X); rotate(p, ROTATE_X); rotate(p, ROTATE_X);
    saiki(x, y + 1, p);
    rotate(p, ROTATE_X);
  }
  {
    rotate(p, ROTATE_Y);
    saiki(x - 1, y, p);
    rotate(p, ROTATE_Y); rotate(p, ROTATE_Y); rotate(p, ROTATE_Y);
  }
  {
    rotate(p, ROTATE_Y); rotate(p, ROTATE_Y); rotate(p, ROTATE_Y);
    saiki(x + 1, y, p);
    rotate(p, ROTATE_Y);
  }
}

vector<vector<char> > enumerate(const vector<char> &org) {
  vector<vector<char> > res(24);
  res[0] = org;
  for (int i = 1; i < 24; ++i) {
    res[i] = res[i - 1];
    rotate(res[i], ROTATE_Z);
    if (i % 8 == 0) rotate(res[i], ROTATE_X);
    else if (i % 4 == 0) rotate(res[i], ROTATE_Y);
  }
  return res;
}

int main() {
  scanf("%d%d", &H, &W);
  memset(fld, '.', sizeof(fld));
  for (int y = 1; y <= H; ++y) {
    for (int x = 1; x <= W; ++x) {
      scanf(" %c", &fld[y][x]);
    }
  }

  vector<char> colors;
  for (int y = 1; y <= H; ++y) {
    for (int x = 1; x <= W; ++x) {
      if (fld[y][x] != '.' && fld[y][x] != '#') colors.pb(fld[y][x]);
    }
  }
  sort(colors.begin(), colors.end());
  colors.erase(unique(colors.begin(), colors.end()), colors.end());
  if (colors.size() != 6) {
    puts("No");
    return 0;
  }
  
  vector<vector<char> > cubes;
  for (int y = 1; y <= H; ++y) {
    for (int x = 1; x <= W; ++x) {
      if (fld[y][x] == '.' || vis[y][x]) continue;
      vector<char> cube(6, '!');
      saiki(x, y, cube);
      cubes.pb(cube);
    }
  }
//   rep (i, cubes.size()) {
//     rep (j, 6) printf("%c ", cubes[i][j]); puts("");
//   }
  if (cubes.size() != 8) {
    puts("No");
    return 0;
  }
  rep (i, cubes.size()) {
    if (count(cubes[i].begin(), cubes[i].end(), '#') != 3) {
      puts("No");
      return 0;
    }
  }

  vector<vector<char> > cube_rots[8];
  rep (i, 8) cube_rots[i] = enumerate(cubes[i]);

  sort(colors.begin(), colors.end());
  do {
    vector<vector<char> > colors_rots = enumerate(colors);
    rep (k, colors_rots.size()) {
      bool f = false;
      rep (i, 8) {
        rep (j, cube_rots[i].size()) {
          if (colors_rots[k][BOTTOM] == cube_rots[i][j][BOTTOM] &&
              colors_rots[k][LEFT  ] == cube_rots[i][j][LEFT  ] &&
              colors_rots[k][FRONT ] == cube_rots[i][j][FRONT ]) {
            f = true;
          }
        }
      }
      if (!f) goto dmp;
    }

    puts("Yes");
    return 0;
  dmp:;
  } while (next_permutation(colors.begin(), colors.end()));

  puts("No");
  return 0;
}
