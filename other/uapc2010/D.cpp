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

typedef pair<int, int> pii;
#define F first
#define S second

int N, W, H;
string title[110];
map<string, vector<pair<pii, pii> > > po;
map<string, vector<string> > to;

int main() {
  for (;;) {
    cin >> N >> W >> H;
    if (!N) return 0;
    
    po.clear();
    to.clear();
    rep (i, N) {
      int k;
      cin >> title[i] >> k;
      rep (j, k) {
        int x, y, X, Y;
        string t;
        cin >> x >> y >> X >> Y >> t;
        po[title[i]].push_back(mp(mp(x, y), mp(X, Y)));
        to[title[i]].push_back(t);
      }
    }

    int M;
    cin >> M;
    vector<string> buffer(1, title[0]);
    int ptr = 0;
    
    rep (i, M) {
      string crr = buffer[ptr];
      
      string cmd;
      cin >> cmd;
      if (cmd[0] == 'c') {
        int x, y;
        cin >> x >> y;
        const vector<pair<pii, pii> > &bs = po[crr];
        rep (j, bs.size()) {
          if (bs[j].F.F <= x && x <= bs[j].S.F &&
              bs[j].F.S <= y && y <= bs[j].S.S ) {
            buffer.erase(buffer.begin() + ptr + 1, buffer.end());
            buffer.pb(to[crr][j]);
            ++ptr;
            break;
          }
        }
      }
      else if (cmd[0] == 'f') {
        if (ptr + 1 < (int)buffer.size()) ++ptr;
      }
      else if (cmd[0] == 'b') {
        if (ptr > 0) --ptr;
      }
      else {
        cout << crr << endl;
      }
    }
  }
}

