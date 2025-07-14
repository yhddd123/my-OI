// Problem: P1667 数列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1667
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
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

int n,a[maxn];
int b[maxn],len,pos[maxn];
bool vis[maxn];
int fac[maxn],inv[maxn];
inline int ksm(int a,int b=mod-2){
	if(b<=0)return 1;
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int C(int m,int n){return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void work(){
	n=read();
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++)b[++len]=a[i]=a[i-1]+read();
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;
	if(len!=n){printf("-1\n");return ;}
	if(b[1]<=0||a[n]!=b[len]){printf("-1\n");return ;}
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=n;i++)pos[a[i]]=i;
	int num=0,ans=1;
	for(int i=1;i<=n;i++)if(!vis[i]){
		int x=i,len=0;
		while(!vis[x]){
			vis[x]=1;x=pos[x];
			++len;
		}
		ans*=ksm(len,len-2),ans%=mod;num+=len-1;
		ans*=C(num,len-1),ans%=mod;
	}
	printf("%lld\n",num);
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
