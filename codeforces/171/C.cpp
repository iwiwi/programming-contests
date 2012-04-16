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




int main() {
  int carrots = 2,
      calories = 0,
      chocolate_spread = 100,
      pack_of_flour = 1,
      egg = 1;

  stack<int> mixing_bowl;
  mixing_bowl.push(calories);

  scanf("%d", &carrots);
  rep (i, carrots) {
    scanf("%d", &chocolate_spread);
    mixing_bowl.push(chocolate_spread);
    {
      int t = mixing_bowl.top(); mixing_bowl.pop();
      mixing_bowl.push(t * pack_of_flour);
    }
    chocolate_spread = mixing_bowl.top(); mixing_bowl.pop();
    mixing_bowl.top() += chocolate_spread;
    mixing_bowl.push(pack_of_flour);
    mixing_bowl.top() += egg;
    pack_of_flour = mixing_bowl.top(); mixing_bowl.pop();
  }

  printf("%d\n", mixing_bowl.top());

  return 0;
}

