#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=30;
const int inf=1e9;

int n,a[maxn];
unordered_map<int,int> mp;
int dfs(int s){
    int k=__builtin_popcount(s);
    if(k<=1)return 1;
    if(mp[s])return mp[s];
    vector<int> idx,idy;
    for(int i=0;i<n;i++)if(s&(1ll<<i))idx.pb(i),idy.pb(i);
    sort(idy.begin(),idy.end(),[&](int u,int v){return a[u]<a[v];});
    vector<int> id(2*k);
    for(int i=0,s1=0,s2=0;i<k;i++){
        s1|=1ll<<idx[i];
        id[2*i]=s1;
        s2|=1ll<<idy[i];
        id[2*i+1]=s2;
    }
    int ans=0;
    vector<int> f(2*k-2);
    for(int i=0;i<2*k-2;i++){
        f[i]=dfs(id[i]);
        for(int j=0;j<i;j++)if((id[i]&id[j])==id[j])(f[i]+=mod-f[j]*dfs(id[i]^id[j])%mod)%=mod;
        (ans+=f[i]*dfs(s^id[i]))%=mod;
    }
    return mp[s]=ans;
}
void work(){
    n=read();
    for(int i=0;i<n;i++)a[i]=read();
    printf("%lld\n",dfs((1<<n)-1));
}

int T;
signed main(){
    freopen("A.in","r",stdin);
    freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}