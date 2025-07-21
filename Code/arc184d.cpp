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
const int inf=1e9;

int n;
pii a[maxn];
int num[maxn][maxn],dp[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)a[i]={read(),read()};
    a[n+1]={0,n+1},a[n+2]={n+1,0};n+=2;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=i+1;k<j;k++)if(a[i].se>a[k].se&&a[k].se>a[j].se)num[i][j]++;
        }
    }
    dp[1]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<i;j++)if(a[j].se>a[i].se){
            bool fl=1;for(int k=j+1;k<i;k++)if(a[j].se>a[k].se&&a[k].se>a[i].se&&num[j][k]+num[k][i]+1==num[j][i]){fl=0;break;}
            if(fl)(dp[i]+=dp[j])%=mod;
        }
    }
    printf("%lld\n",dp[n]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}