// Problem: P6086 【模板】Prüfer 序列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6086
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-21 21:24:34
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
const int maxn=5000010;
const int inf=1e9;
bool mbe;

int n,m,ans;
int fa[maxn],a[maxn],d[maxn];
void work(){
	n=read();m=read();
	if(m==1){
		for(int i=1;i<n;i++)fa[i]=read(),d[fa[i]]++;
		int nn=0;for(int i=1;i<n;i++)if(d[i]==0){
			a[++nn]=fa[i];d[fa[i]]--;
			int u=fa[i];
			while(d[u]==0&&u<i){
				a[++nn]=fa[u];d[fa[u]]--;
				u=fa[u];
			}
		}
		// for(int i=1;i<=n-2;i++)cout<<a[i]<<" ";cout<<"\n";
		for(int i=1;i<=n-2;i++)ans^=i*a[i];
		printf("%lld\n",ans);
	}
	else{
		for(int i=1;i<=n-2;i++)a[i]=read(),d[a[i]]++;a[n-1]=n,d[n]++;
		int nn=0;for(int i=1;i<n;i++)if(d[i]==0){
			fa[i]=a[++nn],d[fa[i]]--;
			int u=fa[i];
			while(d[u]==0&&u<i){
				fa[u]=a[++nn];d[fa[u]]--;
				u=fa[u];
			}
		}
		// for(int i=1;i<=n;i++)cout<<fa[i]<<" ";cout<<"\n";
		for(int i=1;i<=n-1;i++)ans^=i*fa[i];
		printf("%lld\n",ans);
	}
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