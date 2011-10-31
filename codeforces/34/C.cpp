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




int main() {
  string line;
  while (cin >> line) {
    rep (i, line.length()) if (line[i] == ',') line[i] = ' ';
    stringstream ss(line);
    vector<int> v;
    for (int t; ss >> t; ) v.pb(t);
    sort(all(v));
    v.erase(unique(all(v)), v.end());
    int N = v.size();
    
    int i, j;
    for (i = 0; i < N; i = j) {
      j = i + 1;
      while (j < N && v[j] == v[j - 1] + 1) ++j;
      
      if (i > 0) putchar(',');
      
      if (j == i + 1) printf("%d", v[i]);
      else printf("%d-%d", v[i], v[j - 1]);
    }
    puts("");
  }
  
  return 0;
}

