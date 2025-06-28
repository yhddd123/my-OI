// Problem: P3505 [POI 2010] TEL-Teleportation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3505
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-04-17 18:01:17
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n,m,ans;
vector<int> e[maxn];
int dep[maxn],cnt[8];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dep[1]=1,dep[2]=6;
	for(int u:e[1])dep[u]=2;
	for(int u:e[2])dep[u]=5;
	for(int u:e[1]){
		for(int v:e[u])if(!dep[v])dep[v]=3;
	}
	for(int u:e[2]){
		for(int v:e[u])if(!dep[v])dep[v]=4;
	}
	for(int i=1;i<=n;i++)cnt[dep[i]]++;
	for(int i=0;i<=cnt[0];i++){
		cnt[3]+=i,cnt[4]+=cnt[0]-i;
		int res=0;for(int i=1;i<=6;i++)res+=cnt[i]*(cnt[i]-1)/2+cnt[i]*cnt[i+1];
		ans=max(ans,res);
		cnt[3]-=i,cnt[4]-=cnt[0]-i;
	}
	printf("%lld\n",ans-m);
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