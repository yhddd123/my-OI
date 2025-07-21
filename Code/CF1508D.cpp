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
const int inf=1e9;

int n,p;
struct nd{
    int x,y,v;
}a[maxn];
int f[maxn];
int fd(int x){
    if(f[x]==x)return x;
    return f[x]=fd(f[x]);
}
vector<pii> ans;
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]={read(),read(),read()};
    a[p=0]={inf,inf,0};for(int i=1;i<=n;i++)if(a[i].v!=i&&(a[i].x<a[p].x||(a[i].x==a[p].x&&a[i].y<a[p].y)))p=i;
    if(!p){puts("0");return ;}
    vector<int> id;
    for(int i=1;i<=n;i++)if(a[i].v!=i&&i!=p)id.pb(i);
    sort(id.begin(),id.end(),[&](int u,int v){return (a[u].y-a[p].y)*(a[v].x-a[p].x)<(a[v].y-a[p].y)*(a[u].x-a[p].x);});
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1;i<=n;i++)f[fd(i)]=fd(a[i].v);
    for(int i=1;i<id.size();i++)if(fd(id[i-1])!=fd(id[i])){
        ans.pb({id[i-1],id[i]});
        f[fd(id[i-1])]=fd(id[i]);
        swap(a[id[i-1]].v,a[id[i]].v);
    }
    for(int i=0;i<id.size();i++){
        ans.pb({p,a[p].v});
        swap(a[p].v,a[a[p].v].v);
    }
    printf("%lld\n",ans.size());
    for(auto[u,v]:ans)printf("%lld %lld\n",u,v);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}