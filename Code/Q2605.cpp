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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,k;
vector<int> e[maxn];
int d[maxn];
bool vis[maxn];
mt19937 rnd(time(0));
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	while(1){
		for(int i=1;i<=n;i++)vis[i]=rnd()&1;
		int m=0;
		for(int u=1;u<=n;u++){
			for(int v:e[u])m+=vis[u]!=vis[v];
		}
		// for(int i=1;i<=n;i++)cout<<vis[i];cout<<"\n";
		m/=2;
		// cout<<m<<" "<<k*n<<endl;
		if(m>k*n){
			for(int u=1;u<=n;u++){
				d[u]=0;
				for(int v:e[u])d[u]+=vis[u]!=vis[v];
			}
			queue<int> q;
			for(int i=1;i<=n;i++)if(d[i]<=k)q.push(i);
			while(!q.empty()){
				int u=q.front();q.pop();
				for(int v:e[u])if(vis[u]!=vis[v]&&d[v]>k){
					d[v]--;
					if(d[v]<=k)q.push(v);
				}
			}
			vector<int> a,b;
			for(int i=1;i<=n;i++)if(!vis[i]&&d[i]>k)a.pb(i);
			for(int i=1;i<=n;i++)if(vis[i]&&d[i]>k)b.pb(i);
			printf("%d ",a.size());for(int u:a)printf("%d ",u);puts("");
			printf("%d ",b.size());for(int u:b)printf("%d ",u);puts("");
			break;
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}