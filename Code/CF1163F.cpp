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
const int maxn=200010;
const int inf=1e18;

int n,m,q;
int head[maxn],tot=1;
struct nd{
    int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dis1[maxn],disn[maxn],pre[maxn],suf[maxn],eid[maxn];
bool vis[maxn],bk[maxn];int fl[maxn];
int st[maxn],tp;
int res[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mn[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int w){
    if(l>=ql&&r<=qr){mn[nd]=min(mn[nd],w);return ;}
    if(ql<=mid)updata(ls,l,mid,ql,qr,w);
    if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
void down(int nd,int l,int r){
    if(l==r){res[l]=mn[nd];return ;}
    mn[ls]=min(mn[nd],mn[ls]),mn[rs]=min(mn[nd],mn[rs]);
    down(ls,l,mid),down(rs,mid+1,r);
}
void work(){
    n=read();m=read();q=read();
    map<pair<pii,int>,int> mp;
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
        mp[{{u,v},w}]=mp[{{v,u},w}]=i;
    }
    {
    priority_queue<pii> q;
    for(int i=1;i<=n;i++)dis1[i]=inf,vis[i]=0;
    q.push({dis1[1]=0,1});
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(dis1[v]>dis1[u]+e[i].w){
                dis1[v]=dis1[u]+e[i].w;pre[v]=u,eid[v]=i/2;
                q.push({-dis1[v],v});
            }
        }
    }
    for(int i=1;i<=n;i++)disn[i]=inf,vis[i]=0;
    q.push({disn[n]=0,n});
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=1;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;
            if(disn[v]>disn[u]+e[i].w){
                disn[v]=disn[u]+e[i].w;
                q.push({-disn[v],v});
            }
        }
    }
    }
    tp=0;for(int u=n;u;u=pre[u])st[++tp]=u;
    reverse(st+1,st+tp+1);
    for(int i=1;i<tp;i++)fl[eid[st[i+1]]]=i;
    for(int i=1;i<=tp;i++)bk[st[i]]=1;
    for(int i=1;i<=n;i++)pre[i]=suf[i]=0;
    for(int ii=1;ii<=tp;ii++){
        queue<int> q;
        q.push(st[ii]);pre[st[ii]]=ii;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];i;i=e[i].nxt){
                int v=e[i].to;
                if(!bk[v]&&dis1[v]==dis1[u]+e[i].w&&!pre[v])pre[v]=ii,q.push(v);
            }
        }
    }
    for(int ii=tp;ii;ii--){
        queue<int> q;
        q.push(st[ii]);suf[st[ii]]=ii;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=head[u];i;i=e[i].nxt){
                int v=e[i].to;
                if(!bk[v]&&disn[v]==disn[u]+e[i].w&&!suf[v])suf[v]=ii,q.push(v);
            }
        }
    }
    // for(int i=1;i<=n;i++)cout<<pre[i]<<" ";cout<<"\n";
    // for(int i=1;i<=n;i++)cout<<suf[i]<<" ";cout<<"\n";
    for(int i=1;i<=4*tp;i++)mn[i]=inf;
    for(int i=1;i<=m;i++)if(!fl[i]){
        int u=e[2*i].to,v=e[2*i+1].to;
        if(pre[u]<suf[v])updata(1,1,tp-1,pre[u],suf[v]-1,dis1[u]+e[2*i].w+disn[v]);
        swap(u,v);
        if(pre[u]<suf[v])updata(1,1,tp-1,pre[u],suf[v]-1,dis1[u]+e[2*i].w+disn[v]);
    }
    down(1,1,tp-1);
    // for(int i=1;i<tp;i++)cout<<res[i]<<" ";cout<<"\n";
    while(q--){
        int p=read(),w=read(),ans=inf;
        ans=min(ans,dis1[e[2*p].to]+disn[e[2*p+1].to]+w);
        ans=min(ans,dis1[e[2*p+1].to]+disn[e[2*p].to]+w);
        if(fl[p])ans=min(ans,res[fl[p]]);
        else ans=min(ans,dis1[n]);
        printf("%lld\n",ans);
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}