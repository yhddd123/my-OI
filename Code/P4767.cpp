// Problem: P4767 [IOI2000] 邮局 加强版
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4767
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-29 18:43:27
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
const int maxn=3010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,a[maxn];
int f[maxn],g[maxn],w[maxn][maxn];
void sovle(int l,int r,int ql,int qr){
	if(l>r)return ;
	int mid=l+r>>1,p=ql;
	for(int i=ql;i<=min(qr,mid-1);i++){
		if(f[mid]>g[i]+w[i][mid])f[mid]=g[i]+w[i][mid],p=i;
	}
	// cout<<mid<<" "<<f[mid]<<" "<<p<<"\n";
	sovle(l,mid-1,ql,p),sovle(mid+1,r,p,qr);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();a[++n]=inf;m++;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		for(int j=i+1,k=i,sum=-a[i];j<=n;j++){
			sum+=-a[j];
			while(a[j]-a[k]>a[k]-a[i]){
				sum+=a[k];sum+=a[k]-a[i];
				k++;
			}
			w[i][j]=(j-k+1)*a[j]+sum;
			// cout<<i<<" "<<j<<" "<<k<<" "<<w[i][j]<<"\n";
		}
	}
	for(int i=1,sum=0;i<=n;i++){
		sum+=-a[i];
		f[i]=sum+i*a[i];
		// cout<<f[i]<<" ";
	}
	// cout<<"\n";
	for(int j=2;j<=m;j++){
		for(int i=1;i<=n;i++)g[i]=f[i],f[i]=inf;
		sovle(1,n,1,n);
		// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
	}
	printf("%lld\n",f[n]);
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
