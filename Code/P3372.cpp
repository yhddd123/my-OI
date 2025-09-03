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
const int maxn=200010;
const int inf=1e9;

int n,q,m;
int sum[maxn<<3],tag[maxn<<3];
void build(int n){
    for(m=1;m<=n+1;m<<=1);
    for(int i=1;i<=n;i++)sum[m+i]=read();
    for(int i=m-1;i;i--)sum[i]=sum[i<<1]+sum[i<<1|1];
}
void updata(int l,int r,int v){
    int len=1,xl=0,yl=0;
    for(l+=m-1,r+=m+1;l^r^1;l>>=1,r>>=1,len<<=1){
        sum[l]+=xl*v,sum[r]+=yl*v;
        if(~l&1)sum[l^1]+=v*len,xl+=len,tag[l^1]+=v;
        if(r&1)sum[r^1]+=v*len,yl+=len,tag[r^1]+=v;
    }
    while(l){
        sum[l]+=xl*v,sum[r]+=yl*v;
        l>>=1,r>>=1;
    }
}
int query(int l,int r){
    int ans=0;
    int len=1,xl=0,yl=0;
    for(l+=m-1,r+=m+1;l^r^1;l>>=1,r>>=1,len<<=1){
        ans+=xl*tag[l]+yl*tag[r];
        if(~l&1)ans+=sum[l^1],xl+=len;
        if(r&1)ans+=sum[r^1],yl+=len;
    }
    while(l){
        ans+=xl*tag[l]+yl*tag[r];
        l>>=1,r>>=1;
    }
    return ans;
}
void work(){
    n=read();q=read();
    build(n);
    while(q--){
        int op=read();
        if(op==1){
            int l=read(),r=read(),v=read();
            updata(l,r,v);
        }
        else{
            int l=read(),r=read();
            printf("%lld\n",query(l,r));
        }
    }
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=1;
    while(T--)work();
}