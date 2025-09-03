#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=100010;
const int inf=1e18;

int n,m;
int head[maxn],tot;
struct nd{
    int nxt,to,w;
}e[maxn<<2];
void add_e(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dis[maxn];
bool vis[maxn];
int dfn[maxn],lw[maxn],idx;
int st[maxn],tp;
vector<int> id[maxn];int scct;
void tar(int u){
	dfn[u]=lw[u]=++idx;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
			if(lw[v]>=dfn[u]){
				id[++scct].push_back(st[tp]);
				while(st[tp--]!=v){
					id[scct].push_back(st[tp]);
				}
				id[scct].push_back(u);
			}
		}
		else lw[u]=min(lw[u],dfn[v]);
	}
}
bool bk[maxn];
map<int,int> f[maxn];
int d[maxn];
void add(int u,int v,int w){
    if(f[u].find(v)==f[u].end())f[u][v]=f[v][u]=w,d[u]++,d[v]++;
    else if(f[u][v]!=w)f[u][v]=f[v][u]=-1;
}
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        add_e(u,v,w),add_e(v,u,w);
    }
    for(int i=1;i<=n;i++)dis[i]=inf;
    priority_queue<pii> q;
    dis[1]=0;q.push({0,1});
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].w){
                dis[v]=dis[u]+e[i].w;
                q.push({-dis[v],v});
            }
        }
    }
    add_e(1,n,dis[n]),add_e(n,1,dis[n]);
    tar(1);
    for(int i=1;i<=scct;i++){
        int tim=0;for(int j:id[i])tim+=(j==1)+(j==n);
        if(tim==2){
            for(int j:id[i])bk[j]=1;
            break;
        }
    }
    // for(int i=1;i<=n;i++)cout<<bk[i]<<" ";cout<<"\n";
    for(int u=1;u<=n;u++){
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(bk[u]&&bk[v]&&u<v)add(u,v,e[i].w);
        }
    }
    queue<int> qq;
    for(int i=2;i<n;i++)if(d[i]<=2)qq.push(i);
    while(!qq.empty()){
        int u=qq.front();qq.pop();
        if(!d[u])continue;
        else if(d[u]==1){
            int v=(*f[u].begin()).fi;
            d[u]--,d[v]--;f[u].erase(v),f[v].erase(u);
            if(v!=1&&v!=n&&d[v]<=2)qq.push(v);
        }
        else{
            int v1=(*f[u].begin()).fi,v2=(*--f[u].end()).fi;
            add(v1,v2,(f[u][v1]==-1||f[u][v2]==-1)?-1:f[u][v1]+f[u][v2]);
            // cout<<u<<" "<<v1<<" "<<v2<<" "<<f[v1][v2]<<" "<<f[u][v1]<<" "<<f[u][v2]<<"\n";
            d[u]-=2,d[v1]--,d[v2]--;f[u].erase(v1),f[v1].erase(u),f[u].erase(v2),f[v2].erase(u);
            if(v1!=1&&v1!=n&&d[v1]<=2)qq.push(v1);
            if(v2!=1&&v2!=n&&d[v2]<=2)qq.push(v2);
        }
    }
    if(f[1].size()>1||f[1][n]==-1)puts("1");
    else puts("0");
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}