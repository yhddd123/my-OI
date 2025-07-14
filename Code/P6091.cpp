#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1000010;
const int inf=1e18;
const db eps=1e-8;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,d;
int pre[maxn],cnt;
bool vis[maxn],bk[maxn];
int phi[maxn];
void s(int n){
	for(int i=2;i<=n;i++){
		if(!vis[i])pre[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*pre[j]<=n;j++){
			vis[i*pre[j]]=1;phi[i*pre[j]]=phi[i]*(pre[j]-1);
			if(i%pre[j]==0){
				phi[i*pre[j]]=phi[i]*pre[j];
				break;
			}
		}
	}
	bk[2]=bk[4]=1;
	for(int i=2;i<=cnt;i++){
		for(int j=pre[i];j<=n;j*=pre[i])bk[j]=1;
		for(int j=2*pre[i];j<=n;j*=pre[i])bk[j]=1;
	}
}
inline int ksm(int a,int b,int p=mod){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
int gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
bool check(int x,int n){
	int m=phi[n];
	for(int i=2;i*i<=m;i++)if(m%i==0){
		if(ksm(x,i,n)==1||ksm(x,m/i,n)==1)return false;
	}
	return true;
}
int getg(int n){
	if(n==2)return 1;
	for(int i=2;i<n;i++)if(gcd(i,n)==1&&check(i,n))return i;
	return -1;
}
int g,ans[maxn];
void work(){
	n=read();d=read();
	if(bk[n]){
		g=getg(n);
//		cout<<g<<" ";
		int mul=1,tp=0;
		for(int i=1;i<=phi[n];i++){
			mul=mul*g%n;
			if(gcd(i,phi[n])==1)ans[++tp]=mul;
		}
		sort(ans+1,ans+tp+1);
		printf("%lld\n",tp);
		for(int i=d;i<=tp;i+=d)printf("%lld ",ans[i]);
		printf("\n");
	}
	else{
		printf("0\n\n");
	}
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	s(maxn-10);
	T=read();
	while(T--)work();
}
