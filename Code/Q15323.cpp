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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m,k;
int ans[maxn],tp;
vector<pii> g[8];
vector<int> e[8][maxn];
void dfs(int d,vector<int> &a){
	if(tp>=k)return ;
	for(int i=0;i<8;i++){
		vector<int> b;
		for(int u:a){
			for(int v:e[i][u]){
				ans[++tp]=d+1;
				b.pb(v);
				if(tp>=k)break;
			}
			if(tp>=k)break;
		}
		if(tp>=k)break;
		if(b.size())dfs(d+1,b);
		if(tp>=k)break;
	}
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read()-1;
		g[w].pb({u,v});
		e[w][u].pb(v);
	}
	for(int i=0;i<8;i++){
		vector<int> id;
		for(auto[u,v]:g[i])id.pb(v);
		for(int i=0;i<id.size()&&tp<k;i++)ans[++tp]=1;
		dfs(1,id);
	}
	for(int i=1;i<=tp;i++)printf("%lld\n",ans[i]);
	for(int i=tp+1;i<=k;i++)puts("-1");
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