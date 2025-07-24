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
const int maxn=310;
const int maxm=500010;
const int inf=1e18;

int n,q;
int e[maxn][maxn],dis[maxn][maxn];
vector<tuple<int,int,int>> que[maxn];
int ans[maxm];
int tmp[10][maxn][maxn],dep;
void sovle(int l,int r){
    if(l==r){
        for(auto[u,v,id]:que[l])ans[id]=dis[u][v];
        return ;
    }
    int mid=l+r>>1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)tmp[dep][i][j]=dis[i][j];
    }
    for(int k=mid+1;k<=r;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        }
    }
    dep++;sovle(l,mid);dep--;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)dis[i][j]=tmp[dep][i][j];
    }
    for(int k=l;k<=mid;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        }
    }
    dep++;sovle(mid+1,r);dep--;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)dis[i][j]=tmp[dep][i][j];
    }
}
void work(){
    n=read();q=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)dis[i][j]=read();
    }
    for(int i=1;i<=q;i++){
        int u=read(),v=read(),p=read();
        que[p].pb({u,v,i});
    }
    sovle(1,n);
    for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}