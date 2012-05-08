#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

typedef long long ll;

const ll INF = 1LL << 60;

string A, B, S[110], T[110];
int N;

map<string, int> prv_id, crr_id;
ll prv_mat[210][210];
ll crr_mat[210][210];
string crr_str[210];

int main() {
  for (int ca = 1; ; ++ca) {
    cin >> A >> B >> N;
    if (A == ".") return 0;
    rep (i, N) cin >> S[i] >> T[i];
    
    int K = A.length();
    prv_id.clear();
    for (int k = 1; k <= K; ++k) {
      crr_id.clear();
      crr_id[A.substr(K - k)] = 0;
      crr_id[B.substr(K - k)] = 0;
      rep (i, N) if (k <= (int)S[i].length()) {
        crr_id[S[i].substr(S[i].length() - k)] = 0;
        crr_id[T[i].substr(T[i].length() - k)] = 0;
      }
      int V = 0;
      tr (crr_id, ite) {
        ite->second = V++;
        crr_str[ite->second] = ite->first;
        // cout << ite->first << ite->second << endl;
      }

      rep (i, V) rep (j, V) crr_mat[i][j] = i == j ? 0 : INF;
      rep (i, N) if ((int)S[i].length() == k) {
        int s = crr_id[S[i]];
        int t = crr_id[T[i]]; 
        crr_mat[s][t] = min(crr_mat[s][t], 1LL);
      }
      rep (i, V) {
        string a = crr_str[i].substr(1);
        if (prv_id.count(a) == 0) continue;
        
        rep (j, V) {
          if (crr_str[i][0] != crr_str[j][0]) continue;
          
          string b = crr_str[j].substr(1);
          if (prv_id.count(b) == 0) continue;

          ll d = prv_mat[prv_id[a]][prv_id[b]];
          crr_mat[i][j] = min(crr_mat[i][j], d);
        }
      }

      rep (k, V) rep (i, V) rep (j, V) {
        crr_mat[i][j] = min(crr_mat[i][j], crr_mat[i][k] + crr_mat[k][j]);
      }
      prv_id.swap(crr_id);
      memcpy(prv_mat, crr_mat, sizeof(prv_mat));
    }

    printf("Case %d: ", ca);
    ll ans = prv_mat[prv_id[A]][prv_id[B]];
    if (ans == INF) puts("No solution");
    else printf("%lld\n", ans);
  }
}
