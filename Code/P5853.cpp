// Problem: P5853 [USACO19DEC] Tree Depth P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5853
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
const int maxn=90010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,mod;
int f[maxn],sum[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int incc(int u,int v){
	((u+=v)>=mod)&&(u-=mod);
	return u;
}
void add(int u){
	sum[0]=f[0];for(int i=1;i<=k;i++)sum[i]=incc(sum[i-1],f[i]);
	for(int i=0;i<=k;i++){
		if(i-u-1<0)f[i]=sum[i];
		else f[i]=incc(sum[i],mod-sum[i-u-1]);
	}
}
void del(int u){
	for(int i=0;i<=k;i++){
		if(i-u-1<0)sum[i]=f[i];
		else sum[i]=incc(f[i],sum[i-u-1]);
	}
	f[0]=sum[0];for(int i=1;i<=k;i++)f[i]=incc(sum[i],mod-sum[i-1]);
}
int ans[maxn];
void dp(){
	f[0]=1;for(int i=1;i<=k;i++)f[i]=0;
	for(int i=1;i<=n;i++)add(i-1);
	for(int i=1;i<n;i++){
		del(i);
		for(int j=i+1;j<=n;j++)inc(ans[j],f[k]);
		add(i);
	}
}
void work(){
	n=read();k=read();mod=read();
	dp();
	// for(int i=1;i<=n;i++)cout<<ans[i]<<" ";cout<<"\n";
	k=n*(n-1)/2-k;reverse(ans+1,ans+n+1);dp();
	reverse(ans+1,ans+n+1);
	// for(int i=1;i<=n;i++)cout<<ans[i]<<" ";cout<<"\n";cout<<f[k]<<"\n";
	for(int i=1;i<=n;i++)printf("%lld ",incc(ans[i],f[k]));
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
