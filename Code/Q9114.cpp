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
const int maxn=1510;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
int ans[maxn][maxn];
void work(){
	n=read();m=read();k=read();
	bool fl=0,fl1=0;
	if(k>n*m-k)k=n*m-k,fl=1;
	if(m>n)swap(n,m),fl1=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)ans[i][j]=0;
	}
	for(int j=1;j<=m;j+=2)if(k)ans[1][j]=1,k--;
	for(int i=2;i<=n;i++){
		for(int j=2-(i&1);j<=m;j+=2){
			if(k>=2)ans[i][j]=ans[i-1][j]=1,k-=2;
		}
	}
	if(k)ans[n][m]=1;
	if(!fl1){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)printf("%lld",ans[i][j]^fl);puts("");
		}
	}
	else{
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++)printf("%lld",ans[j][i]^fl);puts("");
		}
	}
	// puts("");
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
	
	T=read();
	while(T--)work();
}
