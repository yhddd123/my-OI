// Problem: P3006 [USACO11JAN] Bottleneck G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3006
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-03-30 16:20:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
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

int n,p;
int fa[maxn],a[maxn],w[maxn],num[maxn];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
pii que[maxn];int ans[maxn];
priority_queue<pii> q;
void work(){
	n=read();p=read();int sum=0;
	for(int i=2;i<=n;i++){
		fa[i]=read(),a[i]=read(),w[i]=read();
		num[fa[i]]-=w[i],num[i]+=w[i];sum+=a[i];
	}
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=p;i++)que[i]={read(),i};
	sort(que+1,que+p+1);
	for(int i=2;i<=n;i++)if(num[i]>0)q.push({-a[i]/num[i],i});
	int l=1;
	while(!q.empty()&&l<=p){
		while(l<=p&&que[l].first<=-q.top().first)ans[que[l].second]=a[1]-num[1]*que[l].first,l++;
		int u=q.top().second;q.pop();
		if(f[u]!=u)continue;
		int tp=fd(fa[u]);f[u]=tp;
		// cout<<u<<" "<<tp<<"\n";
		a[tp]+=a[u],num[tp]+=num[u];
		if(num[tp]>0)q.push({-a[tp]/num[tp],tp});
	}
	for(int i=1;i<=p;i++)if(!ans[i])ans[i]=sum;
	for(int i=1;i<=p;i++)printf("%lld\n",ans[i]);
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
