// Problem: CF912E Prime Gift
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF912E
// Memory Limit: 250 MB
// Time Limit: 3500 ms
// Written by yhm.
// Start codeing:2025-03-13 12:52:31
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e18;
bool mbe;

int n,k,a[maxn],b[maxn];
vector<int> v1,v2;
void dfs1(int dep,int val=1){
	if(dep==n/3+1){
		v1.pb(val);
		return ;
	}
	for(int i=1;i<=inf/val;i=(a[dep]<=inf/i?i*a[dep]:inf+1))dfs1(dep+1,val*i);
}
void dfs2(int dep,int val=1){
	if(dep==n+1){
		v2.pb(val);
		return ;
	}
	for(int i=1;i<=inf/val;i=(a[dep]<=inf/i?i*a[dep]:inf+1))dfs2(dep+1,val*i);
}
bool check(int x){
	int res=0;
	for(int v:v1){
		int p=upper_bound(v2.begin(),v2.end(),x/v)-v2.begin();
		res+=p;
		if(res>=k)return 1;
	}
	return 0;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	k=read();
	sort(a+1,a+n+1);
	dfs1(1),dfs2(n/3+1);
	sort(v1.begin(),v1.end()),sort(v2.begin(),v2.end());
	// cout<<v1.size()<<" "<<v2.size()<<"\n";
	int l=1,r=inf,res=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))r=mid-1,res=mid;
		else l=mid+1;
	}
	printf("%lld\n",res);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}