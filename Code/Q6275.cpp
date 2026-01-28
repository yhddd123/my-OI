#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=19;
const int inf=1e9;
bool mbe;

int n,m,q;
char S[maxn+5];
int e[maxn][maxn];
int pw[maxn*maxn];
int num[1<<maxn];
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
int f[1<<maxn];
int g[1<<maxn][maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[u][v]=e[v][u]=1;
		num[(1<<u)|(1<<v)]=1;
	}
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++)if(s&(1<<i))num[s]+=num[s^(1<<i)];
	}
	pw[0]=1;for(int i=1;i<n*n;i++)pw[i]=pw[i-1]*2%mod;
	for(int s=0;s<(1<<n);s++)f[s]=pw[num[s]];
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<n);s++){
			for(int j=0;j<n;j++)g[s][j]=0;
		}
		for(int s=0;s<(1<<n);s++)if(!(s&(1<<i))){
			for(int j=0;j<n;j++)if(s&(1<<j))inc(g[s][j],f[s]);
		}
		for(int s=0;s<(1<<n);s++)if(!(s&(1<<i))){
			for(int j=0;j<n;j++)if(s&(1<<j)){
				for(int k=0;k<=i;k++)if(e[j][k]&&!(s&(1<<k)))inc(g[s|(1<<k)][k],g[s][j]);
			}
		}
		for(int s=(1<<n)-1;~s;s--)if(s&(1<<i)){
			inc(f[s],mod-f[s-(1<<i)]);
			inc(f[s],mod-g[s][i]);
		}
	}
	q=read();
	while(q--){
		scanf("%s",S);int s=0;
		for(int i=0;i<n;i++)if(S[i]=='1')s|=1<<i;
		printf("%lld\n",f[s]);
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}