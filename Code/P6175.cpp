#include<bits/stdc++.h>
#define int long long
#define y1 _y1
#define mod 19260817
using namespace std;
const int maxn=110;
const int inf=2e9;

int n,m,ans;
int dis[maxn][maxn],mp[maxn][maxn];
int u,v,w;
void sovle(){
	cin>>n>>m;ans=inf;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j)dis[i][j]=mp[i][j]=inf;
		}
	}
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		dis[u][v]=min(dis[u][v],w);
		dis[v][u]=dis[u][v];
		mp[u][v]=min(mp[u][v],w);
		mp[v][u]=mp[u][v];
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<k;i++){
			for(int j=i+1;j<k;j++){
				ans=min(ans,dis[i][j]+mp[i][k]+mp[k][j]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	if(ans==inf)cout<<"No solution.\n";
	else cout<<ans<<"\n";
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	T=1;
	while(T--)sovle();
}

