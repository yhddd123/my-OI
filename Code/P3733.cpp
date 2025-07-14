// Problem: P3733 [HAOI2017] 八纵八横
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3733
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-04-25 19:40:58
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q;
struct bas{
	bitset<maxn> p[maxn];
	void insert(bitset<maxn> f){
		for(int i=1000;~i;i--)if(f[i]){
			if(!p[i][i]){p[i]=f;return ;}
			f^=p[i];
		}
	}
	bitset<maxn> query(){
		bitset<maxn> f;
		for(int i=1000;~i;i--)if(p[i][i]){
			if(!f[i])f^=p[i];
		}
		return f;
	}
}b[20];
char s[maxn];
bitset<maxn> in(){
	bitset<maxn> f;
	scanf("%s",s+1);int m=strlen(s+1);
	for(int i=m,j=0;i;i--,j++)f[j]=s[i]-'0';
	return f;
}
void print(bitset<maxn> f){
	bool fl=0;
	for(int i=1000;~i;i--)if(f[i]||fl)printf("%d",(int)f[i]),fl=1;printf("\n");
	return ;
}
bitset<maxn> f[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
	bitset<maxn> w;
}e[maxn];
void add(int u,int v,bitset<maxn> w){e[++tot]={head[u],v,w};head[u]=tot;}
bool vis[maxn];
void dfs(int u,int fa){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		if(vis[v])b[0].insert(f[u]^f[v]^e[i].w);
		else f[v]=f[u]^e[i].w,dfs(v,u);
	}
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct node{
	int u,v;
	bitset<maxn> f;
}que[maxn];int tim[maxn],idx;
vector<node> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,node w){
	// cout<<ql<<" "<<qr<<" "<<w.u<<" "<<w.v<<"\n";
	if(l>=ql&&r<=qr){tree[nd].push_back(w);return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
bitset<maxn> ans[maxn];
void sovle(int nd,int l,int r){
	for(node i:tree[nd])b[(int)log2(nd)].insert(f[i.u]^f[i.v]^i.f);
	if(l==r){
		print(b[(int)log2(nd)].query());
		return ;
	}
	b[(int)log2(ls)]=b[(int)log2(nd)],sovle(ls,l,mid);
	b[(int)log2(rs)]=b[(int)log2(nd)],sovle(rs,mid+1,r);
}
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();bitset<maxn> w=in();
		// cout<<w<<"\n";
		add(u,v,w),add(v,u,w);
	}
	dfs(1,0);
	print(b[0].query());
	for(int i=1;i<=q;i++){
		scanf("%s",s+1);
		if(s[2]=='d'){
			int u=read(),v=read();bitset<maxn> w=in();
			que[++idx]={u,v,w};tim[idx]=i;
		}
		if(s[2]=='h'){
			int id=read();bitset<maxn> w=in();
			updata(1,1,q,tim[id],i-1,que[id]);
			que[id].f=w;tim[id]=i;
		}
		if(s[2]=='a'){
			int id=read();
			updata(1,1,q,tim[id],i-1,que[id]);
			tim[id]=0;
		}
	}
	for(int i=1;i<=idx;i++)if(tim[i])updata(1,1,q,tim[i],q,que[i]);
	if(q)sovle(1,1,q);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}