// Problem: E. Maximum OR Popcount
// Contest: Codeforces - Codeforces Global Round 29 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2147/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-22 10:09:04
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
const int maxn=100010;
const int inf=2e9;
bool mbe;

int n,m=31,q,a[maxn];
int t[32],tmp[32],aa[maxn],val[32];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<m;i++)t[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++)if(a[i]&(1<<j))t[j]++;
	}
	for(int i=1;i<=n;i++)aa[i]=a[i];
	for(int i=0;i<m;i++)tmp[i]=t[i];
	int num=0;for(int i=0;i<m;i++)num+=(t[i]>0);
	for(int i=0;i<=num;i++)val[i]=0;
	for(int i=0;i<m;i++)if(!tmp[i]){
		for(int j=1;j<=n;j++)a[j]=aa[j];
		for(int j=0;j<m;j++)t[j]=tmp[j];
		val[++num]=0;
		for(int j=i;~j;j--)if(!t[j]){
			pii mn={inf,0};
			for(int k=1;k<=n;k++)mn=min(mn,{(1<<j)-(a[k]&((1<<j)-1)),k});
			for(int k=0;k<=j;k++)if(a[mn.se]&(1<<k))t[k]--;
			val[num]+=mn.fi,a[mn.se]+=mn.fi;
			// cout<<mn.fi<<" "<<mn.se<<"\n";
			for(int k=0;k<=j;k++)if(a[mn.se]&(1<<k))t[k]++;
		}
		// cout<<i<<" "<<num<<" "<<val[num]<<"\n";
		// for(int j=1;j<=n;j++)cout<<a[j]<<" ";cout<<"\n";
	}
	// for(int i=0;i<=m;i++)cout<<val[i]<<" ";cout<<"\n";
	while(q--){
		int v=read();
		int p=upper_bound(val,val+m+1,v)-val-1;
		printf("%lld\n",p);
	}
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