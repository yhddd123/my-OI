// Problem: P3735 [HAOI2017] 字符串
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3735
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-07-16 20:27:29
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=400010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,m;
char s[maxn],t[maxn];
int ans[maxn];
int tree[maxn][94],idx,fail[maxn];
int pos[maxn];
struct ask{
	int id,pos,v,fl;
};
vector<ask> que[maxn];
void insert(char *s,int id){
	int n=strlen(s+1),nd=0;
	for(int i=1;i<=n;i++){
		int c=s[i]-33;
		if(!tree[nd][c])tree[nd][c]=++idx;
		nd=tree[nd][c];
	}
	pos[n+1]=nd=0;
	for(int i=n;i;i--){
		int c=s[i]-33;
		if(!tree[nd][c])tree[nd][c]=++idx;
		pos[i]=nd=tree[nd][c];
	}
	nd=0;
	for(int i=0;i<=n-k;i++){
		que[nd].push_back({id,pos[i+k+1],0,1});
		if(i)que[nd].push_back({id,pos[i+k],0,-1});
		nd=tree[nd][s[i+1]-33];
	}
}
queue<int> q;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
vector<pii> upd[maxn];
void build(){
	for(int i=0;i<94;i++)if(tree[0][i])q.push(tree[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=0;i<94;i++){
			if(tree[u][i])fail[tree[u][i]]=tree[fail[u]][i],q.push(tree[u][i]);
			else tree[u][i]=tree[fail[u]][i];
		}
	}
	for(int i=1;i<=idx;i++)add(fail[i],i);
	int nd=0;pos[n+1]=0;
	for(int i=n;i;i--)pos[i]=nd=tree[nd][s[i]-33];
	nd=0;
	for(int i=0;i<=n-k;i++){
		upd[nd].push_back({pos[i+k+1],pos[i+k]});
		nd=tree[nd][s[i+1]-33];
	}
}
int in[maxn],out[maxn],tim;
void dfs(int u){
	in[u]=++tim;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;dfs(v);
	}
	out[u]=tim;
}
#define lb(x) (x&(-x))
struct bit{
	int tree[maxn];
	void upd(int x){
		while(x<=idx)tree[x]++,x+=lb(x);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	int que(int l,int r){return que(r)-que(l-1);}
}T1,T2;
void dfs1(int u){
	for(ask &p:que[u]){
		if(p.fl==1)p.v=T1.que(in[p.pos],out[p.pos]);
		else p.v=T2.que(in[p.pos],out[p.pos]);
	}
	for(pii p:upd[u])T1.upd(in[p.fi]),T2.upd(in[p.se]);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;dfs1(v);
	}
	for(ask p:que[u]){
		if(p.fl==1)ans[p.id]+=T1.que(in[p.pos],out[p.pos])-p.v;
		else ans[p.id]-=T2.que(in[p.pos],out[p.pos])-p.v;
	}
	// cout<<u<<"\n";
	// for(int i=1;i<=m;i++)printf("%lld ",ans[i]);cout<<"\n";
}
void work(){
	k=read();scanf("%s",s+1);n=strlen(s+1);m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",t+1);int len=strlen(t+1);
		if(len<=k)ans[i]=n-len+1;
		else insert(t,i);
	}
	build(),dfs(0),dfs1(0);
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
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
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
