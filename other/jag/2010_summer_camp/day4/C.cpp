#include <stdio.h>
#include <algorithm>
#include <map>
#include <math.h>
#include <vector>
#include <set>
#include <string.h>
using namespace std;

double px[11000],py[11000];

vector<int> adj[11000];

int chk[11000];
/*
bool saiki(int p,int d,int f1,int f2){
	chk[p]=1;
	if(p==d)return true;
	for(int i=0;i<adj[p].size();i++){
		int q=adj[p][i];
		if(p==f1 && q==f2)continue;
		if(q==f1 && p==f2)continue;
		if(chk[q]==0){
			if(saiki(q,d,f1,f2))return true;
		}
	}
	return false;
}
*/

int par[11000];
void init(int n){
	for(int i=0;i<n;i++)par[i]=i;
}

int root(int x){
	return par[x]==x?x:par[x]=root(par[x]);
}

void uni(int x,int y){
	par[root(x)]=root(y);
}

bool find(int x,int y){
	return root(x)==root(y);
}

main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%lf%lf",&px[i],&py[i]);
	}
	
	vector<pair<double,pair<int,int> > > edg;
	
	for(int i=0;i<m;i++){
		int p,q;
		scanf("%d%d",&p,&q);
		p--;q--;
		adj[p].push_back(q);
		adj[q].push_back(p);
		edg.push_back(make_pair(hypot(px[p]-px[q],py[p]-py[q]),make_pair(p,q)));
	}
	
	sort(edg.begin(),edg.end());
	reverse(edg.begin(),edg.end());
	double ans=0;
	
	init(n);
	for(int k=0;k<edg.size();k++){
		int p=edg[k].second.first,q=edg[k].second.second;
		if(find(p,q)){
			ans+=edg[k].first;
		}else{
			uni(p,q);
		}
		/*
		//printf("%d-%d\n",p,q);
		memset(chk,0,sizeof(chk));
		if(saiki(p,q,p,q)){
			//printf("removed %d-%d\n",p,q);
			for(int i=0;i<adj[p].size();i++)if(adj[p][i]==q){adj[p].erase(adj[p].begin()+i);break;}
			for(int i=0;i<adj[q].size();i++)if(adj[q][i]==p){adj[q].erase(adj[q].begin()+i);break;}
			ans+=edg[k].first;
		}
		*/
	}
	printf("%.12f\n",ans);
	return 0;
}