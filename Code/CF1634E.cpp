// Problem: CF1634E Fair Share
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1634E
// Memory Limit: 250 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2025-03-13 12:31:28
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=2e9;
bool mbe;

int n,idx;
vector<int> e[maxn];
void add(int u,int v){e[u].pb(v),e[v].pb(u);}
map<int,int> mp;
int col[maxn];
void dfs(int u){
	for(int v:e[u]){
		if(col[v])continue;
		col[v]=3-col[u];dfs(v);
	}
}
bool bk[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		int m=read(),lst=0;
		while(m--){
			int x=read(),id=++idx;
			if(lst)add(lst,idx),add(idx,lst),lst=0;
			else lst=idx;
			if(mp[x])add(mp[x],idx),add(idx,mp[x]),mp[x]=0;
			else mp[x]=idx;
		}
		bk[idx]=1;
	}
	for(auto[x,id]:mp)if(id){puts("NO");return ;}
	for(int i=1;i<=idx;i++)if(!col[i])col[i]=1,dfs(i);
	puts("YES");
	for(int i=1;i<=idx;i++){
		putchar(col[i]==1?'R':'L');
		if(bk[i])puts("");
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}