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
const ll MOD = 1000000009;

int A[1000010];
ll dpR[1000010];

int main() {
  int T;
  scanf("%d", &T);
  rep (t, T) {
    int N;
    scanf("%d", &N);
    rep (i, N) scanf("%d", &A[i]);

    ll ans = 1;  // 1 という初期値は，全てそのまま (a_i = b_i) の場合の分

    for (int k = 0; k <= 30; ++k) {
      // 全ての i について b_i の k ビット目より上は a_i と同じであり，
      // ある i が存在し b_i の k ビット目が a_i と異なる場合について数える．
      // k ビットより上が同じなので，k ビット目は 1 から 0 への変更のみが許される．
      
      // 方針としては，a_i の k ビット目が 1 である各 i について，
      // - b_j (j>i) の k ビット目は a_j と同じ
      // - b_i の 0 に変更
      // - b_j (j<i) の k ビット目は変更するかもしれないし同じかもしれない
      // という場合を考える．
      
      // 累積 XOR を元とあわせるためには，
      // - k ビット目より上：{a_i} と同じなので既にあっている
      // - k ビット目：1 から 0 への変更を行った回数が偶数回ならあう
      // - k ビット目より下：b_i の k ビット目より下を，調整に使う（逆算により一意に決める）
      //                    ことにすれば，他の b_j (j≠i) についてはどんな値にしてもあう
      
      int msb = 1 << k;
      int lo_msk = msb - 1;

      // dpR[i] := b_i, b_{i+1}, ..., b_{N-1} について，k ビット目も a_i と同じにした場合の，
      //           k ビット目より下の場合の数．
      dpR[N] = 1;
      for (int i = N - 1; i >= 0; --i) {
        dpR[i] = dpR[i + 1] * ((A[i] & lo_msk) + 1) % MOD;
      }

      // dpL[m] := 数 0, 1, ..., i-1 について，k ビット目を 1 から 0 にした回数 mod 2 が
      //           m になるような場合の数．
      ll dpL[2] = {1, 0};
      for (int i = 0; i < N; ++i) {
        if (A[i] & msb) { // 1
          (ans += dpL[1] * dpR[i + 1]) %= MOD;

          ll tmpL[2] = {0, 0};
          rep (j, 2) (tmpL[j]     += dpL[j] * ((A[i] & lo_msk) + 1)) %= MOD;  // 1 -> 1
          rep (j, 2) (tmpL[1 - j] += dpL[j] * msb) %= MOD;                    // 1 -> 0
          rep (j, 2) dpL[j] = tmpL[j];
        } else {
          rep (j, 2) (dpL[j] *= ((A[i] & lo_msk) + 1)) %= MOD;  // 0 -> 0
        }
      }
    }

    cout << (ans + MOD) % MOD << endl;
  }

  return 0;
}

