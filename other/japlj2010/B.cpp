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

int N, K;
int rank[1000010];

int main() {
  while (2 == scanf("%d%d", &N, &K)) {
    vector<vector<int> > lines;
    int t = N;
    while (t >= 1) {
      vector<int> line(t);
      rep (i, t) {
        scanf("%d", &line[i]);
        --line[i];
      }
      lines.pb(line);
      if (t == 1) break;
      t = (t + 1) / 2;
    }
    memset(rank, -1, sizeof(rank));
    rank[lines.back()[0]] = 0;
    for (int i = (int)lines.size() - 2; i >= 0; --i) {
      const vector<int> &line = lines[i];
      for (int j = 0; j + 1 < (int)line.size(); j += 2) {
        int a = line[j];
        int b = line[j + 1];
        // printf("[%d] %d vs %d\n",i, a + 1, b + 1);
        if (rank[a] == -1) rank[a] = rank[b] + 1;
        else rank[b] = rank[a] + 1;
      }
    }

    rep (i, N) {
      // printf("%d: %d\n", i + 1, rank[i]);
      if (rank[i] < K) printf("%d\n", i + 1);
    }
  }
  
  return 0;
}

