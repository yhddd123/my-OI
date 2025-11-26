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

int n,a[maxn],b[maxn],c[maxn],d[maxn];
int id[maxn],ans;
bitset<maxn> f[maxn],g;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	for(int i=1;i<=n;i++)f[i].set();
	for(int i=1;i<=n;i++){
		f[id[i]]&=g;
		g.set(id[i]);
	}
	g.reset();
	sort(id+1,id+n+1,[&](int u,int v){return b[u]<b[v];});
	for(int i=1;i<=n;i++){
		f[id[i]]&=g;
		g.set(id[i]);
	}
	g.reset();
	sort(id+1,id+n+1,[&](int u,int v){return c[u]<c[v];});
	for(int i=1;i<=n;i++){
		f[id[i]]&=g;
		g.set(id[i]);
	}
	g.reset();
	sort(id+1,id+n+1,[&](int u,int v){return d[u]<d[v];});
	for(int i=1;i<=n;i++){
		f[id[i]]&=g;
		g.set(id[i]);
	}
	g.reset();
	for(int i=1;i<=n;i++)ans+=f[i].count();
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