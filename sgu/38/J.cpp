#include <cstdio>
#include <algorithm>
#include <utility>
#include <climits>
#include <iostream>
#include <vector>
#include <functional>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <map>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define all(c) (c).begin(), (c).end()

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, pii> piiii;

bool solve0(vector<int> A) {
  vector<int> sorted(A);
  sort(all(sorted));

  if (sorted == A) {
    puts("0");
    return true;
  }

  return false;
}

bool solve1(vector<int> A) {
  vector<int> sorted(A);
  sort(all(sorted));

  int N = A.size();
  map<pair<int, int>, vector<int> > ma;

  rep (i, N) ma[mp(A[i], sorted[i])].pb(i);

  vector<bool> done(N, false);

  vector<pair<int, int> > res;
  rep (i, N) {
    if (A[i] == sorted[i]) continue;
    if (done[i]) continue;

    vector<int> &ps = ma[mp(sorted[i], A[i])];
    if (ps.empty()) return false;  // oh...

    int j = ps.back();
    ps.pop_back();

    res.pb(mp(i, j));
    done[i] = done[j] = true;
  }

  // ok!!!!
  puts("1");
  printf("%d", (int)res.size());
  rep (i, res.size()) printf(" %d %d", res[i].first + 1, res[i].second + 1);
  puts("");
  return true;
}

void solve2(vector<int> A) {
  int N = A.size();
  vector<pair<int,int> > sw1,sw2;
  vector<pair<int,int> > B;
  for(int i=0;i<N;i++)B.push_back(make_pair(A[i],i));
  sort(B.begin(),B.end());
  vector<int> perm(N);
  for(int i=0;i<N;i++)perm[B[i].second]=i;
  vector<int> chk(N);
  for(int i=0;i<N;i++){
    if(chk[i]==0){
      int p=i;
      vector<int> v;
      for(;;){
        v.push_back(p);
        chk[p]=1;
        p=perm[p];
        if(p==i)break;
      }
      //for(int i=0;i<v.size();i++)printf("%d->",v[i]);puts("");
      int n=v.size();
      if(n==1)continue;
      for(int k=0;k<n;k++){
        int l=n-k;
        if(l>=0 && l<n && k<l)sw1.push_back(make_pair(v[k],v[l]));
      }
      sw2.push_back(make_pair(v[0],v[1]));
      for(int k=0;k<n;k++){
        int l=n+1-k;
        if(l>=0 && l<n && k<l)sw2.push_back(make_pair(v[k],v[l]));
      }
    }
  }
  printf("2\n");
  printf("%d",sw1.size());for(int i=0;i<sw1.size();i++)printf(" %d %d",sw1[i].first+1,sw1[i].second+1);puts("");
  printf("%d",sw2.size());for(int i=0;i<sw2.size();i++)printf(" %d %d",sw2[i].first+1,sw2[i].second+1);puts("");

}

int main() {
  int N;
  while (1 == scanf("%d", &N) && N) {
    vector<int> A(N);
    rep (i, N) scanf("%d", &A[i]);
    // printf("N=%d\n", N);

    if (!solve0(A)) if (!solve1(A)) solve2(A);
  }

  return 0;
}
