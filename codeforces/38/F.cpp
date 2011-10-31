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

typedef pair<int, pair<int, int> > pipii;
#define F first
#define S second

int N;
string S[30];

map<string, pipii> mem;

pipii saiki(const string &s) {
  if (mem.count(s)) return mem[s];

  // cout << s << endl;

  pipii res = mp(-1, mp(0, 0));
  for (char c = 'a'; c <= 'z'; ++c) {
    for (int p = 0; p <= 1; ++p) {
      string ts = p == 0 ? (c + s) : (s + c);

      int num = 0;
      rep (i, N) if (S[i].find(ts) != string::npos) ++num;
      if (num == 0) continue;
      
      int vs = 0, vm = 0;
      rep (i, ts.length()) {
        vs += ts[i] - 'a' + 1;
        vm = max(vm, ts[i] - 'a' + 1);
      }
      int gain = vs * vm + num;
      
      pipii tmp = saiki(ts);
      res = max(res, mp(tmp.first * -1, mp(gain + -tmp.S.S, -tmp.S.F)));
    }
  }

  return mem[s] = res;
}

int main() {
  while (cin >> N) {
    rep (i, N) cin >> S[i];

    mem.clear();
    pair<int, pair<int, int> > res = saiki("");
    
    if (res.first == 1) puts("First");
    else puts("Second");
    printf("%d %d\n", res.second.first, -res.second.second);
  }
  
  return 0;
}

