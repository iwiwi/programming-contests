#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<int> poly;

int P, M, N;

int inv[200];

void debug(const poly& p) {
  for(int i = 0; i < p.size(); ++i) cerr << p[i] << " ";
  cerr << endl;
}

bool divide(poly p1, const poly& p2) {
  int n = p1.size() - 1, m = p2.size() - 1;
  for(int i = n - m; i >= 0; --i) {
    int d = inv[p2[m]] * p1[i + m] % P;
    for(int j = m; j >= 0; --j) {
      p1[i + j] -= d * p2[j] % P;
      p1[i + j] = (p1[i + j] % P + P) % P;
    }
  }
  bool ok = true;
  for(int i = 0; i <= n; ++i) ok = ok && p1[i] == 0;
  return ok;
}

poly add(poly p1, poly p2) {
  poly res(M, 0);
  for(int i = 0; i < M; ++i) res[i] = (p1[i] + p2[i]) % P;
  return res;
}

poly mul(poly p1, poly p2, poly mp) {
  poly res(2 * M, 0);
  for(int i = 0; i < M; ++i) {
    for(int j = 0; j < M; ++j) {
      res[i + j] += p1[i] * p2[j] % P;
      res[i + j] %= P;
    }
  }
  for(int i = M - 1; i >= 0; --i) {
    int d = res[i + M] % P;
    for(int j = M; j >= 0; --j) {
      res[i + j] -= d * mp[j] % P;
      res[i + j] = (res[i + j] % P + P) % P;
    }
  }
  return res;
}

poly mul(poly p1, poly p2) {
  poly res(p1.size() + p2.size() - 1, 0);
  for(int i = 0; i < p1.size(); ++i) {
    for(int j = 0; j < p2.size(); ++j) {
      res[i + j] += p1[i] * p2[j] % P;
      res[i + j] %= P;
    }
  }
  return res;
}

poly pp[10];

poly minpoly() {
  poly res(M + 1, 0);
  res[M] = 1;
  if(M == 1) {
    res[0] = P - 1;
    return res;
  }
  for(int i = 1, j = P; i <= M; ++i, j *= P) {
    pp[i].clear();
    pp[i].resize(j);
    pp[i][j - 1] = 1;
    pp[i][0] = P - 1;
  }
  while(true) {
    bool ok = divide(pp[M], res);
    for(int i = 1; i < M && ok; ++i) ok = !divide(pp[i], res);
    if(ok) {
      return res;
    }
    res[0] = (res[0] + 1) % P;
    for(int i = 0; res[i] == 0; ++i) res[i + 1] = (res[i + 1] + 1) % P;
  }
}

poly itop(int s) {
  poly res(M, 0);
  for(int i = 0; s; ++i, s /= P) res[i] = s % P;
  return res;
}

int ptoi(const poly& p) {
  int res = 0;
  for(int i = M - 1; i >= 0; --i) {
    res = res * P + p[i];
  }
  return res;
}

void output(const poly& p) {
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      if(j) printf(" ");
      poly p1 = itop(i), p2 = itop(j);
      printf("%d", ptoi(add(p1, p2)));
    }
    printf("\n");
  }
  for(int i = 0; i < N; ++i) {
    bool ok = i == 0;
    for(int j = 0; j < N; ++j) {
      if(j) printf(" ");
      poly p1 = itop(i), p2 = itop(j);
      printf("%d", ptoi(mul(p1, p2, p)));
      if(ptoi(mul(p1, p2, p)) == 1) ok = true;
    }
    //assert(ok);
    printf("\n");
  }
}

int isprime[200];
int ps[200];

int main() {
  int n, pn = 0;
  for(int i = 2; i < 200; ++i) if(!isprime[i]) {
    ps[pn++] = i;
    for(int j = 2 * i; j < 200; j += i) isprime[j] = 1;
  }
  //for(int n = 2; n < 150; ++n) {
  cin >> n;
  N = n;
  int p = 0, m = 0;
  bool ok = false;
  for(int i = 0; i < pn; ++i) if(n % ps[i] == 0) {
    p = ps[i];
    int j = n;
    for(; j % ps[i] == 0; j /= ps[i]) ++m;
    ok = j == 1;
    break;
  }
  P = p; M = m;
  for(int i = 1; i < p; ++i) {
    for(int j = 1; j < p; ++j) if(i * j % P == 1) inv[i] = j;
  }
  if(!ok) puts("NO");
  else {
    poly minp = minpoly();
    //debug(minp);
    output(minp);
  }
	return 0;
}
