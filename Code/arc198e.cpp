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
const int maxn=24;
const int inf=1e9;
bool mbe;

int n,m,a[1<<maxn];
int f[(1<<maxn)+1],g[1<<maxn],sf[1<<maxn],sg[1<<maxn];
inline void inc(int &u,int v){u+=v-mod;u+=(u>>31)&mod;}
void sovle(int l,int r){
    if(l+1==r){
    	inc(sf[l],f[l]);
    	// cout<<l<<" "<<a[l]<<" "<<sf[l]<<" "<<sg[l]<<"\n";
    	f[r]=g[l]=(1ll*a[l]*sf[l]%mod+mod-sg[l])%mod;
    	sf[l]=f[l],sg[l]=g[l];
        return ;
    }
    int mid=l+r>>1;
    sovle(l,mid);
    for(int i=l,j=mid;i<mid;i++,j++)inc(sf[j],sf[i]),inc(sg[j],sg[i]);
    sovle(mid,r);
    for(int i=l,j=mid;i<mid;i++,j++)inc(sf[j],sf[i]),inc(sg[j],sg[i]);
}
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++)a[read()]++;
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++)if(s&(1<<i))(a[s]+=a[s^(1<<i)])%=mod;
    }
    // for(int s=0;s<(1<<n);s++)cout<<a[s]<<" ";cout<<"\n";
    f[0]=1;sovle(0,(1<<n));
    // for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
    // for(int s=0;s<(1<<n);s++)cout<<g[s]<<" ";cout<<"\n";
    printf("%lld\n",f[1<<n]);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}