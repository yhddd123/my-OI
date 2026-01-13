#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=100015;
const int maxm=12;
const int inf=1e9;
bool mbe;

inline int ksm(int a,int b=mod-2){
    int ans=1;
    while(b){
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return ans;
}
int fac[maxn],inv[maxn];
int C(int m,int n){
    if(n<0|m<0||m<n)return 0;
    return 1ll*fac[m]*inv[n]%mod*inv[m-n]%mod;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod;
    inv[n]=ksm(fac[n]);for(int i=n-1;~i;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}

int n,k,a[maxn],b[maxn];
int f[maxn];
bool vis[maxn];
int cnt[maxn];
int ans1,ans2;
int len[maxm],sum[1<<maxm];
bool fl0,fl1;
int ans=1;
int val[maxn][13],ni[maxn][13];
void dfs(int s,int mul=1){
	if(s==(1<<k)-1){
		// cout<<s<<" "<<mul<<" "<<ans<<" "<<fl0<<" "<<fl1<<"\n";
		if(!fl0)ans2+=mul;
		else if(!fl1)ans1+=mul,ans2+=mul;
		else ans1+=2*mul,ans2+=ans*mul;
		return ;
	}
	int t=(1<<k)-1-s;
	int k=__lg(t);
	t-=1<<k;
	for(int ss=t;;ss=(ss-1)&t){
		int nw=ss|(1<<k),len=sum[nw];
		cnt[len]++;
		int tmp=ans;
		ans=ans*ni[len][cnt[len]-1]%mod*val[len][cnt[len]]%mod;
		bool tmpfl0=fl0,tmpfl1=fl1;
		if(len>1)fl0=1;
		if(len>2)fl1=1;
		dfs(s|nw,mul*fac[__builtin_popcount(nw)-1]);
		cnt[len]--;
		ans=tmp;
		fl0=tmpfl0,fl1=tmpfl1;
		if(!ss)break;
	}
}
void work(){
	n=read();k=read();init(n);
	for(int i=1;i<=n;i++)a[i]=read(),b[a[i]]=i;
	int j=0;
	for(int i=1;i<=n;i++)if(a[i]&&!b[i]&&!vis[i]){
		int x=i,l=0;
		while(!vis[x]&&x)vis[x]=1,x=a[x],l++;
		if(!x)len[j++]=l;
		else{
			cnt[l]++;
			if(l>1)fl0=1;
			if(l>2)fl1=1;
		}
	}
	for(int i=1;i<=n;i++)if(!vis[i]){
		int x=i,l=0;
		while(!vis[x]&&x)vis[x]=1,x=a[x],l++;
		if(!x)len[j++]=l;
		else{
			cnt[l]++;
			if(l>1)fl0=1;
			if(l>2)fl1=1;
		}
	}
	ans=1;
	for(int i=1;i<=n;i++){
		f[0]=1,f[1]=i;for(int j=2;j<=cnt[i]+12;j++)f[j]=(f[j-1]+(j-1)*f[j-2])%mod*i%mod;
		ans=ans*f[cnt[i]]%mod;
		for(int j=0;j<=k;j++)val[i][j]=f[cnt[i]+j],ni[i][j]=ksm(f[cnt[i]+j]);
		cnt[i]=0;
	}
	// for(int i=0;i<k;i++)cout<<len[i]<<" ";cout<<"\n";
	for(int s=1;s<(1<<k);s++){
		int p=__lg(s);
		sum[s]=sum[s^(1<<p)]+len[p];
	}
	dfs(0);
	printf("%lld\n",ans2%mod);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}