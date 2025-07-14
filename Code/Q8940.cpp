#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=510;
const int inf=1e7;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int a[maxn][maxn];
int t[maxn];
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
map<int,int> vis[maxn];bool bk[maxn];
int x[maxn],y[maxn],id[maxn],rk[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		vis[i].clear();t[i]=0;
		for(int j=1;j<=n;j++)a[i][j]=read()+inf,t[i]+=a[i][j],vis[i][a[i][j]]=j;
		id[i]=i;
	}
	for(int i=1;i<=n;i++)bk[i]=0;
	m=n+1;
	sort(id+1,id+m+1,[&](int u,int v){return t[u]<t[v];});
	for(int i=m;i>1;i--)t[id[i]]=t[id[i]]-t[id[i-1]];
	if(!t[id[2]]){
		for(int i=1;i<=n;i++)printf("%lld ",i);puts("");
		return ;
	}
	int gg=t[id[2]];for(int i=2;i<=m;i++)gg=gcd(gg,t[id[i]]);
	for(int i=2;i<=m;i++)t[id[i]]/=gg;
	t[1]=0;for(int i=2;i<=m;i++)t[id[i]]+=t[id[i-1]];
	// for(int i=1;i<=m;i++)cout<<t[id[i]]<<"\n";cout<<"\n";
	for(int i=1;i<m;i++){
		for(int j=1;j<=n;j++){
			int p=a[id[i+1]][j]-a[id[i]][j],q=t[id[i+1]]-t[id[i]],b=t[id[i+1]]*a[id[i]][j]-t[id[i]]*a[id[i+1]][j];
			if(b%q)continue;
			if(vis[1].find(b/q)==vis[1].end())continue;
			int pos=vis[1][b/q];
			if(bk[pos])continue;
			bool fl=1;
			for(int k=1;k<=m;k++){
				int val=p*t[id[k]]+b;
				if(val%q){fl=0;break;}
				if(vis[id[k]].find(val/q)==vis[id[k]].end()){fl=0;break;}
			}
			if(fl){
				int pos=vis[1][b/q];
				x[pos]=p,y[pos]=q;bk[pos]=1;
			}
		}
	}
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){
		if(x[u]*y[v]==x[v]*y[u])return u<v;
		return x[u]*y[v]<x[v]*y[u];
	});
	for(int i=1;i<=n;i++)rk[id[i]]=i;
	// for(int i=1;i<=n;i++)cout<<x[i]<<" "<<y[i]<<"\n";
	for(int i=1;i<=n;i++)printf("%lld ",rk[i]);puts("");
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("sort.in","r",stdin);
	// freopen("sort.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}