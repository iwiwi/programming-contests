#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
#define MP make_pair
typedef long long ll;

ll func(ll l,ll r,ll a){
  ll p=l/a;
  if(p<0)p=0;
  if(l<=p*a && p*a<=r)return p;
  if(l<=(p+1)*a && (p+1)*a<=r)return p+1;
  return p;
}

ll mypow(ll a,ll b){
  ll ans=1;
  for(ll i=1;i<=b;i++){
    ans*=a;
  }
  return ans;
}

//is a<=b
bool comp(const vector<pair<ll,char> > &a,const vector<pair<ll,char> > &b){
  ll suma=0,sumb=0;
  for(ll i=0;i<a.size();i++)suma+=a[i].first;
  for(ll i=0;i<b.size();i++)sumb+=b[i].first;
  if(suma<sumb)return true;
  if(suma>sumb)return false;
  for(ll i=0;i<min(a.size(),b.size());i++){
    if(a[i].second=='A' && b[i].second=='M')return true;
    if(a[i].second=='M' && b[i].second=='A')return false;
    if(a[i].second=='A' && b[i].second=='A'){
      if(a[i].first>b[i].first)return true;
      if(a[i].first<b[i].first)return false;
    }
    if(a[i].second=='M' && b[i].second=='M'){
      if(a[i].first>b[i].first)return false;
      if(a[i].first<b[i].first)return true;
    }
  }
  return true;
}

vector<pair<ll,char> > myunique(const vector<pair<ll,char> > &in){
  vector<pair<ll,char> > ans;
  if(in.size()==0)return ans;
  ll num=0;
  char ch=0;
  for(ll i=0;i<in.size();i++){
    if(ch==0){
      ch=in[i].second;
      num+=in[i].first;
    }else if(ch!=in[i].second){
      ans.push_back(MP(num,ch));
      ch=in[i].second;
      num=in[i].first;
    }else{
      num+=in[i].first;
    }
  }
  ans.push_back(MP(num,ch));
  return ans;
}

int main(void){

  for(int casenum=1;;casenum++){
    ll a,m,l1,r1,l2,r2,h1,h2;
    cin >> a >> m >> l1 >> r1 >> l2 >> r2;
    //scanf("%lld %lld %lld %lld %lld %lld",&a,&m,&l1,&r1,&l2,&r2);
    if(a==0 && m==0 && l1==0 && r1==0 && l2==0 && r2==0)break;
    printf("Case %d: ",casenum);
    h1=r1-l1;
    h2=r2-l2;
    if(l2<=l1 && r1<=r2){
      printf("empty\n");
      continue;
    }
    if(h1>h2){
      printf("impossible\n");
      continue;
    }
    if(m==1){
      ll l=l2-l1;
      ll r=r2-h1-l1;
      ll p=func(l,r,a);
      if(l<=p*a && p*a<=r){
        cout << p;
        printf("A\n");
      }else{
        printf("impossible\n");
      }
      continue;
    }
    vector<vector<pair<ll,char> > > allans;
    for(ll num=0;num<=30;num++){
      //printf("[%lld]\n",num);

      vector<pair<ll,char> > ans;

      ll h=h1*mypow(m,num);
      //printf("[%lld %lld %lld] %lld %lld (%lld)\n",m,num,mypow(m,num),h1,h2,h);
      if(l1*mypow(m,num)>r2)break;
      if(h>h2)break;

      ll pl=l2-l1*mypow(m,num);
      ll pr=r2-h-l1*mypow(m,num);
      if(pr<0)continue;
      if(pl<0)pl=0;

      //printf("(pl,pr)=(%lld,%lld)\n",pl,pr);

      ll l=pl/a;
      if(!(pl<=l*a && l*a<=pr))l++;
      ll r=pr/a;
      if(l>r)continue;

      //printf("(l,r)=(%lld,%lld)\n",l,r);

      bool end=false;
      for(ll i=num;i>=0;i--){
        ll mp=mypow(m,i);
        //printf("[%lld %lld %lld]\n",m,i,mp);
        ll p=func(l,r,mp);
        //printf("i=%lld p=%lld\n",i,p);
        if(end)p=0;
        if(p!=0)ans.push_back(MP(p,'A'));
        if(l<=p*mp && p*mp<=r){
          end=true;
        }
        l-=p*mp;
        r-=p*mp;
        if(i>0)ans.push_back(MP(1,'M'));
      }
      ans=myunique(ans);

      allans.push_back(ans);

      //for(ll j=0;j<ans.size();j++)printf("%lld%c ",ans[j].first,ans[j].second);
      //printf("\n");
    }
    for(ll i=0;i<allans.size();i++){
      for(ll j=0;j+1<allans.size();j++){
        if(comp(allans[j+1],allans[j])){
          swap(allans[j],allans[j+1]);
        }
      }
    }
    if(allans.size()==0){
      printf("impossible\n");
      continue;
    }
    vector<pair<ll,char> > ans=allans[0];
    for(ll i=0;i<ans.size();i++){
      cout << ans[i].first;
      printf("%c",ans[i].second);
      if(i+1<ans.size()){printf(" ");}
      else{printf("\n");}
    }
  }

  return 0;
}
