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
const int maxn=50010;
const int B=512;
const int inf=1e9;
bool mbe;

int n,a[6][maxn];
int iid[5][maxn];
int dp[maxn];
bitset<B> f[maxn];
bool chk(int i,int j){
    return a[0][i]<=a[0][j]&&a[1][i]<=a[1][j]&&a[2][i]<=a[2][j]&&a[3][i]<=a[3][j]&&a[4][i]<=a[4][j];
}
int id[maxn],rnk[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++){
        for(int j=0;j<=5;j++)a[j][i]=read();
        for(int j=0;j<5;j++)iid[j][i]=i;
    }
    for(int i=1;i<=n;i++)dp[i]=0;
    for(int j=0;j<5;j++)sort(iid[j]+1,iid[j]+n+1,[&](int u,int v){return a[j][u]<a[j][v]||(a[j][u]==a[j][v]&&u<v);});
    for(int i=1;i<=n;i++)id[i]=i;
    for(int l=1,r;l<=n;l=r+1){
        r=min(l+B-1,n);
        for(int i=l;i<=r;i++){
            dp[i]+=a[5][i];
            for(int j=i+1;j<=r;j++)if(chk(i,j))dp[j]=max(dp[i],dp[j]);
        }
        sort(id+l,id+r+1,[&](int i,int j){return dp[i]>dp[j];});
        for(int i=l;i<=r;i++)rnk[id[i]]=i-l;
        for(int i=0;i<5;i++){
            bitset<B> cur;
            for(int jj=1;jj<=n;jj++){
                int j=iid[i][jj];
                if(j<l)continue;
                if(j<=r)cur.set(rnk[j]);
                else{
                    i?f[j]&=cur:f[j]=cur;
                }
            }
        }
        for(int i=r+1;i<=n;i++){
            int p=f[i]._Find_first()+l;
            if(p>r)continue;
            dp[i]=max(dp[i],dp[id[p]]);
        }
    }
    for(int i=1;i<=n;i++)printf("%lld\n",dp[i]);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}