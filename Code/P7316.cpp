// Problem: P7316 [COCI2018-2019#3] NLO
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7316
// Memory Limit: 64 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-09-11 16:46:37
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
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,ans;
int x[maxn],y[maxn],z[maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
int tree[maxn<<2],tag[maxn<<2],laz[maxn<<2];
void add(int nd,int l,int r,int w){
	tree[nd]+=w*(r-l+1);
	if(~laz[nd])laz[nd]+=w;
	else tag[nd]+=w;
}
void cov(int nd,int l,int r,int w){
	tree[nd]=w*(r-l+1);
	laz[nd]=w;tag[nd]=0;
}
void down(int nd,int l,int r){
	if(~laz[nd])cov(ls,l,mid,laz[nd]),cov(rs,mid+1,r,laz[nd]),laz[nd]=-1;
	if(tag[nd])add(ls,l,mid,tag[nd]),add(rs,mid+1,r,tag[nd]),tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		add(nd,l,r,w);
		return ;
	}
	down(nd,l,r);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
void modif(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		cov(nd,l,r,w);
		return ;
	}
	down(nd,l,r);
	if(ql<=mid)modif(ls,l,mid,ql,qr,w);
	if(qr>mid)modif(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=k;i++)x[i]=read(),y[i]=read(),z[i]=read();
	for(int i=1;i<=n;i++){
		modif(1,1,m,1,m,0);
		for(int j=1;j<=k;j++){
			updata(1,1,m,1,m,1);
			if(z[j]*z[j]-(i-x[j])*(i-x[j])>=0){
				int s=sqrt(z[j]*z[j]-(i-x[j])*(i-x[j]));
				int l=y[j]-s,r=y[j]+s;
				// cout<<j<<" "<<l<<" "<<r<<endl;
				modif(1,1,m,l,r,0);
			}
			// cout<<j<<" "<<tree[1]<<endl;
		}
		ans+=tree[1];
		// cout<<i<<" "<<ans<<"\n";
	}
	printf("%lld\n",ans);
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
