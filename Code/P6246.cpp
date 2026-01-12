// Problem: P6246 [IOI 2000] 邮局 加强版 加强版
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6246
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-12 16:42:29
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,k,a[maxn],s[maxn];
int w(int l,int r){
	int mid=l+r>>1;
	return a[mid]*(mid-l+1)-(s[mid]-s[l-1])+(s[r]-s[mid])-a[mid]*(r-mid);
}
pii f[maxn];
struct node{
	int j,l,r;
}st[maxn];int h,t;
pii calc(int i,int j,int lim){return {f[j].fi+w(j+1,i)-lim,f[j].se+1};}
pii calc(int lim){
	f[0]={0,0};
	st[h=t=1]={0,0,n};
	for(int i=1;i<=n;i++){
		st[h].l++;
		while(h<=t&&st[h].l>st[h].r)h++;
		f[i]=calc(i,st[h].j,lim);
		while(h<=t&&calc(st[t].l,st[t].j,lim)>calc(st[t].l,i,lim))t--;
		if(h>t)st[++t]={i,i,n};
		else{
			int l=st[t].l,r=st[t].r,res=l;
			while(l<=r){
				int mid=l+r>>1;
				if(calc(mid,st[t].j,lim)<calc(mid,i,lim))res=mid,l=mid+1;
				else r=mid-1;
			}
			st[t].r=res;
			if(res+1<=n)st[++t]={i,res+1,n};
		}
	}
	// cout<<lim<<" "<<f[n].fi<<" "<<f[n].se<<"\n";
	return f[n];
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
	int l=-inf,r=0,res=-inf;
	while(l<=r){
		int mid=l+r>>1;
		if(calc(mid).se<=k)res=mid,l=mid+1;
		else r=mid-1;
	}
	// cout<<res<<"\n";
	pii dp=calc(res);
	printf("%lld\n",dp.fi+res*k);
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