#include <cstdio>
#include <queue>
#include <string>
#include <iostream>
#include <cctype>
#include <cassert>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)n; ++i)

string S;
int L, p;

const char *supsub(char c) {
  if (c == '^') return "sup";
  if (c == '_') return "sub";
  assert(false);
}

void saiki() {
  while (p < L) {
    char c = S[p];

    if (c == '}') {
      ++p;
      return;
    }
    else if (isalpha(c)) {
      printf("<i>");
      for (; isalpha(S[p]); ++p) printf("%c", S[p]);
      printf("</i>");
    }
    else if (isdigit(c) || c == '(' || c == ')') {
      printf("%c", c);
      ++p;
    }
    else if (c == '^' || c == '_') {
      printf("<%s>", supsub(c));
      if (S[++p] != '{') {
        if (isalpha(S[p])) printf("<i>%c</i>", S[p]);
        else if (isdigit(S[p])) printf("%c", S[p]);
        else assert(false);
        ++p;
      }
      else {
        ++p;
        saiki();
      }
      printf("</%s>", supsub(c));
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/') {
      printf("&nbsp;%c&nbsp;", c);
      ++p;
    }
    else {
      fprintf(stderr, "Unexpected character: %c\n", c);
      assert(false);
    }
  }
}

int main() {
  for (string line; getline(cin, line); ) {
    S = "";
    rep (i, line.length()) if (!isspace(line[i])) S += line[i];
    if (S.empty()) break;

    assert(S.length() >= 2 && S[0] == '$' && S[S.length() - 1] == '$');
    S = S.substr(1, S.length() - 2);

    L = S.length();
    p = 0;
    saiki();
    puts("");
  }

  return 0;
}
