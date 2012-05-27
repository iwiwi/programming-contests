#include<stdio.h>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;
typedef long long ll;

//a is turn
bool doit(vector<ll> a,vector<ll> b,int turn){
  if(turn==1)a.swap(b);
  int win;
  while(1){
    int n=a.size();
    int m=b.size();
    if(n==0){win=1-turn;break;}
    if(m==0){win=turn;break;}
    if(n>=2){
      ll p=a[n-1]+a[n-2];
      if(p<b[m-1]){win=1-turn;break;}
      a.pop_back();
      a.pop_back();
      a.push_back(p);
    }else{
      if(a[n-1]>b[m-1]){
	b.pop_back();
      }else{
	win=1-turn;
	break;
      }
    }

    turn=(turn+1)%2;
    a.swap(b);
  }
  if(win==0)return true;
  else return false;
}

int main(void){
  for(int casenum=1;;casenum++){
    int n,m;
    if(scanf("%d %d",&n,&m)<=0)break;
    vector<ll> a(n),b(m);
    for(int i=0;i<n;i++)scanf("%lld",&a[i]);
    for(int i=0;i<m;i++)scanf("%lld",&b[i]);
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    bool t1=false;
    bool t2=false;

    if(doit(a,b,0))t1=true;
    if(a[n-1]>b[m-1]){
      b.pop_back();
      if(doit(a,b,1))t2=true;
    }

    printf("Case %d: ",casenum);
    if(t1 || t2)printf("Takeover Incorporated\n");
    else printf("Buyout Limited\n");
  }
  return 0;
}
