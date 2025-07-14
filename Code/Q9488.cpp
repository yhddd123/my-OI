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
const int maxn=110;
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
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn*maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int d[maxn];
int dp[maxn][maxn];
struct mat{
	int e[maxn*3][maxn*3];
	mat(){mems(e,0);}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<=m;i++){
			for(int k=0;k<=m;k++){
				for(int j=0;j<=m;j++)(res.e[i][j]+=e[i][k]*tmp.e[k][j])%=mod;
			}
		}
		return res;
	}
}a,b;
mat one(){
	mat res;
	for(int i=0;i<=m;i++)res.e[i][i]=1;
	return res;
}
mat ksm(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
int id(int u,int v){return u*n+v;}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(u,v),add(v,u),d[u]++,d[v]++;
	}
	dp[0][1]=1;
	for(int i=1;i<=5;i++){
		for(int u=1;u<=n;u++){
			for(int ii=head[u];ii;ii=e[ii].nxt){
				int v=e[ii].to;
				(dp[i][v]+=dp[i-1][u])%=mod;
			}
			if(i>=2)(dp[i][u]+=dp[i-2][u]*(mod-(d[u]-(i!=2)))%mod)%=mod;
		}
	}
	if(k<=3){
		printf("%lld\n",dp[k][n]);
		return ;
	}
	for(int i=1;i<=3;i++){
		for(int u=1;u<=n;u++)a.e[1][id(i-1,u)]=dp[i][u];
	}
	for(int i=0;i<2;i++){
		for(int u=1;u<=n;u++)b.e[id(i+1,u)][id(i,u)]=1;
	}
	m=3*n;
	for(int u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			b.e[id(2,v)][id(2,u)]++;
		}
		b.e[id(1,u)][id(2,u)]=mod-(d[u]-1);
	}
	b=ksm(b,k-1);
	a=a*b;
	printf("%lld\n",a.e[1][n]);
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
