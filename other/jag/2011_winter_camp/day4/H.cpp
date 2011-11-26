#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;

ll a[200][200];

main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			scanf("%lld",&a[i][j]);
		}
	}
	ll s=0;
	for(int i=0;i<n;i++)for(int j=0;j<i;j++)s+=min(a[i][j],a[j][i]);
	printf("%lld\n",s);
}