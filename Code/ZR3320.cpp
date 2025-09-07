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
const int maxn=200010;
const int inf=1e9;

int n,m,ans;
void work(){
    n=read();m=read();ans=0;
    while(n){
        int k=__lg(n),v=(1<<k+1)-1;
        if(n==v){ans+=min((1ll<<k)-1,m)*v;break;}
        int d=n-(1<<k)+1;
        if(d<=m)ans+=d*v,m-=d,n=v-n-1;
        else{ans+=m*v;break;}
    }
    printf("%lld\n",ans*2);
}

int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}