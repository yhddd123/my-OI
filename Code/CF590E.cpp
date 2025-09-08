#include<bits/stdc++.h>
// #define int long long
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
const int maxn=755;
const int maxm=10000010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn];
int to[maxm][2],fr[maxm],fail[maxm],idx;
int q[maxm],h,t;
int id[maxm];
int ed[maxn],fa[maxm],st[maxm],tp;
bitset<maxn> f[maxn];
namespace flow{
int head[maxn<<1],tot=1;
struct nd{
    int nxt,to,w;
}e[maxn*maxn<<1];
void add(int u,int v,int w){
    // cout<<u<<" "<<v<<" "<<w<<"\n";
    e[++tot]={head[u],v,w};head[u]=tot;
    e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int rad[maxn<<1],dis[maxn<<1];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
int dinic(){
    flow=0;while(bfs())flow+=dfs(s,inf);
    return flow;
}
void init(){
    for(int i=1;i<=t;i++)head[i]=0;tot=1;
    for(int i=1;i<=n;i++){
        add(s,i,1),add(i+n,t,1);
        for(int j=1;j<=n;j++)if(f[i][j])add(i,j+n,1);
    }
}
bool vis[maxn<<1];
void dfs(int u){
    vis[u]=1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(vis[v]||v>=s)continue;
        if(!e[i].w)dfs(v);
    }
}
}
void work(){
    n=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);int m=strlen(s+1),nd=0;
        for(int j=1;j<=m;j++){
            if(!to[nd][s[j]-'a'])to[nd][s[j]-'a']=++idx,fr[idx]=nd;
            nd=to[nd][s[j]-'a'];
        }
        id[nd]=i,ed[i]=nd;
    }
    h=1,t=0;
    for(int i=0;i<2;i++)if(to[0][i])q[++t]=to[0][i];
    while(h<=t){
        int u=q[h++];
        for(int i=0;i<2;i++){
            if(to[u][i]){
                fail[to[u][i]]=to[fail[u]][i];
                q[++t]=to[u][i];
            }
            else to[u][i]=to[fail[u]][i];
        }
        // cout<<u<<" "<<to[u][0]<<" "<<to[u][1]<<"\n";
    }
    // for(int i=1;i<=idx;i++)cout<<fail[i]<<" ";cout<<"\n";
    for(int i=1;i<=idx;i++)if(!id[i])id[i]=-1;
    for(int i=0;i<=idx;i++)fa[i]=-1;
    id[0]=0;for(int i=1;i<=idx;i++)if(fa[i]==-1){
    	int u=fail[i];st[++tp]=i;
        while(id[u]==-1){
            st[++tp]=u;
            u=fail[u];
        }
        while(tp)fa[st[tp]]=id[u],tp--;
    }
    // for(int i=1;i<=idx;i++)cout<<fa[i]<<" ";cout<<"\n";
    for(int i=1;i<=n;i++){
    	// cout<<i<<"\n";
    	for(int j=ed[i];j;j=fr[j]){
    		// cout<<j<<" "<<id[j]<<" "<<fa[j]<<"\n";
			if(j!=ed[i]&&id[j]>=1)f[id[j]][i]=1;
			if(fa[j])f[fa[j]][i]=1;
    	}
    }
    for(int i=1;i<=n;i++)f[i][i]=1;
    for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)if(f[i][k])f[i]|=f[k];
    for(int i=1;i<=n;i++)f[i][i]=0;
    // for(int i=1;i<=n;i++){
    	// for(int j=1;j<=n;j++)cout<<f[i][j];cout<<"\n";
    // }
    flow::s=2*n+1,flow::t=2*n+2;
    flow::init();
    printf("%d\n",n-flow::dinic());
    flow::dfs(flow::t);
    // for(int i=1;i<=n;i++)cout<<flow::vis[i]<<" "<<flow::vis[i+n]<<"\n";
    vector<int> ans;
    for(int i=1;i<=n;i++)if(flow::vis[i+n]&&!flow::vis[i])ans.pb(i);
    // printf("%d\n",ans.size());
    for(int u:ans)printf("%d ",u);
    
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}