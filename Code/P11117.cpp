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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m;
bool a[maxn];
vector<pii> e[maxn];
vector<int> g[maxn];
int d[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		e[u].pb({v,w}),e[v].pb({u,w});
	}
	for(int i=1;i<=n;i++)a[i]=read();
	for(int u=1;u<=n;u++){
		for(auto[v,w]:e[u])if(a[u]==a[v]&&a[u]!=w){puts("NO");return ;}
	}
	for(int i=1;i<=n;i++)g[i].clear(),d[i]=0;
	for(int u=1;u<=n;u++)if(!a[u]){
		for(auto[v,w]:e[u]){
			if(a[v]){
				if(w)g[v].pb(u),d[u]++;
				else g[u].pb(v),d[v]++;
			}
		}
	}
	queue<int> q;
	for(int i=1;i<=n;i++)if(!d[i])q.push(i);
	vector<pii> ans;
	while(!q.empty()){
		int u=q.front();q.pop();
		if(a[u])ans.pb({u,1});
		else ans.pb({u,1}),ans.pb({u,0});
		for(int v:g[u]){
			d[v]--;
			if(!d[v])q.push(v);
		}
	}
	bool fl=1;for(int i=1;i<=n;i++)fl&=!d[i];
	if(!fl){puts("NO");return ;}
	puts("YES");
	printf("%d\n",ans.size());
	for(auto[u,v]:ans)printf("%d %d\n",u,v);
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