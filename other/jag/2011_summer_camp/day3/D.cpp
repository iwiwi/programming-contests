#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;
#define EPS 1e-9
#define INF 1e9
main(){
  int n,m;
  double l;
  scanf("%d%d%lf",&n,&m,&l);
  double p[200],t[200],v[200];
  for(int i=0;i<n;i++){
    scanf("%lf%lf%lf",&p[i],&t[i],&v[i]);
    if(t[i]==0){p[i]=0;t[i]=1;}
    p[i]/=100;
  }
  double binom[60][60];
  for(int i=0;i<=50;i++)for(int j=0;j<=i;j++)binom[i][j]=(j==0||j==i?1:binom[i-1][j]+binom[i-1][j-1]);
  double prob[200][60];
  memset(prob,0,sizeof(prob));
  for(int i=0;i<n;i++){
    for(int j=0;j<=m;j++){
      if(p[i]==0){
        prob[i][j]=(j==0?1:0);
      }else if(p[i]==1){
        prob[i][j]=(j==m?1:0);
      }else prob[i][j]=binom[m][j]*pow(p[i],j)*pow(1-p[i],m-j);
    }
  }
  double rui[200][60];
  for(int i=0;i<n;i++){
    rui[i][m+1]=0;
    for(int j=m;j>=0;j--)rui[i][j]=rui[i][j+1]+prob[i][j];
  }

  for(int i=0;i<n;i++){
    double ans=0;
    if(v[i]==0)ans=0;
    else{
      for(int k=0;k<=m;k++){
        double prod=1;
        for(int j=0;j<n;j++){
          if(j==i)continue;
          if(v[j]==0)continue;
          double hoge=(l/v[i]+k*t[i]-l/v[j])/t[j];
          int p;
          if(hoge<-EPS)p=0; else p=1+(int)(hoge+EPS);
          if(p>=m+1)p=m+1;
          prod*=rui[j][p];
        }
        ans+=prod*prob[i][k];
      }
    }
    printf("%.10f\n",ans);
  }
}
