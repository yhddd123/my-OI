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
const int maxn=14;
const int inf=1e18;

int m,n,a[maxn];
int sum[1<<maxn];
unordered_map<int,int> f[maxn][1<<maxn];
int dfs(int i,int s,int t){
    if(i==n)return inf;
    if((t&(1<<i))&&a[i]<=sum[s])return -inf;
    if(f[i][s].find(t)!=f[i][s].end())return f[i][s][t];
    if(t&(1<<i))return f[i][s][t]=min(a[i],dfs(i+1,s,t^(1<<i)));
    if(s&(1<<i)){
        int all=s^(1<<i),val=-inf;
        for(int s1=all;;s1=(s1-1)&all){
            val=max(val,dfs(i+1,s1,t)+dfs(i+1,all^s1,t));
            if(!s1)break;
        }
        return f[i][s][t]=a[i]+val;
    }
    return f[i][s][t]=dfs(i+1,s,t);
}
vector<int> ans;
void work(){
    m=read();n=read();
    for(int i=0;i<n;i++)a[i]=read();
    for(int s=1;s<(1<<n);s++)sum[s]=sum[s^(s&(-s))]+a[__lg(s&(-s))];
    for(int s=0;s<(1<<n);s++)if(sum[s]<=m&&m<dfs(0,s,(1<<n)-1-s))ans.pb(sum[s]);
    sort(ans.begin(),ans.end()),ans.erase(unique(ans.begin(),ans.end()),ans.end());
    printf("%lld\n",ans.size());
    for(int u:ans)printf("%lld ",u);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}