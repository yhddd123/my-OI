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
const int maxn=100010;
const int inf=1e9;

int n,m=100001,t[maxn],dp[maxn];
void work(){
    n=read();
    for(int i=1;i<=n;i++)t[read()]++;
    for(int i=2;i<=m;i++)dp[i]=max(dp[i-1],dp[i-2]+t[i-1]);
    printf("%lld\n",n-dp[m]);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}