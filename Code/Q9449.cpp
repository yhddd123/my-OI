#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=10010;
const int maxm=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int f[maxn<<1],siz[maxn<<1];
pii a[maxm];
int fd(int x,bool fl=0){
	if(f[x]==x)return x;
	if(fl)return fd(f[x]);
	return f[x]=fd(f[x]);
}
bool vis[maxn];
int b[maxn],k,t[maxn<<1];
bitset<maxn> dp,g[maxn];
void work(){
	n=read()<<1;m=read();
	for(int i=1;i<=n*2;i++)f[i]=i,siz[i]=(i<=n);
	for(int i=1;i<=m;i++)a[i]={read(),read()};
	for(int i=m;i;i--){
		int u=a[i].fi,v=a[i].se;
		int uu=fd(u+n),vv=fd(v+n);u=fd(u),v=fd(v);
		if(u==v)continue;
		if(u==vv)continue;
		for(int j=0;j<=n;j++)t[j]=0;k=0;
		for(int j=1;j<=2*n;j++)f[j]=fd(j);
		siz[u]+=siz[vv],f[vv]=u;
		siz[v]+=siz[uu],f[uu]=v;
		for(int j=1;j<=n;j++)if(fd(j,1)==j&&fd(j+n,1)>j)t[abs(siz[j]-siz[fd(j+n,1)])]++;
		// for(int j=1;j<=n;j++)cout<<t[j]<<" ";cout<<"\n";
		for(int j=1;j<=n;j++)if(t[j]){
			for(int l=1;l<=t[j];l<<=1){
				b[++k]=j*l;
				t[j]-=l;
			}
			if(t[j])b[++k]=j*t[j];
		}
		dp.reset();dp[n/2]=1;
		for(int j=1;j<=k;j++)dp=(dp<<b[j])|(dp>>b[j]);
		// cout<<k<<" ";for(int j=1;j<=k;j++)cout<<b[j]<<" ";cout<<"\n";
		if(!dp[n/2]){
			siz[u]-=siz[vv],f[vv]=vv;
			siz[v]-=siz[uu],f[uu]=uu;
			siz[u]+=siz[v],f[v]=u;
			if(uu<=n)siz[uu]+=siz[vv],f[vv]=uu;
			else siz[vv]+=siz[uu],f[uu]=vv;
			// cout<<"0\n";
		}
		// cout<<i<<"\n";
		// for(int j=1;j<=n;j++)if(fd(j)==j)cout<<j<<" "<<siz[j]<<"\n";
	}
	// for(int i=1;i<=2*n;i++)if(fd(i)==i)cout<<fd(i)<<" "<<siz[fd(i)]<<"\n";
	g[0][n/2]=1;
	for(int i=1;i<=n;i++){
		if(fd(i)==i&&fd(i+n)>i){
			g[i]=(g[i-1]<<abs(siz[i]-siz[fd(i+n)]))|(g[i-1]>>abs(siz[i]-siz[fd(i+n)]));
		}
		else g[i]=g[i-1];
	}
	int x=n/2;
	for(int i=n;i;i--)if(fd(i)==i&&fd(i+n)>i){
		if(x>=abs(siz[i]-siz[fd(i+n)])&&g[i-1][x-abs(siz[i]-siz[fd(i+n)])]){
			x-=abs(siz[i]-siz[fd(i+n)]);
			if(siz[i]>=siz[fd(i+n)])vis[i]=1;
			else vis[fd(i+n)]=1;
		}
		else{
			x+=abs(siz[i]-siz[fd(i+n)]);
			if(siz[i]>siz[fd(i+n)])vis[fd(i+n)]=1;	
			else vis[i]=1;
		}
	}
	// for(int i=1;i<=n;i++)cout<<vis[i]<<" ";cout<<"\n";
	// int num=0;
	// for(int i=1;i<=n;i++){
		// if(vis[fd(i)])++num;
		// else --num;
	// }
	// cout<<num<<"\n";
	// if(num)return ;
	for(int i=1;i<=n;i++){
		if(vis[fd(i)])putchar('0');
		else putchar('1');
	}
	// puts("ac");
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
	// freopen("1.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}