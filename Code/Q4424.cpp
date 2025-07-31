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

int n,k,ans;
int a[maxn],b[maxn];
vector<pii> res;
int fr[maxn],to[maxn],id[maxn];
unordered_map<int,int> pos;
void work(){
    n=read();k=read();ans=0;res.clear();
    for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
    pos.clear();for(int i=1;i<=n;i++)pos[b[i]]=i;
    for(int i=1;i<=n;i++)to[i]=pos[a[i]],fr[pos[a[i]]]=i;
    for(int i=1;i<=n;i++)id[i]=i;
    sort(id+1,id+n+1,[&](int u,int v){return b[u]<b[v];});
    // for(int i=1;i<=n;i++)cout<<to[i]<<" ";cout<<"\n";
    for(int ii=1;ii<=n;ii++){
        int i=id[ii];
        if(a[i]==b[i])continue;
        int u=fr[i],v=to[i],p=i;
        // cout<<i<<" "<<u<<" "<<v<<"\n";
        while(u!=i){
            if(a[u]<a[i]&&a[i]<=b[u]){p=u;break;}
            if(a[v]<a[i]&&a[i]<=b[v]){p=v;break;}
            u=fr[u],v=to[v];
        }
        res.pb({i,p});ans+=k+abs(a[i]-a[p]);
        swap(a[i],a[p]);
        // cout<<i<<" "<<a[i]<<" "<<pos[a[i]]<<"\n";
        to[i]=pos[a[i]],fr[pos[a[i]]]=i,to[p]=pos[a[p]],fr[pos[a[p]]]=p;
        // for(int j=1;j<=n;j++)cout<<to[j]<<" ";cout<<"\n";
        ii--;
    }
    printf("%lld %lld\n",ans,res.size());
    for(auto[u,v]:res)printf("%lld %lld\n",u,v);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}