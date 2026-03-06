#include<bits/stdc++.h>
#define int long long
#define mod 998244353
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

int n,ans;
int a[maxn],b[maxn],c[maxn],d[maxn];
int id[maxn];
bitset<maxn> f[maxn],vis;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
	for(int i=1;i<=n;i++)id[i]=i,f[i].set();
	sort(id+1,id+n+1,[&](int x,int y){return a[x]<a[y];});
	for(int i=1;i<=n;i++){
		int x=id[i];
		f[x]&=vis;
		vis[x]=1;
	}
	sort(id+1,id+n+1,[&](int x,int y){return b[x]<b[y];});
	vis.reset();
	for(int i=1;i<=n;i++){
		int x=id[i];
		f[x]&=vis;
		vis[x]=1;
	}
	sort(id+1,id+n+1,[&](int x,int y){return c[x]<c[y];});
	vis.reset();
	for(int i=1;i<=n;i++){
		int x=id[i];
		f[x]&=vis;
		vis[x]=1;
	}
	sort(id+1,id+n+1,[&](int x,int y){return d[x]<d[y];});
	vis.reset();
	for(int i=1;i<=n;i++){
		int x=id[i];
		f[x]&=vis;
		vis[x]=1;
	}
	for(int i=1;i<=n;i++)ans+=f[i].count();
	printf("%lld\n",ans);
}

bool med;
signed main(){
	// freopen("A.in","r",stdin);
	// freopen("A.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<" Mb\n";
	
	int T=1;
	while(T--)work();
}
