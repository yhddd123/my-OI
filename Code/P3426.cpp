#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=500010;
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

int n;
char c[maxn];
int nxt[maxn];
int dp[maxn],p[maxn];
void work(){
	scanf("%s",c+1);n=strlen(c+1);
	for(int i=2,j=0;i<=n;i++){
		while(j&&c[i]!=c[j+1])j=nxt[j];
		if(c[i]==c[j+1])j++;
		nxt[i]=j;
	}
	for(int i=1;i<=n;i++){
		dp[i]=i;
		if(p[dp[nxt[i]]]+nxt[i]>=i)dp[i]=dp[nxt[i]];
		p[dp[i]]=i;
	}
	printf("%lld\n",dp[n]);
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
