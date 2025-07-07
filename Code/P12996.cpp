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

int n,c,ans;
int dp[maxn],sum[2][maxn];
int sovle(vector<pii> a){
    int n=a.size();
    a.pb({0,0});sort(a.begin(),a.end());
    unordered_map<int,int> mp;mp[0]=0;
    for(int i=1;i<=n;i++)sum[0][i]=sum[0][i-1],sum[1][i]=sum[1][i-1],sum[a[i].se][i]+=a[i].fi;
    for(int i=1,s=0;i<=n;i++){
        dp[i]=dp[i-1]+2*a[i].fi;
        if(i>=2)dp[i]=min(dp[i],dp[i-2]+2*a[i].fi+(a[i-1].se==a[i].se)*c);
        s+=a[i].se*2-1;
        if(mp.find(s)!=mp.end()){
            int j=mp[s];
            dp[i]=min(dp[i],dp[j]+2*(sum[a[i].se][i]-sum[a[i].se][j]));
        }
        mp[s]=i;
    }
    return dp[n];
}
void work(){
    n=read();c=read();
    vector<pii> a,b;
    for(int i=1;i<=n;i++){
        int x=read(),c=read();
        if(x>0)a.pb({x,c});
        else b.pb({-x,c});
    }
    ans=sovle(a)+sovle(b);
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    for(int t=1;t<=T;t++){
        cout<<"Case #"<<t<<": ";
        work();
    }
}