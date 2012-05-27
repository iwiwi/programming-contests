#include<stdio.h>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;
#define MAX 98765

int n;
string st;

int dame=0;
vector<int> val;
vector<vector<int> > value;

int ans=MAX;
vector<int> ansve;

int bitnum[(1<<20)+100];

void saiki(int pos,int num,int mask){

  if(pos>=value.size()){
    if(ans<bitnum[num])return;
    vector<int> ve;
    for(int i=0;i<20;i++){
      if((num&(1<<i))!=0)ve.push_back(i);
    }
    if(ans>bitnum[num]){
      ans=bitnum[num];
      ansve=ve;
    }else if(ve<ansve){
      ansve=ve;
    }
    return;
  }

  if((val[pos]&num)!=0){
    saiki(pos+1,num,mask);
  }else{
    int m=0;
    for(int i=0;i<value[pos].size();i++){
      int v=value[pos][i];

      if((mask&(1<<v))==0){
        int nnum=num;
        int nmask=mask;

        nnum|=(1<<v);
        nmask|=(m);

        saiki(pos+1,nnum,nmask);
      }

      m|=(1<<v);
    }
  }

  return;
}

int main(void){
  for(int i=0;i<=(1<<20);i++){
    bitnum[i]=__builtin_popcount(i);
  }
  int casenum=0;
  scanf("%d ",&casenum);
  for(int casecnt=1;casecnt<=casenum;casecnt++){
    cin >> st;
    if (count(st.begin(), st.end(), 'L') == st.length()) {
      printf("Case %d: %d\n",casecnt, (int)st.length() + 1);
      continue;
    }
    
    st="L"+st;
    n=st.size();
    dame=0;
    val.clear();
    value.clear();
    for(int i=0;i<n;i++){
      if(st[i]=='W')continue;
      for(int j=0;j<i;j++){
        if(st[j]=='W')continue;
        if(i-j>=21)continue;
        dame|=(1<<(i-j-1));
      }
    }
    for(int i=0;i<n;i++){
      if(st[i]=='L')continue;
      vector<int> ve;
      int v=0;
      for(int j=0;j<i;j++){
        if(st[j]=='W')continue;
        if(i-j>=21)continue;
        v|=(1<<(i-j-1));
      }
      v&=(~dame);
      for(int j=0;j<20;j++){
        if((v&(1<<j))!=0)ve.push_back(j);
      }
      val.push_back(v);
      value.push_back(ve);
      //printf("%d\n",v);
      //for(int i=0;i<ve.size();i++)printf("%d ",ve[i]);
      //printf("\n");
    }
    ans=MAX;
    ansve.clear();
    saiki(0,0,0);
    printf("Case %d:",casecnt);
    for(int i=0;i<ansve.size();i++){
      printf(" %d",ansve[i]+1);
    }
    printf("\n");
  }
  return 0;
}
