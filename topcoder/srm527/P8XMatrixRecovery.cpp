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
#define present(c, e) ((c).find((e)) != (c).end())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair


const int MAX_LR = 3010;

int L, R;
vector<int> adj[MAX_LR];
bool vis[MAX_LR], usd[MAX_LR];
int lev[MAX_LR + 1], mat[MAX_LR];

bool augment(int l) {
  if (l == L) return true;
  if (vis[l]) return false;
  vis[l] = true;
  rep (i, adj[l].size()) {
    int r = adj[l][i], l2 = mat[r];
    if (lev[l2] > lev[l] && augment(l2)) {
      mat[r] = l;
      return true;
    }
  }
  return false;
}

int bipartite_matching() {
  fill(mat, mat + R, L);
  memset(usd, 0, sizeof(bool) * L);
  bool update;
  do {
    fill(lev, lev + L + 1, -1);
    lev[L] = R;
    queue<int> que;
    rep (l, L) if (!usd[l]) {
      que.push(l);
      lev[l] = 0;
    }
    while (!que.empty()) {
      int l = que.front();
      que.pop();
      rep (i, adj[l].size()) {
        int r = adj[l][i], l2 = mat[r];
        if (lev[l2] < 0) {
          lev[l2] = lev[l] + 1;
          que.push(l2);
        }
      }
    }

    memset(vis, 0, sizeof(bool) * L);
    update = false;
    rep (l, L) if (!usd[l] && augment(l)) usd[l] = update = true;
  } while (update);

  return count(usd, usd + L, true);
}



struct P8XMatrixRecovery {
  bool isok(const vector <string> &rows, const vector <string> &columns) {
    L = R = columns.size();

    int r = rows.size();
    int c = columns.size();

    rep (i, c) {
      adj[i].clear();

      rep (j, c) {
        rep (k, r) {
          char a = rows[k][i];
          char b = columns[j][k];
          if (a != '?' && b != '?' && a != b) goto ng;
        }
        adj[i].pb(j);
     ng:;
      }
    }
    int bm = bipartite_matching();
    return bm == c;
  }

  vector <string> solve(vector <string> rows, vector <string> columns) {
    int R = rows.size();
    int C = columns.size();
    rep (r, R) rep (c, C) {
      if (rows[r][c] != '?') continue;

      rows[r][c] = '0';
      if (isok(rows, columns)) continue;
      else rows[r][c] = '1';
    }

    return rows;
  }


// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"10?"
,"?11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"01"
,"10"
,"1?"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"101", "011" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, solve(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0"
,"?"
,"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0?1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"0", "0", "1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, solve(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"10"
,"01"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"10"
,"01"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10", "01" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, solve(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"??0"
,"11?"
,"?01"
,"1?1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"1???"
,"?111"
,"0?1?"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"010", "110", "101", "101" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, solve(Arg0, Arg1)); }

// END CUT HERE

};



// BEGIN CUT HERE
int main() {
  P8XMatrixRecovery ___test;
  ___test.run_test(-1);
}
// END CUT HERE
