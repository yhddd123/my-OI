// Problem: P6178 【模板】Matrix-Tree 定理
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6178
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-21 22:12:48
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=310;
const int inf=1e9;
bool mbe;

int n,m,op;
int a[maxn][maxn];
int det(int n){
	int ans=1;
	for(int i=2;i<=n;i++){
		for(int j=i+1;j<=n;j++)if(a[j][i]){
			while(a[i][i]){
				int d=a[j][i]/a[i][i];
				for(int k=i;k<=n;k++)(a[j][k]+=mod-a[i][k]*d%mod)%=mod;
				swap(a[i],a[j]),ans=mod-ans;
			}
			swap(a[i],a[j]),ans=mod-ans;
		}
	}
	for(int i=2;i<=n;i++)ans=ans*a[i][i]%mod;
	return ans;
}
void work(){
	n=read();m=read();op=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		if(!op)(a[u][u]+=w)%=mod,(a[v][v]+=w)%=mod,(a[u][v]+=mod-w)%=mod,(a[v][u]+=mod-w)%=mod;
		else (a[v][v]+=w)%=mod,(a[v][u]+=mod-w)%=mod;
	}
	printf("%lld\n",det(n));
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