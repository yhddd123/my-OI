#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxn=4010;
const int inf=1e9;
bool mbe;

int n,k,a[maxn],ans=1,res;
int ls[maxn],rs[maxn];
int f[maxn][maxn],siz[maxn],num[maxn];
void dfs(int u){
	if(!u)return ;
	siz[u]=1,num[u]=a[u];
	dfs(ls[u]),dfs(rs[u]);
	siz[u]+=siz[ls[u]]+siz[rs[u]],num[u]+=num[ls[u]]+num[rs[u]];
	
}
void work(){
	n=read();k=read();
	for(int i=1;i<=k;i++)a[read()]++;
	for(int i=1;i<=n;i++)ls[i]=read(),rs[i]=read();
	dfs(1);
	printf("%lld\n",ans);
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