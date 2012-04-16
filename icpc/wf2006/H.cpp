#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
#define M 70
using namespace std;

vector<int> kami[M][M];
vector<int> tatec[M],yokoc[M];
vector<int> newkami[M][M];
vector<int> newtatec[M],newyokoc[M];
int tatedir,yokodir;

int tate,yoko;

void rot(){
  for(int i=1;i<tate+1-i;i++)swap(tatec[i],tatec[tate+1-i]);
  for(int j=1;j<yoko+1-j;j++)swap(yokoc[j],yokoc[yoko+1-j]);
  for(int i=0;i<=tate;i++)for(int j=0;j<=yoko;j++){
      if(make_pair(i,j)<make_pair(tate-i,yoko-j)){
	swap(kami[i][j],kami[tate-i][yoko-j]);
      }
    }
  tatedir*=-1;
  yokodir*=-1;
}

void foldd(int cnum){
  int foldpos;
  for(int i=1;i<=tate;i++){
    bool found=false;
    for(int p=0;p<tatec[i].size();p++){
      if(tatec[i][p]==cnum)found=true;
    }
    if(found){foldpos=i;break;}
  }
  for(int i=0;i<=tate;i++)for(int j=0;j<=yoko;j++)newkami[i][j].clear();
  for(int i=1;i<=tate;i++)newtatec[i].clear();
  for(int i=0;i<=tate;i++){
    for(int j=0;j<=yoko;j++){
      int ni,nj;
      if(i<foldpos)ni=foldpos-1-i; else ni=i-foldpos;
      nj=j;
      if(i<foldpos)reverse(kami[i][j].begin(),kami[i][j].end());
      for(int p=0;p<kami[i][j].size();p++){
	newkami[ni][nj].push_back(kami[i][j][p]);
	if(kami[i][j][p]==0 && i<foldpos)tatedir*=-1;
      }
    }
  }
  for(int i=1;i<foldpos;i++){
    for(int p=0;p<tatec[i].size();p++)newtatec[foldpos-i].push_back(tatec[i][p]);
  }
  for(int i=foldpos+1;i<=tate;i++){
    for(int p=0;p<tatec[i].size();p++)newtatec[i-foldpos].push_back(tatec[i][p]);
  }
  for(int i=0;i<=tate;i++)for(int j=0;j<=yoko;j++)kami[i][j]=newkami[i][j];
  for(int i=1;i<=tate;i++)tatec[i]=newtatec[i];
}

void foldr(int cnum){
  int foldpos;
  //printf("foldr %d\n",cnum);
  for(int j=1;j<=yoko;j++){
    bool found=false;
    for(int p=0;p<yokoc[j].size();p++){
      if(yokoc[j][p]==cnum)found=true;
      //printf("crease #%d at %d\n",yokoc[j][p],j);
    }
    if(found){foldpos=j;break;}
  }
  //printf("foldpos=%d\n",foldpos);
  for(int i=0;i<=tate;i++)for(int j=0;j<=yoko;j++)newkami[i][j].clear();
  for(int j=1;j<=yoko;j++)newyokoc[j].clear();
  for(int i=0;i<=tate;i++){
    for(int j=0;j<=yoko;j++){
      int ni,nj;
      ni=i;
      if(j<foldpos)nj=foldpos-1-j; else nj=j-foldpos;
      if(j<foldpos)reverse(kami[i][j].begin(),kami[i][j].end());
      for(int p=0;p<kami[i][j].size();p++){
	newkami[ni][nj].push_back(kami[i][j][p]);
	if(kami[i][j][p]==0 && j<foldpos)yokodir*=-1;
      }
    }
  }
  for(int j=1;j<foldpos;j++){
    for(int p=0;p<yokoc[j].size();p++)newyokoc[foldpos-j].push_back(yokoc[j][p]);
  }
  for(int j=foldpos+1;j<=yoko;j++){
    for(int p=0;p<yokoc[j].size();p++)newyokoc[j-foldpos].push_back(yokoc[j][p]);
  }
  for(int i=0;i<=tate;i++)for(int j=0;j<=yoko;j++)kami[i][j]=newkami[i][j];
  for(int j=1;j<=yoko;j++)yokoc[j]=newyokoc[j];
}

int calc(vector<pair<int,int> > v){
  //for(int i=0;i<v.size();i++)printf("(%d,%d) ",v[i].first,v[i].second);puts("");
  vector<pair<int,int> > ev;
  for(int i=0;i<v.size();i++){
    ev.push_back(make_pair(v[i].first,1));
    ev.push_back(make_pair(v[i].second,-1));
  }
  sort(ev.begin(),ev.end());
  int ret=0;
  int maisu=0;
  for(int i=0;i<ev.size();i++){
    maisu+=ev[i].second;
    if(maisu==0)ret++;
  }
  return ret-1;
}


main(){
  for(int casenum=1;;casenum++){
    int numcr;
    scanf("%d%d",&tate,&numcr);
    yoko=tate;
    if(tate==0 && yoko==0)return 0;
    
    for(int i=1;i<=tate;i++)tatec[i]=vector<int>(1,i);
    for(int j=1;j<=yoko;j++)yokoc[j]=vector<int>(1,j);
    for(int i=0;i<=tate;i++)for(int j=0;j<=yoko;j++)kami[i][j]=vector<int>(1,i*M+j);
    tatedir=1;yokodir=1;
    for(int fuga=0;fuga<numcr;fuga++){
      int cnum;
      char buf[10];
      scanf("%d %s",&cnum,buf);
      if(buf[0]=='L' || buf[0]=='U')rot();
      /*
      printf("rotated(if necessary)\n");
      for(int i=0;i<=tate;i++){
	for(int j=0;j<=yoko;j++){
	  printf("%d %d: ",i,j);
	  for(int p=0;p<kami[i][j].size();p++)printf("%d ",kami[i][j][p]);
	  puts("");
	}
      }
      */
      if(buf[0]=='U' || buf[0]=='D')foldd(cnum);
      if(buf[0]=='L' || buf[0]=='R')foldr(cnum);
      /*
      printf("folded\n");
      for(int i=0;i<=tate;i++){
	for(int j=0;j<=yoko;j++){
	  printf("%d %d: ",i,j);
	  for(int p=0;p<kami[i][j].size();p++)printf("%d ",kami[i][j][p]);
	  puts("");
	}
      }
      */
      if(buf[0]=='L' || buf[0]=='U')rot();
      /*
      printf("rotated back(if necessary)\n");
      */
      /*
      for(int i=0;i<=tate;i++){
	for(int j=0;j<=yoko;j++){
	  printf("%d %d: ",i,j);
	  for(int p=0;p<kami[i][j].size();p++)printf("%d ",kami[i][j][p]);
	  puts("");
	}
      }
      */
    }
    int zpos[M*M];
    for(int i=0;i<=tate;i++){
      for(int j=0;j<=yoko;j++){
	if(!kami[i][j].empty()){
	  for(int k=0;k<kami[i][j].size();k++)zpos[kami[i][j][k]]=k;
	}
      }
    }
    //for(int i=0;i<=tate;i++)for(int j=0;j<=yoko;j++)printf("%d: zpos=%d\n",i*M+j,zpos[i*M+j]);
    vector<pair<int,int> > ar,al,au,ad;
    for(int i=0;i<=tate;i++){
      for(int j=0;j<=yoko;j++){
	int tatef=tatedir*(i%2?-1:1);
	int yokof=yokodir*(j%2?-1:1);
	if(i<tate){
	  int jibun=zpos[i*M+j];
	  int aite=zpos[(i+1)*M+j];
	  if(jibun>aite)swap(jibun,aite);
	  if(tatef==1)ad.push_back(make_pair(2*jibun,2*aite+1));
	  else au.push_back(make_pair(2*jibun,2*aite+1));
	}
	if(j<yoko){
	  int jibun=zpos[i*M+j];
	  int aite=zpos[i*M+(j+1)];
	  if(jibun>aite)swap(jibun,aite);
	  if(yokof==1)ar.push_back(make_pair(2*jibun,2*aite+1));
	  else al.push_back(make_pair(2*jibun,2*aite+1));
	}
      }
    }
    for(int j=0;j<=yoko;j++){
      int jibun;
      jibun=zpos[0*M+j];
      if(tatedir==1)au.push_back(make_pair(2*jibun,2*jibun+1));
      else ad.push_back(make_pair(2*jibun,2*jibun+1));
      jibun=zpos[tate*M+j];
      if(tatedir*(tate%2?-1:1)==1)ad.push_back(make_pair(2*jibun,2*jibun+1));
      else au.push_back(make_pair(2*jibun,2*jibun+1));
    }
    for(int i=0;i<=tate;i++){
      int jibun;
      jibun=zpos[i*M+0];
      if(yokodir==1)al.push_back(make_pair(2*jibun,2*jibun+1));
      else ar.push_back(make_pair(2*jibun,2*jibun+1));
      jibun=zpos[i*M+yoko];
      if(yokodir*(yoko%2?-1:1)==1)ar.push_back(make_pair(2*jibun,2*jibun+1));
      else al.push_back(make_pair(2*jibun,2*jibun+1));
    }
    calc(ad);
    calc(au);
    calc(ar);
    calc(al);
    printf("Case %d: %d pockets\n",casenum,calc(ad)+calc(au)+calc(ar)+calc(al));
  }
}
