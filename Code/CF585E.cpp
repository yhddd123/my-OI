#include<bits/stdc++.h>
// #define int long long
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
const int maxn=500010;
const int maxm=10000010;
const int inf=1e9;

int n,m=10000000,t[maxm];
int pre[maxm],cnt;
bool vis[maxm];
int mu[maxm];
int pw[maxn];
long long ans;
void work(){
    n=read();
    for(int i=1;i<=n;i++)t[read()]++;
    for(int i=1;i<=m;i++){
    	for(int j=2*i;j<=m;j+=i)t[i]+=t[j];
    }
    mu[1]=1;for(int i=2;i<=m;i++){
        if(!vis[i])pre[++cnt]=i,mu[i]=mod-1;
        for(int j=1;j<=cnt&&i*pre[j]<=m;j++){
            vis[i*pre[j]]=1;
            if(i%pre[j]==0){mu[i*pre[j]]=0;break;}
            mu[i*pre[j]]=mod-mu[i];
        }
    }
    pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
    for(int i=1;i<=m;i++)if(t[i]){
	    // cout<<i<<" "<<mu[i]<<" "<<1ll*n*(pw[t[i]]-1)%mod<<" "<<1ll*t[i]*pw[t[i]-1]%mod<<" "<<t[i]<<"\n";
	    (ans+=1ll*mu[i]*(2ll*t[i]*pw[t[i]-1]%mod+mod-t[i]+mod-1ll*n*(pw[t[i]]-1)%mod))%=mod;
    }
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}