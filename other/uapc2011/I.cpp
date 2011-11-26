#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <climits>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

struct minque {
  deque<int> vque;
  deque<int> mque;

  int size() {
    return vque.size();
  }

  void push_back(int v) {
    vque.push_back(v);
    while (!mque.empty() && mque.back() > v) mque.pop_back();
    mque.push_back(v);
  }

  void push_front(int v) {
    vque.push_front(v);
    if (mque.empty() || mque.front() > v) mque.push_front(v);
  }

  int get_min() {
    return mque.front();
  }

  int pop_front() {
    int v = vque.front();
    vque.pop_front();
    if (mque.front() == v) mque.pop_front();
    return v;
  }
};

struct hogeque {
  minque minq, maxq;

  int size() {
    return minq.size();
  }

  void push_back(int v) {
    minq.push_back(v);
    maxq.push_back(-v);
  }

  void push_front(int v) {
    minq.push_front(v);
    maxq.push_front(-v);
  }

  int pop_front() {
    maxq.pop_front();
    return minq.pop_front();
  }
};

int main() {
  int Q;
  while (1 == scanf("%d", &Q) && Q) {
    hogeque L, R;

    rep (q, Q) {
      int t, x;
      scanf("%d", &t);
      switch (t) {
        case 0:
          scanf("%d", &x);
          R.push_back(x);
          if (L.size() < R.size()) L.push_front(R.pop_front());
          break;
        case 1:
          printf("%d\n", L.pop_front());
          if (L.size() < R.size()) L.push_front(R.pop_front());
          break;
        case 2:
          printf("%d\n", L.minq.get_min());
          break;
        case 3:
          printf("%d\n", R.minq.get_min());
          break;
        case 4:
          scanf("%d", &x);
          printf("%d\n", L.minq.mque[x - 1]);
          break;
        case 5:
          scanf("%d", &x);
          printf("%d\n", R.minq.mque[x - 1]);
          break;
        case 6:
          printf("%d\n", -L.maxq.get_min());
          break;
        case 7:
          printf("%d\n", -R.maxq.get_min());
          break;
        case 8:
          scanf("%d", &x);
          printf("%d\n", -L.maxq.mque[x - 1]);
          break;
        case 9:
          scanf("%d", &x);
          printf("%d\n", -R.maxq.mque[x - 1]);
          break;
      }
    }
    puts("end");
  }
}
