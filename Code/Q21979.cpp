#include<bits/stdc++.h>
#define ll long long
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
const int inf=2e9;
bool mbe;

mt19937 rnd(time(0));
struct weightdsu{
	int fa[maxn],rd[maxn];pii val[maxn];
	int siz[maxn];
	weightdsu(int n){
		for(int i=1;i<=n;i++)fa[i]=i,rd[i]=rnd(),val[i]={inf,inf};
	}
	int fd(int u,pii w={inf-1,inf}){
		while(val[u]<=w){
			while(val[fa[u]]<=val[u]){
				// siz[fa[u]]-=siz[u];
				fa[u]=fa[fa[u]];
			}
			u=fa[u];
		}
		return u;
	}
	void del(int u){
		// if(fa[u]==u)return ;
		// del(fa[u]);siz[fa[u]]-=siz[u];
	}
	int ins(int u,pii w={inf-1,inf}){
		while(val[u]<=w){
			// siz[fa[u]]+=siz[u];
			u=fa[u];
		}
		return u;
	}
	void merge(int u,int v,pii w){
		del(u),del(v);
		while(u!=v){
			u=ins(u,w),v=ins(v,w);
			if(rd[u]<rd[v])swap(u,v);
			swap(fa[u],v),swap(val[u],w);
		}
		ins(u);
	}
	pii max_path(int u,int v){
		int uu=fd(u),vv=fd(v);
		if(uu!=vv)return {inf,-1};
		if(val[u]>val[v])swap(u,v);
		while(fa[u]!=v){
			u=fa[u];
			if(val[u]>val[v])swap(u,v);
		}
		return val[u];
	}
	pii del_path(int u,int v){
		int uu=fd(u),vv=fd(v);
		if(uu!=vv)return {inf,-1};
		if(val[u]>val[v])swap(u,v);
		while(fa[u]!=v){
			u=fa[u];
			if(val[u]>val[v])swap(u,v);
		}
		v=u;
		while(fa[v]!=v){
			// siz[fa[v]]-=siz[v];
			v=fa[v];
		}
		fa[u]=u;
		pii res={inf,inf};swap(res,val[u]);
		return res;
	}
	pii add_edge(int u,int v,pii w){
		pii res=del_path(u,v);
		if(res<=w)swap(res,w);
		merge(u,v,w);
		return res;
	}
};
int n,m;ll ans;
void work(){
	n=read();m=read();
	weightdsu f(n);
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		if(u==v)continue;
		pii res=f.add_edge(u,v,{w,i-1});
		ans+=w;
		if(res.fi!=inf)ans-=res.fi;
	}
	printf("%lld\n",ans);
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