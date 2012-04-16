#include <stdio.h>

main(){
	int q;
	scanf("%d ",&q);
	long long sa=0;
	for(int i=0;i<q;i++){
		int p;
		char c;
		int n;
		scanf("%d %c %d ",&p,&c,&n);
		if(c=='(')sa+=n; else sa-=n;
		if(sa==0)puts("Yes"); else puts("No");
	}
}