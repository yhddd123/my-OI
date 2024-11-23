#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
int a[20][1<<19],b[20][1<<19],c[20][1<<19];
int num[1<<19];
void fwtor(int *a,int n,int x){
	for(int len=2;len<=n;len<<=1){
		int l=len>>1;
		for(int i=0;i<n;i+=len){
			for(int j=i;j<i+l;j++)(a[j+l]+=a[j]*x)%=mod;
		}
	}
}
void work(){
	n=read();
	for(int i=0;i<(1<<n);i++)num[i]=__builtin_popcount(i);
	for(int i=0;i<(1<<n);i++)a[num[i]][i]=read();
	for(int i=0;i<(1<<n);i++)b[num[i]][i]=read();
	for(int i=0;i<=n;i++)fwtor(a[i],1<<n,1),fwtor(b[i],1<<n,1);
	for(int i=0;i<=n;i++){
		for(int j=0;j<=i;j++){
			for(int s=0;s<(1<<n);s++)(c[i][s]+=a[j][s]*b[i-j][s])%=mod;
		}
	}
	for(int i=0;i<=n;i++)fwtor(c[i],1<<n,mod-1);
	for(int i=0;i<(1<<n);i++)printf("%lld ",c[num[i]][i]);
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
