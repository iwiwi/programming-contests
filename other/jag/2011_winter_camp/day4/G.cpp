#include <stdio.h>
#include <complex>
#include <vector>
#define EPS 1e-9
using namespace std;

typedef complex<double> point;

point readpt(void){
	double x,y;
	scanf("%lf%lf",&x,&y);
	return point(x,y);
}

double dot(point p,point q){return real(conj(p)*q);}
double det(point p,point q){return imag(conj(p)*q);}

point cross_l_l(const point &p1,const point &d1,const point &p2,const point &d2){
	double d=det(d1,d2);
	return p1+(d1*det(p2-p1,d2))/d;
}

vector<point> convex_cut(vector<point> &po,point p,point q){
	vector<point> res;
	for(int i=0;i<po.size();i++){
		point a=po[i],b=po[(i+1)%po.size()];
		double pqa=det(q-p,a-p),pqb=det(q-p,b-p);
		if(pqa>-EPS)res.push_back(po[i]);
		if(pqa*pqb<-EPS)res.push_back(cross_l_l(a,b-a,p,q-p));
	}
	return res;
}

main(){
	int m,n;
	scanf("%d%d",&m,&n);
	vector<point> p;
	for(int i=0;i<m;i++){
		p.push_back(readpt());
	}
	vector<point> shel;
	for(int i=0;i<n;i++){
		shel.push_back(readpt());
	}
	double ans=0,ar=0;
	for(int i=0;i<n;i++){
		vector<point> tmp=p;
		for(int j=0;j<n;j++){
			if(i==j)continue;
			point q1=shel[i]+(shel[j]-shel[i])*point(0.5,0.0);
			point q2=shel[i]+(shel[j]-shel[i])*point(0.5,1);
			tmp=convex_cut(tmp,q1,q2);
		}
		for(int k=0;k<tmp.size();k++){
			point a=tmp[k]-shel[i],b=tmp[(k+1)%tmp.size()]-shel[i];
			ans+=(dot(a,a)+dot(a,b)+dot(b,b))*det(a,b)/12.0;
		}
	}
	for(int i=0;i<m;i++){
		ar+=det(p[i],p[(i+1)%m])/2.0;
	}
	printf("%.10f\n",ans/ar);
}