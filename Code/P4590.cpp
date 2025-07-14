#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define mems(x,y) memset(x,y,sizeof x)
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

int n,k,s;
char c[16];
int dp[2][1<<16][3],cur;
int f[16],g[16];
int nxt[1<<16][3];
int go(int s,char ch){
	for(int i=1;i<=k;i++)f[i]=f[i-1]+((s>>i-1)&1);
	for(int i=1;i<=k;i++){
		g[i]=max({g[i-1],f[i],f[i-1]+(c[i]==ch)});
	}
	int ans=0;
	for(int i=1;i<=k;i++)ans|=(g[i]-g[i-1])*(1<<i-1);
	return ans;
}
int ans[16];
void add(int &x,int y){((x+=y)>=mod)&&(x-=mod);}
void work(){
	n=read();k=read();
	scanf("%s",c+1);
	s=(1<<k)-1;
	for(int i=0;i<=s;i++){
		nxt[i][0]=go(i,'N');
		nxt[i][1]=go(i,'O');
		nxt[i][2]=go(i,'I');
//		cout<<nxt[i][0]<<" "<<nxt[i][1]<<" "<<nxt[i][2]<<" "<<i<<" "<<s<<"\n";
	}
	dp[0][0][0]=1;
	for(int i=0;i<n;i++){
		cur^=1;mems(dp[cur],0);
		for(int j=0;j<=s;j++){
			if(dp[i&1][j][0]){
				add(dp[cur][nxt[j][0]][1],dp[i&1][j][0]);
				add(dp[cur][nxt[j][1]][0],dp[i&1][j][0]);
				add(dp[cur][nxt[j][2]][0],dp[i&1][j][0]);
			}
			if(dp[i&1][j][1]){
				add(dp[cur][nxt[j][0]][1],dp[i&1][j][1]);
				add(dp[cur][nxt[j][1]][2],dp[i&1][j][1]);
				add(dp[cur][nxt[j][2]][0],dp[i&1][j][1]);
			}
			if(dp[i&1][j][2]){
				add(dp[cur][nxt[j][0]][1],dp[i&1][j][2]);
				add(dp[cur][nxt[j][1]][0],dp[i&1][j][2]);
			}
		}
	}
	for(int i=0;i<=s;i++){
		int num=__builtin_popcount(i);
		for(int j=0;j<3;j++)add(ans[num],dp[n&1][i][j]);
	}
	for(int i=0;i<=k;i++)printf("%lld\n",ans[i]);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen("dpWA.txt","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
