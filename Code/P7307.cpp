// Problem: P7307 [COCI2018-2019#1] Teoretičar
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7307
// Memory Limit: 256 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2024-09-11 18:29:20
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n1,n2,m;
vector<pii> e[maxn];
vector<int> tmp;
int ans[maxn],num;
int d[maxn];
bool vis[maxn];
void dfs(int u){
	while(e[u].size()){
		if(vis[e[u].back().se])e[u].pop_back();
		else{
			int v=e[u].back().fi;
			tmp.pb(e[u].back().se);
			vis[e[u].back().se]=1;
			e[u].pop_back();
			dfs(v);
		}
	}
}
struct nd{
	int u,v,id;
}g[maxn];
void sovle(int tp){
	if(!tp)return ;
	vector<int> id;
	for(int i=1;i<=tp;i++){
		int u=g[i].u,v=g[i].v;
		id.pb(u),id.pb(v);
		d[u]=d[v]=0;
		// e[u].clear(),e[v].clear();
	}
	for(int i=1;i<=tp;i++){
		int u=g[i].u,v=g[i].v;
		d[u]++,d[v]++;
		e[u].pb({v,g[i].id}),e[v].pb({u,g[i].id});
		vis[g[i].id]=0;
	}
	int mx=0;for(int i:id)mx=max(mx,d[i]);
	// cout<<tp<<endl;
	// for(int i=1;i<=tp;i++)cout<<g[i].u<<" "<<g[i].v<<" "<<g[i].id<<"\n";
	// cout<<endl;
	if(mx==1){
		++num;
		// cout<<num<<" "<<tp<<"\n";
		for(int i=1;i<=tp;i++)ans[g[i].id]=num;
		for(int i:id)e[i].clear();
		return ;
	}
	e[n1+n2+1].clear(),e[n1+n2+2].clear();
	for(int i:id)if(d[i]&1){
		if(i<=n1)e[i].pb({n1+n2+2,i+m}),e[n1+n2+2].pb({i,i+m});
		else e[i].pb({n1+n2+1,i+m}),e[n1+n2+1].pb({i,i+m});
		vis[i+m]=0;
	}
	if(e[n1+n2+1].size()&1)e[n1+n2+1].pb({n1+n2+2,n1+n2+1+m}),e[n1+n2+2].pb({n1+n2+1,n1+n2+1+m}),vis[n1+n2+1+m]=0;
	tmp.clear();
	for(int i:id)if(e[i].size())dfs(i);
	for(int i=0;i<tmp.size();i+=2)if(tmp[i]<=m)ans[tmp[i]]=1;
	for(int i=1;i<tmp.size();i+=2)if(tmp[i]<=m)ans[tmp[i]]=0;
	sort(g+1,g+tp+1,[&](nd u,nd v){return ans[u.id]<ans[v.id];});
	int p=0;for(int i=1;i<=tp;i++)if(!ans[g[i].id])p=i;
	// cout<<"ls\n";
	// for(int i=1;i<=p;i++)cout<<g[i].u<<" "<<g[i].v<<" "<<g[i].id<<"\n";
	sovle(p);
	for(int i=p+1;i<=tp;i++)g[i-p]=g[i];
	sovle(tp-p);
}
void work(){
	n1=read();n2=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read()+n1;
		g[i]={u,v,i};
	}
	sovle(m);
	printf("%lld\n",num);
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