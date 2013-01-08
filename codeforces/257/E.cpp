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

typedef long long ll;
const ll INF = 1LL << 60;

inline void printll(ll x) {
#ifdef LOCAL
  printf("%lld\n", x);
#else
  printf("%I64d\n", x);
#endif
}



typedef int val_t;

val_t sum(int i, val_t *bit) {
  val_t s = 0;
  for (; i > 0; i -= i & -i) s += bit[i];
  return s;
}

void add(int i, val_t v, val_t *bit, int n) {
  for (; i <= n; i += i & -i) bit[i] += v;
}


int N, M;
int waiting_bit[100010];
int T[100010], S[100010], F[100010];
ll ans[100010];

enum move_t { UP, DOWN, STAY };

ll get_next(int p, multimap<int, int> &m, move_t move) {
  if (move == UP) {
    iter(m) i = m.lower_bound(p);
    if (i == m.end()) return INF;
    else return i->first - p;
  } else if (move == DOWN) {
    iter(m) i = m.lower_bound(p);
    if (i == m.begin()) return INF;
    else {
      --i;
      return p - i->first;
    }
  } else {
    return INF;
  }
}

#define DEBUG(...) //fprintf(stderr, __VA_ARGS__)


int main() {
  while (2 == scanf("%d%d", &N, &M)) {
    multimap<int, int> appear;
    rep (i, N) {
      scanf("%d%d%d", &T[i], &S[i], &F[i]);

      appear.insert(mp(T[i], i));
    }

    memset(waiting_bit, 0, sizeof(waiting_bit));
    multimap<int, int> waiting, riding;

    ll t = 0;
    int p = 1;
    int num_up = 0, num_down = 0, num_waiting = 0;
    move_t prv_move = STAY;
    memset(ans, -1, sizeof(ans));

    for (;;) {
      DEBUG("***** t=%lld, p=%d ****\n", t, p);
      //
      // People!!
      //

      // START TO WAIT!!
      while (!appear.empty() && appear.begin()->first <= t) {
        int k = appear.begin()->second;
        appear.erase(appear.begin());
        waiting.insert(mp(S[k], k));

        add(S[k], +1, waiting_bit, M);
        ++num_waiting;

        DEBUG("start to wait %d at %d\n", k, S[k]);
      }

      // GET OUT!!
      {
        pair<iter(riding), iter(riding)> is = riding.equal_range(p);
        for (iter(riding) ite = is.first; ite != is.second; ++ite) {
          int k = ite->second;
          ans[k] = t;

          if (prv_move == UP) --num_up;
          else --num_down;

          DEBUG("GET OUT: %d at %d\n", k, p);
        }
        riding.erase(is.first, is.second);

      }


      // COME IN!!
      {
        pair<iter(waiting), iter(waiting)> is = waiting.equal_range(p);
        for (iter(riding) ite = is.first; ite != is.second; ++ite) {
          int k = ite->second;
          riding.insert(mp(F[k], k));

          add(S[k], -1, waiting_bit, M);
          --num_waiting;

          if (F[k] > S[k]) ++num_up;
          else ++num_down;

          DEBUG("COME IN: %d at %d (%d->%d)\n", k, p, S[k], F[k]);
        }
        waiting.erase(is.first, is.second);
      }

      //
      // Elevator!!
      //

      // DIRECTION!?!?!?!?
      move_t nxt_move = STAY;
      if (riding.size() + waiting.size()) {
        int num_waiting_down = sum(p, waiting_bit);
        int num_waiting_up = num_waiting - num_waiting_down;
        int power_down = num_down + num_waiting_down;
        int power_up = num_up + num_waiting_up;
        if (power_up >= power_down) {
          nxt_move = UP;
        } else {
          nxt_move = DOWN;
        }
        DEBUG("direction. up=%d+%d, down=%d+%d\n", num_up, num_waiting_up, num_down, num_waiting_down);
      }

      // MOVE UNTIL!?!?!?!?
      ll nxt_t = INF;
      if (!appear.empty()) nxt_t = min(nxt_t, (ll)appear.begin()->first);
      nxt_t = min(nxt_t, t + get_next(p, riding, nxt_move));
      nxt_t = min(nxt_t, t + get_next(p, waiting, nxt_move));

      // OH FINALLY FINISHED...
      if (nxt_t == INF) break;
      DEBUG("nxt_t = %lld\n", nxt_t);

      // LET'S GO!!!!!
      if (nxt_move == UP) p += (nxt_t - t);
      else if (nxt_move == DOWN) p -= (nxt_t - t);
      t = nxt_t;
      prv_move = nxt_move;
    }

    rep (i, N) printll(ans[i]);
  }

  return 0;
}

