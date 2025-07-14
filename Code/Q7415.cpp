#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=300010;
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
int a[maxn],b[maxn][3];
priority_queue<int,vector<int>,greater<int>> id;
priority_queue<pii,vector<pii>,greater<pii>> que[maxn];
int f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
bool vis[maxn];
void upd(int i){
	if(vis[i])return ;
	int u=fd(b[i][0]),v=fd(b[i][1]);
	if(u==v)return ;
	if(a[u]+a[v]>=b[i][2]){id.push(i);return ;}
	que[u].push({(b[i][2]+a[u]-a[v]+1)/2,i}),que[v].push({(b[i][2]+a[v]-a[u]+1)/2,i});
}
vector<int> ans;
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i][0]=read(),b[i][1]=read(),b[i][2]=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)upd(i);
	while(!id.empty()){
		int i=id.top();id.pop();
		vis[i]=1;
		int u=fd(b[i][0]),v=fd(b[i][1]);
		if(u==v)continue ;
		ans.push_back(i);
		if(que[u].size()<que[v].size())swap(u,v);
		f[v]=u;a[u]+=a[v];
		while(!que[v].empty()){
			pii p=que[v].top();que[v].pop();
			if(a[u]>=p.fi)upd(p.se);
			else que[u].push(p);
		}
		while(!que[u].empty()){
			pii p=que[u].top();que[u].pop();
			if(a[u]>=p.fi)upd(p.se);
			else{que[u].push(p);break;}
		}
	}
	printf("%lld\n",(int)ans.size());
	for(int i:ans)printf("%lld ",i);
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
