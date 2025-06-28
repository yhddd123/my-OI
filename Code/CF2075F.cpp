// Problem: CF2075F Beautiful Sequence Returns
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2075F
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-03-25 16:28:15
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
int b[maxn],p1,c[maxn],p2;
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2],tag[maxn<<2];
void build(int nd,int l,int r){
	mx[nd]=tag[nd]=0;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void upd(int nd,int w){mx[nd]+=w,tag[nd]+=w;}
void down(int nd){
	upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return 0;
	if(l>=ql&&r<=qr)return mx[nd];
	if(tag[nd])down(nd);
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
#undef mid
int pl[maxn],pr[maxn],ql[maxn],qr[maxn];
bool vis[maxn];
vector<tuple<int,int,int>> que[maxn];
void work(){
	n=read();ans=1,p1=p2=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1,mn=inf;i<=n;i++){
		if(a[i]<mn){
			mn=a[i];
			b[++p1]=i;
		}
	}
	for(int i=n,mx=0;i;i--){
		if(a[i]>mx){
			mx=a[i];
			c[++p2]=i;
		}
	}
	reverse(c+1,c+p2+1);
	for(int i=1;i<=p1;i++)vis[b[i]]=1;
	for(int i=1;i<=p1;i++)pl[b[i]]=pr[b[i]]=i;
	for(int i=1;i<=n;i++)if(!vis[i]){
		int l=1,r=p1,res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(a[b[mid]]>=a[i])l=mid+1,res=mid;
			else r=mid-1;
		}
		pl[i]=res+1,pr[i]=lower_bound(b+1,b+p1+1,i)-b-1;
	}
	for(int i=1;i<=p1;i++)vis[b[i]]=0;
	for(int i=1;i<=p2;i++)vis[c[i]]=1;
	for(int i=1;i<=p2;i++)ql[c[i]]=qr[c[i]]=i;
	for(int i=1;i<=n;i++)if(!vis[i]){
		int l=1,r=p2,res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(a[c[mid]]>a[i])l=mid+1,res=mid;
			else r=mid-1;
		}
		ql[i]=upper_bound(c+1,c+p2+1,i)-c,qr[i]=res;
	}
	for(int i=1;i<=p2;i++)vis[c[i]]=0;
	for(int i=1;i<=p1+1;i++)que[i].clear();
	for(int i=1;i<=n;i++)que[pl[i]].pb({ql[i],qr[i],1}),que[pr[i]+1].pb({ql[i],qr[i],-1});
	// for(int i=1;i<=n;i++)cout<<pl[i]<<" "<<pr[i]<<" "<<ql[i]<<" "<<qr[i]<<"\n";
	build(1,1,n);
	for(int i=1;i<=p1;i++){
		for(auto[l,r,w]:que[i])updata(1,1,n,l,r,w);
		ans=max(ans,query(1,1,n,ql[b[i]],qr[b[i]]));
	}
	printf("%lld\n",ans);
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