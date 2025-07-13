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

int n,a[maxn];
int head[maxn],tot;
struct nd{
    int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
priority_queue<int> q[maxn];
void dfs(int u){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;dfs(v);
        if(q[u].size()<q[v].size())swap(q[u],q[v]);
        vector<int> val;
        while(q[u].size()&&q[v].size()){
            val.pb(max(q[u].top(),q[v].top()));q[u].pop(),q[v].pop();
        }
        for(int vv:val)q[u].push(vv);
    }
    q[u].push(a[u]);
}
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=2;i<=n;i++)add(read(),i);
    dfs(1);
    int sum=0;while(q[1].size())sum+=q[1].top(),q[1].pop();
    printf("%lld\n",sum);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}