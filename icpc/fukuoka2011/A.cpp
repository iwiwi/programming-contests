#include <stdio.h>
#include <algorithm>
using namespace std;

main(){
  for(;;){
    int n;
    scanf("%d",&n);
    if(n==0)return 0;
    long long tot[1010]={};
    int iru[1010]={};
    long long prev=0;
    for(int i=0;i<n;i++){
      int M,D,h,m;
      scanf("%d/%d %d:%d",&M,&D,&h,&m);
      long long t=M*31*24*60+D*24*60+h*60+m;
      char c;
      scanf(" %c",&c);
      int id;
      scanf("%d",&id);
      if(iru[0]==1){
	for(int i=1;i<=999;i++)if(iru[i]==1)tot[i]+=(t-prev);
      }

      if(c=='I'){
	iru[id]=1;
      }else{
	iru[id]=0;
      }
      prev=t;
    }
    long long ans=0;
    for(int i=1;i<=999;i++)ans=max(ans,tot[i]);
    printf("%lld\n",ans);
  }
}
