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

int N;

int M;
ll B[1000010];

int K;
ll A[1000010];

char buf[256];

int main() {
  while (1 == scanf("%d", &N)) {
    map<string, ll> points;
    map<string, int> id;
    rep (i, N) {
      int ptr;
      scanf("%s%d", buf, &ptr);
      points[string(buf)] = ptr;
      id[string(buf)] = 0;
    }

    memset(B, 0, sizeof(B));
    scanf("%d", &M);
    rep (i, M) {
      int b;
      scanf("%d", &b);
      B[i] = b * (ll)N;
    }

    string myname;
    cin >> myname;

    ll P;

    int t = 0;
    K = 0;
    tr (id, ite) {
      ll p = points[ite->first];
      p = p * (ll)N + (N - ++t);

      if (ite->first == myname) {
        P = p;
      } else {
        A[K] = p;
        ite->second = K++;
      }
    }

    sort(A, A + K);
    sort(B, B + N);

    // Highest
    {
      ll myp = P + B[N - 1];

      multiset<ll> bs;
      for (int i = 0; i < N - 1; ++i) bs.insert(B[i]);

      int win = 0;
      rep (i, K) {
        iter(bs) ite = bs.lower_bound(myp - A[i]);
        if (ite == bs.begin()) continue;

        --ite;

        // printf("%lld vs %lld + %d\n", myp, p, *ite);
        ++win;
        bs.erase(ite);
      }

      printf("%d ", N - win);
    }
    // Lowest
    {
      ll myp = P + B[0];

      multiset<ll> bs;
      for (int i = 1; i < N; ++i) bs.insert(B[i]);

      int lose = 0;
      reverse(A, A + K);
      rep (i, K) {
        iter(bs) ite = bs.lower_bound(myp - A[i]);
        if (ite == bs.end()) continue;

        // printf("%lld vs %lld + %lld\n", myp, A[i], *ite);

        ++lose;
        bs.erase(ite);
      }

      printf("%d\n", lose + 1);
    }


    // rep (i, K) printf("%lld\n", A[i]);
    // printf("%lld\n", mypoint);
  }

  return 0;
}

