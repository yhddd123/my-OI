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
const int maxn=5010;

int n,to[maxn];
char s[maxn];
int f[maxn],ans;
bool vis[maxn];
void work(){
    n=read();scanf("%s",s+1);ans=0;
    for(int i=1;i<=n;i++)to[i]=read();
    for(int i=1;i<=n;i++)vis[i]=0;
    int u=n,p=n+1;
    while(!vis[u])vis[u]=1,u=to[u];
    while(vis[u])p=min(u,p),vis[u]=0,u=to[u];
    for(int u=0;u<=1;u++){
        for(int v=0;v<=1;v++){
            for(int i=1;i<=n;i++){
                if(s[i]=='.')f[i]=0;
                if(s[i]=='?')f[i]=(mod+1)/2;
                if(s[i]=='C')f[i]=1;
            }
            int val=0;
            for(int i=1;i<=n;i++){
                if(i==p)val=(u?f[i]:1+mod-f[i])*(v?f[to[i]]:1+mod-f[to[i]])%mod,f[i]=u,f[to[i]]=v;
                int pi=f[i],pt=f[to[i]];
                f[i]=pi*pt%mod;
                f[to[i]]=(pi*(1+mod-pt)+pt)%mod;
                // cout<<f[i]<<" "<<f[to[i]]<<"\n";
            }
            // cout<<f[n]<<" "<<val<<"\n";
            (ans+=f[n]*val)%=mod;
        }
    }
    for(int i=1;i<=n;i++)if(s[i]=='?')ans=(ans+ans)%mod;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    for(int t=1;t<=T;t++){
        cout<<"Case #"<<t<<": ";
        work();
    }
}