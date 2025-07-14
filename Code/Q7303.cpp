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
const int maxn=55;
const int maxm=13;
const int maxs=1594323;

int n,m,ans;
int e[maxn];
int pw[maxm],val[2][maxs];
int f[maxs],g[maxs];
void work(){
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        if(u>v)swap(u,v);
        e[v]|=1<<v-u-1;
    }
    pw[0]=1;for(int i=1;i<13;i++)pw[i]=pw[i-1]*3;
    for(int s=0;s<maxs;s++){
        for(int i=0;i<13;i++){
            if((s/pw[i])%3==1)val[0][s]|=1<<i;
            if((s/pw[i])%3==2)val[1][s]|=1<<i;
        }
    }
    f[0]=1;
    for(int i=1;i<=n;i++){
        for(int s=0;s<maxs;s++){
            g[s*3%maxs]+=f[s];
            if(!(e[i]&val[1][s]))g[(s*3+1)%maxs]+=f[s];
            if(!(e[i]&val[0][s]))g[(s*3+2)%maxs]+=f[s];
        }
        for(int s=0;s<maxs;s++)f[s]=g[s]&3,g[s]=0;
    }
    for(int s=0;s<maxs;s++)ans+=f[s];ans&=3;
    ans/=2;ans&=1;
    printf("%lld\n",ans);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}