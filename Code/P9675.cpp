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
const int maxn=2010;
const int inf=1e18;
bool mbe;

int n,m,x,ans;
vector<pii> e[maxn];
int f[maxn<<2][maxn],g[maxn<<2][maxn];
vector<pii> a[2];
pii que(int op,int p){
    int val=inf;pii tmp={0,0};
    for(auto[k,b]:a[op]){
        if(k*p+b<val)val=k*p+b,tmp={k,b};
    }
    return tmp;
}
void work(){
    n=read();m=read();x=read();ans=0;
    for(int i=1;i<=n;i++)e[i].clear();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read();
        e[u].pb({v,w}),e[v].pb({u,w});
    }
    for(int i=0;i<=4*n+1;i++){
        for(int j=1;j<=n;j++)f[i][j]=g[i][j]=inf;
    }
    f[0][1]=0;g[0][n]=0;
    for(int i=1;i<=4*n+1;i++){
        for(int u=1;u<=n;u++){
            for(auto[v,w]:e[u]){
                f[i][u]=min(f[i][u],f[i-1][v]+w);
                g[i][u]=min(g[i][u],g[i-1][v]+w);
            }
        }
    }
    a[0].clear(),a[1].clear();
    for(int u=1;u<=n;u++){
        int val0=inf,val1=inf;
        for(int i=0;i<=4*n;i++)val0=min(val0,f[i][u]+g[4*n-i][u]);
        for(int i=0;i<=4*n+1;i++)val1=min(val1,f[i][u]+g[4*n+1-i][u]);
        int mn=inf;for(auto[v,w]:e[u])mn=min(mn,w);
        if(val0!=inf)a[0].pb({mn,val0-4*n*mn});
        if(val1!=inf)a[1].pb({mn,val1-(4*n+1)*mn});
    }
    for(int i=1;i<=min(x,4*n+1);i++)(ans+=f[i][n]==inf?0:f[i][n])%=mod;
    // cout<<ans<<"\n";
    for(int op=0;op<2;op++){
        int p=4*n+op+2;
        while(p<=x){
            pii pp=que(op,p);
            int l=p/2+1,r=(x-op)/2,res=p;
            while(l<=r){
                int mid=(l+r>>1);
                if(que(op,2*mid+op)==pp)res=2*mid+op,l=mid+1;
                else r=mid-1;
            }
            auto[k,b]=pp;
            // cout<<p<<" "<<res<<" "<<k<<" "<<b<<" "<<k*p+b<<"\n";
            (ans+=(p+res)*((res-p)/2+1)/2%mod*k+((res-p)/2+1)*(b%mod))%=mod;
            p=res+2;
        }
    }
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}