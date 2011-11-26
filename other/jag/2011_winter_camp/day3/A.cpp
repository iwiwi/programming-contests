#include <cstdio>
#include <cstring>

char S[1010];
int L, p;

char get(int i) {
  if (i >= L) throw 0;
  else return S[i];
}

void parse() {
  if (get(p) != 'm') return;

  ++p;
  parse();

  if (get(p++) != 'e') throw 0;
  parse();

  if (get(p++) != 'w') throw 0;
  return;
}

int main() {
  scanf("%s", S);
  L = strlen(S);

  try {
    p = 0;
    parse();
    if (p < L) throw 0;

    puts("Cat");
  } catch (...) {
    puts("Rabbit");
  }
  return 0;
}
