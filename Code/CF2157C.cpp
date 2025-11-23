// Problem: C. Meximum Array 2
// Contest: Codeforces - Codeforces Round 1066 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2157/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-23 17:44:28
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,k,q;
struct node{
	int op,l,r;
}a[maxn];
int ans[maxn];
bool vis[maxn];
void work(){
	n=read();k=read();q=read();
	for(int i=1;i<=q;i++)a[i]={read(),read(),read()};
	for(int i=1;i<=n;i++)ans[i]=k+1,vis[i]=0;
	for(int i=1;i<=q;i++){
		auto[o,l,r]=a[i];
		if(o==2){
			for(int i=l;i<=r;i++)vis[i]=1;
		}
	}
	for(int i=1;i<=q;i++){
		auto[o,l,r]=a[i];
		if(o==1){
			for(int i=l;i<=r;i++)if(!vis[i])ans[i]=k;
		}
	}
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=q;i++){
		auto[o,l,r]=a[i];
		if(o==1){
			for(int i=l;i<=r;i++)vis[i]=1;
		}
	}
	for(int i=1,v=0;i<=n;i++)if(!vis[i]){
		ans[i]=v;
		v=(v+1)%k;
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);puts("");
	// for(int i=1;i<=q;i++){
		// auto[o,l,r]=a[i];
		// if(o==1){
			// int mn=k+1;for(int i=l;i<=r;i++)mn=min(mn,ans[i]);
			// assert(mn==k);
		// }
		// else{
			// for(int i=0;i<=k;i++)vis[i]=0;
			// for(int i=l;i<=r;i++)vis[ans[i]]=1;
			// int mex=0;while(mex<=k&&vis[mex])mex++;
			// assert(mex==k);
		// }
	// }
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}