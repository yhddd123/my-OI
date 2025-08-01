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
const int maxn=30010;
const int inf=1e9;
bool mbe;

int n,k;
int to[maxn*20][2],siz[maxn*20],idx;
void insert(int w){
    siz[1]++;
    for(int i=19,nd=1;~i;i--){
        int c=(w>>i)&1;
        if(!to[nd][c])to[nd][c]=++idx;
        nd=to[nd][c];siz[nd]++;
    }
}
int dfs(int u,int v,int d=19){
    if(!u||!v)return siz[u]+siz[v];
    if(u==v){
        if(k&(1<<d))return dfs(to[u][0],to[u][1],d-1);
        else return max(dfs(to[u][0],to[u][0],d-1),dfs(to[u][1],to[u][1],d-1));
    }
    else{
        if(k&(1<<d))return dfs(to[u][0],to[v][1],d-1)+dfs(to[v][0],to[u][1],d-1);
        else return max({dfs(to[u][0],to[v][0],d-1),dfs(to[u][1],to[v][1],d-1),siz[u],siz[v]});
    }
}
void work(){
    n=read();k=read()+1;
    while(idx)to[idx][0]=to[idx][1]=0,siz[idx]=0,idx--;idx=1;
    for(int i=1;i<=n;i++)insert(read());
    printf("%lld\n",dfs(1,1));
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