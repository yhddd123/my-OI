// Problem: P5445 [APIO2019] 路灯
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5445
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2025-05-13 18:05:49
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,q;
char c[maxn],op[10];
struct node{
	int l,r;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
set<node> s;
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int tree[maxn<<7],lc[maxn<<7],rc[maxn<<7],idx,rt[maxn];
void updata(int &nd,int l,int r,int p,int w){
	if(!nd)nd=++idx;tree[nd]+=w;
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
#define lb(x) (x&(-x))
void upd(int x,int y,int w){
	if(y>n+1)return ;
	while(x<=n+1)updata(rt[x],1,n+1,y,w),x+=lb(x);
}
int que(int x,int y){
	int res=0;
	while(x)res+=query(rt[x],1,n+1,1,y),x-=lb(x);
	return res;
}
void upd(int l,int r,int ll,int rr,int w){
	upd(l,ll,w),upd(l,rr+1,-w),upd(r+1,ll,-w),upd(r+1,rr+1,w);
}
void upd(int p,int w){
	auto it=s.lower_bound({p,p});
	if((*it).r==p){
		int pl=(*it).l,pr=(*++it).r;
		it--;it=s.erase(it),it=s.erase(it);
		s.insert({pl,pr});
		upd(pl,p,p+1,pr,w);
	}
	else{
		int pl=(*it).l,pr=(*it).r;
		it=s.erase(it);
		s.insert({pl,p}),s.insert({p+1,pr});
		upd(pl,p,p+1,pr,w);
	}
}
void work(){
	n=read();q=read();scanf("%s",c+1);
	for(int i=1;i<=n+1;i++)s.insert({i,i});
	for(int i=1;i<=n;i++)if(c[i]=='1')upd(i,q);
	while(q--){
		scanf("%s",op);
		if(op[0]=='q'){
			int u=read(),v=read();
			int ans=que(u,v);
			auto it=s.find({u,u});
			if((*it).r>=v)ans-=q;
			printf("%d\n",ans);
		}
		else{
			int p=read();
			if(c[p]=='1')upd(p,-q),c[p]='0';
			else upd(p,q),c[p]='1';
		}
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