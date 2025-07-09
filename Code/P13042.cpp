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
const int maxn=35;

int n,m,l,a[maxn];
int siz[maxn],rnk[maxn];
vector<int> id;
int f[maxn],ans;
inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int g[maxn<<2][2];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int calc(int v){
    // cout<<v<<"\n";
    int ans=0;
    for(int s=0;s<(1<<id.size());s++){
        auto dfs=[&](auto &&self,int nd,int l,int r,int d)->void{
            if(l==r){
                g[nd][0]=g[nd][1]=0;
                if(~rnk[a[l]]){
                    if(s&(1<<rnk[a[l]]))g[nd][1]=1;
                    else g[nd][0]=1;
                }
                else g[nd][0]=v-1,g[nd][1]=m-v+1;
                return ;
            }
            self(self,ls,l,mid,d+1),self(self,rs,mid+1,r,d+1);
            if(d&1)g[nd][1]=(g[ls][0]*g[rs][1]+g[ls][1]*g[rs][0]+g[ls][1]*g[rs][1])%mod,g[nd][0]=g[ls][0]*g[rs][0]%mod;
            else g[nd][0]=(g[ls][0]*g[rs][0]+g[ls][0]*g[rs][1]+g[ls][1]*g[rs][0])%mod,g[nd][1]=g[ls][1]*g[rs][1]%mod;
            // cout<<l<<" "<<r<<" "<<g[nd][0]<<" "<<g[nd][1]<<"\n";
        };
        dfs(dfs,1,0,(1<<l)-1,1);
        (ans+=ksm(v-1,id.size()-__builtin_popcount(s))*ksm(m-v+1,__builtin_popcount(s))%mod*g[1][1])%=mod;
        // cout<<s<<" "<<g[1][1]<<" "<<ans<<"\n";
    }
    return ans;
}
void work(){
    n=read();m=read();l=read();ans=0;
    for(int i=0;i<(1<<l);i++)a[i]=read();
    for(int i=1;i<=n;i++)siz[i]=0,rnk[i]=-1;
    for(int i=0;i<(1<<l);i++)siz[a[i]]++;
    id.clear();
    for(int i=1;i<=n;i++)if(siz[i]>1)id.pb(i),rnk[i]=id.size()-1;
    int num=0;for(int i=1;i<=n;i++)if(!siz[i])++num;
    for(int i=1;i<=n+2;i++)f[i]=calc(i);
    // for(int i=1;i<=n+2;i++)cout<<f[i]<<" ";cout<<"\n";
    for(int i=1;i<=n+2;i++)(f[i]+=f[i-1])%=mod;
    // for(int i=1;i<=n+2;i++)cout<<f[i]<<" ";cout<<"\n";
    if(m<=n+2){printf("%lld\n",f[m]*ksm(m,num)%mod);return ;}
	for(int i=1;i<=n+2;i++){
		int mul=f[i];
		for(int j=1;j<=n+2;j++)if(i!=j)mul=mul*(m-j+mod)%mod*ksm(i-j+mod)%mod;
		(ans+=mul)%=mod;
	}
    printf("%lld\n",ans*ksm(m,num)%mod);
}

int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    T=read();
    for(int t=1;t<=T;t++){
        cout<<"Case #"<<t<<": ";
        work();
    }
}