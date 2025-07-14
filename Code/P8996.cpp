// Problem: P8996 [CEOI2022] Abracadabra
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8996
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-08-12 18:53:27
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,q,a[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int tree[maxn<<2];
void updata(int nd,int l,int r,int p,int w){
	if(l==r){tree[nd]=w;return ;}
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=tree[ls]+tree[rs];
}
pii query(int nd,int l,int r,int w){
	if(l==r){return {l,w};}
	if(tree[ls]>=w)return query(ls,l,mid,w);
	else return query(rs,mid+1,r,w-tree[ls]);
}
vector<pii> que[maxn];int ans[maxn*5];
int st[maxn],tp,nxt[maxn],len[maxn],pos[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]]=i;
	a[n+1]=n+1;st[++tp]=n+1;
	for(int i=n;i;i--){
		while(a[st[tp]]<a[i])tp--;st[++tp]=i;
		nxt[i]=st[tp-1];
	}
	for(int i=1;i<=n/2;i=nxt[i]){
		len[i]=min(n/2,nxt[i]-1)-i+1;
		updata(1,1,n,a[i],len[i]);
	}
	for(int i=n/2+1;i<=n;i=nxt[i]){
		len[i]=nxt[i]-1-i+1;
		updata(1,1,n,a[i],len[i]);
	}
	for(int i=1;i<=q;i++){
		int t=read(),d=read();
		if(!t)ans[i]=a[d];
		else que[min(t,n)].push_back({i,d});
	}
	for(int t=1;t<=n;t++){
		for(auto[id,d]:que[t]){
			pii p=query(1,1,n,d);
			// cout<<p.fi<<" "<<p.se<<"\n";
			ans[id]=a[pos[p.fi]+p.se-1];
		}
		pii p=query(1,1,n,n/2);
		int lst=pos[p.fi],r=lst+len[lst]-1,x=lst+p.se;
		len[lst]=p.se;updata(1,1,n,p.fi,p.se);
		while(x<=r){
			len[x]=min(r,nxt[x]-1)-x+1;updata(1,1,n,a[x],len[x]);
			x=nxt[x];
		}
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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
