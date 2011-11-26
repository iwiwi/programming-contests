#include <cstdio>
#include <queue>
#include <string>
#include <iostream>
#include <cctype>
#include <cassert>
#include <map>
#include <sstream>
#include <set>
#include <cstring>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)
#define iter(c) __typeof((c).begin())
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)

typedef long long ll;

const int THRESH = 1000000;

int N, M, B;

set<int> know[100010];
vector<int> memb[100010];
int par[300010];

ll *know_bits[100010];
ll *memb_bits[100010];
ll tmp_bits[2000];

int root(int x) {
  return par[x] == x ? x : par[x] = root(par[x]);
}

bool intersect_bits(ll *bs1, ll *bs2) {
  rep (i, B) if (bs1[i] & bs2[i]) return true;
  return false;
}

int main() {
  scanf("%d%d", &N, &M);
  B = (N + 63) / 64;
  rep (i, M) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a; --b;
    know[a].insert(b);
  }

  rep (i, N) {
    memb[i].push_back(i);
    par[i] = i;
  }

  int Q;
  scanf("%d", &Q);
  rep (q, Q) {
    int t, a, b;
    scanf("%d%d%d", &t, &a, &b);
    --a;
    --b;
    a = root(a);
    b = root(b);

    
    if (t == 1) {
      // printf("%d: ", a + 1); tr (know[a], ite) printf("%d ", *ite + 1); puts("");
      // printf("%d: ", b + 1); tr (memb[b], ite) printf("%d ", *ite + 1); puts("");

      // generate bit masks
      if (know_bits[a] == NULL && know[a].size() >= THRESH) {
        ll *bs = know_bits[a] = new ll[B]; memset(bs, 0, sizeof(ll) * B);
        tr (know[a], ite) {
          int k = *ite;
          bs[k / 64] |= ll(1) << (k % 64);
        }
      }
      if (memb_bits[b] == NULL && memb[b].size() >= THRESH) {
        ll *bs = memb_bits[b] = new ll[B]; memset(bs, 0, sizeof(ll) * B);
        tr (memb[b], ite) {
          int k = *ite;
          bs[k / 64] |= ll(1) << (k % 64);
        }
      }

      // query
      if (know_bits[a] && memb_bits[b]) {
        if (intersect_bits(know_bits[a], memb_bits[b])) goto yes;
      }
      else if (know_bits[a] && !memb_bits[b]) {
        memset(tmp_bits, 0, sizeof(tmp_bits));
        tr (memb[b], ite) {
          int k = *ite;
          tmp_bits[k / 64] |= ll(1) << (k % 64);
        }
        if (intersect_bits(know_bits[a], tmp_bits)) goto yes;
      }
      else if (!know_bits[a] && memb_bits[b]) {
        memset(tmp_bits, 0, sizeof(tmp_bits));
        tr (know[a], ite) {
          int k = *ite;
          tmp_bits[k / 64] |= ll(1) << (k % 64);
        }
        if (intersect_bits(tmp_bits, memb_bits[b])) goto yes;
      }
      else {
        iter(know[a]) itea = know[a].begin();
        iter(memb[b]) iteb = memb[b].begin();
        while (itea != know[a].end() && iteb != memb[b].end()) {
          if (*itea == *iteb) goto yes;
          else if (*itea < *iteb) ++itea;
          else ++iteb;
        }
      }

      puts("NO");
      continue;
    yes:
      puts("YES");
    }
    else {
      // merge
      if (memb[a].size() < memb[b].size()) swap(a, b);

      {
        int k = memb[a].size();
        memb[a].resize(memb[a].size() + memb[b].size());
        rep (i, memb[b].size()) memb[a][k + i] = memb[b][i];
        if (memb_bits[a]) {
          ll *bs = memb_bits[a];
          tr (memb[b], ite) {
            int k = *ite;
            bs[k / 64] |= ll(1) << (k % 64);
          }
        }
      }
      {
        tr (know[b], ite) know[a].insert(*ite);
        if (know_bits[a]) {
          ll *bs = know_bits[a];
          tr (know[b], ite) {
            int k = *ite;
            bs[k / 64] |= ll(1) << (k % 64);
          }
        }
      }
      par[b] = a;

      memb[b].clear();
      know[b].clear();

      // !?
      par[N++] = a;
    }
  }

  return 0;
}
