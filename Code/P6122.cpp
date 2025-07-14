#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
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

int n,m,a[maxn],ans;
int f[maxn],g[maxn];
int flow[maxn];
int ls(int u){return u<<1;}
int rs(int u){return u<<1|1;}
int dw(int u){
	return flow[u]<0?-1:1;
}
int up(int u){
	return flow[u]>0?-1:1;
}
void updata(int u){
	f[u]=inf;
	if(a[u])f[u]=0,g[u]=u;
	if(ls(u)<=n){
		if(f[ls(u)]+dw(ls(u))<f[u])f[u]=f[ls(u)]+dw(ls(u)),g[u]=g[ls(u)];
	}
	if(rs(u)<=n){
		if(f[rs(u)]+dw(rs(u))<f[u])f[u]=f[rs(u)]+dw(rs(u)),g[u]=g[rs(u)];
	}
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i;i--)updata(i);
	while(m--){
		int p=read(),mn=inf,pos=0;
		for(int u=p,val=0;u;val+=up(u),u>>=1){
			if(val+f[u]<mn)mn=val+f[u],pos=u;
		}
		ans+=mn;
		for(int u=p;u!=pos;u>>=1)flow[u]--,updata(u);
		a[g[pos]]--;
		for(int u=g[pos];u!=pos;u>>=1)flow[u]++,updata(u);
		for(int u=pos;u;u>>=1)updata(u);
		printf("%lld ",ans);
	}
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
