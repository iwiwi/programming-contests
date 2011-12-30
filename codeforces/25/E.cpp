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
const ll B = 101;

bool contain(const string &a, const string &b) { // a is in b ?
  int al = a.length(), bl = b.length();
  if (al > bl) return false;
  
  ll ah = 0, bh = 0;
  ll t = 1;
  rep (i, al) {
    ah = ah * B + (a[i] - 'a');
    bh = bh * B + (b[i] - 'a');
    t *= B;
  }
  if (ah == bh) return true;

  for (int i = al; i < bl; ++i) {
    bh = bh * B + (b[i] - 'a') - (b[i - al] - 'a') * t;
    if (ah == bh) return true;
  }

  return false;
}



int overlap(const string &a, const string &b) {
  int al = a.length(), bl = b.length();
  int iub = min(al, bl);
  
  int res = 0;
  
  ll ah = 0, bh = 0;
  ll t = 1;
  for (int i = 0; i < iub; ++i) {
    ah = ah + (a[al - i - 1] - 'a') * t;
    bh = bh * B + (b[i] - 'a');
    t *= B;

    if (ah == bh) res = i + 1;
  }

  return res;
}


  
int main() {
  string in[3];
  while (cin >> in[0] >> in[1] >> in[2]) {
    vector<int> ord;
    // rep (i, 3) { rep (j, 3) printf("%d ", (int)contain(S[i], S[j])); puts(""); } puts("");
    //rep (i, 3) { rep (j, 3) printf("%d ", (int)overlap(in[i], in[j])); puts(""); } puts("");

    int ovl[3][3];
    
    rep (i, 3) {
      rep (j, 3) ovl[i][j] = overlap(in[i], in[j]);
      rep (j, 3) if (i != j && contain(in[i], in[j])) goto ng;
      ord.pb(i);
    ng:;
    }

    if (ord.size() == 0) {
      printf("%d\n", (int)in[0].length());
      continue;
    }

    int res = 987654321;
    
    do {
      int tmp = 0;
      rep (i, ord.size()) tmp += in[ord[i]].length();
      for (int i = 0; i + 1 < (int)ord.size(); ++i) tmp -= ovl[ord[i]][ord[i + 1]];

      res = min(tmp, res);
      
    } while (next_permutation(all(ord)));
    
    printf("%d\n", res);
  }
  
  return 0;
}
