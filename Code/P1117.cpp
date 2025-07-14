// Problem: P1117 [NOI2016] 优秀的拆分
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1117
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2024-07-16 20:10:08
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=30010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans;
char s[maxn];
mt19937 rnd(1);
int bas,val[26],pw[maxn],hsh[maxn];
int calc(int l,int r){return (hsh[r]-hsh[l-1]*pw[r-l+1]%mod+mod)%mod;}
int f[maxn],g[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);ans=0;
	for(int i=1;i<=n;i++)hsh[i]=(hsh[i-1]*bas+val[s[i]-'a'])%mod;
	for(int i=0;i<=n;i++)f[i]=g[i]=0;
	for(int k=1;k<=n/2;k++){
		for(int i=k;i<=n-k;i+=k){
			int l=1,r=k,pre=0,suf=0;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(i-mid+1,i)==calc(i+k-mid+1,i+k))l=mid+1,pre=mid;
				else r=mid-1;
			}
			l=1,r=min(n-i-k+1,k);
			while(l<=r){
				int mid=l+r>>1;
				if(calc(i,i+mid-1)==calc(i+k,i+k+mid-1))l=mid+1,suf=mid;
				else r=mid-1;
			}
			// cout<<i<<" "<<k<<" "<<pre<<" "<<suf<<"\n";
			int L=i+k+k-pre,R=i+k+suf-1;
			if(L<=R)f[R]++,f[L-1]--;
			// cout<<L<<" "<<R<<" f\n";
			L=i-pre+1,R=i-k+suf;
			if(L<=R)g[R]++,g[L-1]--;
			// cout<<L<<" "<<R<<" g\n";
		}
	}
	for(int i=1;i<=n;i++)f[i]+=f[i-1],g[i]+=g[i-1];
	for(int i=1;i<n;i++)ans+=f[i]*g[i+1];
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
	
	bas=rnd()%mod;for(int i=0;i<26;i++)val[i]=rnd()%bas;
	pw[0]=1;for(int i=1;i<=maxn-10;i++)pw[i]=pw[i-1]*bas%mod;
	T=read();
	while(T--)work();
}
