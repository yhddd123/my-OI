// Problem: P7747 [COCI2011-2012#3] TRAKA
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7747
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-09 19:53:25
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

int n,m,a[maxn],b[maxn];
int q[maxn],t,ans;
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=a[i-1]+read();
	for(int i=1;i<=m;i++)b[i]=read();
	if(n==1){
		for(int i=1;i<=m;i++)ans+=a[1]*b[i];
		printf("%lld\n",ans);
		return ;
	}
	for(int i=1;i<=n;i++){
		while(t>1&&(a[i]-a[q[t]])*(a[q[t]-1]-a[q[t-1]-1])>(a[q[t]]-a[q[t-1]])*(a[i-1]-a[q[t]-1]))t--;
		q[++t]=i;
	}
	// for(int i=1;i<=t;i++)cout<<q[i]<<" ";cout<<"\n";
	// for(int i=2;i<=t;i++)cout<<1.0*(a[q[i]]-a[q[i-1]])/(a[q[i]-1]-a[q[i-1]-1])<<"\n";
	int ans=0;
	for(int i=2;i<=m;i++){
		int l=2,r=t,res=1;
		while(l<=r){
			int mid=l+r>>1;
			if((a[q[mid]]-a[q[mid-1]])*b[i-1]>b[i]*(a[q[mid]-1]-a[q[mid-1]-1]))l=mid+1,res=mid;
			else r=mid-1;
		}
		ans+=a[q[res]]*b[i-1]-a[q[res]-1]*b[i];
		// cout<<i<<" "<<res<<"\n";
	}
	ans+=a[n]*b[m];
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
