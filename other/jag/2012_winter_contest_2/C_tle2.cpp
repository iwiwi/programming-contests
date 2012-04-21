#include <stdio.h>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)
#define mp make_pair


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


map<vector<char>, int> ma[10];


int main(){
  { int n = 5;
    m = n * (n + 1) / 2;
    vector<char> s(n * (n + 1) / 2);
    rep (i, m) s[i] = i;
    
    queue<pair<vector<char>, int> > que;

    map<vector<char>, int> &visited = ma[n];
    
    que.push(mp(s, 0));
    visited.insert(mp(s, 0));
    
    while (!que.empty() && visited.size() <= 100000) {
      vector<char> b = que.front().first;
      int pos=que.front().second;
      int d = visited[b];
      que.pop();

      int posp=p[pos], posq=q[pos];
      vector<char> tmp;
      if(posp>0){
        tmp=b;
        int npos=rev[posp-1][posq];
        swap(tmp[pos],tmp[npos]);
        if(visited.count(tmp)==0) {
          que.push(make_pair(tmp,npos));
          visited.insert(mp(tmp, d + 1));
        }
      }
      if(posq>0){
        tmp=b;
        int npos=rev[posp][posq-1];
        swap(tmp[pos],tmp[npos]);
        if(visited.count(tmp)==0){
          que.push(make_pair(tmp,npos));
          visited.insert(mp(tmp, d + 1));
        }
      }
      if(posp+posq<n-1){
        tmp=b;
        int npos=rev[posp+1][posq];
        swap(tmp[pos],tmp[npos]);
        if(visited.count(tmp)==0){
          que.push(make_pair(tmp,npos));
          visited.insert(mp(tmp, d + 1));
        }
      }
      if(posp+posq<n-1){
        tmp=b;
        int npos=rev[posp][posq+1];
        swap(tmp[pos],tmp[npos]);
        if(visited.count(tmp)==0){
          que.push(make_pair(tmp,npos));
          visited.insert(mp(tmp, d + 1));
        }
      }
    }
  }


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

    int ans = 50;
    
    for(;;){
      if(que.empty()){puts("tokenai");break;}
      pair<int,pair<vector<char>,int> > h=*que.begin();

      if (h.first >= ans) break;

      que.erase(que.begin());
      vector<char> b=h.second.first;
      //for(int i=0;i<b.size();i++)printf("%d ",b[i]);puts("");
      //if(visited.count(b)>0)continue;
      visited.insert(b);
      if(h.first>45)continue;
      int c=h.first-heu(b);

      if (ma[n].count(b)) {
        ans = min(ans, c + ma[n][b]);
      }
      
      if(b==fin){
        ans = c;
        break;
      }
      int pos=h.second.second;
      int posp=p[pos],posq=q[pos];
      vector<char> tmp;
      if(posp>0){
        tmp=b;
        int npos=rev[posp-1][posq];
        swap(tmp[pos],tmp[npos]);
        if(visited.count(tmp)==0) {
          que.insert(make_pair(c+1+heu(tmp),make_pair(tmp,npos)));
          visited.insert(tmp);
        }
      }
      if(posq>0){
        tmp=b;
        int npos=rev[posp][posq-1];
        swap(tmp[pos],tmp[npos]);
        if(visited.count(tmp)==0){
          que.insert(make_pair(c+1+heu(tmp),make_pair(tmp,npos)));
          visited.insert(tmp);
        }
      }
      if(posp+posq<n-1){
        tmp=b;
        int npos=rev[posp+1][posq];
        swap(tmp[pos],tmp[npos]);
        if(visited.count(tmp)==0){
          que.insert(make_pair(c+1+heu(tmp),make_pair(tmp,npos)));
          visited.insert(tmp);
        }
      }
      if(posp+posq<n-1){
        tmp=b;
        int npos=rev[posp][posq+1];
        swap(tmp[pos],tmp[npos]);
        if(visited.count(tmp)==0){
          que.insert(make_pair(c+1+heu(tmp),make_pair(tmp,npos)));
          visited.insert(tmp);
        }
      }
    }
    printf("Case %d: %d\n",casenum,ans);
  }
}
