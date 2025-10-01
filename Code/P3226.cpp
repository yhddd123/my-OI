// Problem: P3226 [HNOI2012] 集合选数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3226
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-23 16:47:06
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000001
using namespace std;
const int maxn=100010;
const int maxm=18;
const int inf=1e9;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
    return x*f;
}

int n,ans;
int a[maxm],num;
int g[maxn];
int dp[maxm][maxn];
bool vis[maxn];
void init(int x){
    for(int i=1;i<=18;i++){
        num=i;vis[x]=1;
        int y=x;
        for(int j=1;j<=12;j++){
            a[i]=j;vis[y]=1;
            y*=3;if(y>n) break;
        }
        x*=2;if(x>n)return ;
    }
}
int sovle(){
    int res=0;
    for(int i=0;i<(1<<a[1]);i++)dp[1][i]=g[i];
    for(int i=2;i<=num;i++){
        for(int j=0;j<(1<<a[i]);j++){
            if(!g[j])continue;
            dp[i][j]=0;
            for(int k=0;k<(1<<a[i-1]);k++){
                if(g[k]&&((j&k)==0))dp[i][j]+=dp[i-1][k],dp[i][j]%=mod;
            }
        }
    }
    for(int i=0;i<(1<<a[num]);i++)res+=dp[num][i],res%=mod;
    return res;
}

signed main(){
    n=read();ans=1;
    for(int i=0;i<maxn;i++){
        if((i<<1)&i)g[i]=0;
        else g[i]=1;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            init(i);
            cout<<n/i<<" "<<sovle()<<"\n";
            ans*=sovle(),ans%=mod;
        }
    }
    printf("%lld\n",ans);
}