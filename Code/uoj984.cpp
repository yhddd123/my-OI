#include<bits/stdc++.h>
#include <functional>
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
const int maxn=1000010;
const int inf=1e18;

int n;
pii a[maxn];
int st[maxn],tp;
int l[maxn],r[maxn];
int pre[maxn],nxt[maxn],val[maxn];
bool vis[maxn];
int ans[maxn],m;
void work(){
    n=read();
    for(int i=1;i<=2*n;i++)a[i]={read(),i<=n};
    sort(a+1,a+2*n+1);
    for(int i=1;i<=2*n;i++){
        if(a[i].se)st[++tp]=i;
        else if(tp)r[st[tp]]=i,l[i]=st[tp],tp--;
    }
    tp=0;for(int i=1;i<=2*n;i++){
        if(!a[i].se)st[++tp]=i;
        else if(tp)r[st[tp]]=i,l[i]=st[tp],tp--;
    }
    for(int p=1;p<=2*n;p++)if(!l[p]){
        tp=0;for(int u=p;u;u=r[u])st[++tp]=u;
        if(tp==1)continue;
        // cout<<p<<"\n";
        // for(int i=1;i<=tp;i++)cout<<a[st[i]].fi<<" ";cout<<"\n";
        for(int i=1;i<tp;i++)pre[i]=i-1,nxt[i]=i+1,vis[i]=0,val[i]=a[st[i+1]].fi-a[st[i]].fi;
        pre[0]=0,nxt[0]=1,vis[0]=0;pre[tp]=tp-1,nxt[tp]=tp,vis[tp]=0;val[0]=val[tp]=inf;
        priority_queue<pii,vector<pii>,greater<pii>> q;
        for(int i=1;i<tp;i++)q.push({val[i],i});
        for(int t=1;t<=tp/2;t++){
            while(!q.empty()&&vis[q.top().se])q.pop();
            int u=q.top().se;q.pop();
            if(vis[u])continue;
            // cout<<u<<" "<<val[u]<<"\n";
            ans[++m]=val[u];
            val[u]=val[pre[u]]+val[nxt[u]]-val[u];
            vis[pre[u]]=vis[nxt[u]]=1;
            // cout<<u<<" "<<pre[u]<<" "<<nxt[u]<<" "<<val[u]<<"\n";
            pre[u]=pre[pre[u]],nxt[pre[u]]=u;
            nxt[u]=nxt[nxt[u]],pre[nxt[u]]=u;
            q.push({val[u],u});
        }
    }
    // cout<<m<<"\n";
    sort(ans+1,ans+n+1);
    for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
    for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}