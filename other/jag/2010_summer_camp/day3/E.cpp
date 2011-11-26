#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)

typedef long long ll;

int N;
ll myH, myA, myD, myS;
ll H[40010], A[40010], D[40010], S[40010];

ll cnt[40010], dam[40010];

int main() {
  cin >> N;
  cin >> myH >> myA >> myD >> myS;
  rep (i, N) cin >> H[i] >> A[i] >> D[i] >> S[i];

  vector<pair<double, int> > ord;
  
  ll tott = 0, totd = 0;
  rep (i, N) {
    dam[i] = max(A[i] - myD, 0LL);
    if (dam[i] == 0) continue;
    
    ll t = max(myA - D[i], 0LL);
    if (t == 0) goto ng;

    cnt[i] = (ll)ceil(H[i] / (double)t);
    ord.push_back(make_pair(cnt[i] / (double)dam[i], i));

    if (S[i] > myS) totd += dam[i];
  }
  if (totd >= myH) goto ng;

  sort(ord.begin(), ord.end());
  rep (i, ord.size()) {
    int k = ord[i].second;
    totd += dam[k] * (tott + cnt[k] - 1);
    tott += cnt[k];
    if (totd >= myH) goto ng;
  }

  cout << totd << endl;
  return 0;

 ng:
  cout << -1 << endl;
  return 0;
}
