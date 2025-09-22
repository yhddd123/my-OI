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
const int maxn=20000010;
const int inf=1e9;
bool mbe;

int n,ans;
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
int val[maxn];
int f[maxn];
int pre[2433660],cnt;
bool vis[maxn];
int si[maxn];
void init(int n){
	si[1]=1;for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,si[i]=(i==2?2:i+1);
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;
			if(i%pre[j]==0){
                if(pre[j]==2)si[i*pre[j]]=pre[j]*si[i];
                else si[i*pre[j]]=si[i]+pre[j]*(si[i]-si[i/pre[j]]);
				break;
			}
            if(pre[j]==2)si[i*pre[j]]=pre[j]*si[i];
            else si[i*pre[j]]=(1+pre[j])*si[i];
		}
	}
}
void work(){
    n=read();ans=0;
    for(int i=0;i<=n;i++)val[i]=C(n,i);
    for(int i=0;i<=n;i++)f[i]=0;
    // for(int v=2-(n&1);v<=n;v+=2){
    	// for(int k=(n+v)/2%v;k<=n;k+=v)f[k]-=v;
		// for(int k=((n+v)/2+1)%(v+1);k<=n;k+=v+1)f[k]+=2*(v+1);
		// for(int k=((n+v)/2+1)%(v+2);k<=n;k+=v+2)f[k]-=v+2;
    // }
	for(int i=0;i<=n;i++)f[i]+=mod-si[abs(n-2*i)];
	if(n&1){
		for(int i=0;i<=n;i++)f[i]+=2*si[abs(n-2*i-1)];
	}
	else{
		for(int i=0;i<=n;i++)f[i]+=2*(si[abs(n-2*i-1)]-1);
	}
	if(n&1){
		for(int i=0;i<=n;i++)f[i]+=mod-(si[abs(n-2*i)]-1);
	}
	else{
		for(int i=0;i<n/2;i++)f[i]+=mod-2*(si[n/2-i]-((n/2-i)&1));
		for(int i=n/2+1;i<=n;i++)f[i]+=mod-2*(si[i-n/2]-((i-n/2)&1));
	}
	// for(int i=0;i<=n;i++)cout<<f[i]/2<<" ";cout<<"\n";
    for(int i=0;i<=n;i++)(ans+=f[i]*val[i])%=mod;
    ans%=mod,ans+=mod,ans%=mod;
    // printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	n=2e7;init(n+1);
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	
    T=read();
    while(T--)work();
}