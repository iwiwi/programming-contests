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

const char *names[] = {
  "Sheldon", "Leonard", "Penny", "Rajesh", "Howard"
};


int main() {
  int N;
  while (1 == scanf("%d", &N)) {
    --N;
    for (int k = 1; ; k *= 2) {
      if (N < k * 5) {
        cout << names[N / k] << endl;
        break;
      }
      else {
        N -= k * 5;
      }
    }
  }


  return 0;
}

