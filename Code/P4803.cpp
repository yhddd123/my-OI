// Problem: P4803 [CCO2015] 太阳能飞行
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4803
// Memory Limit: 250 MB
// Time Limit: 15000 ms
// Written by yhm.
// Start codeing:2024-09-19 14:25:59
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
const int maxn=2010;
const int inf=1e18;
const db eps=1e-9;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(long long x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
bool Mbe;

int n,q,ans,k,m;
db a[maxn],b[maxn];
int w[maxn],val[maxn],f[maxn],len[maxn];
db lsh[maxn][maxn],pos[maxn],v[maxn];
struct seg{
	#define mid (l+r>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	int tree[maxn<<2];
	void build(int nd,int l,int r){
		if(l==r){tree[nd]=f[l];return ;}
		build(ls,l,mid),build(rs,mid+1,r);
		tree[nd]=max(tree[ls],tree[rs]);
	}
	int query(int nd,int l,int r,int ql,int qr){
		if(ql>qr)return 0;
		if(l>=ql&&r<=qr)return tree[nd];
		if(qr<=mid)return query(ls,l,mid,ql,qr);
		if(ql>mid)return query(rs,mid+1,r,ql,qr);
		return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
	}
}t[maxn];
void work(){
	m=read();k=read();n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),w[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j){
				pos[j]=v[j]=0;
				continue;
			}
			if(a[i]<=a[j]&&b[i]<b[j]){
				val[i]+=w[j];
				pos[j]=v[j]=0;
				continue;
			}
			if(a[i]>=a[j]&&b[i]>=b[j]){
				pos[j]=v[j]=0;
				continue;
			}
			if(b[i]==b[j]){
				val[i]+=w[j],pos[j]=m,v[j]=-w[j];
				continue;
			}
			pos[j]=1.0*m*abs(a[i]-a[j])/(abs(a[i]-a[j])+abs(b[i]-b[j]));
			if(a[i]>a[j])v[j]=w[j];
			else val[i]+=w[j],v[j]=-w[j];
		}
		for(int j=1;j<=n;j++)lsh[i][j]=pos[j],f[j]=0;
		sort(lsh[i]+1,lsh[i]+n+1);len[i]=unique(lsh[i]+1,lsh[i]+n+1)-lsh[i]-1;
		for(int j=1;j<=n;j++){
			int p=lower_bound(lsh[i]+1,lsh[i]+len[i]+1,pos[j])-lsh[i];
			f[p]+=v[j];
		}
		for(int j=1;j<=len[i];j++)f[j]+=f[j-1];
		t[i].build(1,1,len[i]);
	}
	while(q--){
		int p=read(),l=read(),r=l+k;
		l=upper_bound(lsh[p]+1,lsh[p]+len[p]+1,l)-lsh[p]-1;
		r=lower_bound(lsh[p]+1,lsh[p]+len[p]+1,r)-lsh[p]-1;
		ans=t[p].query(1,1,len[p],l,r)+val[p];
		write(ans);puts("");
	}
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("seg.in","r",stdin);
	// freopen("seg.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
