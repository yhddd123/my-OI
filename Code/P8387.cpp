#include <algorithm>
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
const int maxn=400010;
const int inf=2e9;
bool mbe;

int n,k,x,ans;
int l[maxn],p[maxn],r[maxn];
int lsh[maxn],len;
int f[maxn],g[maxn],sum[maxn];
void work(){
    n=read();k=read();x=read();
    for(int i=1;i<=n;i++){
        l[i]=read(),p[i]=l[i]+read(),r[i]=read();
        lsh[++len]=l[i],lsh[++len]=p[i],lsh[++len]=r[i]+1;
        // cout<<l[i]<<" "<<p[i]<<" "<<r[i]<<"\n";
    }
    lsh[++len]=inf;
    sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
    for(int i=1;i<=n;i++){
        l[i]=lower_bound(lsh+1,lsh+len+1,l[i])-lsh;
        p[i]=lower_bound(lsh+1,lsh+len+1,p[i])-lsh;
        r[i]=lower_bound(lsh+1,lsh+len+1,r[i]+1)-lsh;
        f[l[i]]++,f[r[i]]--;
        if(p[i]<r[i])g[p[i]]++,g[r[i]]--;
    }
    for(int i=1;i<=len;i++)f[i]+=f[i-1],g[i]+=g[i-1];
    // for(int i=1;i<=len;i++)cout<<lsh[i]<<" ";cout<<"\n";
    for(int i=1;i<=len;i++)g[i]=g[i]*(f[i]>=k);
    for(int i=1;i<=len;i++)sum[i]=sum[i-1]+(lsh[i+1]-lsh[i])*g[i];
    // for(int i=1;i<=len;i++)cout<<g[i]<<" ";cout<<"\n";
    for(int i=1,j=1;i<len;i++){
        while(j<len&&lsh[j]-lsh[i]<x){
        	ans=max(ans,sum[j-1]-(i==1?0:sum[i-2])-g[i-1]*(lsh[j]-lsh[i-1]-x));
        	j++;
        }
        // cout<<i<<" "<<lsh[i]<<" "<<j<<" "<<lsh[j]<<"\n";
        ans=max(ans,sum[j-1]-sum[i-1]-g[j-1]*(lsh[j]-lsh[i]-x));
    }
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}