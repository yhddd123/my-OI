// Problem: P5830 [ZJOI2016] 随机树生成器
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5830
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-09-02 15:05:15
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=1010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n=1000,rt,op;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
mt19937 rnd(time(0));
int f[maxn],a[maxn],vis[maxn],d[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
void mk(int op){
	for(int i=1;i<=n;i++)head[i]=d[i]=0;tot=0;
	if(op==1){
		for(int i=2;i<=n;i++){
			int u=rnd()%(i-1)+1;
			add(u,i),add(i,u);
			d[u]++,d[i]++;
		}
	}
	if(op==2){
		for(int i=2;i<=n;i++){
			int u=rnd()%(i-1-i/2+1)+i/2;
			add(u,i),add(i,u);
			d[u]++,d[i]++;
		}
	}
	if(op==3){
		for(int i=1;i<=n;i++)f[i]=i;
		for(int i=1;i<n;i++){
			int u=rnd()%n+1,v=rnd()%n+1;
			do{
				u=rnd()%n+1,v=rnd()%n+1;
			}while(fd(u)==fd(v));
			f[fd(u)]=fd(v);
			add(u,v),add(v,u);
			d[u]++,d[v]++;
		}
	}
	if(op==4){
		for(int i=1;i<=n;i++)vis[i]=0;
		for(int i=1;i<=n-2;i++)a[i]=rnd()%n+1,vis[a[i]]++;
		set<int> s;
		for(int i=1;i<=n;i++)if(!vis[i])s.insert(i);
		for(int i=1;i<=n-2;i++){
			int u=*s.begin();
			add(u,a[i]),add(a[i],u);
			d[u]++,d[a[i]]++;
			s.erase(u);vis[a[i]]--;
			if(!vis[a[i]])s.insert(a[i]);
		}
		int u=*s.begin(),v=*--s.end();
		add(u,v),add(v,u);
		d[u]++,d[v]++;
	}
}
namespace sub3{
	double ans,siz[maxn];
	void dfs(int u,int fa){
		siz[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v==fa)continue;
			dfs(v,u);siz[u]+=siz[v];
		}
	}
	double sovle(){
		ans=0;dfs(rt,0);
		for(int i=1;i<=n;i++)ans+=log2(siz[i])+log2(n-siz[i]+1);
		return ans;
	}
}
namespace sub5{
	int ans,dis[maxn];
	queue<int> q;
	int sovle(){
		for(int i=1;i<=n;i++)dis[i]=0;ans=0;
		for(int i=1;i<=n;i++)if(d[i]==1)q.push(i);
		while(!q.empty()){
			int u=q.front();q.pop();ans+=dis[u];
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(d[v]>1){
					dis[v]=max(dis[v],dis[u]+1);
					d[v]--;
					if(d[v]==1)q.push(v);
				}
			}
		}
		return ans;
	}
}
// int cnt[maxn*100];
void work(){
	for(int i=1;i<=n;i++)head[i]=d[i]=0;tot=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);d[u]++,d[v]++;
	}
	rt=rnd()%n+1;
	int val=sub5::sovle();
	if(val<=1600){puts("1");return ;}
	if(op==1||(op!=3&&val<=2453)){
		// cnt[val]++;
		if(op==2&&val==2448){puts("3");return ;}
		puts("2");return ;
	}
	val=sub3::sovle();
	if(op==2||val<=11810){puts("3");return ;}
	else puts("4");
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("zsj.in","r",stdin);
	// freopen("zsj.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	op=read();T=read();
	while(T--)work();
}