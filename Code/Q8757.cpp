#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=400010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
vector<int> f[maxn];
int fd(int id,int x){
	if(f[id][x]==x)return x;
	return f[id][x]=fd(id,f[id][x]);
}
vector<int> id[maxn];int idx,val[maxn];
vector<int> e[maxn];
int st[maxn],tp;
void dfs(int u,int fa,int ed){
	st[++tp]=val[u];
	if(st[tp]==ed)return ;
	for(int v:e[u])if(v!=fa){
		dfs(v,u,ed);
		if(st[tp]==ed)return ;
	}
	tp--;
}
void work(){
	n=read();m=read();idx=0;
	int k=(m+n-2)/(n-1);
	for(int i=1;i<=k;i++){
		f[i].resize(n+1);id[i].resize(n+1);
		for(int j=1;j<=n;j++)f[i][j]=j,val[id[i][j]=++idx]=j,e[idx].clear();
	}
	while(m--){
		int u=read(),v=read();
		int l=1,r=k,res=k+1;
		while(l<=r){
			int mid=l+r>>1;
			if(fd(mid,u)!=fd(mid,v))r=mid-1,res=mid;
			else l=mid+1;
		}
		if(res<=k){
			f[res][fd(res,u)]=fd(res,v);
			e[id[res][u]].push_back(id[res][v]),e[id[res][v]].push_back(id[res][u]);
		}
	}
	for(int i=1;i<=n;i++)if(fd(k,i)!=i){
		int u=i,v=fd(k,i);
		printf("%lld %lld\n",u,v);
		for(int j=1;j<=k;j++){
			tp=0;dfs(id[j][u],0,v);
			printf("%lld ",tp);
			for(int l=1;l<=tp;l++)printf("%lld ",st[l]);printf("\n");
		}
		return ;
	}
	puts("-1");
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
