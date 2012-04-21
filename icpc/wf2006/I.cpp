#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
#define MAX 98765

int main(void){
  for(int casenum=1;;casenum++){
    int n,m;
    scanf("%d %d",&n,&m);
    if(n==0 && m==0)break;
    vector<vector<int> > dist(n,vector<int>(n));
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
	dist[i][j]=MAX;
    }
    for(int i=0;i<n;i++)dist[i][i]=0;
    map<string,int> ma;
    int num=0;
    for(int i=0;i<m;i++){
      string s1,s2;
      cin >> s1 >> s2;
      if(ma.count(s1)==0){
	ma[s1]=num;
	num++;
      }
      if(ma.count(s2)==0){
	ma[s2]=num;
	num++;
      }
      dist[ma[s1]][ma[s2]]=1;
      dist[ma[s2]][ma[s1]]=1;
    }
    /*for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
	printf("%d ",dist[i][j]);
      }
      printf("\n");
      }*/
    for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++){
	  dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    }
    int ans=0;
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
	ans=max(ans,dist[i][j]);
    }
    printf("Network %d: ",casenum);
    if(ans==MAX)printf("DISCONNECTED\n");
    else printf("%d\n",ans);
    printf("\n");
  }
  return 0;
}

