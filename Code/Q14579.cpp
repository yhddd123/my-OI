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
const int maxn=10010;
const int inf=1e18;
bool mbe;

int n,m,t,c[maxn],v[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dis[maxn],fa[maxn];
vector<int> sum[maxn];
int in[maxn],out[maxn],rnk[maxn<<1],idx;
void dfs(int u){
	dis[u]=dis[fa[u]]+v[u];
	sum[u]={0,dis[u]};
	in[u]=++idx,rnk[idx]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);
		vector<int> nw={0};
		int p=1,q=1;
		while(p<sum[u].size()&&q<sum[v].size()){
			if(sum[u][p]>sum[v][q])nw.pb(sum[u][p++]);
			else nw.pb(sum[v][q++]);
		}
		while(p<sum[u].size())nw.pb(sum[u][p++]);
		while(q<sum[v].size())nw.pb(sum[v][q++]);
		nw.resize(min(t+1,(int)nw.size()));
		sum[u]=nw;
	}
	out[u]=++idx,rnk[idx]=u;
}
vector<vector<int>> f[maxn<<1];
inline void chkmx(int &u,int v){(u<v)&&(u=v);}
int q[maxn],hd,tl,val[maxn];
void work(){
	n=read();m=read();t=read();
	for(int i=1;i<=n;i++)c[i]=read(),v[i]=read();
	for(int i=2;i<=n;i++)add(fa[i]=read(),i);
	dfs(1);
	for(int u=1;u<=n;u++){
		for(int i=1;i<sum[u].size();i++)sum[u][i]+=sum[u][i-1];
	}
	for(int i=1;i<=2*n+1;i++){
		f[i].resize(m+1);
		for(int j=0;j<=m;j++)f[i][j].resize(t+1,-inf);
	}
	f[1][0][0]=0;
	int tim=0;
	for(int i=1;i<=2*n;i++){
		int u=rnk[i];
		if(in[u]==i){
			for(int k=0;k<=t;k++){
				hd=1,tl=0;
				for(int j=1;j<=m;j++){
					int ff=f[i][j-1][k]-(j-1)*v[u];
					while(hd<=tl&&val[tl]<ff)tl--;
					q[++tl]=j-1,val[tl]=ff;
					while(hd<=tl&&q[hd]+c[u]-(t-k)<j)hd++;
					chkmx(f[i+1][j][k],val[hd]+j*v[u]);
				}
			}
			for(int j=0;j<=m;j++){
				for(int k=0;k<=t;k++)if(f[i][j][k]>=0){
					// for(int x=1;j+x<=m&&x<=c[u]-(t-k);x++){
						// chkmx(f[i+1][j+x][k],f[i][j][k]+x*v[u]);
					// }
					// cout<<i<<" "<<j<<" "<<k<<"\n";
					for(int x=0;k+x<=t&&x<sum[u].size();x++){
						++tim;
						chkmx(f[out[u]+1][j][k+x],f[i][j][k]+sum[u][x]);
					}
				}
			}
		}
		else{
			for(int k=0;k<=t;k++){
				hd=1,tl=0;
				for(int j=0;j<=m;j++){
					int ff=f[i][j][k]-j*v[u];
					while(hd<=tl&&val[tl]<ff)tl--;
					q[++tl]=j,val[tl]=ff;
					while(hd<=tl&&q[hd]+t-k<j)hd++;
					chkmx(f[i+1][j][k],val[hd]+j*v[u]);
				}
			}
			for(int k=0;k<t;k++){
				hd=1,tl=0;
				for(int j=0;j<=m;j++){
					int ff=f[i][j][k]-j*v[u];
					while(hd<=tl&&val[tl]<ff)tl--;
					q[++tl]=j,val[tl]=ff;
					while(hd<=tl&&q[hd]+t-k-1<j)hd++;
					chkmx(f[i+1][j][k+1],val[hd]+j*v[u]+dis[u]);
				}
			}
			// for(int j=0;j<=m;j++){
				// for(int k=0;k<=t;k++)if(f[i][j][k]>=0){
					// // for(int x=0;j+x<=m&&x<=t-k;x++){
						// // chkmx(f[i+1][j+x][k],f[i][j][k]+x*v[u]);
					// // }
					// // for(int x=0;j+x<=m&&x<t-k;x++){
						// // chkmx(f[i+1][j+x][k+1],f[i][j][k]+x*v[u]+dis[u]);
					// // }
				// }
			// }
		}
	}
	int ans=0;for(int j=0;j<=m;j++)ans=max(ans,f[2*n+1][j][t]);
	printf("%lld\n",ans);
	cerr<<tim<<"\n";
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