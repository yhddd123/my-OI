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
const int maxn=110;
const int inf=1e9;

int n,m,a[maxn];
void work(){
    n=read();
    int v1=0;
    while(n){
        n--;a[++m]=++v1;
        if(n&1)a[m]=0,a[++m]=v1;
        n>>=1;
    }
    for(int i=m;i;i--)if(!a[i])a[i]=++v1;
    printf("%lld\n",2*m);
    for(int i=1;i<=m;i++)printf("%lld ",a[i]);
    for(int i=1;i<=m;i++)printf("%lld ",i);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}