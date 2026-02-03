// Problem: P7220 [JOISC 2020] 掃除
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7220
// Memory Limit: 2048 MB
// Time Limit: 11000 ms
// Written by yhm.
// Start codeing:2026-02-02 10:55:35
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;	
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1500010;
const int inf=1e9;
bool mbe;

int n,m,q;
int lsh[maxn<<1],len;
pii ask[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
priority_queue<pii,vector<pii>,greater<pii>> tl[maxn<<3];
priority_queue<pii> tr[maxn<<3];
const int maxm=maxn*10;
int pos[maxm],pp[maxn],qq[maxm],idx=1;
bool vis[maxm];
int f[maxm],siz[maxm];
int stk[maxm],top;
int fd(int x) {
    int root = x;
    while (f[root] != root) root = f[root];
    while (f[x] != root) { int tmp = f[x]; f[x] = root; x = tmp; }
    return root;
}
vector<int> e[maxm];
int merge(int u,int v){
	if(!u||!v)return u|v;
	u=fd(u),v=fd(v);
	if(u==v)return u;
	if(siz[u]<siz[v])swap(u,v);
	f[v]=u,siz[u]+=siz[v];e[u].pb(v);
	return u;
}
void upd(int nd,int l,int r,int id){
	int u=top?stk[top--]:++idx,v=top?stk[top--]:++idx;
	// int u=++idx,v=++idx;
	if(u>v)swap(u,v);
	pos[u]=l,pos[v]=r;pp[id]=u;qq[u]=qq[v]=id;
	vis[u]=vis[v]=0;
	// cout<<l<<" "<<r<<" "<<id<<" "<<pp[id]<<" u\n";
	tl[nd].push({l,u}),tr[nd].push({r,v});
	f[u]=u,f[v]=v,siz[u]=siz[v]=1;
}
int bk[maxn];
void updata(int nd,int l,int r,int ql,int qr,int id){
	if(l==r){
		bk[id]=l;pp[id]=0;
		return ;
	}
	if(ql<=mid&&mid<qr)return upd(nd,ql,qr,id);
	if(qr<=mid)updata(ls,l,mid,ql,qr,id);
	else updata(rs,mid+1,r,ql,qr,id);
}
int st[maxn],tp;
void dell(int u){
	if(!vis[u]){
		st[++tp]=qq[u];
		vis[u]=1;siz[fd(u)]--;
		vis[u^1]=1;siz[fd(u^1)]--;
	}
	else stk[++top]=u,stk[++top]=u^1;
	for(int v:e[u])dell(v);
	vector<int>().swap(e[u]);
}
void delr(int u){
	if(!vis[u]){
		st[++tp]=qq[u];
		vis[u]=1;siz[fd(u)]--;
		vis[u^1]=1;siz[fd(u^1)]--;
	}
	else stk[++top]=u,stk[++top]=u^1;
	for(int v:e[u])delr(v);
	vector<int>().swap(e[u]);
}
void modif(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return ;
	if(ql>r||qr<l)return ;
	if(ql<=mid&&mid<qr){
		int id=0;
		while(!tl[nd].empty()){
			int u=tl[nd].top().se;if(tl[nd].top().fi>ql)break;tl[nd].pop();
			id=merge(id,u);
		}
		if(siz[id]){
			pos[id]=ql;
			tl[nd].push({ql,id});
		}
		id=0;
		while(!tr[nd].empty()){
			int u=tr[nd].top().se;if(tr[nd].top().fi<qr)break;tr[nd].pop();
			id=merge(id,u);
		}
		if(siz[id]){
			pos[id]=qr;
			tr[nd].push({qr,id});
		}
	}
	else if(qr<=mid){
		int id=0;
		while(!tl[nd].empty()){
			int u=tl[nd].top().se;if(tl[nd].top().fi>ql)break;tl[nd].pop();
			id=merge(id,u);
		}
		if(siz[id]){
			pos[id]=ql;
			tl[nd].push({ql,id});
		}
		while(!tl[nd].empty()){
			int u=tl[nd].top().se;if(tl[nd].top().fi>qr)break;tl[nd].pop();
			tp=0;dell(u);
			for(int i=1;i<=tp;i++)updata(ls,l,mid,pos[u],qr,st[i]);
		}
	}
	else{
		int id=0;
		while(!tr[nd].empty()){
			int u=tr[nd].top().se;if(tr[nd].top().fi<qr)break;tr[nd].pop();
			id=merge(id,u);
		}
		if(siz[id]){
			pos[id]=qr;
			tr[nd].push({qr,id});
		}
		while(!tr[nd].empty()){
			int u=tr[nd].top().se;if(tr[nd].top().fi<ql)break;tr[nd].pop();
			tp=0;delr(u);
			for(int i=1;i<=tp;i++)updata(rs,mid+1,r,ql,pos[u],st[i]);
		}
	}
	modif(ls,l,mid,ql,qr),modif(rs,mid+1,r,ql,qr);
}

void work(){
	n=read();m=read();q=read();
	lsh[++len]=0,lsh[++len]=n;
	for(int i=1;i<=m;i++)ask[i+q]={read(),n-read()},lsh[++len]=ask[i+q].fi,lsh[++len]=ask[i+q].se;
	for(int i=1;i<=q;i++){
		int o=read();
		if(o==1)ask[i]={-o,read()};
		if(o==2){
			int p=n-read();
			ask[i]={-o,p};lsh[++len]=p;
		}
		if(o==3){
			int p=read();
			ask[i]={-o,p};lsh[++len]=p;
		}
		if(o==4){
			int l=read(),r=n-read();
			lsh[++len]=l,lsh[++len]=r;
			ask[i]={l,r};
		}
	}
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=q+m;i++){
		auto&[l,r]=ask[i];
		if(l>=0){
			l=lower_bound(lsh+1,lsh+len+1,l)-lsh;
			r=lower_bound(lsh+1,lsh+len+1,r)-lsh;
		}
		else if(l!=-1){
			r=lower_bound(lsh+1,lsh+len+1,r)-lsh;
		}
	}
	for(int i=1;i<=m;i++)updata(1,1,len,ask[i+q].fi,ask[i+q].se,i);
	for(int i=1;i<=q;i++){
		auto[l,r]=ask[i];
		if(l==-1){
			if(bk[r])write(lsh[bk[r]]),putchar(' '),write(n-lsh[bk[r]]);
			else write(lsh[pos[fd(pp[r])]]),putchar(' '),write(n-lsh[pos[fd(pp[r]^1)]]);
			puts("");
		}
		if(l==-2){
			modif(1,1,len,r,len);
		}
		if(l==-3){
			modif(1,1,len,1,r);
		}
		if(l>0){
			++m;updata(1,1,len,l,r,m);
		}
		// cout<<i<<" "<<idx<<"\n";
		// for(int i=1;i<=m;i++){
			// if(bk[i])printf("%d %d\n",lsh[bk[r]],lsh[bk[r]]);
			// else cout<<lsh[pos[fd(pp[i])]]<<" "<<lsh[pos[fd(pp[i]+1)]]<<"\n";
		// }
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