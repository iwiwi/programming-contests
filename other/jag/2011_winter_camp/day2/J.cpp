#include <stdio.h>
#include <complex>
#include <algorithm>
#include <vector>
#include <iostream>

#define EPS 1e-12

using namespace std;

typedef complex<long long> p_t;

#define d(k) (dot(P[(k)%n],v))

long long dot(p_t p,p_t q){return real(conj(p)*q);}
long long det(p_t p,p_t q){return imag(conj(p)*q);}

int convex_extreme_id(const vector<p_t> &P,const p_t &v){
	int n=P.size();
	int a=0,b=n;
	if(d(0)>=d(n-1) && d(0)>=d(1))return 0;
	while(b-a>1){
		int c=(a+b)/2;
		if(d(c)>=d(c-1) && d(c)>=d(c+1))return c;
		if(d(a+1)>d(a)){
			if(d(c+1)<=d(c) || d(a)>d(c))b=c;
			else a=c;
		}else{
			if(d(c+1)>d(c) || d(a)>=d(c))a=c;
			else b=c;
		}
	}
	if(d(a)>d(b%n))return a;
	else return b%n;
}

p_t readpt(void){
	double x,y;
	scanf("%lf%lf",&x,&y);
	return p_t((long long)(x*10000),(long long)(y*10000));
}

complex<double> cross_l_l(const p_t &p1,const p_t &d1,const p_t &p2,const p_t &d2){
	double d=(double)det(d1,d2);
	return (p1+(complex<double>)d1*det(p2-p1,d2)/d);
}

long long s[200000];


main(){
	vector<p_t> P;
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)P.push_back(readpt());
	long long ar=0;
	for(int i=0;i<n;i++)ar+=det(P[i],P[(i+1)%n]);
	if(ar<0){reverse(P.begin(),P.end());ar=-ar;}

	//for(int i=0;i<n;i++)cout << P[i] << endl;

	s[0]=0;
	for(int i=1;i<=3*n;i++)s[i]=s[i-1]+det(P[(i-1)%n],P[i%n]);
	int q;
	scanf("%d",&q);
	//printf("%d queries\n",q);
	for(int piyo=0;piyo<q;piyo++){
		p_t p1,p2;
		p1=readpt();
		p2=readpt();
		p_t v=(p2-p1)*p_t(0,1);
		
		//for(int i=0;i<n;i++)printf("%lf ",d(i));puts("");
		
		long long dp1=dot(p1,v);
		
		int a=convex_extreme_id(P,v),b=convex_extreme_id(P,-v);
		if((d(a)-dp1)>=0 && (d(b)-dp1)>=0)printf("%.6f\n",0.0);
		else if((d(a)-dp1)<=0 && (d(b)-dp1)<=0)printf("%.6f\n",0.0);
		else if((d(a)-dp1)==0 && (((d(a+1)-dp1)<0 || (d(a+n-1)-dp1)<0)))printf("%.6f\n",0.0);
		else if((d(b)-dp1)<=0 && (((d(b+1)-dp1)<0 || (d(b+n-1)-dp1)<0)))printf("%.6f\n",0.0);
		else{
			if(a>b){swap(a,b);v=-v;dp1=-dp1;}
			
			//printf("%d,%d\n",a,b);
			
			//for(int i=0;i<n;i++)printf("%f ",d(i)-dp1);puts("");
			
			int lb1=a,ub1=b;
			while(ub1-lb1>1){
				int mid=(lb1+ub1)/2;
				if((d(mid%n)-dp1)>=0)lb1=mid;
				else ub1=mid;
			}
			int lb2=b,ub2=a+n;
			while(ub2-lb2>1){
				int mid=(lb2+ub2)/2;
				if((d(mid%n)-dp1)<=0)lb2=mid;
				else ub2=mid;
			}
			
			//printf("%d-%d %d-%d\n",lb1,ub1,lb2,ub2);
			
			complex<double> m1=cross_l_l(P[lb1%n],P[ub1%n]-P[lb1%n],p1,p2-p1);
			complex<double> m2=cross_l_l(P[lb2%n],P[ub2%n]-P[lb2%n],p1,p2-p1);
			
			double ans=det(m1,P[ub1%n])/2-s[ub1]+s[lb2]+det(P[lb2%n],m2)/2+det(m2,m1)/2;
			printf("%.6f\n",(long)max((long long)0.0,min(ar-ans,ans))/1e8);
		}
	}
}