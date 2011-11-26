#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

const char *blds = "ABO";

string repr1(string s) {
  if (s[0] == 'O') return string("") + s[1];
  else if (s[1] == 'O') return string("") + s[0];
  else if (s[0] == s[1]) return string("") + s[0];
  else return "AB";
}

char repr2(string s) {
  if (s[0] == '-' && s[1] == '-') return '-';
  else return '+';
}

string repr(string s) {
  return repr1(s.substr(0, 2)) + repr2(s.substr(2));
}

vector<string> child(string a, string b) {
  vector<string> res;
  rep (i, 2) rep (j, 2) rep (k, 2) rep (l, 2) {
    string c = "";
    c += a[i];
    c += b[j];
    c += a[2 + k];
    c += b[2 + l];
    // cout << "? " << c << endl;
    res.push_back(repr(c));
  }
  return res;
}

void output(const string &a, const vector<string> &v) {
  if (a != "?") {
    cout << " " << a;
  }
  else if (v.empty()) {
    cout << " IMPOSSIBLE";
  }
  else if (v.size() == 1) {
    cout << " " << v[0];
  } else {
    cout << " {";
    rep (i, v.size()) {
      if (i > 0) cout << ", ";
      cout << v[i];
    }
    cout << "}";
  }
}

int main() {
  vector<string> all;
  rep (i, 3) rep (j, i + 1) rep (k, 2) rep(l, k + 1) {
    all.push_back((string("") + "ABO"[j]) + "ABO"[i] + "-+"[l] + "-+"[k]);
  }
  int n = all.size();

  /*
  rep (i, all1.size()) cout << all1[i] << ": " << repr(all1[i]) << endl;
  return 0;
  */
  
  for (int ca = 1; ; ++ca) {
    string a, b, c;
    cin >> a >> b >> c;
    if (a == "E" && b == "N" && c == "D") return 0;

    vector<string> ans;
    rep (ia, n) rep (ib, n) rep (ic, n) {
      string ra = repr(all[ia]);
      string rb = repr(all[ib]);
      string rc = repr(all[ic]);
      if (a != "?" && a != ra) continue;
      if (b != "?" && b != rb) continue;
      if (c != "?" && c != rc) continue;

      vector<string> v = child(all[ia], all[ib]);
      if (find(v.begin(), v.end(), rc) == v.end()) continue;

      // cout << all[ia] << " " << all[ib] << " " << all[ic] << endl;
      // rep (i, v.size()) cout << " " << v[i] << endl;
      // cout << ra << " " << rb << " " << rc << endl;

      if (a == "?") ans.push_back(ra);
      if (b == "?") ans.push_back(rb);
      if (c == "?") ans.push_back(rc);
    }
    
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    
    cout << "Case " << ca << ":";
    output(a, ans);
    output(b, ans);
    output(c, ans);
    cout << endl;
    // rep (i, ans.size()) cout << ans[i] << endl;
  }
}
