// Problem: P7973 [KSN2021] Binary Land
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7973
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-10-18 14:29:18
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],b[maxn];
int f[maxn],w[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int mx[maxn];
vector<int> pos[64];
bool vis[64];
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v)return ;
	f[u]=v,w[v]+=w[u];
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)f[i]=i,w[i]=b[i];
	for(int i=1;i<=n;i++){
		for(int j=0;j<63;j++)if(a[i]&(1ll<<j))mx[i]=j;
		pos[mx[i]].pb(i);
	}
	for(int i=n;i;i--){
		for(int j=0;j<mx[i];j++)if(!(a[i]&(1ll<<j))){
			if(!vis[j]){
				vis[j]=1;
				for(int k:pos[j])merge(k,pos[j].back());
			}
			if(pos[j].size())merge(i,pos[j].back());
		}
	}
	for(int i=1;i<=n;i++)printf("%lld\n",w[fd(i)]);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen("graph.in","r",stdin);
//	freopen("graph.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
