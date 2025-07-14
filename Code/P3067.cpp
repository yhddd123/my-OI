#include<iostream>
#include<map>
#include<vector>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[21],ans;
map<int,vector<int> > mp;
bool vis[1<<20];
int pw[20];
void dfs(int dep,int sum,int s){
	if(dep>n/2){
		mp[sum].push_back(s);
		return ;
	}
	dfs(dep+1,sum,s);
	dfs(dep+1,sum+a[dep],s+pw[dep-1]);
	dfs(dep+1,sum-a[dep],s+pw[dep-1]);
}
void dfs2(int dep,int sum,int s){
	if(dep>n){
		if(!mp[sum].size())return ;
		int len=mp[sum].size();
		for(int i=0;i<len;++i){
			vis[s|mp[sum][i]]=1;
		}
		return ;
	}
	dfs2(dep+1,sum,s);
	dfs2(dep+1,sum+a[dep],s+pw[dep-1]);
	dfs2(dep+1,sum-a[dep],s+pw[dep-1]);
}
signed main(){
	n=read();pw[0]=1;
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]<<1;
	dfs(1,0,0);
	dfs2(n/2+1,0,0);
	for(int i=1;i<=(1<<n)-1;++i)ans+=vis[i];
	printf("%d\n",ans);
}
