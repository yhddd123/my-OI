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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,p;
vector<int> e[maxn];
int fa[maxn],siz[maxn];
int dfn[maxn],idx,st[18][maxn];
int dep[maxn];
vector<int> id[maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1,id[dep[u]].pb(u);
	st[0][dfn[u]=++idx]=fa;
	sort(e[u].begin(),e[u].end(),[&](int u,int v){return siz[u]>siz[v];});
	for(int v:e[u]){
		dfs(v,u);
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
int dis(int u,int v){return dep[u]+dep[v]-2*dep[lca(u,v)];}
int ask(int u,int k){
	printf("? %lld %lld\n",u,k);fflush(stdout);
	// return dis(u,p)<=k;
	return read();
}
mt19937 rnd(2);
int res,sum,rt;
bool vis[maxn];
void getrt(int u){
	siz[u]=1;
	for(int v:e[u]){
		if(vis[v])continue;
		getrt(v);siz[u]+=siz[v];
	}
	if(siz[u]<=sum/2){
		if(!rt||siz[rt]<siz[u])rt=u;
	}
}
int sovle(int u){
	if(sum==1)return u;
	rt=0;getrt(u);
	// cout<<u<<" "<<rt<<" "<<sum<<"\n";
	if(ask(rt,res-dep[rt]))u=rt,sum=siz[rt];
	else vis[rt]=1,sum=siz[u]-siz[rt];
	return sovle(u);
}
void work(){
	n=read();
	for(int i=0;i<=n;i++)e[i].clear(),id[i].clear();
	for(int i=2;i<=n;i++){
		e[fa[i]=read()].pb(i);
	}
	for(int i=1;i<=n;i++)siz[i]=1;
	for(int i=n;i;i--)siz[fa[i]]+=siz[i];
	dep[0]=-1;idx=0;dfs(1,0);
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)vis[i]=0;
	int l=0,r=n;res=n;
	while(l<=r){
		int mid=l+r>>1;
		if(ask(1,mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	sum=n;for(int p:id[res])e[p].clear(),sum-=siz[p]-1;
	int pos=sovle(1);
	printf("! %lld\n",pos);fflush(stdout);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}