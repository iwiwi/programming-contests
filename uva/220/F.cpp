#include <cstdio>
#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair
#define pb push_back

int n;
bool inv[70000];
pair<int, int> cnt[70000];

void init(int n_) {
  for (n = 1; n < n_; n *= 2);
  memset(inv, 0, sizeof(inv));
  memset(cnt, 0, sizeof(cnt));
}

void init2(int k, int l, int r) {
  if (k == 0) r = n;
  cnt[k] = mp(0, r - l);
  if (r - l >= 2) {
    init2(k * 2 + 1, l, (l + r) / 2);
    init2(k * 2 + 2, (l + r) / 2, r);
  }
}

pair<int, int> query(int a, int b, int k = 0, int l = 0, int r = 0) {
  if (k == 0) r = n;
  if (r <= a || b <= l) return cnt[k];
  if (a <= l && r <= b) {
    inv[k] = !inv[k];
    return cnt[k] = mp(cnt[k].second, cnt[k].first);
  }
  else {
    pair<int, int> lc = query(a, b, k * 2 + 1, l, (l + r) / 2);
    pair<int, int> rc = query(a, b, k * 2 + 2, (l + r) / 2, r);
    cnt[k] = mp(lc.first + rc.first, lc.second + rc.second);
    if (inv[k]) cnt[k] = mp(cnt[k].second, cnt[k].first);
    return cnt[k];
  }
}

int m;
int x0[120010],x1[120010],y0[120010],y1[120010];
vector<pair<int, int> > evt[30010];

int main() {
  int cases;
  scanf("%d", &cases);
  
  rep (ca, cases) {
    int N, M_;
    scanf("%d%d", &N, &M_);

    n = N;
    m = 0;
    rep (i, M_) {
      int y,x,ysiz,xsiz;
      scanf("%d%d%d%d", &y, &x, &xsiz, &ysiz);
      x--;y--;
      if(x+xsiz<=n && y+ysiz<=n){
        x0[m]=x;x1[m]=x+xsiz;
        y0[m]=y;y1[m]=y+ysiz;
        m++;
      }
      if(x+xsiz<=n && y+ysiz>n){
        x0[m]=x;x1[m]=x+xsiz;
        y0[m]=y;y1[m]=n;
        m++;
        x0[m]=x;x1[m]=x+xsiz;
        y0[m]=0;y1[m]=y+ysiz-n;
        m++;
      }
      if(x+xsiz>n && y+ysiz<=n){
        x0[m]=x;x1[m]=n;
        y0[m]=y;y1[m]=y+ysiz;
        m++;
        x0[m]=0;x1[m]=x+xsiz-n;
        y0[m]=y;y1[m]=y+ysiz;
        m++;
      }
      if(x+xsiz>n && y+ysiz>n){
        x0[m]=x;x1[m]=n;
        y0[m]=y;y1[m]=n;
        m++;
        x0[m]=x;x1[m]=n;
        y0[m]=0;y1[m]=y+ysiz-n;
        m++;
        x0[m]=0;x1[m]=x+xsiz-n;
        y0[m]=y;y1[m]=n;
        m++;
        x0[m]=0;x1[m]=x+xsiz-n;
        y0[m]=0;y1[m]=y+ysiz-n;
        m++;
      }
    }      

    init(N);
    init2(0, 0, 0);
    
    rep (x, N) evt[x].clear();
    evt[0].pb(mp(0, N));
    rep (i, N) evt[i + 1].pb(mp(i, i + 1));
    rep (i, m) {
      //printf("[%d, %d) x [%d, %d)\n", x0[i], x1[i], y0[i], y1[i]);
      evt[x0[i]].pb(mp(y0[i], y1[i]));
      evt[x1[i]].pb(mp(y0[i], y1[i]));
    }

    pair<int, int> crr = mp(0, 0);
    ll ans = 0;
    rep (x, N) {
      rep (i, evt[x].size()) {
        // printf(" [%d, %d)\n", evt[x][i].first, evt[x][i].second);
        crr = query(evt[x][i].first, evt[x][i].second);
      }
      // printf("%d: %d %d\n", x, crr.first, crr.second);
      ans += crr.first;
    }

    printf("Case %d: %lld\n", ca + 1, ans);
  }
}
