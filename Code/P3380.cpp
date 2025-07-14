// Problem: P3380 【模板】树套树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3380
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-04-11 18:22:40
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int maxn=50010;
const int maxm=5000010;
const int inf=1e8;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0' || c>'9'){if(c=='-') f=-1;c=getchar();}while(c>='0' && c<='9') {x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
#define put() putchar(' ')
#define endl puts("")
bool Mbe;

int n,m,a[maxn];
namespace fhq{
	int val[maxm],w[maxm],siz[maxm],idx,ls[maxm],rs[maxm];
	void up(int u){siz[u]=siz[ls[u]]+siz[rs[u]]+1;}
	pii split(int u,int k){
		if(!u)return {0,0};
		// cout<<u<<" "<<val[u]<<" "<<k<<" s\n";
		if(val[u]<=k){
			pii t=split(rs[u],k);
			rs[u]=t.first;
			up(u);
			return {u,t.second};
		}
		else{
			pii t=split(ls[u],k);
			ls[u]=t.second;
			up(u);
			return {t.first,u};
		}
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
	void create(int k){
		val[++idx]=k,w[idx]=rand(),siz[idx]=1;
	}
	void insert(int &rt,int k){
		pii t=split(rt,k-1);create(k);
		rt=merge(t.first,merge(idx,t.second));
	}
	void del(int &rt,int k){
		pii u=split(rt,k),v=split(u.first,k-1);
		v.second=merge(ls[v.second],rs[v.second]);
		rt=merge(v.first,merge(v.second,u.second));
	}
	int quenum(int rt,int l,int r){
		pii u=split(rt,l-1),v=split(u.second,r);
		int res=siz[v.first];
		rt=merge(u.first,merge(v.first,v.second));
		return res;
	}
	// int findrnk(int rt,int x){
		// int res=0;
		// pii u=split(rt,x-1);
		// res=siz[u.first]+1;
		// // cout<<u.first<<" "<<siz[u.first]<<" "<<siz[u.second]<<"\n";
		// rt=merge(u.first,u.second);
		// return res;
	// }
	// int findkey(int u,int k){
		// if(!k)return -2147483647;
		// if(k>siz[u])return 2147483647;
		// if(k==siz[ls[u]]+1)return val[u];
		// if(k<=siz[ls[u]])return findkey(ls[u],k);
		// else return findkey(rs[u],k-siz[ls[u]]-1);
	// }
	// int pre(int u,int k){return findkey(u,findrnk(u,k)-1);}
	// int nxt(int u,int k){return findkey(u,findrnk(u,k+1));}
}
namespace sgt{
	#define ls lc[nd]
	#define rs rc[nd]
	#define mid (l+r>>1)
	int tree[maxn<<5],lc[maxn<<5],rc[maxn<<5],rt,idx;
	void insert(int &nd,int l,int r,int p,int w){
		if(!nd)nd=++idx;
		fhq::insert(tree[nd],w);
		if(l==r)return ;
		if(p<=mid)insert(ls,l,mid,p,w);
		else insert(rs,mid+1,r,p,w);
	}
	int quernk(int nd,int l,int r,int ql,int qr,int pl,int pr){
		if(ql>qr)return 0;
		if(l>=ql&&r<=qr){
			return fhq::quenum(tree[nd],pl,pr);
		}
		if(qr<=mid)return quernk(ls,l,mid,ql,qr,pl,pr);
		if(ql>mid)return quernk(rs,mid+1,r,ql,qr,pl,pr);
		return quernk(ls,l,mid,ql,qr,pl,pr)+quernk(rs,mid+1,r,ql,qr,pl,pr);
	}
	int quekey(int nd,int l,int r,int pl,int pr,int k){
		if(l==r)return l;
		int val=fhq::quenum(tree[ls],pl,pr);
		// cout<<nd<<" "<<l<<" "<<r<<" "<<pl<<" "<<pr<<" "<<k<<" "<<val<<"\n";
		if(val>=k)return quekey(ls,l,mid,pl,pr,k);
		return quekey(rs,mid+1,r,pl,pr,k-val);
	}
	void del(int nd,int l,int r,int p,int w){
		fhq::del(tree[nd],w);
		if(l==r)return ;
		if(p<=mid)del(ls,l,mid,p,w);
		else del(rs,mid+1,r,p,w);
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),sgt::insert(sgt::rt,0,inf,a[i],i);
	// return ;
	while(m--){
		int op=read();
		if(op==1){
			int l=read(),r=read(),k=read();
			write(sgt::quernk(1,0,inf,0,k-1,l,r)+1);endl;
		}
		if(op==2){
			int l=read(),r=read(),k=read();
			write(sgt::quekey(1,0,inf,l,r,k));endl;
		}
		if(op==3){
			int p=read(),k=read();
			sgt::del(1,0,inf,a[p],p),a[p]=k,sgt::insert(sgt::rt,0,inf,a[p],p);
		}
		if(op==4){
			int l=read(),r=read(),k=read();
			int x=sgt::quernk(1,0,inf,0,k-1,l,r);
			if(!x)printf("-2147483647\n");
			else write(sgt::quekey(1,0,inf,l,r,x)),endl;
		}
		if(op==5){
			int l=read(),r=read(),k=read();
			int x=sgt::quernk(1,0,inf,0,k,l,r);
			// cout<<x<<"\n";
			if(x==r-l+1)printf("2147483647\n");
			else write(sgt::quekey(1,0,inf,l,r,x+1)),endl;
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	// cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;

	
	T=1;srand(time(0));
	while(T--)work();
}