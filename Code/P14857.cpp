// Problem: P14857 [ICPC 2021 Yokohama R] Planning Railroad Discontinuation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14857
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-02-03 15:02:25
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,l,k,ans;
int a[maxn],b[maxn];
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
bool vis[maxn];
int id[maxn];
int tim[maxn],val[maxn],cnt;
void work(){
	n=read();m=read();
	vector<tuple<int,int,int>> edge;
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1,w=read();
		edge.pb({w,u,v});
	}
	sort(edge.begin(),edge.end());
	l=read();
	for(int i=0;i<l;i++)a[i]=read(),b[i]=read();
	k=read();
	for(int i=1;i<=k;i++)vis[read()+1]=1;
	for(int i=1;i<=n;i++)ff[i]=i;
	int sum=0;
	for(auto[w,u,v]:edge){
		u=fd(u),v=fd(v);
		if(u==v)continue;
		if(vis[u]&&vis[v])tim[++cnt]=w,val[cnt]=val[cnt-1]+w;
		ff[v]=u;vis[u]|=vis[v];sum+=w;
	}
	for(int i=0;i<l;i++)ans+=b[i]*(n-1)+sum;
	for(int i=0;i<l;i++)id[i]=i;
	for(int i=0;i<l;i++)ff[i]=i;
	sort(id,id+l,[&](int u,int v){return a[u]<a[v];});
	// cout<<ans<<" "<<sum<<"\n";
	for(int ii=0;ii<l-1;ii++){
		int i=id[ii];
		int u=fd(i),v=fd((i+1)%l);
		if(b[u]>b[v])swap(u,v);
		ff[v]=u;
		int t=a[i]-b[v];
		int p=lower_bound(tim+1,tim+cnt+1,t)-tim-1;
		// cout<<i<<" "<<u<<" "<<v<<" "<<p<<"\n";
		ans-=(cnt-p)*b[v]+val[cnt]-val[p];
		ans+=(k-p)*a[i];
	}
	printf("%lld\n",ans);
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