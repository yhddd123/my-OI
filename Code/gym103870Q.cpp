#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m,q;
bool vis[maxn];
int dp[maxn];
vector<int> id;
int pre[maxn],cnt;
bool bk[maxn];
void init(int n){
    for(int i=2;i<=n;i++){
        if(!bk[i])pre[++cnt]=i;
        for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
            bk[i*pre[j]]=1;
            if(i%pre[j]==0)break;
        }
    }
}
void work(){
    n=read();m=read();q=read();init(n);
    for(int i=1;i<=n;i++)id.pb(n/i);
    sort(id.begin(),id.end());
    id.erase(unique(id.begin(),id.end()),id.end());
    // for(int u:id)cout<<u<<" ";cout<<"\n";
    for(int u:id)dp[u]=u;
    for(int i=1;i<=m;i++){
        int p=i;vis[i]=1;p=pre[p];
        for(int j=id.size()-1;~j;j--)dp[id[j]]-=dp[id[j]/p];
    }
    // for(int u:id)cout<<u<<" "<<dp[u]<<"\n";
    // printf("%lld\n",n-dp[n]);
    while(q--){
        int p=read();
        if(vis[p]){
            vis[p]=0;p=pre[p];
            for(int j=0;j<id.size();j++)dp[id[j]]+=dp[id[j]/p];
        }
        else{
            vis[p]=1;p=pre[p];
            for(int j=id.size()-1;~j;j--)dp[id[j]]-=dp[id[j]/p];
        }
        write(n-dp[n]),puts("");
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