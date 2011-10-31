#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

void solve(vector<int> v){
  int twocnt=0,threecnt=0;
  for(int i=0;i<v.size();i++){
    if(v[i]==2)twocnt++;
    if(v[i]==3)threecnt++;
  }
  if(twocnt==v.size()-1 && threecnt==1){
  	if(twocnt>0){
	    for(int i=0;i<twocnt-1;i++)printf("2\n");
	    printf("3\n");
	    printf("2\n");
	}else{
		printf("3\n");
	}
  }else{
    for(int i=0;i<v.size();i++)printf("%d\n",v[i]);
  }
}

main(){
  int n;
  scanf("%d",&n);
  int a[200];
  for(int i=0;i<n;i++)scanf("%d",&a[i]);
  int zerocnt=0,onecnt=0;
  for(int i=0;i<n;i++){
    if(a[i]==0)zerocnt++;
    if(a[i]==1)onecnt++;
  }
  if(zerocnt==n){
    for(int i=0;i<n;i++)printf("0\n");
  }else if(zerocnt+onecnt==n){
    for(int i=0;i<zerocnt/2*2;i++)printf("0\n");
    printf("1\n");
    for(int i=0;i<zerocnt%2;i++)printf("0\n");
    for(int i=0;i<onecnt-1;i++)printf("1\n");
  }else if(zerocnt==n-1 && zerocnt%2==1){
    for(int i=0;i<zerocnt-1;i++)printf("0\n");
    for(int i=0;i<n;i++)if(a[i]!=0)printf("%d\n",a[i]);
    printf("0\n");
  }else{
    vector<int> ookii;
    for(int i=0;i<n;i++)if(a[i]>=2)ookii.push_back(a[i]);
    sort(ookii.begin(),ookii.end());
    if(onecnt==0 && zerocnt%2==1){
      vector<int> v;
      for(int i=1;i<ookii.size();i++)v.push_back(ookii[i]);
      solve(v);
      for(int i=0;i<zerocnt-1;i++)printf("0\n");
      printf("%d\n",ookii[0]);
      printf("0\n");
    }else{
      solve(ookii);
      if(onecnt>=1){
        for(int i=0;i<zerocnt/2*2;i++)printf("0\n");
        printf("1\n");
        for(int i=0;i<zerocnt%2;i++)printf("0\n");
        for(int i=0;i<onecnt-1;i++)printf("1\n");
      }else{
        for(int i=0;i<zerocnt;i++)printf("0\n");
      }
    }
  }
}
