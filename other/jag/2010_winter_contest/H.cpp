#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

int perm[1000][1000];

main(){
	int n;
	int d;
	int i,j,k,l;
	scanf("%d",&n);
	scanf("%d",&d);
	for(i=0;i<d-1;i++){
		for(j=0;j<n;j++){
			scanf("%d",&perm[i][j]);
			perm[i][j]--;
		}
	}
	bool ok=true;
	for(k=0;k<=n/2;k++){
		for(l=0;l<=n/2;l++){
			int vec[200];
			for(i=0;i<n;i++)vec[i]=1;
			for(i=0;i<k;i++)vec[i]=0;
			for(i=0;i<l;i++)vec[n/2+i]=0;
			
			for(i=d-2;i>=0;i--){
				int newvec[200];
				for(j=0;j<n;j++)newvec[j]=vec[perm[i][j]];
				sort(newvec,newvec+n/2);
				sort(newvec+n/2,newvec+n);
				memcpy(vec,newvec,n*sizeof(int));
			}
			for(i=0;i<n-1;i++)if(vec[i]==1 && vec[i+1]==0)ok=false;
		}
	}
	if(ok)puts("Yes");
	else puts("No");
}