#include<bits/stdc++.h>
#include <cstdio>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
const int maxn=5000010;
const ll inf=1e18;

int n;ll ans=inf;
char s[maxn<<1];
int fa[maxn];
int dep[maxn],mxd[maxn],sed[maxn],son[maxn],top[maxn];
int num[maxn];ll sum[maxn];
ll f[maxn];
int st[maxn],tp;
void upd(int u,int v,int w){
    f[u]=min(f[u],f[v]+sum[v]-sum[u]-1ll*(num[v]-num[u])*dep[v]+max(dep[u]-max(w,dep[v]),0));
}
void work(){
    scanf("%d%s",&n,s+1);
    for(int i=1,idx=0,u=0;i<=2*n;i++){
        if(s[i]=='(')fa[++idx]=u,u=idx;
        else u=fa[u];
    }
    for(int i=2;i<=n;i++)dep[i]=dep[fa[i]]+1;
    for(int i=n;i;i--){
        if(!num[i])num[i]=1,sum[i]=mxd[i]=dep[i];
        num[fa[i]]+=num[i],sum[fa[i]]+=sum[i];
        if(mxd[fa[i]]<mxd[i])mxd[fa[i]]=mxd[i],son[fa[i]]=i;
    }
    for(int i=n;i;i--)if(i!=son[fa[i]])sed[fa[i]]=max(sed[fa[i]],mxd[i]);
    for(int i=1;i<=n;i++){
        if(i==1||i!=son[fa[i]])top[i]=i;
        else top[i]=top[fa[i]];
    }
    // for(int i=1;i<=n;i++)cout<<fa[i]<<" "<<top[i]<<" "<<son[i]<<" "<<mxd[i]<<" "<<sed[i]<<"\n";
    for(int i=1;i<=n;i++)f[i]=inf;f[1]=0;
    for(int i=1;i<=n;i++)if(top[i]==i){
        if(i!=1){
            for(int u=i;u;u=son[u])upd(u,fa[i],mxd[fa[i]]);
        }
        tp=0;
        for(int u=i;u;u=son[u]){
            if(u!=i)upd(u,fa[u],sed[fa[u]]);
            while(tp&&sed[st[tp]]<dep[u])tp--;
            if(tp)upd(u,st[tp],sed[st[tp]]);
            while(tp&&sed[st[tp]]<=sed[u])tp--;
            st[++tp]=u;
        }
    }
    // for(int i=1;i<=n;i++)cout<<f[i]<<" "<<num[i]<<" "<<sum[i]<<"\n";
    for(int i=1;i<=n;i++)ans=min(ans,f[i]+sum[i]-1ll*dep[i]*num[i]);
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}