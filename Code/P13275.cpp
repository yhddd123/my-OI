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
const int maxn=20;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int n,a[1<<maxn],ans;
pii operator*(pii u,pii v){return {u.fi*v.fi%mod,u.se+v.se};}
pii operator/(pii u,pii v){return {u.fi*ksm(v.fi)%mod,u.se-v.se};}
pii operator+(pii u,pii v){
	if(u.se<v.se)return u;
	if(u.se>v.se)return v;
	return {(u.fi+v.fi)%mod,u.se};}
pii operator-(pii u,pii v){
	if(u.se<v.se)return u;
	if(u.se>v.se)return v;
	return {(u.fi+mod-v.fi)%mod,u.se};}
pii init(int v){
	if(!v)return {1,1};
	return {v,0};
}
int calc(pii p){return p.se?0:p.fi;}
pii f[1<<maxn],g[1<<maxn],h[1<<maxn];
void work(){
    n=read();ans=0;
    for(int i=0;i<(1<<n);i++)a[i]=read();
    for(int i=0;i<(1<<n);i++)f[i]=init((a[i]+1)%mod),g[i]=init((2*a[i]+1)%mod);
    for(int i=0;i<n;i++){
        for(int s=0;s<(1<<n);s++)if(s&(1<<i)){
            f[s^(1<<i)]=f[s^(1<<i)]*f[s];
            g[s^(1<<i)]=g[s^(1<<i)]*g[s];
        }
    }
    for(int s=0;s<(1<<n);s++){
    	h[s]={f[s].fi*((__builtin_popcount(s)&1)?mod-1:1)%mod*(1<<__builtin_popcount(s))%mod,f[s].se};
    }
    for(int i=0;i<n;i++){
    	for(int s=0;s<(1<<n);s++)if(s&(1<<i)){
    		h[s]=h[s]+h[s^(1<<i)];
    	}
    }
    for(int s=0;s<(1<<n);s++)h[s]=h[s]*h[s];
    for(int i=0;i<n;i++){
    	for(int s=0;s<(1<<n);s++)if(s&(1<<i)){
    		h[s]=h[s]-h[s^(1<<i)];
    	}
    }
    for(int s=0;s<(1<<n);s++){
    	pii p=h[s]*g[s]/f[s]/f[s];
    	(ans+=calc(p)*ksm(2,mod-1-__builtin_popcount(s)))%=mod;
    }
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    read();T=read();
    while(T--)work();
}