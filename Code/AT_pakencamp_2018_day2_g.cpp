// Problem: AT_pakencamp_2018_day2_g グランド・グラフ　(Grand Graph)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_pakencamp_2018_day2_g
// Memory Limit: 1024 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-09-05 07:39:21
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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

int n,m,k,ans=1;
map<int,pii> f[maxn];
int d[maxn];
void add(int u,int v,int v1,int v2){
	if(f[u].find(v)==f[u].end())f[u][v]=f[v][u]={1,1},d[u]++,d[v]++;
	f[u][v]=f[v][u]={f[u][v].fi*v1%mod,f[u][v].se*v2%mod};
}
queue<int> q;
int st[maxn],tp,res,c[maxn];
void dfs(int d,int lim,int mul){
	if(d==tp+1){
		for(int i=1;i<=tp;i++){
			int u=st[i];
			for(int j=i+1;j<=tp;j++){
				int v=st[j];
				if(f[u].find(v)!=f[u].end()){
					mul=mul*(c[i]==c[j]?f[u][v].fi:f[u][v].se)%mod;
				}
			}
		}
		(res+=mul)%=mod;
		return ;
	}
	for(int i=1;i<=lim;i++)c[d]=i,dfs(d+1,lim,mul);
	if(lim<k)c[d]=lim+1,dfs(d+1,lim+1,mul*(k-lim)%mod);
}
void work(){
	n=read();m=read();k=read();
	if(k==1){puts(n==1?"1":"0");return ;}
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v,0,1);
	}
	for(int i=1;i<=n;i++)if(d[i]<=2)q.push(i);
	int rt=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		if(!d[u])continue;
		if(d[u]==1){
			int v=(*f[u].begin()).fi;
			ans=ans*(f[u][v].fi+f[u][v].se*(k-1)%mod)%mod;
			d[u]--,d[v]--;f[u].erase(v),f[v].erase(u);
			rt=v;
			if(d[v]<=2)q.push(v);
		}
		else if(d[u]==2){
			int v1=(*f[u].begin()).fi,v2=(*--f[u].end()).fi;
			int vf=(f[u][v1].fi*f[u][v2].fi+f[u][v1].se*f[u][v2].se%mod*(k-1))%mod;
			int vg=(f[u][v1].fi*f[u][v2].se+f[u][v1].se*f[u][v2].fi+f[u][v1].se*f[u][v2].se%mod*(k-2))%mod;
			add(v1,v2,vf,vg);
			d[u]-=2,d[v1]--,d[v2]--;f[u].erase(v1),f[v1].erase(u),f[u].erase(v2),f[v2].erase(u);
			if(d[v1]<=2)q.push(v1);
			if(d[v2]<=2)q.push(v2);
		}
	}
	for(int i=1;i<=n;i++)if(d[i]>=3)st[++tp]=i;
	if(!tp)st[++tp]=rt;
	dfs(1,0,1);
	printf("%lld\n",ans*res%mod);
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