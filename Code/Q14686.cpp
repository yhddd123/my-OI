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

int n,a[maxn],b[maxn],c[maxn];
int ans[maxn];
vector<int> e[maxn];
set<pii> s;
void dfs(int u){
	for(int v:e[u]){
		if(ans[v])continue;
		if(b[u]<c[u]){
			if(b[v]<b[u])ans[v]=c[u]-b[v],c[v]=c[u];
			else if(b[v]<c[u])ans[v]=(b[v]-b[u])/2,c[v]=(b[u]+b[v])/2;
			else ans[v]=max(b[v]-c[u],(b[v]-b[u])/2),c[v]=(ans[v]==b[v]-c[u]?c[u]:(b[u]+b[v])/2);
		}
		else{
			if(b[v]>b[u])ans[v]=b[v]-c[u],c[v]=c[u];
			else if(b[v]>c[u])ans[v]=(b[u]-b[v])/2,c[v]=(b[u]+b[v])/2;
			else ans[v]=max(c[u]-b[v],(b[u]-b[v])/2),c[v]=(ans[v]==c[u]-b[v]?c[u]:(b[u]+b[v])/2);
		}
		// cout<<u<<" "<<v<<" "<<ans[v]<<"\n";
		// cout<<b[u]<<" "<<c[u]<<" "<<b[v]<<"\n";
		dfs(v);
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),e[a[i]].pb(i);
	for(int i=1;i<=n;i++)b[i]=2*read();
	for(int i=1;i<=n;i++){
		if((b[i]-b[a[i]])*(b[a[i]]-b[a[a[i]]])<0)s.insert({abs(b[i]-b[a[i]]),i});
	}
	while(!s.empty()){ 
		int u=(*s.begin()).se;s.erase(*s.begin());
		if(ans[u])continue;
		// cout<<u<<" "<<a[u]<<" "<<b[u]<<" "<<b[a[u]]<<"\n";
		ans[u]=abs(b[u]-b[a[u]])/2;
		c[u]=(b[u]+b[a[u]])/2;
		dfs(u);
	}
	for(int i=1;i<=n;i++)printf("%lld ",ans[i]);
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