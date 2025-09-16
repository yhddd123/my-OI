#include <algorithm>
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

int n,m,k,a[maxn];
vector<tuple<int,int,int>> upd[maxn];
queue<int> q;
bool vis[maxn];
void work(){
    n=read();m=read();k=read();
    for(int i=1;i<=k;i++){
        int u=read(),x=read(),v=read(),y=read();
        upd[u].pb({x-1,v,y-1});
        upd[u].pb({x,v,y});
        upd[v].pb({y-1,u,x-1});
        upd[v].pb({y,u,x});
    }
    for(int i=1;i<=n;i++){
        sort(upd[i].begin(),upd[i].end());
        reverse(upd[i].begin(),upd[i].end());
        a[i]=1;
        if(upd[i].size()&&a[i]>get<0>(upd[i].back()))q.push(i),vis[i]=1;
    }
    while(!q.empty()){
        int u=q.front();q.pop();vis[u]=0;
        while(upd[u].size()&&a[u]>get<0>(upd[u].back())){
            auto[x,v,y]=upd[u].back();upd[u].pop_back();
            if(a[v]<y+1){
                a[v]=y+1;
                if(!vis[v])q.push(v);
            }
        }
    }
    for(int i=1;i<=n;i++)if(a[i]>m){puts("-1");return ;}
    int sum=0;for(int i=1;i<=n;i++)sum+=a[i];
    printf("%lld\n",sum);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}