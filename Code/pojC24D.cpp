// Problem: C24D:Number Solidity
// Contest: OpenJudge - PKU Online Judge - 练习
// URL: http://poj.openjudge.cn/practice/C24D?lang=en_US
// Memory Limit: 512 MB
// Time Limit: 15000 ms
// Written by yhm.
// Start codeing:2024-07-12 08:41:32
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll __int128
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=10000010;
const int inf=1e18;
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
inline void write(ll x){if(x>9)write(x/10);putchar(x%10+'0');}
bool Mbe;

ll n,ans;
int pre[maxn],cnt;
bool vis[maxn];
void init(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;
			if(i%pre[j]==0)break;
		}
	}
}
void work(){
	n=read();init(maxn-10);
	for(int i=1;i<=cnt;i++){
		if(pre[i]*pre[i]>n)break;
		for(int j=1;j<=i;j++){
			ll num=1;
			for(int k=1;k<=pre[j];k++){
				num*=pre[i];
				if(num>n)break;
			}
			if(num>n)break;
			ll bas=num;
			if(i!=j)num*=pre[j];
			while(num<=n){
				for(int s=0;s<(1<<j-1);s++){
					ll mul=num;
					for(int k=1;k<j;k++)if(s&(1<<k-1))mul*=pre[k];
					ans+=((__builtin_popcount(s)&1)?-1:1)*(n/mul);
				}
				num*=bas;
			}	
		}
	}
	write(ans);
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
