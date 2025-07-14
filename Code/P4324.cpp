// Problem: P4324 [JSOI2016] 扭动的回文串
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4324
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-05-15 16:49:18
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

int n,ans;
char s[maxn],t[maxn];
int bas,val[27],f[2][maxn],g[2][maxn],pw[maxn];
int calc(int fl,int op,int l,int r){
	if(fl==0&&op==0)return (f[0][r]-f[0][l-1]*pw[r-l+1]%mod+mod)%mod;
	if(fl==0&&op==1)return (f[1][l]-f[1][r+1]*pw[r-l+1]%mod+mod)%mod;
	if(fl==1&&op==0)return (g[0][r]-g[0][l-1]*pw[r-l+1]%mod+mod)%mod;
	if(fl==1&&op==1)return (g[1][l]-g[1][r+1]*pw[r-l+1]%mod+mod)%mod;
}
void work(){
	n=read();scanf("%s%s",s+1,t+1);
	srand(time(0));bas=rand()*rand()%mod;
	for(int i=0;i<27;i++)val[i]=rand()*rand()%mod;
	// bas=10;for(int i=0;i<27;i++)val[i]=i+1;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	for(int i=1;i<=n;i++)f[0][i]=(f[0][i-1]*bas+val[s[i]-'A'])%mod;
	for(int i=n;i>=1;i--)f[1][i]=(f[1][i+1]*bas+val[s[i]-'A'])%mod;
	for(int i=1;i<=n;i++)g[0][i]=(g[0][i-1]*bas+val[t[i]-'A'])%mod;
	for(int i=n;i>=1;i--)g[1][i]=(g[1][i+1]*bas+val[t[i]-'A'])%mod;
	// for(int i=1;i<=n;i++)cout<<f[0][i]<<" "<<f[1][i]<<" "<<g[0][i]<<" "<<g[1][i]<<"\n";
	for(int i=1;i<=n;i++){
		int l=1,r=min(i,n-i+1),res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(calc(0,0,i-mid+1,i)==calc(0,1,i,i+mid-1))res=mid,l=mid+1;
			else r=mid-1;
		}
		ans=max(ans,res*2-1);
		int p1=i-res,p2=i+res-1,lst=res;
		if(p1){
			l=1,r=min(p1,n-p2+1),res=0;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(0,0,p1-mid+1,p1)==calc(1,1,p2,p2+mid-1))res=mid,l=mid+1;
				else r=mid-1;
			}
			ans=max(ans,(lst+res)*2-1);
		}
		
		l=1,r=min(i,n-i+1),res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(calc(1,0,i-mid+1,i)==calc(1,1,i,i+mid-1))res=mid,l=mid+1;
			else r=mid-1;
		}
		ans=max(ans,res*2-1);
		p1=i-res+1,p2=i+res,lst=res;
		if(p2<=n){
			l=1,r=min(p1,n-p2+1),res=0;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(0,0,p1-mid+1,p1)==calc(1,1,p2,p2+mid-1))res=mid,l=mid+1;
				else r=mid-1;
			}
			ans=max(ans,(lst+res)*2-1);
		}
		// cout<<i<<" "<<ans<<"\n";
		
		l=1,r=min(i,n-i+1),res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(calc(0,0,i-mid+1,i)==calc(1,1,i,i+mid-1))res=mid,l=mid+1;
			else r=mid-1;
		}
		ans=max(ans,res*2);
		
		if(i==n)break;
		if(s[i]==s[i+1]){
			l=1,r=min(i,n-i),res=0;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(0,0,i-mid+1,i)==calc(0,1,i+1,i+mid))res=mid,l=mid+1;
				else r=mid-1;
			}
			ans=max(ans,res*2);
			p1=i-res,p2=i+res,lst=res;
			if(p1){
				l=1,r=min(p1,n-p2+1),res=0;
				while(l<=r){
					int mid=l+r>>1;
					if(calc(0,0,p1-mid+1,p1)==calc(1,1,p2,p2+mid-1))res=mid,l=mid+1;
					else r=mid-1;
				}
				ans=max(ans,(lst+res)*2);
			}
		}
		if(t[i]==t[i+1]){
			l=1,r=min(i,n-i),res=0;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(1,0,i-mid+1,i)==calc(1,1,i+1,i+mid))res=mid,l=mid+1;
				else r=mid-1;
			}
			ans=max(ans,res*2);
			p1=i-res+1,p2=i+res+1,lst=res;
			if(p2<=n){
				l=1,r=min(p1,n-p2+1),res=0;
				while(l<=r){
					int mid=l+r>>1;
					if(calc(0,0,p1-mid+1,p1)==calc(1,1,p2,p2+mid-1))res=mid,l=mid+1;
					else r=mid-1;
				}
				ans=max(ans,(lst+res)*2);
			}
		}
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
