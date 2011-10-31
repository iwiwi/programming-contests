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
#include <cstdarg>
#include <sys/time.h>

using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

#define CASE_LABEL_FORMAT "Case #%d: "  // "Case #%d:\n"

void debug(const char* format, ...) __attribute__((format(printf, 1, 2)));


void init() {
}

int N;
ll K;
ll C[110], T[110], S[110];

void input() {
  cin >> N >> K;
  rep (i, N) cin >> C[i] >> T[i] >> S[i];
}

void echo() {
  cout << N << K;
  rep (i, N) cout << C[i] << T[i] << S[i];
}


void solve() {
  pair<ll, pair<ll, ll> > cof[110];
  rep (i, N) cof[i] = mp(T[i], mp(C[i], S[i]));
  sort(cof, cof + N);
  reverse(cof, cof + N);
  cof[N] = mp(0, mp(0, 0));

  priority_queue<pair<ll, ll> > que;

  ll ans = 0;
  rep (i, N) {
    ll t = cof[i].first - cof[i + 1].first;
    ll c = cof[i].second.first;
    ll s = cof[i].second.second;
    que.push(mp(s, c));

    while (t > 0 && !que.empty()) {
      pair<ll, ll> q = que.top();
      que.pop();

      ll tt = min(t, q.second);
      q.second -= tt;
      t -= tt;

      ans += q.first * tt;
      if (q.second > 0) que.push(q);
    }
  }

  cout << ans << endl;
}




void debug(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fflush(stderr);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    // Run normally
    init();
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
      input();
      printf(CASE_LABEL_FORMAT, i);
      solve();
    }
  } else if (argc == 2 && strcmp(argv[1], "-d") == 0) {
    // Divide input
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
      char filename[256];
      sprintf(filename, "in/%06d.in", i);
      freopen(filename, "w", stdout);
      input();
      echo();
    }
  } else if (argc == 2) {
    // Run one case
    printf(CASE_LABEL_FORMAT, atoi(argv[1]));
    init();
    input();
    solve();
  } else {
    // Bad usage
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "  ./a.out          < ALL_INPUT  : Run normally\n");
    fprintf(stderr, "  ./a.out -d       < ALL_INPUT  : Divide input files\n");
    fprintf(stderr, "  ./a.out CASE_NUM < CASE_INPUT : Run one case\n");
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
