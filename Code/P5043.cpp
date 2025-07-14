// Problem: P5043 【模板】树同构（[BJOI2015]树的同构）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5043
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=110;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int siz[maxn],w[maxn],mn;
void dfs(int u,int fa){
	siz[u]=1;w[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa){
			dfs(v,u);
			siz[u]+=siz[v];
			w[u]=max(w[u],siz[v]);
		}
	}
	w[u]=max(w[u],n-siz[u]);
	mn=min(mn,w[u]);
}
#define ull unsigned long long
ull mp[maxn],val;
ull g(ull x){
	x^=val;
	x^=x<<13;x^=x>>7;x^=x<<11;
	x^=val;
	return x;
}
ull dfs2(int u,int fa){
	ull f=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		f+=g(dfs2(v,u));
	}
	return f;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	srand(time(0));val=rand();
	T=read();
	for(int t=1;t<=T;t++){
		for(int i=1;i<=n;i++)head[i]=0;
		tot=0;mn=inf;mp[t]=0;
		n=read();
		for(int i=1;i<=n;i++){
			int u=read();
			if(!u)continue;
			add(i,u);add(u,i);
		}
		dfs(1,0);
		for(int i=1;i<=n;i++){
			if(w[i]==mn){
				mp[t]=max(mp[t],dfs2(i,i));
//				cout<<i<<" ";
			}
		}
		for(int i=1;i<=t;i++){
			if(mp[t]==mp[i]){
				printf("%lld\n",i);
				break;
			}
		}
//		cout<<mp[t]<<"\n";
	}
}