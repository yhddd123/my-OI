#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn=3010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,b,ans;
char a[maxn][maxn];
int f[maxn<<1],siz[maxn<<1],num[maxn<<1],val[maxn<<1],sum[maxn<<1],mn[maxn<<1],d[maxn<<1];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void work(){
	n=read();m=read();k=read();b=read();
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n+m;i++)f[i]=i,siz[i]=1,mn[i]=inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]=='b'){
			d[i]++,d[j+n]++;
			int u=fd(i),v=fd(j+n);
			if(siz[u]<siz[v])swap(u,v);
			num[u]++;
			if(u==v)continue;
			f[v]=u,siz[u]+=siz[v],num[u]+=num[v];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(a[i][j]=='k'){
			int u=fd(i),v=fd(j+n);
			if(u==v)sum[u]++;
			else sum[u]++,sum[v]++,val[i]++,val[j+n]++;
		}
	}
	for(int i=1;i<=n+m;i++)if(d[i]==1)mn[fd(i)]=min(mn[fd(i)],val[i]);
	for(int i=1;i<=n+m;i++)if(i==fd(i)){
		if(siz[i]==num[i]+1)ans=max(ans,sum[i]-mn[i]);
		else ans=max(ans,sum[i]);
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
