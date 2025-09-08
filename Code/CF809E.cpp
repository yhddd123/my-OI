#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int inf=1e9;
bool mbe;

int n,a[maxn],b[maxn],ans;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int dfn[maxn],siz[maxn],st[18][maxn],idx,dep[maxn];
void dfs(int u,int fa){
    st[0][dfn[u]=++idx]=fa,siz[u]=1;dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);siz[u]+=siz[v];
    }
}
int mmax(int u,int v){return dfn[u]<dfn[v]?u:v;}
int lca(int u,int v){
    if(u==v)return u;
    u=dfn[u],v=dfn[v];
    if(u>v)swap(u,v);u++;
    int k=__lg(v-u+1);
    return mmax(st[k][u],st[k][v-(1<<k)+1]);
}
int pre[maxn],cnt;
bool vis[maxn];
int phi[maxn],mu[maxn];
void init(int n){
    phi[1]=1,mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i])pre[++cnt]=i,phi[i]=i-1,mu[i]=mod-1;
        for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
            vis[i*pre[j]]=1;
            if(i%pre[j]==0){
                phi[i*pre[j]]=phi[i]*pre[j],mu[i*pre[j]]=0;
                break;
            }
            phi[i*pre[j]]=phi[i]*(pre[j]-1),mu[i*pre[j]]=mod-mu[i];
        }
    }
}
int f[maxn];
int id[maxn<<1],m,stk[maxn],tp,fa[maxn];
int val[maxn],sum[maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]=i;
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    dfs(1,0);
    for(int j=1;j<18;j++){
        for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    init(n);
    for(int i=1;i<=n;i++){
        m=0;for(int j=i;j<=n;j+=i)id[++m]=b[j],val[b[j]]=sum[b[j]]=phi[j];
        sort(id+1,id+m+1,[&](int u,int v){return dfn[u]<dfn[v];});
        for(int j=1;j<m;j++)id[j+m]=lca(id[j],id[j+1]);id[2*m]=lca(id[1],id[m]);
        m=2*m;sort(id+1,id+m+1,[&](int u,int v){return dfn[u]<dfn[v];});m=unique(id+1,id+m+1)-id-1;
        tp=0;for(int j=1;j<=m;j++){
            int u=id[j];
            while(tp&&dfn[u]>=dfn[stk[tp]]+siz[stk[tp]])tp--;
            fa[u]=stk[tp];stk[++tp]=u;
        }
        for(int j=1,s1=0,s2=0;j<=m;j++){
            int u=id[j];
            (f[i]+=s1*val[u]%mod*dep[u])%=mod,(f[i]+=s2*val[u])%=mod;
            (s1+=val[u])%=mod,(s2+=val[u]*dep[u])%=mod;
        }
        for(int j=m;j;j--){
            int u=id[j];
            (f[i]+=mod-2*sum[fa[u]]*sum[u]%mod*dep[fa[u]]%mod)%=mod;
            (sum[fa[u]]+=sum[u])%=mod;
        }
        for(int j=1;j<=m;j++)val[id[j]]=sum[id[j]]=0;
    }
    // for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
    for(int i=n;i;i--){
        for(int j=2*i;j<=n;j+=i)(f[i]+=mod-f[j])%=mod;
    }
    // for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
    for(int i=1;i<=n;i++)(ans+=i*ksm(phi[i])%mod*f[i])%=mod;
    // printf("%lld\n",ans);
    ans=ans*2*ksm(n*(n-1)%mod)%mod;
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}