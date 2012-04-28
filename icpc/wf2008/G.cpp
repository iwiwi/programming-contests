#include <stdio.h>
#include <math.h>
#define EPS 1e-9
#include <vector>
#include <algorithm>
using namespace std;

vector<double> gaussjordan(vector<vector<double> > A,vector<double> b){
  int m=A.size(),n=A[0].size();
  for(int i=0;i<m;i++)A[i].resize(n+1,b[i]);
  int pi=0;
  for(int pj=0;pj<n&&pi<m;pj++){
    for(int i=pi+1;i<m;i++)if(fabs(A[pi][pj])<fabs(A[i][pj]))swap(A[pi],A[i]);
    if(fabs(A[pi][pj])<EPS)continue;
    for(int j=n;j>=pj;j--)A[pi][j]=A[pi][j]/A[pi][pj];
    for(int i=0;i<m;i++)if(i!=pi)for(int j=n;j>=pj;j--)A[i][j]=A[i][j]-A[i][pj]*A[pi][j];
    pi++;
  }

  vector<double> x(n,0);
  for(int i=0;i<m;i++){
    int j;
    for(j=0;j<n;j++)if(fabs(A[i][j])>=EPS)break;
    if(j==n && fabs(A[i][n])>=EPS)return vector<double>();
    else if(j<n)x[j]=A[i][n];
  }
  return x;
}

double mypow(double x,int n){
  double ret=1;
  for(int i=0;i<n;i++)ret*=x;
  return ret;
}

main(){
  for(int casenum=1;;casenum++){
    int m;
    scanf("%d",&m);
    if(m==0)return 0;
    double p[100];
    for(int i=m;i>=0;i--)scanf("%lf",&p[i]);
    double c;
    scanf("%lf",&c);
    double ka0=0,ka1=0,kb0=0,kb1=0,ka0sq,ka0a1,ka1sq,kb0sq,kb0b1,kb1sq;
    for(int n=0;n<=m;n++){
      ka0+=-2*p[n]*(mypow(c,n+1)-mypow(-1,n+1))/(double)(n+1);
      ka1+=-2*p[n]*(mypow(c,n+2)-mypow(-1,n+2))/(double)(n+2);
      kb0+=-2*p[n]*(mypow(1,n+1)-mypow(c,n+1))/(double)(n+1);
      kb1+=-2*p[n]*(mypow(1,n+2)-mypow(c,n+2))/(double)(n+2);
    }
    ka0sq=c+1;
    ka0a1=c*c-1;
    ka1sq=(c*c*c+1)/3;
    kb0sq=1-c;
    kb0b1=1-c*c;
    kb1sq=(1-c*c*c)/3;
    
    double mat[5][5]={
      {2*ka0sq,ka0a1,0,0,1},
      {ka0a1,2*ka1sq,0,0,c},
      {0,0,2*kb0sq,kb0b1,-1},
      {0,0,kb0b1,2*kb1sq,-c},
      {1,c,-1,-c,0}
    };
    double vec[5]={-ka0,-ka1,-kb0,-kb1,0};
    
    vector<vector<double> > A(5,vector<double>(5));
    vector<double> b(5);
    for(int i=0;i<5;i++)for(int j=0;j<5;j++)A[i][j]=mat[i][j];
    for(int i=0;i<5;i++)b[i]=vec[i];
    vector<double> ret=gaussjordan(A,b);
    printf("Case %d: %.3f %.3f %.3f %.3f\n",casenum,ret[1],ret[0],ret[3],ret[2]);
  }
}
