// Problem: P5443 [APIO2019] 桥梁
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5443
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-13 12:29:58
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
const int maxn=100010;
const int B=1000;
const int inf=1e9;
bool mbe;

int n,m,q;
tuple<int,int,int> e[maxn],que[maxn];
int ans[maxn];
bool vis[maxn];
int f[maxn],siz[maxn];
int st[maxn],tp;
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v)return ;
	if(siz[u]<siz[v])swap(u,v);
	f[v]=u,siz[u]+=siz[v];st[++tp]=v;
}
void del(){
	int v=st[tp],u=f[v];
	f[v]=v,siz[u]-=siz[v];
	tp--;
}
int val[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)e[i]={read(),read(),inf-read()+1};
	q=read();
	for(int i=1;i<=q;i++)que[i]={read(),read(),inf-read()+1};
	for(int l=1,r;l<=q;l=r+1){
		r=min(q,l+B-1);
		vector<pii> a;
		for(int i=l;i<=r;i++){
			auto[op,x,y]=que[i];
			if(op==1)vis[x]=1;
			else a.pb({y,i});
		}
		for(int i=1;i<=m;i++)if(!vis[i]){
			auto[u,v,w]=e[i];
			a.pb({w,-i});
		}
		for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;tp=0;
		sort(a.begin(),a.end());
		vector<int> eid;
		for(int i=1;i<=m;i++)if(vis[i])eid.pb(i);
		for(auto[w,id]:a){
			// cout<<w<<" "<<id<<"\n";
			if(id<0)merge(get<0>(e[-id]),get<1>(e[-id]));
			else{
				int lst=tp;
				for(int i:eid)val[i]=get<2>(e[i]);
				for(int i=l;i<id;i++){
					auto[op,x,y]=que[i];
					if(op==1)val[x]=y;
				}
				for(int i:eid)if(val[i]<=w)merge(get<0>(e[i]),get<1>(e[i]));
				ans[id]=siz[fd(get<1>(que[id]))];
				while(tp>lst)del();
			}
		}
		for(int i=l;i<=r;i++){
			auto[op,x,y]=que[i];
			if(op==1){
				get<2>(e[x])=y;
				vis[x]=0;
			}
		}
	}
	for(int i=1;i<=q;i++)if(get<0>(que[i])==2)printf("%d\n",ans[i]);
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