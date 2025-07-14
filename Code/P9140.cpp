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
const int inf=1e18;

int n,q;
int v[maxn],c[maxn];
int f[maxn],st[maxn],tp;
void work(){
    n=read();q=read();
    int m=1,w=0;
    for(int i=1;i<=n;i++){
        v[i]=read(),c[i]=read();
        if(c[i]*m>w*v[i])m=v[i],w=c[i];
    }
    for(int i=0;i<m;i++)f[i]=-inf;f[0]=0;
    for(int i=1;i<=n;i++){
        int g=__gcd(m,v[i]);
        for(int j=0;j<g;j++){
            st[tp=1]=j;for(int k=(j+v[i])%m;k!=j;k=(k+v[i])%m)st[++tp]=k;
            for(int k=2;k<=tp;k++)f[st[k]]=max(f[st[k]],f[st[k-1]]+c[i]-(v[i]/m+(st[k]<=st[k-1]))*w);
            f[st[1]]=max(f[st[1]],f[st[tp]]+c[i]-(v[i]/m+1)*w);
            for(int k=2;k<=tp;k++)f[st[k]]=max(f[st[k]],f[st[k-1]]+c[i]-(v[i]/m+(st[k]<=st[k-1]))*w);
        }
    }
    while(q--){
        int lim=read();
        printf("%lld\n",max(-1ll,f[lim%m]+lim/m*w));
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    T=1;
    while(T--)work();
}