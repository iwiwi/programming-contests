#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<vector>
#include<string>
#include<stack>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
#define INF 987654321

int n,m;
vector<vector<int> > graph;
vector<int> edge;
vector<int> edge2,edge4;
vector<vector<vector<int> > > dir;

vector<int> saiki1(int x,int pre){
  int now=x;
  vector<int> ans;
  ans.push_back(pre);
  while(1){
    ans.push_back(now);
    if(edge[now]==4)break;
    for(int i=0;i<graph[now].size();i++){
      if(graph[now][i]==pre)continue;
      pre=now;
      now=graph[now][i];
      break;
    }
  }
  return ans;
}

int num;
vector<int> border;
vector<vector<vector<int> > > path;

vector<int> dp[2][3];
vector<int> back[2][3];
int kotae[2];
vector<int> iro[2];

int main(void){
  scanf("%d %d",&n,&m);
  graph.resize(n);
  for(int i=0;i<m;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    a--;b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  edge.resize(n);
  for(int i=0;i<n;i++){
    edge[i]=graph[i].size();
    if(edge[i]==2)edge2.push_back(i);
    if(edge[i]==4)edge4.push_back(i);
  }
  dir.resize(edge4.size());
  for(int i=0;i<dir.size();i++)dir[i].resize(4);
  for(int i=0;i<edge4.size();i++){
    int pos=edge4[i];
    for(int j=0;j<4;j++)dir[i][j]=saiki1(graph[pos][j],pos);
  }

  num=edge4.size();
  border.resize(num+1);
  path.resize(num);
  for(int i=0;i<num;i++)path[i].resize(2);
  int start=edge4[0];
  int next=dir[start][0][dir[start][0].size()-1];
  for(int i=1;i<4;i++){
    if(next==dir[start][i][dir[start][i].size()-1]){
      border[0]=start;
      border[1]=next;
      path[0][0]=dir[start][0];
      path[0][1]=dir[start][i];
      break;
    }
  }
  for(int i=1;i<num;i++){
    int pos=border[i];
    int pre=border[i-1];
    int cnt=0;
    for(int j=0;j<4;j++){
      int d=dir[pos][j][dir[pos][j].size()-1];
      if(d==pre)continue;
      border[i+1]=d;
      path[i][cnt]=dir[pos][j];
      cnt++;
    }
  }

  for(int p=0;p<2;p++){
    for(int i=0;i<3;i++){
      dp[p][i].resize(num+1);
      back[p][i].resize(num+1);
    }
    for(int i=0;i<3;i++){
      dp[p][i][0]=INF;
      back[p][i][0]=-1;
    }
    dp[p][p][0]=(1-p);//!!!!!
    for(int i=1;i<=num;i++){
      for(int j=0;j<3;j++){
        dp[p][i][j]=INF;
        for(int k=0;k<3;k++){
          //dp[p][i-1][k] -> dp[p][i][j];
          if(k==0 || j==0){
            dp[p][i][j]=min(dp[p][i][j],dp[p][i-1][k]+(j==0?1:0));
          }else{
            if(k==j){
              if(path[i-1][0].size()%2==0 || path[i-1][1].size()%2==0)continue;
            }else{
              if(path[i-1][0].size()%2==1 || path[i-1][1].size()%2==0)continue;
            }
            dp[p][i][j]=min(dp[p][i][j],dp[p][i-1][k]);
          }
        }
        for(int k=0;k<3;k++){
          if(dp[p][i][j]==dp[p][i-1][k])back[p][i][j]=k;
        }
      }
    }
    kotae[p]=dp[p][num][p];
    iro[p].resize(num+1);
    iro[p][0]=iro[p][num]=p;
    int now=p;
    for(int i=num;i>0;i--){
      now=back[p][i][now];
      iro[p][i-1]=now;
    }
  }

  int mini=INF+1,pp=0;
  for(int p=0;p<2;p++){
    if(mini>kotae[p]){
      mini=kotae[p];
      pp=p;
    }
  }

  vector<int> group[3];
  for(int i=0;i<num;i++){
    group[iro[pp][i]].push_back(edge4[i]);
  }
  for(int i=0;i<num;i++){
    for(int j=0;j<2;j++){
      int now=iro[pp][i];
      int nex=iro[pp][i+1];
      int st;
      if(now!=0)st=3-now;
      else{
        if(nex==0)st=1;
        else{
          if(path[i][j].size()%2==0)st=nex;
          else st=3-nex;
        }
      }
      for(int k=1;k<path[i][j].size()-1;k++){
        group[st].push_back(path[i][j][k]);
        st=3-st;
      }
    }
  }

  for(int i=1;i<=2;i++){
    printf("%d",group[i].size());
    if(group[i].size()>0)printf(" ");
    for(int j=0;j<group[i].size();j++){
      printf("%d",group[i][j]);
      if(j<(int)group[i].size()-1)printf(" ");
    }
    printf("\n");
  }

  return 0;
}
