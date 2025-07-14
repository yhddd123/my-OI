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
const int maxn=1000010;
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
vector<int> e[maxn],g[maxn];
int d[maxn];
int st[maxn],tp;
int ans[maxn];
bool vis[maxn];
queue<int> q;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),g[u].pb(v);
		d[u]++,d[v]--;
	}
	for(int t=1;t<=60;t++){
		int p=0;for(int i=1;i<=n;i++)if(d[i]>0){p=i;break;}
		if(!p)break;
		tp=0;d[p]--;
		while(d[p]>=0){
			st[++tp]=p;
			int v=e[p].back();e[p].pop_back();
			p=v;
		}
		st[++tp]=p;d[p]++;
		for(int i=1;i<=n;i++)vis[i]=0;
		int num=0;
		for(int i=tp;i;i--){
			q.push(st[i]),vis[st[i]]=1;
			while(!q.empty()){
				int u=q.front();q.pop();;++num;
				for(int v:g[u]){
					if(!vis[v])q.push(v),vis[v]=1;
				}
			}
			if(!ans[st[i]])ans[st[i]]=num;
			// cout<<st[i]<<" "<<ans[st[i]]<<"\n";
		}
		// cout<<tp<<"\n";
		// for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
	}
	for(int i=1;i<=n;i++)if(!ans[i])ans[i]=1;
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
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
