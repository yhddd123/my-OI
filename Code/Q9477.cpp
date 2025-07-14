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
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],ans=1;
int st[maxn],tp;
int pw[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=n;i++){
		while(tp&&a[st[tp]]<a[i])tp--;
		if(!tp)ans=ans*pw[i-1]%mod;
		else ans=ans*(pw[i-1]+mod-pw[st[tp]-1])%mod;
		st[++tp]=i;
	}
	printf("%lld\n",ans);
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
