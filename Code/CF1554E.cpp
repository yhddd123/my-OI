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
const int inf=1e9;
bool mbe;

int n,ans[maxn];
int d[maxn],a[maxn];
vector<int> e[maxn];
int pre[maxn],cnt,f[maxn];
bool vis[maxn];
void init(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i])pre[++cnt]=i,f[i]=i;
        for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
            vis[i*pre[j]]=1;f[i*pre[j]]=pre[j];
            if(i%pre[j]==0)break;
        }
    }
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)e[i].clear();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        e[u].pb(v),e[v].pb(u);
    }
    int x=n-1;while(x>1){
        int g=f[x];while(f[x]==g)x/=f[x];
        for(int i=1;i<=n;i++)a[i]=0,d[i]=e[i].size();
        queue<int> q;
        for(int i=1;i<=n;i++)if(d[i]==1)q.push(i);
        bool fl=1;int rt=0;
        while(!q.empty()){
            int u=q.front(),fa=0;q.pop();
            for(int v:e[u])if(d[v])fa=v;
            if(!fa)break;
            if(a[u]%g==0)a[fa]++;
            else if((a[u]+1)%g==0)a[u]++;
            else{fl=0;break;}
            d[u]=0,d[fa]--,rt=fa;
            if(d[fa]==1)q.push(fa);
        }
        // for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
        if(a[rt]%g!=0)fl=0;
        if(fl){
            int val=0;for(int i=1;i<=n;i++)val=__gcd(val,a[i]);
            ans[val]=1;
        }
    }
    ans[1]=1;for(int i=1;i<n;i++)ans[1]=ans[1]*2%mod;
    for(int i=2;i<=n;i++)ans[1]-=ans[i];ans[1]+=mod,ans[1]%=mod;
    for(int i=1;i<=n;i++)printf("%lld ",ans[i]),ans[i]=0;puts("");
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();init(maxn-10);
    while(T--)work();
}