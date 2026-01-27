#include<bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
using namespace __gnu_pbds;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,a[maxn];ll ans;
vector<int> e[maxn];
__gnu_pbds::priority_queue<ll> q[maxn];
void dfs(int u,int fa){
	for(int v:e[u])if(v!=fa)dfs(v,u),q[u].join(q[v]);
	ll v=a[u];
	while(q[u].size()>1&&q[u].top()>v){
		v-=q[u].top();q[u].pop();
		v+=q[u].top();q[u].pop();
	}
	if(!q[u].size())q[u].push(v);
	else if(q[u].top()>v){
		ans+=((n&1)?-1:1)*(v-q[u].top());
		q[u].pop();
	}
	else q[u].push(v);
}
void work(){
	n=read();ll sum=0;
	for(int i=1;i<=n;i++)a[i]=read(),sum+=a[i];
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v);e[v].pb(u);
	}
	dfs(1,0);
	int o=0;
	while(!q[1].empty()){
		ans+=(o?-1:1)*q[1].top();q[1].pop();
		o^=1;
	}
	printf("%lld\n",(sum+ans)/2);
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