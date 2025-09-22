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
const int maxn=1000010;
const int maxm=2010;
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
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int n,m;
int pl[maxm],pr[maxm];
tuple<int,int,int> upd[maxm];
int lsh1[maxm],len1,lsh2[maxm],len2;
int calc(int l,int r,int v){
	// int res=1;
	// for(int i=l;i<=r;i++)res=res*min(i,v+1)%mod;
	// return res;
	if(v+1<=l)return ksm(v+1,r-l+1);
	if(r<=v+1)return fac[r]*inv[l-1]%mod;
	return fac[v]*inv[l-1]%mod*ksm(v+1,r-v)%mod;
}
int dp[maxm][maxm],sum[maxm];
void work(){
    n=read();m=read();
    len1=len2=0;for(int i=1;i<=m;i++){
        int k=read(),l=read(),r=read();
        upd[i]={k,l,r};
        lsh1[++len1]=l+1;
        if(r<n)lsh1[++len1]=r+1;
        lsh2[++len2]=k+1;
    }
    lsh1[++len1]=1,lsh2[++len2]=0;
    lsh1[++len1]=n+1,lsh2[++len2]=n;
    sort(lsh1+1,lsh1+len1+1),len1=unique(lsh1+1,lsh1+len1+1)-lsh1-1;
    sort(lsh2+1,lsh2+len2+1),len2=unique(lsh2+1,lsh2+len2+1)-lsh2-1;
    pl[0]=1,pr[0]=2;for(int i=1;i<=len1;i++)pl[i]=1,pr[i]=len2;
    for(int i=1;i<=m;i++){
    	auto[k,l,r]=upd[i];
    	l=lower_bound(lsh1+1,lsh1+len1+1,l+1)-lsh1-1;
    	r=lower_bound(lsh1+1,lsh1+len1+1,r+1)-lsh1;
    	k=lower_bound(lsh2+1,lsh2+len2+1,k+1)-lsh2;
    	// cout<<l<<" "<<r<<" "<<k<<"\n";
	    pr[l]=min(pr[l],k),pl[r]=max(pl[r],k);
    }
    if(!m){printf("%lld\n",fac[n]);return ;}
    for(int i=len1-1;i;i--)pr[i]=min(pr[i],pr[i+1]);
    for(int i=2;i<=len1;i++)pl[i]=max(pl[i],pl[i-1]);
    // for(int i=1;i<len1;i++)cout<<lsh1[i]<<" ";cout<<"\n";
    // for(int i=1;i<len2;i++)cout<<lsh2[i]<<" ";cout<<"\n";
    // for(int i=1;i<len1;i++)cout<<pl[i]<<" "<<pr[i]<<"\n";
    for(int i=1;i<len1;i++)if(pl[i]>=pr[i]){puts("0");return ;}
    for(int i=1;i<len1;i++){
        for(int j=1;j<len2;j++)dp[i][j]=0;
    }
    dp[0][1]=1;
    for(int i=1;i<len1;i++){
    	sum[pl[i-1]-1]=0;for(int j=pl[i-1];j<pr[i-1];j++)sum[j]=sum[j-1]+dp[i-1][j];
    	auto que=[&](int l,int r){
    		l=max(l,pl[i-1]),r=min(r,pr[i-1]-1);
    		if(l>r)return 0ll;
    		return (sum[r]-sum[l-1])%mod;
    	};
        for(int j=pl[i];j<pr[i];j++){
        	dp[i][j]=dp[i-1][j]*calc(lsh1[i],lsh1[i+1]-1,lsh2[j+1]-1)%mod;
       		int coef1=(calc(lsh1[i],lsh1[i+1]-1,lsh2[j+1]-1)+mod-calc(lsh1[i],lsh1[i+1]-1,lsh2[j]-1))%mod,coef2=0;
       		if(lsh1[i]+1<lsh1[i+1]){
       			coef2=(max(0ll,lsh2[j]-lsh2[pl[i]])*(calc(lsh1[i]+1,lsh1[i+1]-1,lsh2[j+1]-1)+mod-calc(lsh1[i]+1,lsh1[i+1]-1,lsh2[j]-1))+max(0ll,min(lsh1[i],lsh2[j+1])-lsh2[j])*calc(lsh1[i]+1,lsh1[i+1]-1,lsh2[j+1]-1))%mod;
       		}
       		else coef2=max(0ll,min(lsh1[i],lsh2[j+1])-lsh2[j]);
       		(dp[i][j]+=que(pl[i],j-1)*coef1)%=mod;
       		(dp[i][j]+=que(pl[i-1],pl[i]-1)*coef2)%=mod;
            // cout<<i<<" "<<j<<" "<<dp[i][j]<<" "<<coef1<<" "<<coef2<<"\n";
        }
    }
    int ans=0;for(int i=1;i<len2;i++)(ans+=dp[len1-1][i])%=mod;
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    init(maxn-10);
    T=read();
    while(T--)work();
}