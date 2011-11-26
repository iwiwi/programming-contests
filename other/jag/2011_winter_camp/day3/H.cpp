#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

bool mat[1100][1100];
vector<int> graph[1100];
int n,m;

int cnt;
vector<int> pos;
bool check[1100];

void saiki(int x){
	if(check[x])return;
	check[x]=true;
	cnt++;
	pos.push_back(x);
	for(int i=0;i<graph[x].size();i++){
		saiki(graph[x][i]);
	}
	return;
}

int main(void){
	int i,j,k;
	scanf("%d ",&n);
	for(i=0;i<n;i++){
		char ch[1100];
		scanf("%s",ch);
		for(j=0;j<n;j++){
			if(ch[j]=='Y'){
				mat[i][j]=true;
				graph[i].push_back(j);
				m++;
			}else{
				mat[i][j]=false;
			}
		}
	}
	m/=2;
	int even=0,odd=0,left=0;
	for(i=0;i<n;i++){
		if(check[i])continue;
		cnt=0;
		pos.clear();
		saiki(i);
		if(cnt%2==0)even++;
		else odd++;
		for(j=0;j<pos.size();j++){
			for(k=j+1;k<pos.size();k++){
				if(!mat[pos[j]][pos[k]])left++;
			}
		}
	}
	//printf("n=%d m=%d even=%d odd=%d left=%d\n",n,m,even,odd,left);
	bool tarowin;
	if((n*(n-1)/2-m)%2==0){
		if(odd==0 || odd%2==1)tarowin=false;
		else{
			if(even>=2)tarowin=false;
			else{
				if(odd==2)tarowin=true;
				else{
					if(left%2==0)tarowin=false;
					else{
						if(odd==4)tarowin=false;
						else tarowin=false;
					}
				}
			}
		}
	}else{
		if(odd==0 || odd%2==1)tarowin=true;
		else{
			if(even>=1)tarowin=true;
			else{
				if(odd==2)tarowin=false;
				else{
					if(left%2==1)tarowin=true;
					else{
						if(odd==4)tarowin=true;
						else tarowin=true;
					}
				}
			}
		}
	}
	if(tarowin)puts("Taro");
	else puts("Hanako");
	return 0;
}
