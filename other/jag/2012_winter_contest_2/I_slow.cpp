#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define P 1000000009

map<long long, vector<long long> > m;
vector<pair<long long,vector<long long> > > v;

vector<vector<long long> > matpow(vector<vector<long long> > &mat, int m){
  int n=mat.size();
  vector<vector<long long> > ret(n,vector<long long>(n));
  if(m==0){
    for(int i=0;i<n;i++)ret[i][i]=1;
    return ret;
  }
  ret=matpow(mat,m/2);
  vector<vector<long long> > sqret(n,vector<long long>(n));
  for(int i=0;i<n;i++)for(int j=0;j<n;j++)for(int k=0;k<n;k++)sqret[i][k]=(sqret[i][k]+ret[i][j]*ret[j][k])%P;
  if(m%2==0)return sqret;
  vector<vector<long long> > sqretmat(n,vector<long long>(n));
  for(int i=0;i<n;i++)for(int j=0;j<n;j++)for(int k=0;k<n;k++)sqretmat[i][k]=(sqretmat[i][k]+sqret[i][j]*mat[j][k])%P;
  return sqretmat;
}

main(){
  for(int casenum=1;;casenum++){
    m.clear();v.clear();
    long long yoko,tate,n;
    scanf("%lld%lld%lld\n",&yoko,&tate,&n);
    if(yoko==0)return 0;
    vector<vector<long long> > mat(yoko,vector<long long>(yoko));
    for(int i=0;i<yoko;i++)for(int j=0;j<yoko;j++)mat[i][j]=((i==j||i==j-1||i==j+1)?1:0);
    for(int i=0;i<n;i++){
      long long p,q;
      scanf("%lld%lld",&q,&p);p--;q--;
      if(m.count(p)==0)m.insert(make_pair(p,vector<long long>(1,q)));
      else m[p].push_back(q);
    }
    for(map<long long,vector<long long> >::iterator ite=m.begin();ite!=m.end();ite++)v.push_back(*ite);
    if(v.back().first!=tate-1)v.push_back(make_pair(tate-1,vector<long long>(0)));
    long long dp[80];
    for(int i=0;i<yoko;i++)dp[i]=(i==0?1:0);
    long long prev=0;
    for(int i=0;i<v.size();i++){
      if(v[i].first==0)continue;
      vector<vector<long long> > a=matpow(mat,v[i].first-prev-1);
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
