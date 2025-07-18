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
const int maxn=300010;
const int inf=1e9;

int n,k,a[maxn],ans;
int pre[maxn],suf[maxn];
int st[19][maxn];
int que(int l,int r){
    l++;if(l>r)return 0;
    int k=__lg(r-l+1);
    return __gcd(st[k][l],st[k][r-(1<<k)+1]);
}
void work(){
    n=read();k=read();ans=0;
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<=n;i++)pre[i]=__gcd(pre[i-1],a[i]);
    suf[n+1]=0;for(int i=n;i;i--)suf[i]=__gcd(suf[i+1],a[i]);
    ans=pre[n];
    for(int i=2;i<=n;i++)st[0][i]=abs(a[i]-a[i-1]);
    for(int j=1;j<=18;j++){
        for(int i=2;i+(1<<j)-1<=n;i++)st[j][i]=__gcd(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    for(int i=1;i<=n;i++)if(pre[i-1]!=pre[i]){
        for(int j=i;j<=n;j++){
            ans=max(ans,__gcd(__gcd(pre[i-1],suf[j+1]),__gcd(que(i,j),a[j]+k)));
            // cout<<i<<" "<<j<<" "<<ans<<"\n";
        }
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}