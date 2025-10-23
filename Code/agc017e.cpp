// Problem: AT_agc017_e [AGC017E] Jigsaw
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc017_e
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-22 20:34:31
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
const int maxn=410;
const int inf=1e9;
bool mbe;

int n,m;
int deg[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
bool fl[maxn],fl1[maxn],fl2[maxn],fl3[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=2*m;i++)f[i]=i;
	for(int i=1;i<=n;i++){
		int a=read(),b=read(),c=read(),d=read(),l=0,r=0;
		if(!c)l=a;
		else l=-c;
		if(!d)r=-b;
		else r=d;
		// cout<<l<<" "<<r<<"\n";
		l+=m,r+=m;
		f[fd(l)]=fd(r);fl[fd(r)]=1;
		deg[l]++,deg[r]--;
	}
	for(int i=0;i<=2*m;i++){
		// cout<<i<<" "<<deg[i]<<"\n";
		if(i>m&&deg[i]>0)fl1[fd(i)]=1;
		if(i<m&&deg[i]<0)fl2[fd(i)]=1;
		if(i>m&&deg[i]<0)fl3[fd(i)]=1;
		if(i<m&&deg[i]>0)fl3[fd(i)]=1;
	}
	for(int i=0;i<=2*m;i++)if(i==f[i]&&fl[i]&&(!fl1[i]||!fl2[i]||fl3[i])){puts("NO");return ;}
	puts("YES");
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