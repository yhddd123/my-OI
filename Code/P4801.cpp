// Problem: P4801 [CCO2015] 饥饿的狐狸
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4801
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-04-28 18:27:56
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

int n,m,a[maxn],ans;
int calc(int op){
	int l=1,r=n,p=m,res=0;
	for(int i=1;i<=n;i++){
		if((i&1)==op)res+=max(abs(m-a[l]),abs(p-a[l])),p=a[l++];
		else res+=max(abs(m-a[r]),abs(p-a[r])),p=a[r--];
	}
	return res;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	ans=max(0ll,m-a[1])+max(0ll,a[n]-m);
	printf("%lld ",ans);ans=0;
	ans=max(calc(0),calc(1));
	printf("%lld",ans);
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
