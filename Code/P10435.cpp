// Problem: P10435 [JOIST 2024] 有趣的家庭菜园 5 / Growing Vegetables is Fun 5
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10435
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// Written by yhm.
// Start codeing:2026-01-05 18:25:17
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=600010;
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],c[maxn];
int pl[maxn],pr[maxn];
int f[maxn],g[maxn];
int to[maxn];
void sovle(int v,int *b,int *f){
	for(int i=1,j=1;i<=n;i++){
		while(j<=n&&b[j]<a[i]-v)j++;
		pl[i]=j;
	}
	for(int i=2*n,j=1;i>n;i--){
		while(j<=n&&b[j]<a[i]-v)j++;
		pl[i]=j;
	}
	for(int i=1,j=0;i<=n;i++){
		while(j+1<=n&&b[j+1]<=a[i]+v)j++;
		pr[i]=j;
	}
	for(int i=2*n,j=0;i>n;i--){
		while(j+1<=n&&b[j+1]<=a[i]+v)j++;
		pr[i]=j;
	}
	auto chk=[&](int i,int v){return pl[i]-1<=v&&v<=pr[i]-1;};
	auto upd=[&](int l,int r){if(l<=r)f[l]++,f[r+1]--;};
	for(int i=1;i<=2*n;i++)if(pl[i]<=pr[i]){
		if(i<=n){
			int p=min(i,to[i]-n);
			upd(max(1,i-pr[i]+1),min(p,i-pl[i]+1));
			if(chk(i,i+n-to[i]))upd(p+1,i);
			// for(int j=1;j<=i;j++)if(chk(i,i-j+max(0,j+n-to[i])))upd(j,j);
			p=max(i+n+1,to[i]);
			if(chk(i,i-1+2*n-to[i]+1))upd(i+n+1,p-1);
			upd(max(p,i-1+2*n+1-pr[i]+1),min(2*n,i-1+2*n+1-pl[i]+1));
			// for(int j=i+n+1;j<=2*n;j++)if(chk(i,i-1+2*n-max(j,to[i])+1))upd(j,j);
		}else{
			int p=min(n,to[i]+1);
			if(chk(i,to[i]+1+n-i-1))upd(i-n+1,p);
			upd(max(p+1,pl[i]-1-(n-i-1)),min(n,pr[i]-1-(n-i-1)));
			// for(int j=i-n+1;j<=n;j++)if(chk(i,max(0,to[i]-j+1)+j+n-i-1))upd(j,j);
			p=max(n+1,to[i]+n+1);
			if(chk(i,to[i]+2*n-i))upd(p+1,i);
			upd(max(n+1,pl[i]-1-(n-i-1)),min(p,pr[i]-1-(n-i-1)));
			// for(int j=n+1;j<=i;j++)if(chk(i,min(to[i],j-n-1)+2*n-i))upd(j,j);
		}
	}
	for(int i=1;i<=2*n;i++)f[i]+=f[i-1];
}
bool check(int v){
	for(int i=1;i<=2*n;i++)f[i]=g[i]=0;
	sovle(v,b,f),sovle(v,c,g);
	for(int i=1;i<=n;i++)if(f[i]==n&&g[i+n]==n)return 1;
	for(int i=1;i<=n;i++)if(g[i]==n&&f[i+n]==n)return 1;
	return 0;
}
int calc(){
	int l=0,r=inf,res=inf;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
}
void work(){
	n=read();
	for(int i=1;i<=2*n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	sort(b+1,b+n+1),sort(c+1,c+n+1);
	for(int i=1,j=2*n;i<=n;i++){
		while(j>n&&a[j]<a[i])j--;
		to[i]=j+1;
	}
	for(int i=2*n,j=1;i>n;i--){
		while(j<=n&&a[j]<=a[i])j++;
		to[i]=j-1;
	}
	printf("%lld\n",calc());
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