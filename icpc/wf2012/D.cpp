#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)n; ++i)

typedef long long ll;

int N, L;
string P;

ll countit(const string &S) {
  const int B = 3;

  // puts("VERY FAST!!");
  
  const string &a = P;
  const string &b = S;
  int al = a.length(), bl = b.length();
  if (al > bl) return 0;
  ll ah = 0, bh = 0, t = 1;
  rep (i, al) {
    ah = ah * B + a[i];
    bh = bh * B + b[i];
    t *= B;
  }
  ll ans = 0;
  for (int i = al; i <= bl; ++i) {
    if (ah == bh) ++ans;
    if (i < bl) bh = bh * B + b[i] - b[i - al] * t;
  }
  return ans;

  /*
  ll ans = 0;
  for (int i = 0; i + L <= (int)S.length(); ++i) {
    if (S.compare(i, L, P) == 0) ++ans;
  }
  return ans;
  */
}

string F[110];
ll cnt[110];

int main() {
  for (int ca = 1; cin >> N >> P; ++ca) {
    printf("Case %d: ", ca);
    
    L = P.length();
    
    F[0] = "0";
    F[1] = "1";
    
    int k = 2;
    for (; k <= N; ++k) {
      F[k] = F[k - 1] + F[k - 2];
      if ((int)F[k - 1].length() >= 2 * L) break;
    }
    if (k >= N) {
      printf("%lld\n", countit(F[N]));
    } else {
      // cerr << endl;
      // cerr << k - 1 << ": " << F[k - 1] << endl;
      // cerr << k     << ": " << F[k] << endl;

      cnt[k - 1] = countit(F[k - 1]);
      cnt[k    ] = countit(F[k    ]);
      
      string pfx = F[k].substr(0, L - 1);
      string sfx0 = F[k    ].substr(F[k    ].length() - (L - 1));
      string sfx1 = F[k - 1].substr(F[k - 1].length() - (L - 1));
      ll mid0 = countit(sfx0 + pfx);
      ll mid1 = countit(sfx1 + pfx);
      
      // puts("large");
      for (++k; k <= N; ++k) {
	cnt[k] = cnt[k - 1] + mid0 + cnt[k - 2];
	swap(mid0, mid1);
      }
      printf("%lld\n", cnt[N]);
    }
  }
}
