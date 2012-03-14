#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;

#define MAX 510000

int oya[MAX],left[MAX],right[MAX];
ll leafnum[MAX],rootdist[MAX],nosave[MAX],dosave[MAX];
vector<int> ord;

int main(void){
  int n;
  scanf("%d",&n);
  rootdist[0]=0;
  for(int i=0;i<n-1;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    a--;b--;
    oya[a]=i;
    oya[b]=i;
    left[i]=a;
    right[i]=b;
    if(i!=0)rootdist[i]=rootdist[oya[i]]+1;
  }
  {//BFS
    queue<int> qu;
    vector<bool> check(MAX);
    qu.push(0);
    while(qu.size()){
      int p=qu.front();
      qu.pop();
      if(p==n-1)continue;
      ord.push_back(p);
      qu.push(left[p]);
      qu.push(right[p]);
    }
    ord.push_back(n-1);
  }
  reverse(ord.begin(),ord.end());
  /*for(int i=0;i<ord.size();i++){
    printf("%d ",ord[i]+1);
  }
  printf("\n");*/

  leafnum[n-1]=1;
  nosave[n-1]=0;
  dosave[n-1]=0;
  for(int pp=1;pp<ord.size();pp++){
    int p=ord[pp];
    int lp=left[p],rp=right[p];
    //printf("%d\n",p+1);
    leafnum[p]=leafnum[lp]+leafnum[rp];
    nosave[p]=(nosave[lp]+leafnum[lp])+(nosave[rp]+leafnum[rp]);
    ll a,b,c;
    a=(nosave[lp]+leafnum[lp])+(1+dosave[rp]);
    b=(1+dosave[lp])+(nosave[rp]+leafnum[rp]);
    c=(1+dosave[lp])+rootdist[p]+(1+dosave[rp]);
    dosave[p]=min(min(a,b),c);
  }

  /*for(int i=0;i<n;i++){
    printf("%d : leafnum:%lld rootdist:%lld nosave:%lld dosave:%lld\n",i+1,leafnum[i],rootdist[i],nosave[i],dosave[i]);
    }*/

  printf("%lld\n",dosave[0]);

  return 0;
}
