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
const int maxn=2010;
const int inf=1e9;

int n,m;
int a[maxn],b[maxn],c[maxn],d[maxn];
int dp[maxn][maxn];
int lshc[maxn<<1],lenc;
pii lsh[maxn*maxn];int len;
int low(pii x){return lower_bound(lsh+1,lsh+len+1,x)-lsh;}
int upp(pii x){return upper_bound(lsh+1,lsh+len+1,x)-lsh-1;}
int s1[maxn<<1][maxn],s2[maxn<<1][maxn];
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
struct sgt{
int tree[maxn*maxn<<2];
void build(int nd,int l,int r){
    tree[nd]=-inf;
    if(l==r)return;
    build(ls,l,mid);build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int p,int w){
    if(l==r){tree[nd]=max(tree[nd],w);return;}
    if(p<=mid)updata(ls,l,mid,p,w);
    else updata(rs,mid+1,r,p,w);
    tree[nd]=max(tree[ls],tree[rs]);
}
int query(int nd,int l,int r,int ql,int qr){
	if(ql>qr)return -inf;
    if(l>=ql&&r<=qr)return tree[nd];
    if(qr<=mid)return query(ls,l,mid,ql,qr);
    if(ql>mid)return query(rs,mid+1,r,ql,qr);
    return max(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
}T[2];
void work(){
    for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
    for(int i=1;i<=m;i++)c[i]=read(),d[i]=read();
    lenc=len=0;a[n+1]=c[m+1]=0;
    for(int i=1;i<=n;i++)lshc[++lenc]=a[i];
    for(int i=1;i<=m;i++)lshc[++lenc]=c[i];
    sort(lshc+1,lshc+lenc+1);lenc=unique(lshc+1,lshc+lenc+1)-lshc-1;
    for(int i=1;i<=n;i++)a[i]=lower_bound(lshc+1,lshc+lenc+1,a[i])-lshc;
    for(int i=1;i<=m;i++)c[i]=lower_bound(lshc+1,lshc+lenc+1,c[i])-lshc;
    for(int i=1;i<=lenc;i++){
        for(int j=1;j<=n;j++)s1[i][j]=s1[i][j-1]+(a[j]==i)*b[j];
        for(int j=1;j<=m;j++)s2[i][j]=s2[i][j-1]+(c[j]==i)*d[j];
    }
    lsh[++len]={inf,inf};for(int i=1;i<=lenc;i++)lsh[++len]={i,0};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)if(a[i+1]==c[j+1]){
            lsh[++len]={a[i+1],s1[a[i+1]][i]-s2[a[i+1]][j]};
        }
    }
    sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
    T[0].build(1,1,len);T[1].build(1,1,len);
    for(int i=1;i<=lenc;i++)T[0].updata(1,1,len,low({i,0}),0),T[1].updata(1,1,len,low({i,0}),0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            if(a[i]==c[j]){
                // cout<<i<<" "<<j<<"\n";
                dp[i][j]=max(dp[i][j],T[0].query(1,1,len,low({a[i],s1[a[i]][i]-s2[a[i]][j]-b[i]+1}),upp({a[i],s1[a[i]][i]-s2[a[i]][j]}))+s2[a[i]][j]);
                dp[i][j]=max(dp[i][j],T[1].query(1,1,len,low({a[i],s1[a[i]][i]-s2[a[i]][j]}),upp({a[i],s1[a[i]][i]-s2[a[i]][j]+d[j]-1}))+s1[a[i]][i]);
            }
            if(a[i+1]==c[j+1]){
                int p=low({a[i+1],s1[a[i+1]][i]-s2[a[i+1]][j]});
                T[0].updata(1,1,len,p,dp[i][j]-s2[a[i+1]][j]);
                T[1].updata(1,1,len,p,dp[i][j]-s1[a[i+1]][i]);
            }
        }
    }
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++)cout<<dp[i][j]<<" ";cout<<"\n";
    // }
    printf("%d\n",dp[n][m]);
}

signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    while(~scanf("%d%d",&n,&m))work();
}