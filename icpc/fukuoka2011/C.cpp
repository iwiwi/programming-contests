#include<stdio.h>
#include<ctype.h>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

char ch[1000];

int n;
vector<char> dic;
string word[120];
vector<string> st;

vector<vector<char> > ansdic;

string conv(const string &st){
  string ans=st;
  for(int i=0;i<(int)ans.size();i++){
    ans[i]=dic[ans[i]];
  }
  return ans;
}


bool check(int pos, const vector<char> &ndic){
  for(int i=pos;i<(int)st.size();i++){
    bool aru=false;
    for(int j=0;j<n;j++){
      if(st[i].size()!=word[j].size())continue;
      bool ok=true;
      for(int k=0;k<(int)st[i].size();k++){
	int a=ndic[st[i][k]];
	if(a==-1){
	  if(ndic[word[j][k]]!=-1){ok=false;break;}
	}else{
	  if(a!=word[j][k]){ok=false;break;}
	}
      }
      if(ok){aru=true;break;}
    }
    if(!aru)return false;
  }
  return true;
}

void saiki(int pos){
  if(ansdic.size()>=2)return;
  if(pos==(int)st.size()){
    ansdic.push_back(dic);
    return;
  }
  
  vector<char> ndic,olddic;
  olddic=dic;
  for(int i=0;i<n;i++){
    if(st[pos].size()!=word[i].size())continue;
    ndic=dic;
    bool ok=true;
    for(int j=0;j<(int)st[pos].size();j++){
      int a=ndic[st[pos][j]];
      if(a==-1){
	if(ndic[word[i][j]]!=-1){ok=false;break;}
	ndic[st[pos][j]]=word[i][j];
	ndic[word[i][j]]=st[pos][j];
      }else{
	if(a!=word[i][j]){ok=false;break;}
      }
    }
    if(!ok)continue;
    if(check(pos+1, ndic)){
      dic=ndic;
      saiki(pos+1);
      dic=olddic;
    }
  }
  return;
}

int main(void){
  for(;;){
    scanf("%d",&n);
    if(n==0)break;
    for(int i=0;i<n;i++){
      scanf("%s",ch);
      word[i]=string(ch);
    }
    sort(word,word+n);
    n=unique(word,word+n)-word;
    dic.clear();
    dic.resize(280);
    for(int i=0;i<256;i++)dic[i]=-1;
    ansdic.clear();
    st.clear();
    while(1){
      scanf("%s",ch);
      string s=string(ch);
      bool end=false;
      if(s[s.size()-1]=='.'){
	s.erase(s.end()-1);
	end=true;
      }
      st.push_back(s);
      if(end)break;
    }
    saiki(0);
    if(ansdic.size()>=2){
      printf("-.\n");
    }else{
      dic=ansdic[0];
      for(int i=0;i<(int)st.size();i++){
	string s=conv(st[i]);
	printf("%s",s.c_str());
	if(i==(int)st.size()-1)printf(".\n");
	else printf(" ");
      }
    }
  }
  return 0;
}
