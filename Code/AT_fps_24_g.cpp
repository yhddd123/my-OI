// Problem: G - Coin
// Contest: AtCoder - FPS 24: 24 Problems on Formal Power Series
// URL: https://atcoder.jp/contests/fps-24/tasks/fps_24_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-13 19:19:34
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
const int maxn=5010;
const int inf=1e9;
bool mbe;

int n,m,l;
int f[maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void ins(int v){
	for(int i=v;i<=n;i++)inc(f[i],f[i-v]);
}
void del(int v){
	for(int i=n;i>=v;i--)inc(f[i],mod-f[i-v]);
}
void work(){
	n=read();m=read();l=read();
	f[0]=1;
	for(int i=1;i<=l;i++)ins(i);
	for(int i=1;i<=m-l+1;i++){
		printf("%lld\n",f[n]);
		ins(i+l);del(i);
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