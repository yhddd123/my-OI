#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,k,a[maxn];
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int ans,num=1;
void inc(int &x,int y){((x+=y)>=mod)&&(x-=mod);}
int fac[maxn],inv[maxn];
int C(int m,int n){
	if(m<0||n<0||m<n)return 0;
	return fac[m]*inv[n]%mod*inv[m-n]%mod;
}
void work(){
	n=read();k=read();
	fac[0]=1;for(int i=1;i<=k;i++)fac[i]=fac[i-1]*i%mod;
	inv[k]=ksm(fac[k]);for(int i=k-1;~i;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int j=29;~j;j--){
		sort(a+1,a+n+1);
		int cnt=0;
		for(int i=1;i<=n;i++)if(a[i]&(1<<j))++cnt;
		// cout<<j<<" "<<cnt<<" "<<k<<" "<<ans<<"\n";
		if(k==1){
			int sum=(1<<30)-1;
			for(int i=1;i<=n;i++)sum&=a[i];
			ans+=sum;
			break;
		}
		if(cnt<=k-1){
			for(int i=n-cnt+1;i<=n;i++)ans+=a[i];
			num*=C(k,cnt)*fac[cnt]%mod,num%=mod;
			k-=cnt,n-=cnt;
		}
		else if(cnt==n){
			for(int i=1;i<=n;i++)a[i]-=(1<<j);
			ans+=k*(1<<j);
		}
		else{
			reverse(a+1,a+n+1);int sum=(1<<30)-1;
			for(int i=1;i<=cnt;i++)a[i]-=(1<<j);
			for(int i=cnt+1;i<=n;i++)sum&=a[i];
			ans+=(k-1)*(1<<j);
			a[cnt+1]=sum;n=cnt+1;
		}
		// cout<<ans<<"\n";
	}
	int val=0;
	// {n,k}
	for(int i=0;i<=k;i++){
		if((k-i)&1)inc(val,mod-ksm(i,n)*inv[i]%mod*inv[k-i]%mod);
		else inc(val,ksm(i,n)*inv[i]%mod*inv[k-i]%mod);
	}
	val=val*fac[k]%mod;
	num=num*val%mod;
	printf("%lld %lld",ans,num);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
