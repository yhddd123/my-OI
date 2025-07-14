// Problem: P9734 [JOISC 2021 Day2] 逃走経路 (Escape Route)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9734
// Memory Limit: 2 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
using namespace std;
const int maxn=95;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q,tim;
pii e[maxn][maxn],g[maxn*maxn];
int dis1[maxn][maxn],dis2[maxn][maxn],dis3[maxn][maxn],dis4[maxn][maxn];
vector<pii> f[maxn][maxn];
bool vis[maxn];
void work(){
	n=read();m=read();tim=read();q=read();
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1,l=read(),c=read();
		e[u][v]=e[v][u]={l,c};g[i]={u,v};
	}
	
	//1 day
	
	for(int num=1;num<=m;num++){
		int uu=g[num].first,vv=g[num].second;
		//s->u->v->t
		for(int i=1;i<=n;i++)dis1[uu][i]=-1,vis[i]=0;dis1[uu][uu]=e[uu][vv].second-e[uu][vv].first;
		for(int t=1;t<=n;t++){
			int u=0;for(int i=1;i<=n;i++)if((!u||dis1[uu][i]>=dis1[uu][u])&&!vis[i])u=i;
			if(!u)break;vis[u]=1;
			for(int v=1;v<=n;v++)if(e[u][v].first){
				if(dis1[uu][u]<=e[u][v].second&&dis1[uu][v]<dis1[uu][u]-e[u][v].first)dis1[uu][v]=dis1[uu][u]-e[u][v].first;
			}
		}
		for(int i=1;i<=n;i++)dis2[vv][i]=inf,vis[i]=0;dis2[vv][vv]=e[uu][vv].second;
		for(int t=1;t<=n;t++){
			int u=0;for(int i=1;i<=n;i++)if((!u||dis2[vv][i]<=dis2[vv][u])&&!vis[i])u=i;
			if(!u)break;vis[u]=1;
			for(int v=1;v<=n;v++)if(e[u][v].first&&dis2[vv][u]+e[u][v].first<=e[u][v].second){
				if(dis2[vv][v]>dis2[vv][u]+e[u][v].first)dis2[vv][v]=dis2[vv][u]+e[u][v].first;
			}
		}
		// cout<<uu<<" "<<vv<<"\n";
		for(int u=1;u<=n;u++){
			for(int v=1;v<=n;v++){
				// cout<<u<<" "<<v<<" "<<dis1[uu][u]<<" "<<dis2[vv][v]<<"\n";
				if(dis1[uu][u]>=0&&dis2[vv][v]<=tim)f[u][v].push_back({dis1[uu][u],-(dis2[vv][v]-dis1[uu][u])});
			}
		}
		
		uu=g[num].second,vv=g[num].first;
		//s->u->v->t
		for(int i=1;i<=n;i++)dis1[uu][i]=-1,vis[i]=0;dis1[uu][uu]=e[uu][vv].second-e[uu][vv].first;
		for(int t=1;t<=n;t++){
			int u=0;for(int i=1;i<=n;i++)if((!u||dis1[uu][i]>=dis1[uu][u])&&!vis[i])u=i;
			if(!u)break;vis[u]=1;
			for(int v=1;v<=n;v++)if(e[u][v].first){
				if(dis1[uu][u]<=e[u][v].second&&dis1[uu][v]<dis1[uu][u]-e[u][v].first)dis1[uu][v]=dis1[uu][u]-e[u][v].first;
			}
		}
		for(int i=1;i<=n;i++)dis2[vv][i]=inf,vis[i]=0;dis2[vv][vv]=e[uu][vv].second;
		for(int t=1;t<=n;t++){
			int u=0;for(int i=1;i<=n;i++)if((!u||dis2[vv][i]<=dis2[vv][u])&&!vis[i])u=i;
			if(!u)break;vis[u]=1;
			for(int v=1;v<=n;v++)if(e[u][v].first&&dis2[vv][u]+e[u][v].first<=e[u][v].second){
				if(dis2[vv][v]>dis2[vv][u]+e[u][v].first)dis2[vv][v]=dis2[vv][u]+e[u][v].first;
			}
		}
		// cout<<uu<<" "<<vv<<"\n";
		for(int u=1;u<=n;u++){
			for(int v=1;v<=n;v++){
				// cout<<u<<" "<<v<<" "<<dis1[uu][u]<<" "<<dis2[vv][v]<<"\n";
				if(dis1[uu][u]>=0&&dis2[vv][v]<=tim)f[u][v].push_back({dis1[uu][u],-(dis2[vv][v]-dis1[uu][u])});
			}
		}
	}
	for(int u=1;u<=n;u++){
		for(int v=1;v<=n;v++){
			sort(f[u][v].begin(),f[u][v].end());
			vector<pii> tmp;
			for(pii p:f[u][v]){
				while(tmp.size()&&tmp.back().second>(-p.second))tmp.pop_back();
				tmp.push_back({p.first,-p.second});
			}
			f[u][v]=tmp;
			// cout<<u<<" "<<v<<" f\n";
			// for(pii p:f[u][v])cout<<p.first<<" "<<p.second<<"\n";
		}
	}
	
	//n days
	
	//day 1 u->uu
	for(int s=1;s<=n;s++){
		for(int i=1;i<=n;i++)dis1[s][i]=-1,vis[i]=0;dis1[s][s]=tim;
		for(int t=1;t<=n;t++){
			int u=0;for(int i=1;i<=n;i++)if((!u||dis1[s][i]>=dis1[s][u])&&!vis[i])u=i;
			if(!u)break;vis[u]=1;
			for(int v=1;v<=n;v++)if(e[u][v].first){
				if(dis1[s][v]<min(dis1[s][u],e[u][v].second)-e[u][v].first)dis1[s][v]=min(dis1[s][u],e[u][v].second)-e[u][v].first;
			}
		}
	}
	// cout<<dis1[18][11]<<"\n";
	// for(int i=1;i<=n;i++)cout<<dis1[3][i]<<" ";cout<<"\n";
	//day n vv->v
	for(int s=1;s<=n;s++){
		for(int i=1;i<=n;i++)dis2[s][i]=inf,vis[i]=0;dis2[s][s]=0;
		for(int t=1;t<=n;t++){
			int u=0;for(int i=1;i<=n;i++)if((!u||dis2[s][i]<=dis2[s][u])&&!vis[i])u=i;
			if(!u)break;vis[u]=1;
			for(int v=1;v<=n;v++)if(e[u][v].first&&dis2[s][u]+e[u][v].first<=e[u][v].second){
				if(dis2[s][v]>dis2[s][u]+e[u][v].first)dis2[s][v]=dis2[s][u]+e[u][v].first;
			}
		}
	}
	//day 2 to n-1 uu->vv
	for(int u=1;u<=n;u++)for(int v=1;v<=n;v++){
		if(dis2[u][v]<inf)dis3[u][v]=1;
		else dis3[u][v]=inf;
	}
	for(int i=1;i<=n;i++)dis3[i][i]=0;
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)dis3[i][j]=min(dis3[i][j],dis3[i][k]+dis3[k][j]);
		}
	}
	//pre uu->v
	for(int uu=1;uu<=n;uu++){
		for(int v=1;v<=n;v++){
			dis4[uu][v]=dis3[uu][v]*tim;
			for(int vv=1;vv<=n;vv++)dis4[uu][v]=min(dis4[uu][v],dis3[uu][vv]*tim+dis2[vv][v]);
		}
	}
	
	//que
	while(q--){
		int u=read()+1,v=read()+1,t=read(),ans=inf;
		auto it=lower_bound(f[u][v].begin(),f[u][v].end(),make_pair(t,-1ll));
		if(it!=f[u][v].end())ans=(*it).second;
		// cout<<ans<<"\n";
		if(t<=dis1[v][u])ans=min(ans,tim-dis1[v][u]);
		for(int uu=1;uu<=n;uu++)if(dis1[uu][u]>=t){
			ans=min(ans,tim-t+dis4[uu][v]);
			// cout<<uu<<" "<<dis4[uu][v]<<"\n";
		}
		printf("%lld\n",ans);
	}
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
