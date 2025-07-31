#include<bits/stdc++.h>
#include <cstdio>
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
const int maxn=17;
const int p=17;
bool mbe;

int n,m;
int a[maxn][maxn][maxn];
int f[1<<maxn][maxn],g[1<<maxn][maxn];
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int gg=ksm(3,(mod-1)/p),ig=ksm(gg);
int ni[maxn+1];
void dft(int *a,int fl=1){
    int w=(fl==1)?gg:ig;
    static int b[maxn];
    for(int i=0,bas=1;i<p;i++,bas=bas*w%mod){
        b[i]=0;
        for(int j=0,mul=1;j<p;j++,mul=mul*bas%mod)(b[i]+=mul*a[j])%=mod;
    }
    for(int i=0;i<p;i++)a[i]=b[i];
    if(fl==-1){
        for(int i=0;i<p;i++)a[i]=a[i]*ni[p]%mod;
    }
}
int ff[maxn+1][1<<maxn][maxn],hh[maxn+1][maxn];
void fmt(int f[][maxn],int n,int w=1){
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++)if(s&(1<<i)){
            for(int x=0;x<p;x++)(f[s][x]+=f[s^(1<<i)][x]*w)%=mod;
        }
    }
}
void ln(int f[][maxn],int g[][maxn],int n){
    for(int s=0;s<(1<<n);s++){
        for(int x=0;x<p;x++)ff[__builtin_popcount(s)][s][x]=f[s][x];
    }
    for(int i=0;i<=n;i++)fmt(ff[i],n,1);
    for(int s=0;s<(1<<n);s++){
        for(int i=0;i<n;i++){
            for(int x=0;x<p;x++)hh[i][x]=ff[i+1][s][x]*(i+1)%mod;
            for(int j=1;j<=i;j++){
                for(int x=0;x<p;x++)(hh[i][x]+=mod-ff[j][s][x]*hh[i-j][x]%mod)%=mod;
            }
        }
        for(int i=0;i<=n;i++){
            for(int x=0;x<p;x++)ff[i][s][x]=hh[i-1][x]*ni[i]%mod;
        }
    }
    for(int i=1;i<=n;i++)fmt(ff[i],n,mod-1);
    for(int s=0;s<(1<<n);s++){
        for(int x=0;x<p;x++)g[s][x]=ff[__builtin_popcount(s)][s][x];
    }
}
void work(){
    n=read();m=read();
    ni[0]=ni[1]=1;for(int i=2;i<=p;i++)ni[i]=(mod-mod/i)*ni[mod%i]%mod;
    for(int i=1;i<=m;i++){
        int u=read()-1,v=read()-1,w=read();
        a[u][v][w]++,a[v][u][w]++;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)if(i!=j){
            a[i][j][0]++;
            dft(a[i][j]);
        }
    }
    // for(int i=0;i<n;i++){
    	// for(int j=0;j<n;j++){
    		// dft(a[i][j],-1);
    		// for(int x=0;x<p;x++)cout<<a[i][j][x]<<" ";cout<<"\n";
    		// dft(a[i][j],1);
    	// }
    // }
    f[0][0]=1;dft(f[0]);
    for(int s=1;s<(1<<n);s++){
        int i=__builtin_ctz(s),ss=s^(1<<i);
        for(int x=0;x<p;x++)f[s][x]=f[ss][x];
        for(int j=0;j<n;j++)if((s&(1<<j))&&i!=j){
            for(int x=0;x<p;x++)f[s][x]=f[s][x]*a[i][j][x]%mod;
        }
    }
    // for(int s=0;s<(1<<n);s++){
    	// dft(f[s],-1);
    	// for(int x=0;x<p;x++)cout<<f[s][x]<<" ";cout<<"\n";
    	// dft(f[s],1);
    // }
    ln(f,g,n);
    dft(g[(1<<n)-1],-1);
    for(int x=0;x<p;x++)printf("%lld\n",g[(1<<n)-1][x]);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}