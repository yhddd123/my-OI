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
const int maxn=410;
const int maxm=100010;
const int inf=1e9;
bool mbe;

int n,m,ans;
pii a[maxm];
bool fl[maxn];
bool vis[maxn][maxn];
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++)a[i]={read(),read()};
    for(int i=1;i<=n;i++){
        vis[i][i]=1;
        for(int j=m;j;j--){
            if(!vis[i][a[j].fi]&&!vis[i][a[j].se])continue;
            if(vis[i][a[j].fi]&&vis[i][a[j].se])fl[i]=1;
            vis[i][a[j].fi]=vis[i][a[j].se]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(!fl[i]&&!fl[j]){
                bool flag=1;
                for(int k=1;k<=n;k++)if(vis[i][k]&&vis[j][k])flag=0;
                if(flag)++ans;
            }
        }
    }
    printf("%lld\n",ans);
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