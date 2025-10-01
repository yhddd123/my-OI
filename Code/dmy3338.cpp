#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
#define mkp make_pair
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=100010;
const int inf=2e9;
bool mbe;

int n,q;
pii a[maxn];
int dp[maxn][2],sum[maxn];
#define all 1,0,n
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct sgt{
	int mn[maxn<<2];
	void build(int nd,int l,int r){
	    mn[nd]=inf;
	    if(l==r)return ;
	    build(ls,l,mid),build(rs,mid+1,r);
	}
	void modif(int nd,int l,int r,int p,int w){
		mn[nd]=min(mn[nd],w);
	    if(l==r)return ;
	    if(p<=mid)modif(ls,l,mid,p,w);
	    else modif(rs,mid+1,r,p,w);
	}
	int query(int nd,int l,int r,int ql,int qr){
		if(ql>qr)return inf;
	    if(l>=ql&&r<=qr)return mn[nd];
	    if(qr<=mid)return query(ls,l,mid,ql,qr);
	    if(ql>mid)return query(rs,mid+1,r,ql,qr);
	    return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}t[2][3];
void upd(int i,int op,int w){
	if(dp[i][op]<=w)return ;
	dp[i][op]=w;
	t[op][0].modif(all,i,w-sum[i]),t[op][1].modif(all,i,w),t[op][2].modif(all,i,w+sum[i]);
}
int que(int i,int op){
	return min({t[op][0].query(all,0,i-1)+sum[i],dp[i][op],t[op][2].query(all,i+1,n)-sum[i]});
}
int que(int l,int r,int op){
	return min({t[op][0].query(all,0,l-1)+sum[l],t[op][1].query(all,l,r),t[op][2].query(all,r+1,n)-sum[r]});
}
int que1(int l,int r,int op){
	return min({t[op][0].query(all,0,l-1),t[op][0].query(all,l,r),t[op][2].query(all,r+1,n)-2*sum[r]});
}
void init(){
	t[0][0].build(all),t[0][1].build(all),t[0][2].build(all);
	t[1][0].build(all),t[1][1].build(all),t[1][2].build(all);
}
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	sort(a+1,a+n+1);a[n+1].fi=2e9;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i].se;
	while(q--){
		int k=read();
		init();
		memset(dp,0x3f,sizeof(dp));
		upd(0,0,0),upd(0,1,0);
		for(int i=1;i<=n;i++){
			int pl=upper_bound(a+1,a+n+1,mkp(a[i].fi-k,inf))-a-1,pr=upper_bound(a+1,a+n+1,mkp(a[i+1].fi-k-1,inf))-a-1;
			// cout<<i<<" "<<pl<<" "<<pr<<"\n";
			if(pl<=pr){
				upd(i,0,que1(pl,pr,1)+sum[i]);
				upd(i,1,que(pl,pr,0));
			}
			// if(a[i+1].fi-a[i].fi>k)upd(i,0,que(i,1));
			int p=upper_bound(a+1,a+n+1,mkp(a[i+1].fi-k-1,inf))-a-1;
			// cout<<i<<" "<<p<<" "<<que(i,1)<<" "<<sum[i]-sum[p]<<"\n";
			if(p<=i)upd(p,0,que(i,1)+sum[i]-sum[p]);
		}
		// for(int i=1;i<=n;i++)cout<<dp[i][0]<<" "<<dp[i][1]<<"\n";R
		printf("%d\n",min(que(n,0),que(n,1)));
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