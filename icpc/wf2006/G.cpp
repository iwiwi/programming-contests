#include<stdio.h>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
#define MP make_pair

int main(void){
  for(;;){
    int n;
    scanf("%d",&n);
    if(n==0)break;
    int kagen=0;
    int nowpay=0;
    int nownin=0;
    bool dedasi=true;
    vector<pair<int,int> > ve;
    for(int i=0;i<n;i++){
      char ch[100];
      int v;
      scanf("%s %d",ch,&v);
      if(ch[0]=='C')continue;
      if(ch[0]=='P'){
	nowpay+=v;
      }
      if(ch[0]=='I'){
	if(!dedasi)ve.push_back(MP(nowpay,nownin));
	nowpay=0;nownin+=v;
	kagen=min(kagen,nownin);
	dedasi=false;
      }
      if(ch[0]=='O'){
	if(!dedasi)ve.push_back(MP(nowpay,nownin));
	nowpay=0;nownin-=v;
	kagen=min(kagen,nownin);
	dedasi=false;
      }
    }
    kagen=(-kagen+1);
    bool allzero=true;

    /*printf("kagen=%d\n",kagen);
    for(int i=0;i<ve.size();i++){
      printf("(%d,%d)\n",ve[i].first,ve[i].second);
      }*/

    for(int i=0;i<ve.size();i++){
      if(ve[i].first!=0)allzero=false;
    }
    if(allzero){
      printf("SIZE >= %d\n",kagen);
      //printf("IMPOSSIBLE\n");
      continue;
    }
    vector<int> ans;
    for(int k=kagen;k<=500000;k++){
      bool ok=true;
      for(int i=0;i<ve.size();i++){
	if(k+ve[i].second<=0)while(1);
	if(ve[i].first%(k+ve[i].second)!=0)ok=false;
      }
      if(ok)ans.push_back(k);
    }
    if(ans.size()==0){
      printf("IMPOSSIBLE");
    }
    for(int i=0;i<ans.size();i++){
      printf("%d",ans[i]);
      if(i+1<ans.size())printf(" ");
    }
    printf("\n");
  }
  return 0;
}
