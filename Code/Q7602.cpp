#include<bits/stdc++.h>
#include <cstring>
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
const int maxn=20;
const int inf=1e9;
bool mbe;

int n,a[1<<maxn],b[1<<maxn];
int f[1<<maxn];
void work(){
    n=read();
    for(int s=0;s<(1<<n);s++)a[s]=read();
    for(int s=0;s<(1<<n);s++)b[s]=read();
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++)if(s&(1<<i))a[s]+=a[s^(1<<i)];
    }
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++)if(s&(1<<i))b[s]+=b[s^(1<<i)];
    }
    memset(f,0x3f,sizeof(f));
    f[0]=min(a[0],b[0]);
    for(int s=1;s<(1<<n);s++){
        for(int i=0;i<n;i++)if(s&(1<<i)){
            f[s]=min(f[s],f[s^(1<<i)]+min(a[s]-a[s^(1<<i)],b[s]-b[s^(1<<i)]));
        }
    }
    printf("%lld\n",f[(1<<n)-1]);
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