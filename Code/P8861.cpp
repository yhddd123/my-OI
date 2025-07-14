// Problem: P8861 线段
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8861
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-10-16 12:30:34
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
#define db double
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int q,n=200000,typ,ans;
struct bit{
	#define lb(x) (x&(-x))
	int tree[maxn];
	void upd(int x,int w){
		while(x<=n)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;
		while(x)res+=tree[x],x-=lb(x);
		return res;
	}
	int que(int l,int r){
		if(l>r)return 0;
		return que(r)-que(l-1);
	}
}numl,numr,suml,sumr;
void updl(int p,int w){numl.upd(p,w),suml.upd(p,p*w);}
void updr(int p,int w){numr.upd(p,w),sumr.upd(p,p*w);}
int getans(int l,int r){
	// cout<<l<<" "<<r<<" "<<sumr.que(l,r)<<" "<<suml.que(l,r)<<"\n";
	return -numl.que(1,l-1)*l+numr.que(1,l-1)*l-suml.que(l,r)+sumr.que(l,r)+numr.que(r+1,n)*r-numl.que(r+1,n)*r;
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
priority_queue<pii,vector<pii>,greater<pii>> tl[maxn<<2];
priority_queue<pii> tr[maxn<<2];
int pos[maxn<<5],idx=1,vis[maxn<<5];
int f[maxn<<5],siz[maxn<<5];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
vector<int> e[maxn<<5];
int merge(int u,int v){
	if(!u||!v)return u|v;
	u=fd(u),v=fd(v);
	if(u==v)return u;
	if(siz[u]<siz[v])swap(u,v);
	f[v]=u,siz[u]+=siz[v];e[u].pb(v);
	return u;
}
void upd(int nd,int l,int r){
	int u=++idx,v=++idx;
	pos[u]=l,pos[v]=r;
	tl[nd].push({l,u}),tr[nd].push({r,v});
	f[u]=u,f[v]=v,siz[u]=siz[v]=1;
	updl(l,1),updr(r,1);
}
void updata(int nd,int l,int r,int ql,int qr){
	if(l==r)return ;
	if(ql<=mid&&mid<qr)return upd(nd,ql,qr);
	if(qr<=mid)updata(ls,l,mid,ql,qr);
	else updata(rs,mid+1,r,ql,qr);
}
void dell(int u){
	if(!vis[u]){
		vis[u]=1;siz[fd(u)]--;updl(pos[fd(u)],-1);
		vis[u^1]=1;siz[fd(u^1)]--;updr(pos[fd(u^1)],-1);
	}
	for(int v:e[u])dell(v);
}
void delr(int u){
	if(!vis[u]){
		vis[u]=1;siz[fd(u)]--;updr(pos[fd(u)],-1);
		vis[u^1]=1;siz[fd(u^1)]--;updl(pos[fd(u^1)],-1);
	}
	for(int v:e[u])delr(v);
}
void modif(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return ;
	if(ql>r||qr<l)return ;
	if(ql<=mid&&mid<qr){
		int id=0;
		while(!tl[nd].empty()){
			int u=tl[nd].top().se;if(tl[nd].top().fi>ql)break;tl[nd].pop();
			updl(pos[u],-siz[u]);id=merge(id,u);
		}
		if(id){
			pos[id]=ql,updl(pos[id],siz[id]);
			tl[nd].push({ql,id});
		}
		id=0;
		while(!tr[nd].empty()){
			int u=tr[nd].top().se;if(tr[nd].top().fi<qr)break;tr[nd].pop();
			updr(pos[u],-siz[u]);id=merge(id,u);
		}
		if(id){
			pos[id]=qr,updr(pos[id],siz[id]);
			tr[nd].push({qr,id});
		}
	}
	else if(qr<=mid){
		int id=0;
		while(!tl[nd].empty()){
			int u=tl[nd].top().se;if(tl[nd].top().fi>ql)break;tl[nd].pop();
			// assert(siz[u]);
			updl(pos[u],-siz[u]);id=merge(id,u);
		}
		if(id){
			pos[id]=ql,updl(pos[id],siz[id]);
			tl[nd].push({ql,id});
		}
		while(!tl[nd].empty()){
			int u=tl[nd].top().se;if(tl[nd].top().fi>qr)break;tl[nd].pop();
			for(int i=1;i<=siz[u];i++)updata(ls,l,mid,pos[u],qr);
			dell(u);
			// assert(!siz[u]);
		}
	}
	else{
		int id=0;
		while(!tr[nd].empty()){
			int u=tr[nd].top().se;if(tr[nd].top().fi<qr)break;tr[nd].pop();
			updr(pos[u],-siz[u]);id=merge(id,u);
		}
		if(id){
			pos[id]=qr,updr(pos[id],siz[id]);
			tr[nd].push({qr,id});
		}
		while(!tr[nd].empty()){
			int u=tr[nd].top().se;if(tr[nd].top().fi<ql)break;tr[nd].pop();
			for(int i=1;i<=siz[u];i++)updata(rs,mid+1,r,ql,pos[u]);
			delr(u);
		}
	}
	modif(ls,l,mid,ql,qr),modif(rs,mid+1,r,ql,qr);
}
void work(){
	q=read();typ=read();
	while(q--){
		int op=read(),l=(read()+typ*ans)%(n+1),r=(read()+typ*ans)%(n+1);
		if(op==1){
			updata(1,1,n,l,r);
		}
		if(op==2){
			modif(1,1,n,l,r);
		}
		if(op==3){
			printf("%lld\n",ans=getans(l,r));
		}
	}
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
