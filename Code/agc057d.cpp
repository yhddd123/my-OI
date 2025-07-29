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
const int inf=1e18;
bool mbe;

int n,k;
int f[maxn];
void work(){
    n=read();k=read();
    if(k>(n-1)/2){puts("-1");return ;}
    int p=1;while(n%p==0)p++;
    f[0]=0;for(int i=1;i<=p;i++)f[i]=n+1;
    // cout<<p<<"\n";
    for(int t=1;t<p;t++){
        int mn=inf;
        for(int i=1;i<p;i++){
            int mx=0;
            for(int j=1;j<p;j++)mx=max(mx,(n-f[(n-i*j%p+p)%p])/j+1);
            while(mx%p!=i)mx++;
            if(mx<f[i])mn=min(mn,mx);
        }
        if(mn>(n-1)/2)break;
        f[mn%p]=mn;
        int gg=__gcd(mn,p);
        for(int i=0;i<gg;i++){
            for(int j=i,k=0;k<2;j=(j+mn)%p,k+=(i==j))f[(j+mn)%p]=min(f[(j+mn)%p],f[j]+mn);
        }
        if(f[n%p]<=n){
        	exit(0);
        }
    }
    f[0]=p;
    auto calc=[&](int v){
        int res=0;
        for(int i=0;i<p;i++)if(f[i]<=v)res+=(v-f[i])/p+1;
        return res;
    };
    int num=calc((n-1)/2);
    // cout<<num<<"\n";
    if(num>=k){
        int l=1,r=(n-1)/2,res=(n-1)/2;
        while(l<=r){
            int mid=l+r>>1;
            if(calc(mid)>=k)res=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%lld\n",res);
    }
    else{
        int l=n-(n-1)/2,r=n-1,res=n-1;
        while(l<=r){
            int mid=l+r>>1;
            if(calc(n-mid-1)+(n-1)/2-(n-mid)+1>=k)res=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%lld\n",res);
    }
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=read();
    while(T--)work();
}