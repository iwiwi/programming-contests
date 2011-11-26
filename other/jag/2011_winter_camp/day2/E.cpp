#include <cstdio>
#include <queue>
#include <string>
#include <iostream>
#include <cctype>
#include <cassert>
#include <map>
#include <sstream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)

map<string, int> name2id;

int get_id(const string &name) {
  if (name2id.count(name)) return name2id[name];
  else {
    int id = name2id.size();
    return name2id[name] = id;
  }
}

string type[5010];
vector<int> adj[5010];

string input_value;
int mem[5010], nxt[5010];

int saiki(int v) {
  if (mem[v] != -1) return mem[v];

  int ret;
  if (type[v] == "NOT") {
    ret = !saiki(adj[v][0]);
  }
  else if (type[v] == "AND" || type[v] == "NAND") {
    ret = 1;
    rep (i, adj[v].size()) ret &= saiki(adj[v][i]);
    if (type[v][0] == 'N') ret = !ret;
  }
  else if (type[v] == "OR" || type[v] == "NOR") {
    ret = 0;
    rep (i, adj[v].size()) ret |= saiki(adj[v][i]);
    if (type[v][0] == 'N') ret = !ret;
  }
  else if (type[v] == "INPUT") {
    ret = input_value[adj[v][0]] == '1';
  }
  else {
    // cerr << type[v] << endl;
    // assert(false);
    for (;;) puts("HELL WORLD!!");
  }

  ret = ret ? 1 : 0;
  // printf("v=%d : %d\n", v, ret);
  return mem[v] = ret;
}

int main() {
  int num_input = 0;
  vector<int> output;

  for (string line; getline(cin, line); ) {
    while (!line.empty() && isspace(line[line.length() - 1])) {
      line = line.substr(0, line.length() - 1);
    }
    // cout << line << "!!" << endl;

    if (!line.empty() && line[0] == '#') continue;
    if (line == "INPUT VALUES") break;

    rep (i, line.length()) if (!isalnum(line[i]) && line[i] != '_') line[i] = ' ';
    stringstream ss(line);

    string s1, s2;
    if (!(ss >> s1 >> s2)) continue;

    if (s1 == "INPUT") {
      int id = get_id(s2);
      type[id] = "INPUT";
      adj[id].push_back(num_input++);
    }
    else if (s1 == "OUTPUT") {
      int id = get_id(s2);
      output.push_back(id);
    }
    else {
      int id = get_id(s1);
      type[id] = s2;
      for (string s; ss >> s; ) adj[id].push_back(get_id(s));
    }
  }

  int N = name2id.size();

  while (cin >> input_value) {
    // cout << input_value << endl;

    rep (i, N) {
      if (type[i] == "DFF") mem[i] = nxt[i];
      else mem[i] = -1;
    }

    rep (i, output.size()) printf("%d", saiki(output[i]));
    puts("");
    
    rep (i, N) if (type[i] == "DFF") nxt[i] = saiki(adj[i][0]);
  }

  return 0;
}
