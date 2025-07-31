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
const int maxn=250010;
const int inf=1e9;
bool mbe;

int n,ans;
int l[maxn],r[maxn],w[maxn],id[maxn];
int st[maxn],tp;
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn];
void add(int u,int v){
    // cout<<u<<" "<<v<<"\n";
    e[++tot]={head[u],v};head[u]=tot;}
priority_queue<int> q[maxn];
void dfs(int u){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;dfs(v);
        if(q[u].size()<q[v].size())swap(q[u],q[v]);
        vector<int> val;
        while(q[v].size()){
            val.pb(q[u].top()+q[v].top());
            q[u].pop(),q[v].pop();
        }
        for(int w:val)q[u].push(w);
    }
    // cout<<u<<" "<<q[u].size()<<"\n";
    q[u].push(w[u]);
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)l[i]=read(),r[i]=read(),w[i]=read(),id[i]=i;
    sort(id+1,id+n+1,[&](int u,int v){return r[u]<r[v]||(r[u]==r[v]&&l[u]>l[v]);});
    for(int i=1;i<=n;i++){
        while(tp&&l[st[tp]]>=l[id[i]])add(id[i],st[tp]),tp--;
        st[++tp]=id[i];
    }
    for(int i=1;i<=tp;i++)add(0,st[i]);
    dfs(0);
    for(int i=1;i<=n;i++){
        if(q[0].size())ans+=q[0].top(),q[0].pop();
        printf("%lld ",ans);
    }
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