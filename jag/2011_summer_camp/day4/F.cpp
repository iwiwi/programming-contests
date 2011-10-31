#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
using namespace std;

#define M 1000000

typedef vector<vector<double> > mat;
#define EPS 1e-9

vector<double> gj(mat A,const vector<double>& b){
  int n=A.size();
  for(int i=0;i<n;i++)A[i].resize(n+1,b[i]);
  for(int k=0;k<n;k++){
    int piv=k;
    for(int i=k+1;i<n;i++)
      if(fabs(A[i][k])>fabs(A[piv][k]))piv=i;
    swap(A[k],A[piv]);
    for(int i=n;i>=k;i--)A[k][i]/=A[k][k];
    for(int i=0;i<n;i++){
      if(i==k)continue;
      for(int j=n;j>=k;j--)A[i][j]-=A[i][k]*A[k][j];
    }
  }
  vector<double> x;
  for(int i=0;i<n;i++)x.push_back(A[i][n]);
  return x;
  /*
  int pi=0;
  for(int pj=0;pj<n&&pi<m;pj++){
    for(int i=pi+1;i<m;i++)if(fabs(A[pi][pj])<abs(A[i][pj]))swap(A[pi],A[i]);
    if(fabs(A[pi][pj])<EPS)continue;
    for(int j=n;j>=
  }
  */
}

double dp[M+1];


main(){
  int s,n,k;
  scanf("%d%d%d",&s,&n,&k);
  if(s==0){printf("0\n");return 0;}
  if(s<0)s=-s;
  if(n==1){
    if(s%k==0)printf("%d\n",s/k);
    else printf("-1\n");
    return 0;
  }
  double dicedp[200]={};
  dicedp[0]=1;
  for(int i=0;i<k;i++){
    double tmp[200]={};
    for(int a=0;a<=n*i;a++){
      for(int d=1;d<=n;d++){
        tmp[a+d]+=dicedp[a]/n;
      }
    }
    memcpy(dicedp,tmp,sizeof(tmp));
  }
  int m=n*k;

  mat ren(m);
  for(int i=0;i<m;i++)ren[i].resize(m);

  ren[0][0]=1;
  for(int i=1;i<m;i++){
    for(int d=1;d<=m;d++){
      ren[i][abs(i-d)]+=dicedp[d];
    }
    ren[i][i]=ren[i][i]-1;
  }
  vector<double> b(m);
  for(int i=1;i<m;i++)b[i]=-1;
  //printmat(ren);
  vector<double> x=gj(ren,b);

  for(int i=0;i<m;i++)dp[i]=x[i];
  for(int i=m;i<=M;i++){
    dp[i]=1;
    for(int d=1;d<=m;d++){
      dp[i]+=dicedp[d]*dp[abs(i-d)];
    }
  }
  double ans;
  if(s<=M)ans=dp[s];
  else ans=dp[M]+(double)(s-M)*2/((n+1)*k);
  printf("%.10lf\n",ans);
}
