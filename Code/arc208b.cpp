// Problem: B - Sum of Mod
// Contest: AtCoder - AtCoder Regular Contest 208 (Div. 2)
// URL: https://atcoder.jp/contests/arc208/tasks/arc208_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-12 20:02:34
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

int n,k,a[maxn];
int check(int x){
	int num=1;
	for(int i=x;i<k+x;){
		i=2*i-1;
		++num;
	}
	return num;
}

void work(){
	n=read();k=read();
	int l=2,r=k,res=k+1;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)<=n)res=mid,r=mid-1;
		else l=mid+1;
	}
	int num=check(res);
	cout<<res<<" ";
	for(int i=res;i<k+res;){
		i=min(2*i-1,k+res);
		cout<<i<<" ";
	}
	for(int i=num+1;i<=n;i++)cout<<k+res<<" ";cout<<"\n";
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