#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=20;
const int inf=1e9;
const db eps=1e-10;
bool mbe;

int n;
db f[1<<maxn],mn[1<<maxn],ans;
void work(){
    n=read();
    for(int i=0;i<(1<<n);i++)scanf("%Lf",&f[i]);
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++)if(s&(1<<i))f[s]+=f[s^(1<<i)];
    }
    for(int i=0;i<n;i++)if(f[((1<<n)-1)^(1<<i)]+eps>=1){puts("INF");return ;}
    for(int s=1;s<(1<<n);s++){
        mn[s]=1.0/(1-f[((1<<n)-1)^s]);
        ans+=(((__builtin_popcount(s)+1)&1)?-1:1)*mn[s];
    }
    printf("%.10Lf\n",ans);
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