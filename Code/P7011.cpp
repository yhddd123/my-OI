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
const int inf=1e12;

int n,t,a[maxn];
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
map<int,int> mp[maxn];
void insert(int u,int x,int y){
    auto it=mp[u].upper_bound(x);
    if(it!=mp[u].begin()){
        it--;
        if(x<=(*it).fi+(*it).se)(*it).se+=y,x=(*it).fi;
        else mp[u][x]=y;
    }
    else mp[u][x]=y;
    it=mp[u].upper_bound(x);
    while(it!=mp[u].end()&&(*it).fi<=x+mp[u][x]){
        mp[u][x]+=(*it).se;
        it=mp[u].erase(it);
    }
}
void dfs(int u,int fa){
    mp[u].clear();
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==fa)continue;
        dfs(v,u);
        if(mp[u].size()<mp[v].size())swap(mp[u],mp[v]);
        for(auto[x,y]:mp[v])insert(u,x,y);
    }
    if(a[u]>0)insert(u,0,a[u]);
    if(a[u]<0){
        int k=-a[u];
        while(mp[u].size()){
            auto[x,y]=*mp[u].begin();mp[u].erase(mp[u].begin());
            if(y<=k)k-=y;
            else{
                mp[u][x+k]=y-k;
                break;
            }
        }
    }
    // cout<<u<<"\n";
    // for(auto[x,y]:mp[u])cout<<x<<" "<<x+y<<"\n";
}
void work(){
    n=read();t=read();
    for(int i=1;i<=n;i++)a[i]=read();a[++n]=2*inf;
    for(int i=1;i<=n;i++)head[i]=0;tot=0;
    for(int i=1;i<n-1;i++){
        int u=read(),v=read();
        add(u,v),add(v,u);
    }
    add(t,n),add(n,t);
    dfs(1,0);
    if(mp[1].size()&&(*mp[1].begin()).fi==0&&(*mp[1].begin()).se>=inf)puts("escaped");
    else puts("trapped");
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}