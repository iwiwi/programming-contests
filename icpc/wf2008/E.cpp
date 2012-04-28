#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> node;

int val[2000000];

int ans;

int siz;

void saiki(int idx,int ub){
  if(idx==siz){
    ans++;
    return;
  }
  int p=node[idx];
  for(int i=1;i<=val[p]-i;i++){
    if(val[p]-i>ub)continue;
    val[2*p]=val[p]-i;
    val[2*p+1]=i;
    saiki(idx+1,i);
  }
}

main(){
  for(int casenum=1;;casenum++){
    int n;
    scanf("%d ",&n);
    if(n==0)return 0;
    bool fukasugi=false;
    node.clear();
    for(int i=0;i<n;i++){
      char buf[100];
      scanf("%s",buf);
      if(strlen(buf)>30)fukasugi=true;
      else{
        int p=1;
        for(int k=0;buf[k];k++){
          node.push_back(p);
          if(buf[k]=='1')p=p*2; else p=p*2+1;
        }
        //ha[p]=true;
      }
    }
    sort(node.begin(),node.end());
    node.erase(unique(node.begin(),node.end()),node.end());
    siz=node.size();
    val[1]=100;
    ans=0;
    saiki(0,100);
    printf("Case %d: %d\n",casenum,ans);
  }
}
