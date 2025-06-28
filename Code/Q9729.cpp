#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=5010;
const int inf=2e9;
bool mbe;

int n,a[maxn];
int ans[maxn],m;
int f[2][maxn],cur;
void work(){
	n=read();m=0;
	for(int i=1;i<=n;i++)a[i]=read();a[n+1]=0;
	for(int i=1;i<=n;i++)f[0][i]=0;f[cur=0][0]=1;
	for(int t=1;t<=n;t++){
		for(int i=1;i<=n;i++)f[t&1][i]=0;
		int mn=inf;
		for(int i=m;i<=min(n,2*m);i++)if(f[cur][i])mn=min(mn,a[i+1]);
		ans[++m]=mn;
		for(int i=m-1;i<=min(n,2*(m-1));i++)if(f[cur][i]){
			if(a[i+1]==mn)f[t&1][i+1]=1;
		}
		bool fl=0;
		for(int i=m;i<min(n,2*m);i++)if(f[t&1][i]){
			if(a[i+1]==ans[i-m+1])f[t&1][i+1]=1;
			// cout<<i<<" "<<a[i+1]<<" "<<ans[i-m+1]<<"\n";
			if(a[i+1]<ans[i-m+1])fl=1;
		}
		if(fl||f[t&1][n])break;
		cur^=1;
		// for(int i=0;i<=n;i++)cout<<f[t&1][i];cout<<"\n";
	}
	printf("%d\n",m);
	for(int i=1;i<=m;i++)printf("%d ",ans[i]);puts("");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}