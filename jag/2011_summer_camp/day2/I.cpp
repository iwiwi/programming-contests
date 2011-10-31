#include<stdio.h>

bool line[11000];
int pos[300];

int main(void){
	int n,k,t,u,v,l;
	scanf("%d %d %d %d %d %d",&n,&k,&t,&u,&v,&l);
	for(int i=0;i<n;i++){
		int a;
		scanf("%d",&a);
		pos[i]=a;
		line[a]=true;
	}
	int num=0,left=0,ans=0;
	for(int i=0;i<l;i++){
		if(line[i]){
			if(num==k){
				left=v*t;
			}else{
				num++;
			}
		}
		if(left==0 && num>0){
			num--;
			left=v*t;
		}
		if(left>0){
			left--;
			ans++;
		}
	}
	printf("%.10lf\n",(double)ans/v+(double)(l-ans)/u);
	return 0;
}

