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
const int maxn=300010;
const int inf=1e9;
bool mbe;
 
int n,q,a[maxn];
pii st[maxn];int tp;
map<int,int> mp;
int f[maxn],siz[maxn],w[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int merge(int u,int v){
	if(siz[u]<siz[v])swap(u,v);
	w[v]-=w[u],f[v]=u,siz[u]+=siz[v];
	return u;
}
int calc(int x){
	if(f[x]==x)return w[x];
	return w[x]+calc(f[x]);
}
vector<pii> upd[maxn];
vector<int> que[maxn];
int ans[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read(),x=read();
		upd[r].pb({x,i});
		que[l].pb(i);
	}
	for(int i=1;i<=q;i++)f[i]=i,siz[i]=1;
	for(int i=n;i;i--){
		for(auto[x,id]:upd[i]){
			if(mp.find(x)!=mp.end())mp[x]=merge(mp[x],id);
			else mp[x]=id;
		}
		auto it=mp.lower_bound(a[i]);
		tp=0;while(it!=mp.end()){
			int x=(*it).fi,id=(*it).se;it=mp.erase(it);
			w[id]+=(x-a[i]+1)/2*i;x=(x+a[i])/2;
			if(tp&&st[tp].fi==x)st[tp].se=merge(st[tp].se,id);
			else st[++tp]={x,id};
		}
		for(int i=1;i<=tp;i++)mp[st[i].fi]=st[i].se;
		for(int id:que[i])ans[id]=calc(id);
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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