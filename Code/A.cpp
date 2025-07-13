#include<bits/stdc++.h>
#include <queue>
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
const int maxn=300010;
const int inf=1e18;

int n,m;
int head[maxn],tot=1;
struct nd{
    int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int val[maxn];
int dis[maxn],dis1[maxn];
int fr[maxn];
bool vis[maxn];
void dij(int s){
    priority_queue<pii> q;
    for(int i=1;i<=n;i++)dis[i]=inf,vis[i]=0;
    q.push({dis[s]=0,s});
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].w){
                dis[v]=dis[u]+e[i].w;
                if(s==1)fr[v]=u;
                q.push({-dis[v],v});
            }
        }
    }
}
bool bk[maxn],fl[maxn];
int pre[maxn],suf[maxn];
int st[maxn],tp;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
#define all 1,1,tp-1
int mn[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr){mn[nd]=min(mn[nd],w);return ;}
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
int res[maxn],ans;
void down(int nd,int l,int r){
    if(l==r){res[l]=mn[nd];return ;}
    mn[ls]=min(mn[ls],mn[nd]),mn[rs]=min(mn[rs],mn[nd]);
    down(ls,l,mid),down(rs,mid+1,r);
}
void work(){
    n=read();m=read();
    map<pii,int> mp;
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        val[i]=w;mp[{u,v}]=mp[{v,u}]=i;
        add(u,v,w),add(v,u,w);
    }
    for(int i=m;i;i--)val[i]=max(val[i],val[i+1]);
    dij(1);for(int i=1;i<=n;i++)dis1[i]=dis[i];dij(n);
    for(int u=n;u;u=fr[u])st[++tp]=u,bk[u]=1;
    reverse(st+1,st+tp+1);
    for(int i=1;i<tp;i++)fl[mp[{st[i],st[i+1]}]]=1;
    for(int i=1;i<=n;i++)vis[i]=0,pre[i]=suf[i]=-1;
    queue<int> q;
    for(int ii=1;ii<=tp;ii++){
        q.push({st[ii]});pre[st[ii]]=ii;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];i;i=e[i].nxt){
                int v=e[i].to;
                if(!bk[v]&&dis1[v]==dis1[u]+e[i].w&&pre[v]==-1){
                    pre[v]=pre[u];q.push(v);
                }
            }
        }
    }
    for(int ii=tp;ii;ii--){
        q.push({st[ii]});suf[st[ii]]=ii;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];i;i=e[i].nxt){
                int v=e[i].to;
                if(!bk[v]&&dis[v]==dis[u]+e[i].w&&suf[v]==-1){
                    suf[v]=suf[u];q.push(v);
                }
            }
        }
    }
    memset(mn,0x3f,sizeof(mn));
	for(int i=2;i<=tot;i+=2){
		int u=e[i].to,v=e[i+1].to;
		if(fl[i/2])continue;
		if(pre[u]<suf[v]){
			updata(all,pre[u],suf[v]-1,dis1[u]+dis[v]+e[i].w);
		}
		swap(u,v);
		if(pre[u]<suf[v]){
			updata(all,pre[u],suf[v]-1,dis1[u]+dis[v]+e[i].w);
		}
	}
    down(all);
    for(int i=1;i<tp;i++){
	    	// cout<<i<<" "<<res[i]<<" "<<st[i]<<" "<<st[i+1]<<"\n";
        res[i]=min(res[i],dis[1]+val[mp[{st[i],st[i+1]}]+1]);
        ans=max(ans,res[i]);
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
    
    T=1;
    while(T--)work();
}