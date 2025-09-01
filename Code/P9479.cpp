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
const int maxn=3010;
const int inf=1e9;

int n,m,k;
int f[1<<10],g[1<<10];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
void work(){
    n=read();m=read();k=read();
    for(int i=2;i<=n;i++)read();
    memset(f,0,sizeof(f));f[0]=1;
    for(int i=1;i<=m;i++){
        for(int s=0;s<(1<<k);s++)if(f[s]){
            if(s&1)inc(g[s>>1],f[s]);
            else{
                int num=n+i-1+__builtin_popcount(s);
                inc(g[s>>1],f[s]*(2*num-1)%mod);
                for(int j=0;j<k;j++)if(!((s>>1)&(1<<j)))inc(g[(s>>1)|(1<<j)],f[s]*(num-1)%mod);
            }
        }
        for(int s=0;s<(1<<k);s++)f[s]=g[s],g[s]=0;
        // for(int s=0;s<(1<<k);s++)cout<<f[s]<<" ";cout<<"\n";
    }
    printf("%lld\n",f[0]);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    read();T=read();
    while(T--)work();
}