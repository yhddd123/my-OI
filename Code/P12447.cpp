// Problem: P12447 [COTS 2025] 砍树 / Stablo
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12447
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-05-28 19:31:34
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=512;
const int inf=1e9;
bool mbe;

int n,id[maxn];
vector<pii> ans;
int ask(int u,int v,int w){
	printf("? %d %d %d\n",u,v,w);fflush(stdout);
	return read();
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){ans.pb({u,v});e[++tot]={head[u],v};head[u]=tot;}
int siz[maxn],son[maxn],to[maxn];
int dfn[maxn],rnk[maxn],idx,dw[maxn];
void dfs(int u){
	siz[u]=1;son[u]=to[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==son[u])continue;
		to[u]=v;
	}
}
void dfs1(int u){
	rnk[dfn[u]=++idx]=u;dw[u]=u;
	if(!son[u])return ;
	dfs1(son[u]);dw[u]=dw[son[u]];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==son[u])continue;
		dfs1(v);
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)id[i]=i;
	stable_sort(id+2,id+n+1,[&](int u,int v){return ask(1,u,v)==1;});
	// for(int i=2;i<=n;i++)cout<<id[i]<<" ";cout<<"\n";
	for(int i=2;i<=n;i++){
		idx=0;dfs(1),dfs1(1);
		int u=1;
		while(son[u]){
			int l=dfn[u],r=dfn[dw[u]]-1,res=dfn[dw[u]];
			while(l<=r){
				int mid=l+r>>1;
				if(ask(id[i],rnk[mid],rnk[mid+1])==1)res=mid,r=mid-1;
				else l=mid+1;
			}
			u=rnk[res];
			if(to[u]){
				if(u==1&&ask(id[i],1,to[1])==1){
					for(int ii=head[1];ii;ii=e[ii].nxt){
						int v=e[ii].to;if(v==son[1]||v==to[1])continue;
						u=v;break;
					}
					if(u==1)break;
				}
				else u=to[u];
			}
			else break;
		}
		add(u,id[i]);
		// cout<<u<<" "<<id[i]<<"\n";
	}
	printf("!\n");
	for(auto[u,v]:ans)printf("%d %d\n",u,v);
	fflush(stdout);
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