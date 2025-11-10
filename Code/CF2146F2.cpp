// Problem: F2. Chain Prefix Rank (Hard Version)
// Contest: Codeforces - Codeforces Global Round 30 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2164/problem/F2
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-11-10 18:16:34
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,p[maxn];
vector<int> e[maxn],g[maxn];
mt19937 rnd(0);
int w[maxn],ls[maxn],rs[maxn],idx,rt;
int siz[maxn];
void up(int u){
	siz[u]=siz[ls[u]]+siz[rs[u]]+1;
}
int merge(int u,int v){
	if(!u||!v)return u|v;
	if(w[u]<w[v]){
		rs[u]=merge(rs[u],v);
		up(u);
		return u;
	}
	else{
		ls[v]=merge(u,ls[v]);
		up(v);
		return v;
	}
}
pii split(int u,int k){
	if(!u)return {0,0};
	if(siz[ls[u]]+1>k){
		pii t=split(ls[u],k);
		ls[u]=t.se;
		up(u);
		return {t.fi,u};
	}
	else{
		pii t=split(rs[u],k-siz[ls[u]]-1);
		rs[u]=t.fi;
		up(u);
		return {u,t.se};
	}
}
void newnode(int p){
	w[p]=rnd();siz[p]=1;ls[p]=rs[p]=0;
}
void dfs(int u){
	newnode(u);
	int a,b,c,d;
	pii t=split(rt,p[u]+1);
	c=t.fi,d=t.se;
	t=split(c,p[u]);
	b=t.fi,c=t.se;
	t=split(b,p[u]-1);
	a=t.fi,b=t.se;
	g[b].pb(u),g[u].pb(c);
	// cout<<u<<" "<<a<<" "<<b<<" "<<c<<" "<<d<<"\n";
	rt=merge(a,merge(b,merge(u,merge(c,d))));
	for(int v:e[u])dfs(v);
	t=split(rt,p[u]+1);
	b=t.fi,c=t.se;
	t=split(b,p[u]);
	a=t.fi,b=t.se;
	rt=merge(a,c);
}
map<int,pii> mp[maxn];
int d[maxn];
queue<int> q;
void add(int u,int v,pii w){
    if(mp[u].find(v)==mp[u].end())mp[u][v]={1,0},d[u]++;
    (mp[u][v].fi*=w.fi)%=mod,mp[u][v].se+=w.se;
}
void work(){
	n=read();init(n+2);
	for(int i=1;i<=n+2;i++)e[i].clear(),g[i].clear();
	for(int i=2;i<=n;i++)e[read()].pb(i);e[n+1].pb(n+2),e[n+2].pb(1);
	for(int i=1;i<=n;i++)p[i]=read()+1;p[n+1]=0,p[n+2]=1;
	for(int i=1;i<=n+2;i++)d[i]=0,mp[i].clear();
	newnode(n+1),newnode(n+2);
	rt=merge(n+1,n+2);
	dfs(1);
	g[n+1].pb(n+2);
	for(int u=1;u<=n+2;u++){
		for(int v:g[u])add(u,v,{1,0}),add(v,u,{1,0});
		// for(int v:g[u])cout<<u<<" "<<v<<" e\n";
	}
    for(int i=1;i<=n;i++)if(d[i]<=2)q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        // cout<<u<<" "<<d[u]<<"\n";
        if(!d[u]||u>n)continue;
        if(d[u]==2){
            int v1=(*mp[u].begin()).fi,v2=(*--mp[u].end()).fi;
            pii w1=(*mp[u].begin()).se,w2=(*--mp[u].end()).se;
            pii w={w1.fi*w2.fi%mod*C(mp[v1][v2].se+w1.se+w2.se+1,w1.se+w2.se+1)%mod,w1.se+w2.se+1};
            add(v1,v2,w),add(v2,v1,w);
            mp[u].erase(v1),mp[u].erase(v2),mp[v1].erase(u),mp[v2].erase(u),d[u]-=2,d[v1]--,d[v2]--;
            if(d[v1]<=2)q.push(v1);
            if(d[v2]<=2)q.push(v2);
        }
    }
    printf("%lld\n",mp[n+1][n+2].fi);
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