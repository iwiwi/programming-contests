#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
#define EPS 1e-9

typedef vector<double> vec_t;
typedef vector<vec_t> mat_t;

vec_t gauss_jordan(mat_t A,const vec_t &b){
  int m=A.size(),n=A[0].size();
  for(int i=0;i<m;i++)A[i].resize(n+1,b[i]);
  int pi=0;
  for(int pj=0;pj<n&&pi<m;pj++){
    for(int i=pi+1;i<m;i++)if(fabs(A[pi][pj])<fabs(A[i][pj]))swap(A[pi],A[i]);
    if(fabs(A[pi][pj])<EPS)return vec_t();
    for(int j=n;j>=pj;j--)A[pi][j]=A[pi][j]/A[pi][pj];
    for(int i=0;i<m;i++)if(i!=pi)for(int j=n;j>=pj;j--)A[i][j]=A[i][j]-A[i][pj]*A[pi][j];
    pi++;
  }
  vec_t x(n,0);
  for(int i=0;i<m;i++){
    int j;
    for(j=0;j<n;j++)if(!(fabs(A[i][j])<EPS))break;
    if(j==n&&!(fabs(A[i][n])<EPS))return vec_t();
    else if(j<n)x[j]=A[i][n];
  }
  return x;
}

main(){
  for(;;){
    int n;
    if(scanf("%d ",&n)<=0)break;
    string nick[2000],sig[2000];
    for(int i=0;i<n;i++){
      char buf[2000];
      gets(buf);
      bool hoge=false;
      for(int k=0;buf[k];k++){
        if(buf[k]==':'){
          hoge=true;
        }else{
          if(hoge)sig[i]=sig[i]+buf[k];
          else nick[i]=nick[i]+buf[k];
        }
      }
      sig[i]=sig[i]+' ';
    }
    map<string,int> m;
    for(int i=0;i<n;i++){
      m.insert(make_pair(nick[i],i));
    }
    mat_t A(n);
    for(int i=0;i<n;i++)A[i].resize(n);
    vec_t b(n);
    bool adj[110][110];
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)adj[i][j]=(i==j);
    for(int i=0;i<n;i++){
      int cnt[200]={};
      int tot=0;
      int l=sig[i].length();
      string tmp=string("");
      for(int k=0;k<l;k++){
        if(sig[i][k]>='a' && sig[i][k]<='z'){
          tmp+=sig[i][k];
        }else{
          if(m.find(tmp)!=m.end() && m[tmp]!=i){
            tot++;
            cnt[m[tmp]]++;
            adj[i][m[tmp]]=true;
            //printf("%s -> %s\n",nick[i].c_str(),tmp.c_str());
          }
          tmp=string("");
        }
      }
      for(int j=0;j<n;j++)A[i][j]=0;
      A[i][i]=1;
      if(tot!=0){
        for(int j=0;j<n;j++)A[i][j]-=(double)cnt[j]/tot;
      }
      b[i]=1;
    }
    for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)adj[i][j]=adj[i][j]||(adj[i][k]&&adj[k][j]);
    vector<int> ikeru;
    int p;
    for(int i=0;i<n;i++){
      if(adj[m[string("princess")]][i]){
        ikeru.push_back(i);
        //printf("ikeru %s\n",nick[i].c_str());
        if(nick[i]==string("princess"))p=ikeru.size()-1;
      }
    }
    int newn=ikeru.size();
    mat_t newA(newn);
    for(int i=0;i<newn;i++)newA[i].resize(newn);
    vec_t newb(newn);
    for(int i=0;i<newn;i++)for(int j=0;j<newn;j++)newA[i][j]=A[ikeru[i]][ikeru[j]];
    for(int i=0;i<newn;i++)newb[i]=b[ikeru[i]];
    /*
    for(int i=0;i<newn;i++){
      for(int j=0;j<newn;j++)printf("%.3f ",newA[i][j]);
      printf("  %.3f\n",newb[i]);
    }
    */
    vec_t ret=gauss_jordan(newA,newb);
    if(ret.empty())printf("Infinity\n");
    else printf("%.3f\n",ret[p]);
  }
}
