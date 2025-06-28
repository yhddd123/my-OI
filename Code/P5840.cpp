// Problem: P5840 [COCI 2015] Divljak
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5840
// Memory Limit: 768 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-04-08 18:33:35
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=2000010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
char s[maxn];
int to[maxn][26],idx,fail[maxn];
int ed[maxn];
void build(){
	queue<int> q;
	for(int i=0;i<26;i++)if(to[0][i])q.push(to[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(to[u][i]){
				fail[to[u][i]]=to[fail[u]][i];
				q.push(to[u][i]);
			}
			else to[u][i]=to[fail[u]][i];
		}
	}
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],tim,st[21][maxn],siz[maxn];
void dfs(int u){
	st[0][dfn[u]=++tim]=fail[u],siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);siz[u]+=siz[v];
	}
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
	if(u==v)return u;
	u=dfn[u],v=dfn[v];
	if(u>v)swap(u,v);u++;
	int k=__lg(v-u+1);
	return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=tim)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
int que(int l,int r){return que(r)-que(l-1);}
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);int m=strlen(s+1);
		for(int j=1,nd=0;j<=m;j++){
			if(!to[nd][s[j]-'a'])to[nd][s[j]-'a']=++idx;
			nd=to[nd][s[j]-'a'];
			ed[i]=nd;
		}
	}
	build();
	for(int i=1;i<=idx;i++)add(fail[i],i);
	dfs(0);
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<=tim;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	q=read();
	while(q--){
		int op=read();
		if(op==1){
			scanf("%s",s+1);int m=strlen(s+1);
			for(int i=1,nd=0;i<=m;i++){
				nd=to[nd][s[i]-'a'];
				a[i]=nd;
			}
			sort(a+1,a+m+1,[&](int u,int v){return dfn[u]<dfn[v];});
			for(int i=1;i<=m;i++){
				upd(dfn[a[i]],1);
				upd(dfn[lca(a[i-1],a[i])],-1);
				// cout<<dfn[a[i]]<<" "<<dfn[lca(a[i-1],a[i])]<<"\n";
			}
		}
		else{
			int x=read();
			printf("%d\n",que(dfn[ed[x]],dfn[ed[x]]+siz[ed[x]]-1));
			// cout<<dfn[ed[x]]<<" "<<siz[ed[x]]<<"\n";
		}
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