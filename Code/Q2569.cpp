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

int n,ans;
vector<int> e[maxn];
int dfs(int u,int fa){
	if(e[u].size()==1)return 1;
	int t=0;
	for(int v:e[u]){
		if(v==fa)continue;
		int op=dfs(v,u);
		// cout<<u<<" "<<v<<" "<<op<<"\n";
		if(!op)continue;
		if(op==1)t++;
	}
	if(t>=2){++ans;return 0;}
	if(t==1)return 1;
	return 0;
}
void work(){
	n=read();
	if(n<=2){puts("1");return ;}
	for(int i=2;i<=n;i++){
		int u=read();
		e[u].pb(i),e[i].pb(u);
	}
	int rt=1;
	if(e[rt].size()==1)rt=e[rt][0];
	dfs(rt,0);
	printf("%lld\n",ans);
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