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
const int maxn=500010;
const int inf=1e18;

int n,p[maxn],ans;
int f[maxn][maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)p[i]=-1;
    for(int i=1;i<=n;i++)p[read()]=i&1;
    for(int i=1;i<=n;i++)for(int j=0;j<=(n+1)/2;j++)f[i][j]=inf;
    if(p[1]==0||p[1]==-1)f[1][0]=0;
    if(p[1]==1||p[1]==-1)f[1][1]=0;
    for(int i=1;i<n;i++){
        for(int j=0;j<=i&&j<=(n+1)/2;j++){
            f[i][j]+=j*(n/2-(i-j))+(i-j)*((n+1)/2-j);
            if(p[i+1]==0||p[i+1]==-1)f[i+1][j]=min(f[i+1][j],f[i][j]);
            if(p[i+1]==1||p[i+1]==-1)f[i+1][j+1]=min(f[i+1][j+1],f[i][j]);
        }
    }
    ans=0;for(int i=1;i<=n;i++)ans+=i*i;ans-=f[n][(n+1)/2];
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}