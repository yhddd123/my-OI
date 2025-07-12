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
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
void work(){
    n=read()-1;m=read();
    ans=(1+m*(m+1)%mod*ksm(2)%mod*(ksm(2,n)-1)%mod+(m+1)*(ksm(m+1,n)-m*(ksm(2,n)-1)%mod-1+mod)%mod+(m+1)*m%mod*(m-1)%mod*ksm(6)%mod*(ksm(4,n)-1-3*(ksm(3,n)-1)+3*(ksm(2,n)-1)+3*mod)%mod)%mod;
    // cout<<"1 "<<m*(m+1)%mod*ksm(2)%mod*(ksm(2,n)-1)%mod<<" "<<(m+1)*(ksm(m+1,n)-m*(ksm(2,n)-1)%mod-1+mod)%mod<<" "<<(m+1)*m%mod*(m-1)%mod*ksm(6)%mod*(ksm(4,n)-1-3*(ksm(3,n)-1)+3*(ksm(2,n)-1)+3*mod)%mod<<"\n";
    printf("%lld\n",ans*ksm(2,m)%mod);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    while(T--)work();
}