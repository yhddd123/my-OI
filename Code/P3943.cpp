#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=40010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k,a[maxn],b[maxn],c[maxn];
int dis[16][maxn];
queue<int> q;
int dp[1<<16];
void work(){
	n=read()+1;m=read();k=read();
	for(int i=0;i<m;i++)c[read()]=1;
	for(int i=1;i<=k;i++)b[i]=read();
	for(int i=n;i;i--)c[i]^=c[i-1];
	m=0;for(int i=1;i<=n;i++)if(c[i])a[m++]=i;
	// for(int i=0;i<m;i++)cout<<a[i]<<" ";cout<<"\n";
	for(int s=0;s<m;s++){
		q.push(a[s]);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=1;i<=k;i++){
				int v=u-b[i];
				if(v>=1){
					if(!dis[s][v])dis[s][v]=dis[s][u]+1,q.push(v);
				}
				v=u+b[i];
				if(v<=n){
					if(!dis[s][v])dis[s][v]=dis[s][u]+1,q.push(v);
				}
			}
		}
		for(int i=1;i<=n;i++)if(!dis[s][i])dis[s][i]=2*inf;
		// for(int i=1;i<=n;i++)cout<<dis[s][i]<<" ";cout<<"\n";
	}
	mems(dp,0x3f);dp[0]=0;
	for(int s=0;s<(1<<m);s++){
		for(int i=0;i<m;i++)if(s&(1<<i)){
			for(int j=0;j<m;j++)if(i!=j&&(s&(1<<j))){
				dp[s]=min(dp[s],dp[s^(1<<i)^(1<<j)]+dis[i][a[j]]);
			}
		}
	}
	printf("%d\n",dp[(1<<m)-1]);
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
