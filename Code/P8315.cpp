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
const int maxn=65;
const int inf=1e9;
bool mbe;

int n,m,k,ans,a[maxn][maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
map<pii,int> mp;
int st[maxn],tp;
void dfs(int u,int ed){
	st[++tp]=u;
	if(u==ed)return ;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==st[tp-1])continue;
		dfs(v,ed);
		if(st[tp]==ed)return ;
	}
	tp--;
}
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
		mp[{u,v}]=mp[{v,u}]=i;
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		tp=0;dfs(u,v);
		for(int j=1;j<=tp;j++)a[i][j]=st[j];
	}
	for(int s=0;s<(1<<m);s++){
		for(int i=1;i<n;i++)f[i]=i;
		for(int i=1;i<=m;i++)if(s&(1<<i-1)){
			for(int j=3;a[i][j];j++)f[fd(mp[{a[i][j-2],a[i][j-1]}])]=fd(mp[{a[i][j-1],a[i][j]}]);
		}
		int res=1;for(int i=1;i<n;i++)if(f[i]==i)res=res*k%mod;
		if(__builtin_popcount(s)&1)(ans+=mod-res)%=mod;
		else (ans+=res)%=mod;
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen("pearl.in","r",stdin);
	// freopen("pearl.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}