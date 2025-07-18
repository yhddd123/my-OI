#include<bits/stdc++.h>
// #define int long long
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
const int inf=1e9;

int n;
bool e[maxn][maxn];
vector<int> g[maxn];
char s[maxn];
int ans[maxn][maxn];
bool vis[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        for(int j=1;j<=n;j++)e[i][j]=(s[j]=='1');
    }
    pii p={0,0};
    if(n&1){
        n++;
        for(int i=1;i<n;i++){
            for(int j=i+1;j<n;j++)if(!e[i][j]){
                e[i][j]=e[j][i]=1;
                for(int k=1;k<n;k++)if(i!=k&&j!=k)e[k][n]=e[n][k]=1;
                p={i,j};
                break;
            }
            if(p.fi)break;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)if(i!=j&&!e[i][j])g[i].pb(j);
    }
    vector<vector<int>> cyc[2];
    for(int i=1;i<=n;i++)if(!vis[i]){
        vector<int> a;
        int x=i,y=g[i][0];
        while(!vis[x]){
            a.pb(x),vis[x]=1;
            x=e[y][0]+e[y][1]-x;
            swap(x,y);
        }
        cyc[a.size()&1].pb(a);
    }
    
    if(p.fi){
        n--;
        ans[p.fi][p.se]=ans[p.se][p.fi]=-1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)printf("%d ",ans[i][j]);puts("");
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}