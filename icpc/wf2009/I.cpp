#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

double x[200],y[200],xx[200],yy[200];

//true is bane!!!
bool isx1[200],isx2[200],isx3[200];
bool isy1[200],isy2[200],isy3[200];

bool isoya[200][200];
int oyacnt[200];

int oya[200];

double x0[200],x1[200],yy0[200],yy1[200];
bool check[200];

bool inrect(double x0,double y0,double x1,double y1,double X0,double Y0,double X1,double Y1){
  if(X0<=x0 && Y0<=y0 && x1<=X1 && y1<=Y1)return true;
  return false;
}

void doit(double p1,double p2,double p3,bool is1,bool is2,bool is3,double len,double &n1,double &n2,double &n3){
  double sum=0,bsum=0;

  if(!is1){n1=p1;bsum+=p1;}
  else{sum+=p1;}
  if(!is2){n2=p2;bsum+=p2;}
  else{sum+=p2;}
  if(!is3){n3=p3;bsum+=p3;}
  else{sum+=p3;}

  if(is1){n1=p1/sum*(len-bsum);}
  if(is2){n2=p2/sum*(len-bsum);}
  if(is3){n3=p3/sum*(len-bsum);}

  return;
}

void saiki(int pos,double &nx0,double &ny0,double &nx1,double &ny1){
  if(check[pos]){
    nx0=x0[pos];
    ny0=yy0[pos];
    nx1=x1[pos];
    ny1=yy1[pos];
    return;
  }

  int opos=oya[pos];

  double px0,py0,px1,py1;
  saiki(opos,px0,py0,px1,py1);

  double ax1,ax2,ax3;
  double ay1,ay2,ay3;
  doit(x[pos]-x[opos],xx[pos],xx[opos]-xx[pos]-(x[pos]-x[opos]),isx1[pos],isx2[pos],isx3[pos],px1-px0,ax1,ax2,ax3);
  doit(y[pos]-y[opos],yy[pos],yy[opos]-yy[pos]-(y[pos]-y[opos]),isy1[pos],isy2[pos],isy3[pos],py1-py0,ay1,ay2,ay3);

  x0[pos]=nx0=px0+ax1;
  x1[pos]=nx1=px0+ax1+ax2;
  yy0[pos]=ny0=py0+ay1;
  yy1[pos]=ny1=py0+ay1+ay2;
  check[pos]=true;

  return;
}

int main(void){
  for(int casenum=1;;casenum++){
    int n,m;
    x[0]=y[0]=0;
    scanf("%d %d %lf %lf",&n,&m,&xx[0],&yy[0]);
    if(n==0 && m==0 && xx[0]==0 && yy[0]==0)break;
    for(int i=1;i<=n;i++){
      scanf("%lf %lf %lf %lf",&x[i],&y[i],&xx[i],&yy[i]);
      int a,b,c,d,e,f;
      scanf("%d %d %d %d %d %d",&a,&b,&c,&d,&e,&f);
      isx1[i]=isx2[i]=isx3[i]=isy1[i]=isy2[i]=isy3[i]=false;
      if(e==1)isx1[i]=true;
      if(a==1)isx2[i]=true;
      if(f==1)isx3[i]=true;
      if(c==1)isy1[i]=true;
      if(b==1)isy2[i]=true;
      if(d==1)isy3[i]=true;
      if(!isx1[i] && !isx2[i] && !isx3[i])isx3[i]=true;
      if(!isy1[i] && !isy2[i] && !isy3[i])isy1[i]=true;
    }
    n++;
    for(int i=0;i<n;i++){
      oyacnt[i]=0;
      for(int j=0;j<n;j++){
        isoya[i][j]=false;
        if(i==j)continue;
        if(inrect(x[i],y[i],x[i]+xx[i],y[i]+yy[i],x[j],y[j],x[j]+xx[j],y[j]+yy[j])){
          isoya[i][j]=true;
          oyacnt[i]++;
        }
      }
    }
    oya[0]=-1;
    for(int i=1;i<n;i++){
      for(int j=0;j<n;j++){
        if(i==j)continue;
        if(isoya[i][j] && oyacnt[i]-1==oyacnt[j])oya[i]=j;
      }
    }
    for(int openum=1;openum<=m;openum++){
      for(int i=0;i<n;i++){
        check[i]=false;
      }
      double xsize,ysize;
      scanf("%lf %lf",&xsize,&ysize);
      x0[0]=x[0];
      yy0[0]=y[0];
      x1[0]=x[0]+xsize;
      yy1[0]=y[0]+ysize;
      check[0]=true;
      printf("Case %d, resize operation %d:\n",casenum,openum);
      for(int i=1;i<n;i++){
        double nx0,ny0,nx1,ny1;
        saiki(i,nx0,ny0,nx1,ny1);
        printf("    Window %d, x = %.f, y = %.f, width = %.f, height = %.f\n",i,nx0,ny0,nx1-nx0,ny1-ny0);
      }
    }
  }
  return 0;
}
