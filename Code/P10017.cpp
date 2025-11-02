#include<bits/stdc++.h>
// #define int long long
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
const int maxn=18;
const int inf=1e9;
bool mbe;

int n,m;
vector<tuple<int,int,int>> e[maxn+1];
struct node{
	int v,d,s,st,ed;
}a[1<<maxn+2];
vector<int> iid;
vector<int> path[maxn][maxn];
void dfs(int u,int fa,int fr,int s1=0,int s2=0,int d=0,int s3=0,bool fl=0){
	path[fr][u]=iid;
	fl|=e[u].size()==1;
	// cout<<u<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<d<<"\n";
	if(d&&fl){
		for(int ss=s2;;ss=(ss-1)&s2){
			a[++m]={s1|ss,d,s3,fr,u};
			if(!ss)break;
		}
	}
	for(auto[v,w,id]:e[u])if(v!=fa){
		iid.pb(id);
		dfs(v,u,fr,w==2?s1:(s1|((1<<d)*w)),w==2?(s2|(1<<d)):s2,d+1,s3|(1<<id),fl);
		iid.pop_back();
	}
}
int lcp[1<<maxn+2];
int f[1<<maxn-1][maxn+1];
bool vis[1<<maxn-1][maxn+1];
vector<int> id[maxn+1];
const int maxm=40000010;
tuple<int,int,int> st[maxm];int tp;
int bel[1<<maxn-1];
int p1[1<<maxn+2],p2[1<<maxn+2];
int col[maxn];
int mx[1<<maxn-1];
inline void chkmx(int &u,int v){(u<v)&&(u=v);}
void work(){
	n=read();m=0;
	for(int i=0;i<n;i++)e[i].clear();
	for(int i=0;i<n-1;i++){
		int u=read(),v=read(),w=read();
		col[i]=w;
		e[u].pb({v,w,i}),e[v].pb({u,w,i});
	}
	m=0;for(int i=0;i<n;i++)dfs(i,-1,i);
	sort(a+1,a+m+1,[&](node u,node v){
		for(int j=0;j<min(u.d,v.d);j++)if(((u.v>>j)&1)!=((v.v>>j)&1))return ((u.v>>j)&1)<((v.v>>j)&1);
		return u.d<v.d;
	});
	for(int i=1;i<m;i++){
		lcp[i]=min(a[i].d,a[i+1].d);
		for(int j=0;j<min(a[i].d,a[i+1].d);j++)if(((a[i].v>>j)&1)!=((a[i+1].v>>j)&1)){lcp[i]=j;break;}
	}
	// cout<<m<<" "<<(1<<n+2)<<"\n";
	// for(int i=1;i<=m;i++){
		// cout<<i<<" "<<a[i].v<<" "<<a[i].d<<" "<<a[i].s<<" "<<lcp[i-1]<<"\n";
	// }
	for(int s=0;s<(1<<n-1);s++){
		bel[s]=0;mx[s]=-inf;
		for(int i=0;i<=n;i++)f[s][i]=-inf;
	}
	f[0][0]=mx[0]=0;vis[0][0]=1,id[0].pb(0);
	for(int i=1;i<=m;i++){
		p1[i]=tp;
		for(int j=lcp[i-1]+1;j<=n;j++){
			for(int s:id[j]){
				if(bel[s]!=i)st[++tp]={s,lcp[i-1],f[s][lcp[i-1]]},bel[s]=i;
				chkmx(f[s][lcp[i-1]],f[s][j]);chkmx(mx[s],f[s][lcp[i-1]]-lcp[i-1]);
				if(!vis[s][lcp[i-1]])vis[s][lcp[i-1]]=1,id[lcp[i-1]].pb(s);
				vis[s][j]=0;
			}
			id[j].clear();
		}
		p2[i]=tp;
		int ss=(1<<n-1)-1-a[i].s;
		for(int s=ss;;s=(s-1)&ss){
			// int mx=0;for(int j=0;j<=n;j++)mx=max(mx,f[s][j]+a[i].d-j);
			st[++tp]={s|a[i].s,a[i].d,f[s|a[i].s][a[i].d]};
			chkmx(f[s|a[i].s][a[i].d],mx[s]+a[i].d);chkmx(mx[s|a[i].s],f[s|a[i].s][a[i].d]-a[i].d);
			if(!vis[s|a[i].s][a[i].d])vis[s|a[i].s][a[i].d]=1,id[a[i].d].pb(s|a[i].s);	
			if(!s)break;
		}
	}
	int ans=0,ss,jj;
	for(int s=0;s<(1<<n-1);s++){
		for(int j=0;j<=n;j++)if(ans<f[s][j])ans=f[s][j],ss=s,jj=j;
	}
	vector<pii> edge;
	for(int i=m;i;i--){
		int val=f[ss][jj];
		while(tp>p2[i]){
			auto[s,j,v]=st[tp--];
			f[s][j]=v;
		}
		if((ss&a[i].s)==a[i].s&&jj==a[i].d){
			int s=ss^a[i].s;
			pii mx={0,0};for(int j=0;j<=lcp[i-1];j++)mx=max(mx,{f[s][j]+a[i].d-j,j});
			if(mx.fi==val){
				ss=s,jj=mx.se;val=f[ss][jj];
				edge.pb({a[i].st,a[i].ed});
				for(int p=0;p<a[i].d;p++)col[path[a[i].st][a[i].ed][p]]=(a[i].v>>p)&1;
			}
		}
		while(tp>p1[i]){
			auto[s,j,v]=st[tp--];
			f[s][j]=v;
		}
		if(f[ss][jj]!=val){
			for(int j=lcp[i-1]+1;j<=n;j++)if(f[ss][j]==val){jj=j;break;}
		}
	}
	printf("%d\n",ans+1);
	printf("%d\n",edge.size());
	for(int i=0;i<n-1;i++)printf("%d ",col[i]?1:0);puts("");
	for(auto[u,v]:edge)printf("%d %d\n",u,v);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();read();
	puts("1");
	while(T--)work();
}