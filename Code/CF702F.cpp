// Problem: CF702F T-Shirts
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF702F
// Memory Limit: 1000 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-06-02 17:00:28
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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m;
pii a[maxn];
mt19937 rnd(1);
int ls[maxn],rs[maxn],w[maxn],rt;
int val[maxn],del[maxn],res[maxn],add[maxn];
void upd(int u,int w1,int w2){
	val[u]-=w1,del[u]+=w1,res[u]+=w2,add[u]+=w2;
}
void down(int u){
	upd(ls[u],del[u],add[u]),upd(rs[u],del[u],add[u]);
	del[u]=add[u]=0;
}
int merge(int u,int v){
	if(!u||!v)return u|v;down(u),down(v);
	if(w[u]<w[v]){
		rs[u]=merge(rs[u],v);
		return u;
	}
	else{
		ls[v]=merge(u,ls[v]);
		return v;
	}
}
pii split(int u,int v){
	if(!u)return {0,0};down(u);
	if(val[u]<=v){
		pii t=split(rs[u],v);
		rs[u]=t.fi;return {u,t.se};
	}
	else{
		pii t=split(ls[u],v);
		ls[u]=t.se;return {t.fi,u};
	}
}
void ins(int &rt,int i){
	ls[i]=rs[i]=add[i]=del[i]=0;
	auto[u,v]=split(rt,val[i]);
	rt=merge(u,merge(i,v));
}
vector<int> id;
void dfsid(int u){
	if(!u)return ;down(u);
	dfsid(ls[u]);
	id.pb(u);
	dfsid(rs[u]);
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	sort(a+1,a+n+1,[&](pii u,pii v){return u.se>v.se||(u.se==v.se&&u.fi<v.fi);});
	m=read();
	for(int i=1;i<=m;i++){
		val[i]=read(),w[i]=rnd();
		ins(rt,i);
	}
	for(int i=1;i<=n;i++){
		auto[u,v]=split(rt,a[i].fi-1);
		upd(v,a[i].fi,1);
		auto[x,y]=split(v,a[i].fi-1);
		id.clear();dfsid(x);
		for(int j:id)ins(u,j);
		rt=merge(u,y);
		// cout<<i<<"\n";
		// for(int j=1;j<=m;j++)cout<<val[j]<<" "<<res[j]<<"\n";
	}
	id.clear();dfsid(rt);
	for(int i=1;i<=m;i++)printf("%lld ",res[i]);
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