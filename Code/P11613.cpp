// Problem: P11613 [PA 2016] 覆盖 / Pokrycia
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11613
// Memory Limit: 512 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2026-01-06 12:57:27
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
const int maxn=(1<<15)+5;
const int inf=1e9;
bool mbe;

int n,k,q;
bool f[maxn],g[maxn],h[maxn];
vector<pii> que[maxn];
bool ans[maxn];
void work(){
	q=read();
	for(int i=1;i<=q;i++){
		n=read(),k=n-read();
		que[n].pb({k,i});
	}
	n=1<<14;
	f[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++)h[j]=0;
		g[0]=0;for(int j=1;j<=i;j++){
			g[j]=f[j-1]^f[j+(j&(-j))-1];
			if(g[j])h[j]^=1,h[j-(j&(-j))]^=1;
		}
		swap(f,g);
		for(auto[k,id]:que[i])ans[id]=h[k];
	}
	for(int i=1;i<=q;i++)putchar('0'+ans[i]),puts("");
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