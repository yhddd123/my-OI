// Problem: P9338 [JOISC 2023 Day3] Chorus
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9338
// Memory Limit: 1 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2024-09-03 10:28:01
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
const int maxn=2000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k;
char ss[maxn];
int f[maxn],dp[maxn];
int c[maxn],s[maxn],p[maxn];
int q[maxn],h,t;
int Y(int x){return dp[x]-s[p[x]-1]+x*p[x]-x;}
int val(int x,int u){return s[u]-u*x+Y(x);}
bool check(int x){
	h=t=0;
	for(int i=1;i<=n;i++){
		while(h<t&&val(q[h+1],i)<val(q[h],i))h++;
		int j=q[h];f[i]=f[j]+1,dp[i]=val(j,i)+x;
		while(h<t&&(Y(q[t])-Y(q[t-1]))*(i-q[t])>(Y(i)-Y(q[t]))*(q[t]-q[t-1]))t--;
		q[++t]=i;
	}
	return f[n]<=k;
}
void work(){
	n=read();k=read();scanf("%s",ss+1);
	for(int i=1,num=0,cnt=0;i<=2*n;i++){
		if(ss[i]=='A')c[++num]=cnt,s[num]=s[num-1]+c[num];
		else ++cnt;
	}
	for(int i=1;i<=n;i++)p[i]=max(i+1,(int)(lower_bound(c+1,c+n+1,i)-c));
	int l=0,r=inf,res=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	check(res);
	// cout<<f[n]<<" "<<dp[n]<<" "<<res<<"\n";
	printf("%lld\n",dp[n]-k*res);
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
