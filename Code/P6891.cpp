// Problem: ビルの飾りつけ 4 (Building 4)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_joisc2020_a
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// Written by yhm.
// Start codeing:2024-07-07 18:49:13
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
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],b[maxn];
pii dp[maxn][2];
void merge(pii &u,pii v){u.fi=min(u.fi,v.fi),u.se=max(u.se,v.se);}
bool in(int i,int fl,int x){return dp[i][fl].fi<=x&&dp[i][fl].se>=x;}
bool ans[maxn];
void work(){
	n=read()<<1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++){
		dp[i][0]=dp[i][1]={2*n+1,0};
		if(a[i]>=a[i-1]){
			merge(dp[i][0],{dp[i-1][0].fi+1,dp[i-1][0].se+1});
		}
		if(a[i]>=b[i-1]){
			merge(dp[i][0],{dp[i-1][1].fi+1,dp[i-1][1].se+1});
		}
		if(b[i]>=a[i-1]){
			merge(dp[i][1],{dp[i-1][0].fi,dp[i-1][0].se});
		}
		if(b[i]>=b[i-1]){
			merge(dp[i][1],{dp[i-1][1].fi,dp[i-1][1].se});
		}
	}
	if(in(n,0,n>>1)){
		for(int i=n,fl=0,num=n>>1;i;i--){
			ans[i]=fl;
			if(!fl&&a[i]>=a[i-1]&&in(i-1,0,num-1))num--;
			else if(!fl&&a[i]>=b[i-1]&&in(i-1,1,num-1))fl=1,num--;
			else if(fl&&b[i]>=a[i-1]&&in(i-1,0,num))fl=0;
		}
		for(int i=1;i<=n;i++)ans[i]?printf("B"):printf("A");
	}
	else if(in(n,1,n>>1)){
		for(int i=n,fl=1,num=n>>1;i;i--){
			ans[i]=fl;
			if(!fl&&a[i]>=a[i-1]&&in(i-1,0,num-1))num--;
			else if(!fl&&a[i]>=b[i-1]&&in(i-1,1,num-1))fl=1,num--;
			else if(fl&&b[i]>=a[i-1]&&in(i-1,0,num))fl=0;
		}
		for(int i=1;i<=n;i++)ans[i]?printf("B"):printf("A");
	}
	else puts("-1");
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
