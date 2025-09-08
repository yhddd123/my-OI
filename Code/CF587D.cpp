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
const int maxn=50010;
const int inf=1e9;
bool mbe;

int n,m;
map<int,pii> mp[maxn];
int w[maxn],lsh[maxn];
vector<int> gg[maxn];
vector<tuple<int,int,int>> g[maxn];
const int maxm=6*maxn,maxe=17*maxn;
int head[maxm],tot;
struct node{
    int nxt,to;
}e[maxe];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxm],lw[maxm],idx;
int st[maxm],tp;
int scc[maxm],scct;
void tar(int u){
    dfn[u]=lw[u]=++idx;st[++tp]=u;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(!dfn[v]){
            tar(v);
            lw[u]=min(lw[u],lw[v]);
        }
        else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
    }
    if(dfn[u]==lw[u]){
        scc[st[tp]]=++scct;
        while(st[tp--]!=u)scc[st[tp]]=scct;
    }
}
bool check(int x){
    for(int i=1;i<=6*m;i++)head[i]=0;tot=0;
    for(int i=1;i<=m;i++)if(w[i]>lsh[x])add(i,i+m);
    for(int u=1;u<=n;u++){
        for(auto[c,v1,v2]:g[u])add(v1,v2+m),add(v1+m,v2),add(v2,v1+m),add(v2+m,v1);
    }
    int num=2*m+1;
    for(int u=1;u<=n;u++){
        for(int i=0;i<gg[u].size();i++)add(num+i,gg[u][i]+m);
        for(int i=1;i<gg[u].size();i++)add(num+i,num+i-1);
        for(int i=1;i<gg[u].size();i++)add(gg[u][i],num+i-1);
        num+=gg[u].size();
        for(int i=0;i<gg[u].size();i++)add(num+i,gg[u][i]+m);
        for(int i=0;i+1<gg[u].size();i++)add(num+i,num+i+1);
        for(int i=0;i+1<gg[u].size();i++)add(gg[u][i],num+i+1);
        num+=gg[u].size();
    }
    // for(int u=1;u<=n;u++){
    	// for(int i=0;i<gg[u].size();i++){
    		// for(int j=0;j<i;j++)add(gg[u][i],gg[u][j]+m);
    		// for(int j=i+1;j<gg[u].size();j++)add(gg[u][i],gg[u][j]+m);
    	// }
    // }
    for(int i=1;i<num;i++)dfn[i]=scc[i]=0;idx=scct=0;
    for(int i=1;i<num;i++)if(!dfn[i])tar(i);
    for(int i=1;i<=m;i++)if(scc[i]==scc[i+m])return 0;
    return 1;
}
vector<int> ee[maxm];
int d[maxm],rnk[maxm],tim;
queue<int> q;
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),c=read();w[i]=lsh[i]=read();
        if(mp[u][c].se||mp[v][c].se){puts("No");return ;}
        if(!mp[u][c].fi)mp[u][c].fi=i;
        else mp[u][c].se=i;
        if(!mp[v][c].fi)mp[v][c].fi=i;
        else mp[v][c].se=i;
        gg[u].pb(i),gg[v].pb(i);
    }
    for(int u=1;u<=n;u++){
        for(auto[c,p]:mp[u])if(p.se)g[u].pb({c,p.fi,p.se});
    }
    sort(lsh+1,lsh+m+1);
    int l=0,r=m,res=m+1;
    while(l<=r){
        int mid=l+r>>1;
        if(check(mid))res=mid,r=mid-1;
        else l=mid+1;
    }
    if(res==m+1){puts("No");return ;}
    puts("Yes");
    check(res);
    for(int u=1;u<=6*m;u++){
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;if(scc[u]==scc[v])continue;
            ee[scc[u]].pb(scc[v]),d[scc[v]]++;
        }
    }
    for(int i=1;i<=scct;i++)if(!d[i])q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();rnk[u]=++tim;
        for(int v:ee[u]){
            d[v]--;
            if(!d[v])q.push(v);
        }
    }
    vector<int> ans;
    for(int i=1;i<=m;i++)if(rnk[scc[i]]>rnk[scc[i+m]])ans.pb(i);
    printf("%d %d\n",lsh[res],ans.size());
    for(int id:ans)printf("%d ",id);
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