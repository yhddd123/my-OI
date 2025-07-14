#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=500010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
void dfs(int u){
	if(!head[u]){
		a[u]=a[u]*2-1;
		return ;
	}
	a[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;dfs(v);
		a[u]+=a[v];
	}
	if(a[u]>0)a[u]++;
	else if(a[u]<0)a[u]--;
	else a[u]=(n&1)?1:-1;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=2;i<=n;i++){
		int u=read();
		add(u,i);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1);
	if(a[1]<=0)puts("Alice");
	else puts("Bob");
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
