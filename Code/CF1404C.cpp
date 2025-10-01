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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2],mn[maxn<<2],tag[maxn<<2];
void upd(int nd,int w){mx[nd]+=w,mn[nd]+=w,tag[nd]+=w;}
void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]=0;}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr)return upd(nd,w);
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mx[nd]=max(mx[ls],mx[rs]);
	mn[nd]=min(mn[ls],mn[rs]);
}
int query(int nd,int l,int r,int p){
	if(l==r)return mx[nd];
	if(tag[nd])down(nd);
	if(p<=mid)return query(ls,l,mid,p);
	else return query(rs,mid+1,r,p);
}
int find(int nd,int l,int r,int w){
	// cout<<l<<" "<<r<<" "<<mx[nd]<<" "<<w<<"\n";
	if(mx[nd]<w)return l-1;
	if(l==r)return l;
	if(tag[nd])down(nd);
	if(mn[ls]>=w)return find(rs,mid+1,r,w);
	return find(ls,l,mid,w);
}
vector<pii> ask[maxn];
int ans[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++){
		int v=read();
		if(i-v<0)a[i]=n;
		else a[i]=i-v;
	}
	for(int i=1;i<=q;i++){
		int l=read()+1,r=n-read();
		ask[r].pb({l,i});
	}
	for(int i=1;i<=n;i++){
		int p=min(i,find(1,1,n,a[i]));
		// cout<<i<<" "<<a[i]<<" "<<p<<"\n";
		updata(1,1,n,1,p,1);
		for(auto[l,id]:ask[i])ans[id]=query(1,1,n,l);
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen("delete.in","r",stdin);
	// freopen("delete.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}