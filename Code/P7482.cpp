// Problem: P7482 不条理狂诗曲
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7482
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,a[maxn],ans;
int f[maxn][2],g[maxn];
int b[maxn],len,sum[maxn];
void sovle(int l,int r){
	if(l==r){
		(ans+=a[l])%=mod;
		return ;
	}
	int mid=l+r>>1;
	f[mid][0]=0,f[mid][1]=a[mid];
	if(mid-1>=l)f[mid-1][0]=a[mid-1],f[mid-1][1]=max(a[mid-1],a[mid]);
	for(int i=mid-2;i>=l;i--){
		f[i][0]=max(f[i+1][0],f[i+2][0]+a[i]);
		f[i][1]=max(f[i+1][1],f[i+2][1]+a[i]);
	}
	f[mid+1][0]=0,f[mid+1][1]=a[mid+1];
	if(mid+2<=r)f[mid+2][0]=a[mid+2],f[mid+2][1]=max(a[mid+2],a[mid+1]);
	for(int i=mid+3;i<=r;i++){
		f[i][0]=max(f[i-1][0],f[i-2][0]+a[i]);
		f[i][1]=max(f[i-1][1],f[i-2][1]+a[i]);
	}
	int sl=0,sr=0;
	for(int i=l;i<=mid;i++)(sl+=f[i][0])%=mod;
	for(int i=mid+1;i<=r;i++)(sr+=f[i][0])%=mod;
	(ans+=sl*(r-mid)+sr*(mid-l+1))%=mod;
//	cout<<l<<" "<<r<<" "<<ans<<"\n"; 
	for(int i=l;i<=r;i++)g[i]=f[i][1]-f[i][0];
	len=0; 
	for(int i=mid+1;i<=r;i++)b[++len]=g[i];
	sort(b+1,b+len+1);sum[len+1]=0;
	for(int i=len;i>=1;i--)sum[i]=(sum[i+1]+b[i]%mod+mod)%mod;
	for(int i=l;i<=mid;i++){
		int p=upper_bound(b+1,b+len+1,g[i])-b;
		(ans+=(g[i]%mod+mod)*(p-1)+sum[p])%=mod;
//		cout<<i<<" "<<g[i]<<" "<<p<<" "<<sum[p]<<"\n";
	}
	sovle(l,mid),sovle(mid+1,r);
}
void sovle(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sovle(1,n);printf("%lld\n",ans);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	T=1;
	while(T--)sovle();
}