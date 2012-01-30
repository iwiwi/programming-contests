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
#include <climits>
#include <numeric>
#include <bitset>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb push_back
#define mp make_pair

struct RequiredSubstrings {
  int solve(vector <string> words, int C, int L);
};



const int MAX_NODES = 310;
const int A = 26;
int alphabet2id(int a) {
  return a - 'a';
}


struct node_t {
  node_t *parent, *fail, *next[A];
  // MODIFY HERE!
  int msk;
  int dp[60][1 << 6];
};

node_t nodes[MAX_NODES], *root;
int num_nodes;

node_t *new_node() {
  node_t *p = &nodes[num_nodes++];
  p->parent = p->fail = NULL;
  rep (i, A) p->next[i] = NULL;
  // MODIFY HERE!
  p->msk = 0;
  return p;
}

void construct(const vector<string> &words) {
  num_nodes = 0;
  root = new_node();
  rep (i, words.size()) {
    const string &w = words[i];
    node_t *p = root;
    rep (j, w.length()) {
      node_t *&q = p->next[alphabet2id(w[j])];
      if (!q) q = new_node();
      q->parent = p;
      p = q;
    }
    // MODIFY HERE!
    p->msk |= 1 << i;
  }

  queue<node_t*> que;
  que.push(root);
  while (!que.empty()) {
    node_t *p = que.front();
    que.pop();
    rep (i, A) {
      node_t *&q = p->next[i];
      if (!q) q = p->fail ? p->fail->next[i] : root;
      else {
        node_t *r = p->fail;
        while (r && !r->next[i]) r = r->fail;
        q->fail = r ? r->next[i] : root;
        que.push(q);
        // MODIFY HERE!
        q->msk |= q->fail->msk;
      }
    }
  }
}



char id2alphabet(int i) {
  return 'a' + i;
}

string get_prefix(node_t *p) {
  string s = "";
  while (p->parent != NULL) {
    node_t *q = p->parent;
    rep (i, A) {
      if (q->next[i] == p) {
        s += id2alphabet(i);
        break;
      }
    }
    p = q;
  }
  reverse(all(s));
  return s;
}

void print_all() {
  rep (v, num_nodes) {
    node_t *p = &nodes[v];
    cout << v << ": " << get_prefix(p) << ": " << bitset<6>(p->msk) << endl;
    rep (i, A) cout << " " << id2alphabet(i) << " -> " << get_prefix(p->next[i]) << endl;
    cout << endl;
  }
}




const int MOD = 1000000009;

int RequiredSubstrings::solve(vector <string> words, int C, int L) {
  memset(nodes, 0, sizeof(nodes));
  construct(words);
  int N = words.size();

  root->dp[0][root->msk] = 1;
  rep (k, L) {
    rep (i, num_nodes) {
      const node_t &n = nodes[i];
      rep (b, 1 << N) {
        rep (a, 26) {
          node_t &tn = *n.next[a];
          int tb = b | tn.msk;
          tn.dp[k + 1][tb] += n.dp[k][b];
          tn.dp[k + 1][tb] %= MOD;
        }
      }
    }
  }

  // print_all();

  int ans = 0;
  rep (b, 1 << N) if (__builtin_popcount(b) == C) {
    rep (i, num_nodes) {
      ans += nodes[i].dp[L][b];
      ans %= MOD;
    }
  }
  return ans;
}











// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			}
			return;
		}

		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}

		if (total == 0) {
			cerr << "No test cases run." << endl;
		} else if (correct < total) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}

	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) {
		cerr << "Example " << casenum << "... ";

		string verdict;
		vector<string> info;
		char buf[100];

		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}

		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}

		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;

		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl;
			cerr << "    Received: " << received << endl;
		}

		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			string words[]            = {"a","aa","aaa","aaaa"};
			int C                     = 2;
			int L                     = 3;
			int expected__            = 50;

			clock_t start__           = clock();
			int received__            = RequiredSubstrings().solve(vector <string>(words, words + (sizeof words / sizeof words[0])), C, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string words[]            = {"abcdefgh"};
			int C                     = 0;
			int L                     = 7;
			int expected__            = 31810104;

			clock_t start__           = clock();
			int received__            = RequiredSubstrings().solve(vector <string>(words, words + (sizeof words / sizeof words[0])), C, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string words[]            = {"abcdefgh"};
			int C                     = 1;
			int L                     = 7;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = RequiredSubstrings().solve(vector <string>(words, words + (sizeof words / sizeof words[0])), C, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string words[]            = {"a","b","c","d"};
			int C                     = 3;
			int L                     = 3;
			int expected__            = 24;

			clock_t start__           = clock();
			int received__            = RequiredSubstrings().solve(vector <string>(words, words + (sizeof words / sizeof words[0])), C, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string words[]            = {"ab","bc","xy","yz"};
			int C                     = 2;
			int L                     = 3;
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = RequiredSubstrings().solve(vector <string>(words, words + (sizeof words / sizeof words[0])), C, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			string words[]            = ;
			int C                     = ;
			int L                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = RequiredSubstrings().solve(vector <string>(words, words + (sizeof words / sizeof words[0])), C, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 6: {
			string words[]            = ;
			int C                     = ;
			int L                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = RequiredSubstrings().solve(vector <string>(words, words + (sizeof words / sizeof words[0])), C, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string words[]            = ;
			int C                     = ;
			int L                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = RequiredSubstrings().solve(vector <string>(words, words + (sizeof words / sizeof words[0])), C, L);
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
