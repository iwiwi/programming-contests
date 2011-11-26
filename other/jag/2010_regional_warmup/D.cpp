#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <complex>
#include <iostream>
#include <queue>
#include <set>
#include <cassert>

using namespace std;

const int INF = 987654321;

typedef long long ll;
typedef complex<double> p_t;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define pb push_back
#define mp make_pair

typedef vector<string> face;
typedef vector<face> dice;

/*
enum { FRONT, RIGHT, BACK, LEFT, TOP, BOTTOM };

#define ROTATE_X TOP, BACK, BOTTOM, FRONT
#define ROTATE_Y TOP, LEFT, BOTTOM, RIGHT
#define ROTATE_Z BACK, LEFT, FRONT, RIGHT

dice rorate_dice_common(dice d, int a, int b, int c, int d) {
  swap(p[a], p[b]);
  swap(p[b], p[c]);
  swap(p[c], p[d]);
}
*/

face rotate_face(face f) {
  face tf(3, string(3, ' '));
  rep (i, 3) rep (j, 3) tf[2 - j][i] = f[i][j];
  return tf;
}

dice rotate_dice_x(dice d) {
  dice td = d;
  td[4] = d[0];
  td[2] = rotate_face(rotate_face(d[4]));
  td[5] = rotate_face(rotate_face(d[2]));
  td[0] = d[5];

  td[1] = rotate_face(rotate_face(rotate_face(d[1])));
  td[3] = rotate_face(d[3]);

  return td;
}

dice rotate_dice_y(dice d) {
  dice td = d;
  td[4] = rotate_face(d[1]);
  td[1] = rotate_face(d[5]);
  td[5] = rotate_face(d[3]);
  td[3] = rotate_face(d[4]);

  td[0] = rotate_face(d[0]);
  td[2] = rotate_face(rotate_face(rotate_face(d[2])));

  return td;
}

dice rotate_dice_z(dice d) {
  swap(d[0], d[1]);
  swap(d[1], d[2]);
  swap(d[2], d[3]);
  return d;
}

void print_dice(dice d) {
  rep (i, 6) {
    printf("[%d]\n", i + 1);
    rep (y, d[i].size()) cout << d[i][y]  << endl;
  }
  cout << endl;
}

deque<pair<dice, int> > que;
set<dice> mem;
void push(dice d, int c) {
  if (mem.count(d)) return;
  que.push_back(mp(d, c));
  mem.insert(d);
}

int main() {
  freopen("D.txt", "r", stdin);

  dice d(6, face(3));
  rep (i, 6) {
    d[i][0] = string(".") + (char)('0' + i + 1) + string(".");
    d[i][1] = d[i][2] = "...";
  }

//   assert(d == rotate_dice_x(rotate_dice_x(rotate_dice_x(rotate_dice_x(d)))));
//   assert(d == rotate_dice_y(rotate_dice_y(rotate_dice_y(rotate_dice_y(d)))));
  
  //print_dice(d);
//   print_dice(rotate_dice_x(d));
//   print_dice(rotate_dice_y(d));
//   print_dice(rotate_dice_z(d));
  
//   print_dice(d);
//   d = rotate_dice_y(d);
//   print_dice(d);
//   d = rotate_dice_y(d);
//   print_dice(d);
//   d = rotate_dice_x(rotate_dice_x(rotate_dice_x(d)));
//   print_dice(d);
  // return 0;
  
  
  for (;;) {
    dice d(6, face(3));
    rep (i, 6) {
      rep (y, 3) {
        cin >> d[i][y];
        if (d[i][y][0] == '#') return 0;
      }
    }

    que.clear();
    mem.clear();
    
    // puts("hoge");

    que.push_back(mp(d, 0));
    mem.insert(d);
    while (!que.empty()) {
      dice d = que.front().first;
      int c = que.front().second;
      que.pop_front();

      bool ok0 = false, ok2 = false;
      rep (x, 3) ok0 |= d[0][2][x] == '*';
      rep (x, 3) ok2 |= d[2][2][x] == '*';

      if (ok0 && ok2) {
        printf("%d\n", c);
        // print_dice(d);
        break;
      }

      push(rotate_dice_x(d), c + 1); push(rotate_dice_x(rotate_dice_x(rotate_dice_x(d))), c + 1);
      push(rotate_dice_y(d), c + 1); push(rotate_dice_y(rotate_dice_y(rotate_dice_y(d))), c + 1);
      // push(rotate_dice_z(d), c + 1); push(rotate_dice_z(rotate_dice_z(rotate_dice_z(d))), c + 1);
    }
  }
}
