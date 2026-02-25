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
const int maxn=2010;
const int inf=1e9;
bool mbe;


int n,m,k;
char s[maxn],t[maxn];
vector<vector<int>> ans,tmp;
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
		tp=0;for(int u=T;u!=S;u=pre[u])st[++tp]=u;
		vector<int> a(k);
		for(int i=1,j=0;i<=n;i++)if(S&(1<<i-1))a[j++]=i;
		ans.pb(a);
		for(int i=tp;i;i--){
			int ss=st[i];
			vector<int> a;
			for(int p:ans.back())a.pb(ee[ss][p-1]);
			ans.pb(a);
		}
		printf("%d\n",ans.size()-1);
		for(auto a:ans){
			for(int p:a)printf("%d ",p);puts("");
		}
	}
}


int to[maxn];
namespace flow{
const int maxm=100010;
struct nd{
	int nxt,to,w;
}e[maxm<<1];
int head[maxn<<1],tot=1,s,t,flow;
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int rad[maxn<<1],dis[maxn<<1];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
void init(){
	s=2*n+1,t=2*n+2;
	for(int i=1;i<=t;i++)head[i]=0;tot=1;
	for(int u=1;u<=n;u++){
		for(int v:(::e[u]))add(u,v+n,1);
	}
	for(int i=1;i<=n;i++)add(s,i,1);
	for(int i=1;i<=n;i++)add(i+n,t,1);
}
bool chk(vector<int> a){
	s=2*n+1,t=2*n+2;
	for(int i=1;i<=2*m+2*n;i++)e[2*i].w=1,e[2*i+1].w=0;
	for(int i=2*m+1;i<=2*m+n;i++)e[2*i].w=0;
	for(int p:a)e[2*(2*m+p)].w=1;
	flow=0;while(bfs())flow+=dfs(s,n);
	for(int u:a){
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v<=2*n&&!e[i].w)to[u]=v-n;
		}
	}
	return flow==a.size();
}
}

int dis[maxn][maxn][2],pre[maxn][maxn][2];
void dij(int s){
	for(int i=1;i<=n;i++)dis[s][i][0]=dis[s][i][1]=0;
	queue<pii> q;
	dis[s][s][0]=1;q.push({s,0});
	while(!q.empty()){
		auto[u,o]=q.front();q.pop();
		for(int v:e[u]){
			if(!dis[s][v][o^1])dis[s][v][o^1]=dis[s][u][o]+1,pre[s][v][o^1]=u,q.push({v,o^1});
		}
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
vector<int> get(char *s){
	vector<int> a;
	for(int i=1;i<=n;i++)if(s[i]=='1')a.pb(i);
	return a;
}
int rnk[maxn],ed[maxn];
bool bk1[maxn],bk2[maxn];
mt19937 rnd(0);
pair<vector<int>,vector<int>> dfs1(int u,int o1,int o2){
	vis[u]=1;
	vector<int> id1,id2;
	if(col[u]!=o1&&!bk1[u]&&s[u]=='1')id1.pb(u);
	if(col[u]!=o2&&!bk2[u]&&t[u]=='1')id2.pb(u);
	for(int v:e[u])if(!vis[v]){
		auto[iv1,iv2]=dfs1(v,o1,o2);
		for(int p:iv1)id1.pb(p);
		for(int p:iv2)id2.pb(p);
	}
	if(id1.size()&&id2.size()){
		shuffle(id1.begin(),id1.end(),rnd);
		shuffle(id2.begin(),id2.end(),rnd);
		while(id1.size()&&id2.size()){
			bk1[id1.back()]=bk2[id2.back()]=1;
			ed[rnk[id1.back()]]=id2.back();
			id1.pop_back(),id2.pop_back();
		}
	}
	return {id1,id2};
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
	for(int u:id)vis[u]=0;
	dfs1(rt,0,o);
	for(int u:id)vis[u]=0;
	dfs1(rt,1,o^1);
	for(int u:id)vis[u]=0;
	dfs1(rt,2,2);
	return 1;
}
vector<int> pos[maxn];
int lim;
bool sol(int o){
	for(int i=1;i<=n;i++)vis[i]=bk1[i]=bk2[i]=0;
	for(int i=1;i<=n;i++)if(!vis[i]){
		if(!sovle(i,o))return 0;
	}
	vector<int> a=get(t);
	if(!flow::chk(a))return 0;
	a=get(s);
	ans.pb(a);
	// for(int i=0;i<k;i++)cout<<a[i]<<" ";cout<<"\n";
	// for(int i=0;i<k;i++)cout<<ed[i]<<" ";cout<<"\n";
	// for(int i=0;i<k;i++)cout<<dis[ed[i]][a[i]][o]<<" ";cout<<"\n";
	// for(int i=0;i<k;i++)assert(dis[ed[i]][a[i]][o]);
	while(ans.size()<=lim){
		vector<int> a=ans.back(),b(k);
		bool fl=1;for(int i=0;i<k;i++)fl&=a[i]==ed[i];
		if(fl)break;
		if(!flow::chk(a))return 0;
		for(int i=0;i<k;i++){
			if(a[i]!=ed[i])b[i]=pre[ed[i]][a[i]][o];
			else b[i]=to[a[i]];
			pos[b[i]].pb(i);
		}
	for(int i=0;i<k;i++)cout<<a[i]<<" ";cout<<"\n";
	// for(int i=0;i<k;i++)cout<<b[i]<<" ";cout<<"\n";
	// for(int i=0;i<k;i++)cout<<ed[i]<<" ";cout<<"\n";
	for(int i=0;i<k;i++)cout<<dis[ed[i]][a[i]][o]<<" ";cout<<endl;
		queue<int> q;
		for(int i=0;i<k;i++)if(pos[b[i]].size()>1)q.push(b[i]);
		while(!q.empty()){
			int u=q.front();q.pop();
			if(pos[u].size()<=1)continue;
			int p=pos[u][0];for(int id:pos[u])if(to[a[id]]==u)p=id;
			for(int id:pos[u])if(id!=p){
				b[id]=to[a[id]];
				pos[b[id]].pb(id);
				if(pos[b[id]].size()==2)q.push(b[id]);
			}
			pos[u]={p};
		}
		for(int i=0;i<k;i++)pos[b[i]].clear();
		ans.pb(b);
		// int num=0;for(int i=0;i<k;i++)num+=b[i]==pre[ed[i]][a[i]][o];
		// cout<<num<<endl;
		o^=1;
	}
	return 1;
}
void work(){
	n=read();m=read();scanf("%s%s",s+1,t+1);ans.clear();
	k=0;for(int i=1;i<=n;i++)if(s[i]=='1')rnk[i]=k++;
	lim=min(2*n*n,10000000/n-1);
	cout<<lim<<"\n";
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
	// if(n<=20&&m<=20)return sub1::sovle();
	flow::init();
	for(int i=1;i<=n;i++)dij(i);
	bool fl0=sol(0);
	tmp=ans,ans.clear();
	bool fl1=sol(1);
	if(!fl0&&!fl1){puts("NO");return ;}
	if(fl0&&fl1){
		if(tmp.size()<ans.size())swap(tmp,ans);
	}
	else if(!fl1)ans=tmp;
	puts("YES");
	if(ans.size()>lim)assert(0);
	printf("%d\n",ans.size()-1);
	for(auto a:ans){
		for(int p:a)printf("%d ",p);puts("");
	}
}

bool med;
signed main(){
	// freopen("stone.in","r",stdin);
	// freopen("stone.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=read();
	while(T--)work();
}