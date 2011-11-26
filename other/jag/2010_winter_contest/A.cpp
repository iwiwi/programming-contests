#include <stdio.h>

double p,q,r,s,t,u,v,w,x;
double d,e,f;


main(){
	int i;
	int n;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		double px,py;
		scanf("%lf%lf",&px,&py);
		p+=px*px;
		q+=px*py;
		r+=px;
		s+=px*py;
		t+=py*py;
		u+=py;
		v+=px;
		w+=py;
		x+=1;
		d-=px*(px*px+py*py);
		e-=py*(px*px+py*py);
		f-=(px*px+py*py);
	}
	double det=p*t*x+q*u*v+r*s*w-p*u*w-q*s*x-r*t*v;
	double a,b,c;
	a=((t*x-u*w)*d+(r*w-q*x)*e+(q*u-r*t)*f)/det;
	b=((u*v-s*x)*d+(p*x-r*v)*e+(r*s-p*u)*f)/det;
	c=((s*w-t*v)*d+(q*v-p*w)*e+(p*t-q*s)*f)/det;
	printf("%.3f %.3f %.3f\n",a,b,c);
}