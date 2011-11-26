#include <stdio.h>
#include <math.h>
#include <complex>
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#define EPS 1e-9
#define LEPS 1e-8
#define INF 1e9
#define M_PI 3.1415926535897932384626433

using namespace std;

typedef long long ll;

typedef complex<ll> point;

point readpt(){
	ll x,y;
	cin >> x >> y;
	return point(x,y);
}

point pt[20000];


main(){
	for(int t=1;;t++){
		int n;
		int theta;
		cin >> n >> theta;
		if(n==0)return 0;
		
		pt[0]=point(0,0);
		for(int i=1;i<=n;i++)pt[i]=readpt();
		
		printf("Case %d: ",t);
		
		if(theta==0){
			puts("Acceptable as proposed");
		}else{
			vector<pair<double,int> > ev;
			for(int i=0;i<n;i++){
				double theta=atan2((double)imag(pt[i+1]-pt[i]),(double)real(pt[i+1]-pt[i]));
				//cout << pt[i+1]-pt[i] << endl;
				//printf("muki:%.2f deg\n",theta/M_PI*180);
				if(theta>=-M_PI/2 && theta<=M_PI/2){
					ev.push_back(make_pair(theta-M_PI/2-EPS,1));
					ev.push_back(make_pair(theta+M_PI/2+EPS,-1));
				}else if(theta<-M_PI/2){
					ev.push_back(make_pair(-M_PI-EPS,1));
					ev.push_back(make_pair(theta+M_PI/2+EPS,-1));
					ev.push_back(make_pair(theta+3*M_PI/2-EPS,1));
					ev.push_back(make_pair(M_PI+EPS,-1));
				}else{
					ev.push_back(make_pair(-M_PI-EPS,1));
					ev.push_back(make_pair(theta-3*M_PI/2+EPS,-1));
					ev.push_back(make_pair(theta-M_PI/2-EPS,1));
					ev.push_back(make_pair(M_PI+EPS,-1));
				}
			}
			sort(ev.begin(),ev.end());
			int cnt=0;
			double l=INF,r=INF;
			for(int i=0;i<ev.size();i++){
				//printf("%.2f deg:%d\n",ev[i].first/M_PI*180,ev[i].second);
				int ncnt=cnt+ev[i].second;
				//printf("%d\n",ncnt);
				if(cnt==n || ncnt==n){
					double th=ev[i].first;
					if(th<=0)l=min(l,-th);
					if(th>=0)r=min(r,th);
				}
				cnt=ncnt;
			}
			if(l<LEPS || r<LEPS){
				puts("Acceptable as proposed");
			}else if(l==INF && r==INF){
				puts("Unacceptable");
			}else if(l<r){
				printf("Acceptable after counterclockwise rotation of %.2f degrees\n",l/M_PI*180);
			}else{
				printf("Acceptable after clockwise rotation of %.2f degrees\n",r/M_PI*180);
			}
		}
		puts("");
	}
}