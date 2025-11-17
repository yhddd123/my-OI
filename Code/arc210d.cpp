// Problem: D - Independent Set Game
// Contest: AtCoder - AtCoder Regular Contest 210
// URL: https://atcoder.jp/contests/arc210/tasks/arc210_d
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-16 21:18:21
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

int n,m,d[maxn];
int f[maxn],siz[maxn],flg[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
vector<int> e[maxn];
bool vis[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=n;i++)d[i]=0;
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=0,flg[i]=1;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		d[u]++,d[v]++;
		f[fd(u)]=fd(v);
		e[u].pb(v),e[v].pb(u);
	}
	if(!m){puts("Alice");return ;}
	if(n&1){puts("Bob");return ;}
	for(int i=1;i<=n;i++)siz[fd(i)]++,flg[fd(i)]&=d[i]==2;
	int num=0;for(int i=1;i<=n;i++)num+=siz[i]>=3;
	bool fl=(num>=1);
	if(num>1){puts("Bob");return ;}
	num=0;for(int i=1;i<=n;i++)if(f[i]==i)num+=flg[i];
	if(num>1){puts("Bob");return ;}
	if(num==1){
		for(int i=1;i<=n;i++)if(f[i]==i&&flg[i]){
			if(siz[i]&1)puts("Alice");
			else puts("Bob");
		}
		return ;
	}
	num=0;for(int i=1;i<=n;i++)num+=d[i]>=3;
	if(num>1){puts("Bob");return ;}
	int p=0;for(int i=1;i<=n;i++)if(d[i]>=3)p=i;
	if(!p){
		for(int i=1;i<=n;i++)if(siz[i]>5){puts("Bob");return ;}
	}
	else{
		for(int i=1;i<=n;i++)vis[i]=0;
		vis[p]=1;
		for(int u:e[p]){
			vis[u]=1;
			for(int v:e[u])if(v!=p){
				vis[v]=1,d[v]=2;
				if(e[v].size()==1||(e[v].size()==2&&(e[v][0]==p||e[v][1]==p))){}
				else{puts("Bob");return ;}
			}
		}
		for(int i=1;i<=n;i++)if(fd(i)==fd(p)&&!vis[i]){puts("Bob");return ;}
	}
	num=0;for(int i=1;i<=n;i++)num+=d[i]<=1;
	if((num&1)||!fl)puts("Alice");
	else puts("Bob");
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