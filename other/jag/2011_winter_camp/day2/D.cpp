#include <stdio.h>
#include <algorithm>

using namespace std;

int l[2000],r[2000];
int c;

main(){
	for(;;){
		char s;
		int a,b;
		if(scanf("%c %d %d ",&s,&a,&b)!=3)return 0;
		if(s=='+'){
			int ans=0;
			for(int i=0;i<c;i++){
				if(l[i]>=a && r[i]<=b)ans++;
			}
			printf("%d\n",ans);
			l[c]=a;r[c]=b;c++;
		}else{
			for(int i=0;i<c;i++){
				if(l[i]==a && r[i]==b){
					l[i]=l[c-1];
					r[i]=r[c-1];
					c--;
					break;
				}
			}
		}
	}
}