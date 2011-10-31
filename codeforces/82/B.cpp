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


void print(const vector<int> &v) {
  printf("%d", (int)v.size());
  rep (i, v.size()) printf(" %d", v[i]);
  puts("");
}

int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    map<int, vector<int> > bel;
    int M = N * (N - 1) / 2;
    rep (i, M) {
      int k, a;
      scanf("%d", &k);
      rep (j, k) {
        scanf("%d", &a);
        bel[a].pb(i);
      }
    }

    if (N == 2) {
      vector<int> nums;
      tr (bel, ite) nums.pb(ite->first);
      printf("1 %d\n", nums.back());
      nums.pop_back();
      print(nums);
    }
    else {
      map<vector<int>, vector<int> > sets;
      tr (bel, ite)  sets[ite->second].pb(ite->first);
      tr (sets, ite) {
        const vector<int> &v = ite->second;
        print(v);
      }
    }
  }

  return 0;
}

