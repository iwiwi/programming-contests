#include <stdio.h>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef long long ll;

ll get(ll x, int i) {
  return (x >> i * 4);
}




int n,m;

int p[15]={0,0,1,0,1,2,0,1,2,3,0,1,2,3,4};
int q[15]={0,1,0,2,1,0,3,2,1,0,4,3,2,1,0};
int rev[5][5]={
  {0,1,3,6,10},
  {2,4,7,11,-1},
  {5,8,12,-1,-1},
  {9,13,-1,-1,-1},
  {14,-1,-1,-1,-1}
};

int heu(vector<char> &state){
  int ret=0;
  for(int i=0;i<m;i++){
    if(state[i]!=0){
      ret+=abs(p[i]-p[state[i]])+abs(q[i]-q[state[i]]);
    }
  }

  int ret2=0;
  //for(int i=0;i<m;i++)for(int j=i+1;j<m;j++)if(state[i]>state[j] && state[j]>0)ret2++;
  //ret2/=4;
  return max(ret,ret2);
}





main(){
  for(int casenum=1;;casenum++){
    scanf("%d",&n);
    if(n==0)return 0;
    m=n*(n+1)/2;
    vector<char> init(m);
    vector<char> fin(m);
    int pos;
    for(int i=0;i<m;i++){int tmp;scanf("%d",&tmp);init[i]=tmp-1;if(tmp==1)pos=i;}
    for(int i=0;i<m;i++)fin[i]=i;
    set<vector<char> > visited;
    multimap<int,pair<vector<char>,int> > que;
    que.insert(make_pair(0+heu(init),make_pair(init,pos)));
    for(;;){
      if(que.empty()){puts("tokenai");break;}
      pair<int,pair<vector<char>,int> > h=*que.begin();
      que.erase(que.begin());
      vector<char> b=h.second.first;
      //for(int i=0;i<b.size();i++)printf("%d ",b[i]);puts("");
      if(visited.count(b)>0)continue;
      visited.insert(b);
      if(h.first>45)continue;
      int c=h.first-heu(b);
      if(b==fin){
        printf("Case %d: %d\n",casenum,c);
        break;
      }
      int pos=h.second.second;
      int posp=p[pos],posq=q[pos];
      vector<char> tmp;
      if(posp>0){
        tmp=b;
        int npos=rev[posp-1][posq];
        swap(tmp[pos],tmp[npos]);
        que.insert(make_pair(c+1+heu(tmp),make_pair(tmp,npos)));
      }
      if(posq>0){
        tmp=b;
        int npos=rev[posp][posq-1];
        swap(tmp[pos],tmp[npos]);
        que.insert(make_pair(c+1+heu(tmp),make_pair(tmp,npos)));
      }
      if(posp+posq<n-1){
        tmp=b;
        int npos=rev[posp+1][posq];
        swap(tmp[pos],tmp[npos]);
        que.insert(make_pair(c+1+heu(tmp),make_pair(tmp,npos)));
      }
      if(posp+posq<n-1){
        tmp=b;
        int npos=rev[posp][posq+1];
        swap(tmp[pos],tmp[npos]);
        que.insert(make_pair(c+1+heu(tmp),make_pair(tmp,npos)));
      }
    }
  }
}
