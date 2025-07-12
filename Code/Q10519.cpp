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
const int maxn=500010;
const int inf=1e9;

int n,a[maxn],b[maxn],ans;
int pre[maxn],cnt;
bool vis[maxn];
int p[maxn];
void init(int n){
    p[1]=1;for(int i=2;i<=n;i++){
        if(!vis[i])pre[++cnt]=i,p[i]=i;
        for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
            vis[i*pre[j]]=1,p[i*pre[j]]=pre[j];
            if(i%pre[j]==0)break;
        }
    }
}
pii f[maxn],g[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)b[i]=read();
    init(maxn-10);
    for(int i=1;i<=n;i++){
        int val=0;
        int x=a[i];
        while(x!=1){
            int pp=p[x];
            val=max(val,f[pp].se==b[i]?g[pp].fi:f[pp].fi);
            while(x%pp==0)x/=pp;
        }
        val++;
        x=a[i];
        while(x!=1){
            int pp=p[x];
            if(b[i]==f[pp].se)f[pp].fi=max(f[pp].fi,val);
            else if(val>f[pp].fi)g[pp]=f[pp],f[pp]={val,b[i]};
            else if(val>g[pp].fi)g[pp].fi=val;
            while(x%pp==0)x/=pp;
        }
        ans=max(ans,val);
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}