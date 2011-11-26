#include <stdio.h>
#include <complex>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

#define EPS 1e-9
#define INF 1e9

typedef complex<double> point;

point readpt(){
	double x,y;
	scanf("%lf%lf",&x,&y);
	return point(x,y);
}

double dot(point p,point q){return real(conj(p)*q);}
double det(point p,point q){return imag(conj(p)*q);}

int ccw(point a,point b,point c){
	b-=a;c-=a;
	if(det(b,c)>EPS)return 1;
	if(det(b,c)<-EPS)return -1;
	if(dot(b,c)<-EPS)return 2;
	if(norm(b)<norm(c)-EPS)return -2;
	return 0;
}

bool on_ls(point p,point p1,point p2){
	return abs(p1-p)+abs(p2-p)-abs(p1-p2)<EPS;
}

bool intersect(point p1,point p2,point p3,point p4){
	return ccw(p1,p2,p3)*ccw(p1,p2,p4)<=0
		&& ccw(p3,p4,p1)*ccw(p3,p4,p2)<=0;
}

bool intersect_polygon(point a,point b,const vector<point> &ps,int n){
	int ai=-1,bi=-1;
	for(int i=0;i<n;i++){
		if(abs(ps[i]-a)<EPS)ai=i;
		if(abs(ps[i]-b)<EPS)bi=i;
	}
	for(int i=0;i<n;i++){
		int j=(i+1)%n;
		if(i==ai || j==ai || i==bi || j==bi)continue;
		const point &p=ps[i],&q=ps[j];
		if(on_ls(a,p,q)){
			if(ccw(p,q,b)>0)return true;
		}else if(on_ls(b,p,q)){
			if(ccw(p,q,a)>0)return true;
		}else if(intersect(a,b,p,q))return true;
	}
	for(int t=0;t<2;t++){
		if(ai!=-1){
			const point &p=ps[(ai-1+n)%n];
			const point &q=ps[(ai+1)%n];
			if(ccw(p,a,q)>0){
				if(ccw(a,q,b)>0 && ccw(a,b,p)>0)return true;
			}else{
				if(ccw(a,p,b)<0 || ccw(a,b,q)<0)return true;
			}
		}
		swap(a,b);
		swap(ai,bi);
	}
	return false;
}

double dist[200][200];

main(){
	for(int hoge=1;;hoge++){
		int n;
		double vl,vp;
		vector<point> pt;
		scanf("%d",&n);
		if(n==0)return 0;
		for(int i=0;i<n;i++)pt.push_back(readpt());
		point s=readpt();
		scanf("%lf%lf",&vl,&vp);
		//puts("Hello!!!!");
		//return 0;
		//for(int i=0;i<n;i++)cout << pt[i] << endl;
		
		pt.push_back(pt[0]);
		vector<point> vertex=pt;
		vertex[n]=s;
		
		
		//for(int i=0;i<=n;i++)cout << vertex[i] << endl;
		
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++){
				if(i==j)dist[i][j]=0;
				else{
					if(intersect_polygon(vertex[i],vertex[j],pt,n))dist[i][j]=INF;
					else dist[i][j]=abs(vertex[i]-vertex[j]);
				}
			}
		}
		/*
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++)printf("%lf ",dist[i][j]);
			puts("");
		}
		puts("");
		*/
		for(int k=0;k<=n;k++)for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
		/*
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++)printf("%lf ",dist[i][j]);
			puts("");
		}
		*/
		double shu=0;
		for(int i=0;i<n;i++)shu+=abs(pt[i+1]-pt[i]);
		double isshutime=shu/vl;
		
		double ub=INF,lb=0;
		for(int z=0;z<100;z++){
			//printf("z=%d %lf-%lf\n",z,lb,ub);
			double mid=(ub+lb)/2;
			double amari;
			double ipart;
			amari=modf(mid/isshutime,&ipart)*shu;
			double now=0;
			point pos;
			for(int i=0;i<n;i++){
				double next=now+abs(pt[i+1]-pt[i]);
				if(next>amari-EPS){
					pos=pt[i]+(pt[i+1]-pt[i])*(amari-now)/(next-now);
					break;
				}
				now=next;
			}
			//cout << mid <<" " << amari << pos << endl;
			double mindist=INF;
			for(int i=0;i<=n;i++){
				if(intersect_polygon(vertex[i],pos,pt,n))continue;
				mindist=min(mindist,dist[n][i]+abs(vertex[i]-pos));
			}
			if(mindist/vp<mid)ub=mid;
			else lb=mid;
		}
		double ans=(ub+lb)/2+EPS;
		int byo=(int)(ans*60+0.5);
		printf("Case %d: Time = %d:%02d\n",hoge,byo/60,byo%60);
	}
}