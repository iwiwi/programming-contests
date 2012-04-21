#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define P 1000000009

map<long long, vector<long long> > m;
vector<pair<long long,vector<long long> > > v;

long long mat[80][80];
long long matkjo[80][80][80];

long long charpoly[80];

int n;

vector<long long> polypow(long long m){
  vector<long long> ret(n);
  if(m==0){ret[0]=1;return ret;}
  ret=polypow(m/2);
  vector<long long> tmp(2*n);
  for(int i=0;i<n;i++)for(int j=0;j<n;j++)tmp[i+j]=(tmp[i+j]+ret[i]*ret[j])%P;
  for(int d=n-1;d>=0;d--){
    long long coef=tmp[d+n];
    for(int i=0;i<=n;i++)tmp[d+i]=((tmp[d+i]-coef*charpoly[i])%P+P)%P;
  }
  if(m%2==0){tmp.resize(n);return tmp;}
  vector<long long> tmp2(2*n);
  for(int i=0;i<n;i++)for(int j=0;j<n;j++)tmp2[i+j]=(tmp2[i+j]+tmp[i]*(j==1?1:0))%P;
  for(int d=n-1;d>=0;d--){
    long long coef=tmp2[d+n];
    for(int i=0;i<=n;i++)tmp2[d+i]=((tmp2[d+i]-coef*charpoly[i])%P+P)%P;
  }
  tmp2.resize(n);return tmp2;
}

vector<vector<long long> > matpow(long long m){
  vector<vector<long long> > ret(n,vector<long long>(n));
  vector<long long> hoge=polypow(m);
  //printf("polypow %lld: ",m);
  //for(int i=0;i<n;i++)printf("%lld ",hoge[i]);puts("");
  for(int k=0;k<n;k++){
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)ret[i][j]=(ret[i][j]+hoge[k]*matkjo[k][i][j])%P;
  }
  return ret;
}

long long binom[80][80];

main(){
  for(int i=0;i<80;i++)for(int j=0;j<=i;j++)binom[i][j]=(j==0||j==i?1:(binom[i-1][j]+binom[i-1][j-1])%P);
  for(int casenum=1;;casenum++){
    m.clear();v.clear();
    long long yoko,tate,pts;
    scanf("%lld%lld%lld\n",&yoko,&tate,&pts);
    n=yoko;
    if(yoko==0)return 0;
    for(int i=0;i<yoko;i++)for(int j=0;j<yoko;j++)mat[i][j]=((i==j||i==j-1||i==j+1)?1:0);
    //powkjo
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)matkjo[0][i][j]=(i==j?1:0);
    for(int k=1;k<n;k++){
      for(int i=0;i<n;i++)for(int j=0;j<n;j++)matkjo[k][i][j]=0;
      for(int i=0;i<n;i++)for(int j=0;j<n;j++){
          matkjo[k][i][j]=matkjo[k-1][i][j];
          if(j>0)matkjo[k][i][j]=(matkjo[k][i][j]+matkjo[k-1][i][j-1])%P;
          if(j<n-1)matkjo[k][i][j]=(matkjo[k][i][j]+matkjo[k-1][i][j+1])%P;
        }
    }
    //charateristic poly
    for(int i=0;i<=n;i++)charpoly[i]=0;
    for(int d=n,x=n,y=0,e=1;d>=0;d-=2,x--,y++,e*=-1){
      for(int i=0,f=1;i<=d;i++,f*=-1){
        charpoly[i]=(charpoly[i]+e*binom[x][y]*f*binom[d][i])%P;
      }
    }
    if(n%2==1)for(int i=0;i<=n;i++)charpoly[i]=(P-charpoly[i])%P;
    //for(int i=0;i<=n;i++)printf("%lld ",charpoly[i]);puts("");
    for(int i=0;i<pts;i++){
      long long p,q;
      scanf("%lld%lld",&q,&p);p--;q--;
      if(m.count(p)==0)m.insert(make_pair(p,vector<long long>(1,q)));
      else m[p].push_back(q);
    }
    if(yoko==1){printf("Case %d: %d\n",casenum,pts>0?0:1);continue;}
    for(map<long long,vector<long long> >::iterator ite=m.begin();ite!=m.end();ite++)v.push_back(*ite);
    if(v.size()==0 || v.back().first!=tate-1)v.push_back(make_pair(tate-1,vector<long long>(0)));
    long long dp[80];
    for(int i=0;i<yoko;i++)dp[i]=(i==0?1:0);
    long long prev=0;
    for(int i=0;i<v.size();i++){
      if(v[i].first==0)continue;
      vector<vector<long long> > a=matpow(v[i].first-prev-1);
      long long dp2[80]={};
      /*
      for(int k=0;k<yoko;k++){
        for(int l=0;l<yoko;l++)printf("%lld ",a[k][l]);puts("");
      }
      puts("");
      */
      for(int k=0;k<yoko;k++)for(int l=0;l<yoko;l++)dp2[k]=(dp2[k]+a[k][l]*dp[l])%P;
      for(int k=0;k<yoko;k++){
        dp[k]=dp2[k];
        if(k>0)dp[k]=(dp[k]+dp2[k-1])%P;
        if(k<yoko-1)dp[k]=(dp[k]+dp2[k+1])%P;
      }
      for(int r=0;r<v[i].second.size();r++)dp[v[i].second[r]]=0;
      prev=v[i].first;
      //for(int k=0;k<yoko;k++)printf("%lld ",dp[k]);puts("");
    }
    printf("Case %d: %lld\n",casenum,dp[yoko-1]);
  }
}
