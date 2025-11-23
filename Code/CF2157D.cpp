// Problem: D. Billion Players Game
// Contest: Codeforces - Codeforces Round 1066 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2157/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-23 17:53:19
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

int n,pl,pr,a[maxn],ans,s1,s2;
int pre[maxn],suf[maxn];
int calc1(int i,int j){
	return j*pl-pre[j]-(n-i+1)*pl+suf[i]+s1;
}
int calc2(int i,int j){
	return suf[i]-(n-i+1)*pr+j*pr-pre[j]+s2;
}
void work(){
	n=read();pl=read();pr=read();ans=s1=s2=0;
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	int nn=0;for(int i=1;i<=n;i++){
		if(a[i]<=pl)s1+=pl-a[i],s2+=pr-a[i];
		else if(a[i]>=pr)s1+=a[i]-pl,s2+=a[i]-pr;
		else a[++nn]=a[i];
	}n=nn;
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]+a[i];
	suf[n+1]=0;for(int i=n;i;i--)suf[i]=suf[i+1]+a[i];
	for(int i=n+1;i;i--){
		int l=1,r=i-1,res=0;
		while(l<=r){
			int mid=l+r>>1;
			if(calc1(i,mid)>=calc2(i,mid))res=mid,l=mid+1;
			else r=mid-1;
		}
		ans=max(ans,min(calc1(i,res),calc2(i,res)));
		if(res+1<i){
			ans=max(ans,min(calc1(i,res+1),calc2(i,res+1)));
		}
	}
	printf("%lld\n",ans);
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