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
char s[maxn],t[maxn];
vector<vector<int>> ans;
vector<int> e[maxn];

namespace sub1{
	int S,T;
	int dis[1<<20],pre[1<<20];
	int st[maxn],tp;
	vector<int> to,ee[1<<20];
	void sovle(){
		to.resize(n);
		S=T=0;
		for(int i=1;i<=n;i++)if(s[i]=='1')S|=1<<i-1;
		for(int i=1;i<=n;i++)if(t[i]=='1')T|=1<<i-1;
		for(int s=0;s<(1<<n);s++)dis[s]=pre[s]=0;
		queue<int> q;
		dis[S]=1,q.push(S);
		while(!q.empty()){
			int u=q.front();q.pop();
			auto ddfs=[&](auto &&self,int d,int v)->void{
				if(d==n){
					if(!dis[v])dis[v]=dis[u]+1,pre[v]=u,ee[v]=to,q.push(v);
					return ;
				}
				if(!(u&(1<<d)))self(self,d+1,v);
				else{
					for(int c:e[d+1])if(!(v&(1<<c-1))){
						to[d]=c;
						self(self,d+1,v|(1<<c-1));
					}
				}
			};
			ddfs(ddfs,0,0);
		}
		if(!dis[T]){puts("NO");return ;}
		puts("YES");
		// tp=0;for(int u=T;u!=S;u=pre[u])st[++tp]=u;
		// vector<int> a(k);
		// for(int i=1,j=0;i<=n;i++)if(S&(1<<i-1))a[j++]=i;
		// ans.pb(a);
		// for(int i=tp;i;i--){
		// 	int ss=st[i];
		// 	vector<int> a;
		// 	for(int p:ans.back())a.pb(ee[ss][p-1]);
		// 	ans.pb(a);
		// }
		// printf("%d\n",ans.size()-1);
		// for(auto a:ans){
		// 	for(int p:a)printf("%d ",p);puts("");
		// }
	}
}

bool vis[maxn];
vector<int> id;
int col[maxn];
bool fl;
void dfs(int u,int fa){
	vis[u]=1,id.pb(u);
	col[u]=col[fa]^1;
	for(int v:e[u]){
		if(!vis[v])dfs(v,u);
		else if(col[u]==col[v])fl=1;
	}
}
bool sovle(int rt,int o){
	fl=0;id.clear();dfs(rt,0);
	int num=0;for(int u:id)num+=(s[u]=='1')-(t[u]=='1');
	if(num)return 0;
	if(!fl){
		int v1[2],v2[2];v1[0]=v1[1]=v2[0]=v2[1]=0;
		for(int u:id)v1[col[u]]+=s[u]=='1',v2[col[u]]+=t[u]=='1';
		if(!(v1[0]==v2[o]))return 0;
	}
	return 1;
}
bool sol(int o){
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=1;i<=n;i++)if(!vis[i]){
		if(!sovle(i,o))return 0;
	}
	return 1;
}
void work(){
	n=read();m=read();scanf("%s%s",s+1,t+1);ans.clear();
	k=0;for(int i=1;i<=n;i++)k+=s[i]=='1';
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	bool fl=1;for(int i=1;i<=n;i++)fl&=s[i]==t[i];
	if(fl){
		puts("YES");
		puts("0");
		for(int i=1;i<=n;i++)if(s[i]=='1')printf("%d ",i);puts("");
		return ;
	}
	if(n<=20&&m<=20)return sub1::sovle();
	if(sol(0)){}
	else if(sol(1)){}
	else{puts("NO");return ;}
	puts("YES");
	// puts("0");
	// for(int i=1;i<=n;i++)if(s[i]=='1')printf("%d ",i);puts("");
}

bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=read();
	while(T--)work();
}