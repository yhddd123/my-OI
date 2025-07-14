// Problem: P6790 [SNOI2020] 生成树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6790
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-12 15:49:47
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
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,cnt,ans=1;
map<int,int> mp[maxn];
int f[maxn],g[maxn],d[maxn];
queue<int> q;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		if(!mp[u][v])mp[u][v]=mp[v][u]=++cnt,f[cnt]=g[cnt]=1,d[u]++,d[v]++;
		else f[mp[u][v]]++;
	}
	for(int i=1;i<=n;i++)if(d[i]<=2)q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		// cout<<u<<" "<<f[u]<<" "<<g[u]<<" "<<d[u]<<"\n";
		if(!d[u])continue;
		if(d[u]==1){
			int v=(*mp[u].begin()).fi,id=(*mp[u].begin()).se;
			ans=ans*f[id]%mod;
			d[u]--,d[v]--;mp[u].erase(v),mp[v].erase(u);
			if(d[v]<=2)q.push(v);
		}
		else{
			int v=(*mp[u].begin()).fi,id=(*mp[u].begin()).se;
			int vv=(*--mp[u].end()).fi,id1=(*--mp[u].end()).se;
			int p=mp[v][vv];
			int clr=mp[u][v];
			mp[u].erase(v),mp[v].erase(u);
			mp[u].erase(vv),mp[vv].erase(u);
			int valf=f[id]*f[id1]%mod,valg=(f[id]*g[id1]+f[id1]*g[id])%mod;
			if(p){
				f[p]=(valf*g[p]+f[p]*valg)%mod,g[p]=g[p]*valg%mod;
			}
			else{
				p=mp[v][vv]=mp[vv][v]=clr,d[v]++,d[vv]++;
				f[p]=valf,g[p]=valg;
			}
			d[u]-=2,d[v]--,d[vv]--;
			if(d[v]<=2)q.push(v);
			if(d[vv]<=2)q.push(vv);
		}
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
