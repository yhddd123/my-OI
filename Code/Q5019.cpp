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
const int maxn=18;
const int inf=1e9;
bool mbe;

int n,lim[maxn],b[1<<maxn];
char s[1<<maxn];
int f[1<<maxn],g[1<<maxn];
void fwt(int *f,int d,int w=1){
    for(int i=0;i<n;i++){
        bool op=(lim[i]>>d)&1;
        for(int s1=0;s1<(1<<i-1);s1++){
            for(int s2=0;s2<(1<<n-i);s2++){
                int s=s1|(s2<<i+1)|(1<<i);
                if(op)(f[s^(1<<i)]+=f[s]*w)%=mod;
                else (f[s]+=f[s^(1<<i)]*w)%=mod;
            }
        }
    }
}
void work(){
    n=read();
    for(int i=0;i<n;i++)lim[i]=read();
    scanf("%s",s);
    for(int i=0;i<(1<<n);i++)b[i]=s[i]-'0';
    f[0]=1;
    for(int i=0;i<60;i++){
        for(int s=0;s<(1<<n);s++)g[s]=b[s];
        fwt(f,i),fwt(g,i);
        for(int s=0;s<(1<<n);s++)f[s]=f[s]*g[s]%mod;
        fwt(f,i,mod-1);
        // for(int s=0;s<(1<<n);s++)cout<<f[s]<<" ";cout<<"\n";
    }
    printf("%lld\n",f[0]);
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