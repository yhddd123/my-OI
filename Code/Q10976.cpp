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

int n;
pii a[maxn];
int st[maxn],tp;
pii dp[maxn];
pii operator-(pii a,pii b){return {a.fi-b.fi,a.se-b.se};}
int cross(pii a,pii b){return a.fi*b.se-a.se*b.fi;}
int q[maxn],h,t;
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]={read(),read()};
    if(n==1){puts("1"),puts("0");return ;}
    sort(a+1,a+n+1);
    for(int i=n,mx=-1;i;i--){
        if(a[i].se>mx)st[++tp]=i,mx=a[i].se;
    }
    reverse(st+1,st+tp+1);
    for(int i=1;i<=tp;i++)a[i]=a[st[i]];
    n=tp,tp=0;
    for(int i=1;i<=n;i++){
        while(tp>1&&cross(a[st[tp]]-a[st[tp-1]],a[i]-a[st[tp-1]])>=0)tp--;
        st[++tp]=i;
    }
    // for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
    dp[0]={0,0};q[h=t=1]=0;
    for(int i=1,j=1;i<=n;i++){
        dp[i]={dp[i-1].fi+1,dp[i-1].se};
        int p=a[st[j+1]].se+(a[st[j]].se-a[st[j+1]].se)*(a[st[j+1]].fi-a[i].fi)/(a[st[j+1]].fi-a[st[j]].fi);
        // cout<<i<<" "<<p<<"\n";
        while(h<t&&a[q[h]+1].se>p)h++;
        if(h<=t)dp[i]=min(dp[i],{dp[q[h]].fi+1,dp[q[h]].se+1});
        while(h<t&&dp[i]<dp[q[t]])t--;q[++t]=i;
        if(i==st[j+1])j++;
    }
    printf("%lld\n%lld\n",dp[n].fi,dp[n].se);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}