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
const int maxn=20010;
const int maxm=maxn*5;
const int inf=1e9;
bool mbe;

int a,b,n,S,T;
int f[maxn];
int head[maxn],rad[maxn],tot=1;
struct nd{
	int nxt,to,w;
}e[maxm<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int d[maxn];
void add(int u,int v,int l,int r){
	add(u,v,r-l);
	d[u]-=l,d[v]+=l;
}
int s,t,flow;
int dis[maxn];
bool bfs(){
	queue<int> q;
	for(int i=1;i<=2*n+3;i++)dis[i]=0,rad[i]=head[i];
	dis[s]=1,q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].w&&!dis[v])dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int val){
	if(u==t)return val;
	int res=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].w&&dis[v]==dis[u]+1){
			int out=dfs(v,min(val,e[i].w));
			val-=out,res+=out;
			e[i].w-=out,e[i^1].w+=out;
			if(!val)break ;
		}
	}
	return res;
}
void work(){
	a=read(),b=read(),n=read();S=1,T=2*n+1;s=2*n+2,t=2*n+3;
	if(!n){puts("Yes");return ;}
	for(int i=1;i<=t;i++)head[i]=d[i]=f[i]=0;tot=1;
	add(T,S,inf);
	for(int i=1;i<=n;i++){
		int o=read(),l=read(),r=read();
		if(o==1)add(l,r+1,0,1);
		else add(l,r+1,1,1);
		f[l]++,f[r+1]--;
	}
	for(int i=1;i<=2*n+1;i++)f[i]+=f[i-1];
	for(int i=1;i<=2*n;i++){
		if(a+b-f[i]<0){puts("No");return ;}
		add(i,i+1,0,a+b-f[i]);
	}
	int sum=0;
	for(int i=1;i<=2*n+1;i++){
		if(d[i]>=0)add(s,i,d[i]),sum+=d[i];
		else add(i,t,-d[i]);
	}
	flow=0;while(bfs())flow+=dfs(s,inf);
	if(flow!=sum){puts("No");return ;}
	flow=e[3].w;e[2].w=e[3].w=0;
	s=T,t=S;
	while(bfs())flow-=dfs(s,inf);
	if(flow<=a)puts("Yes");
	else puts("No");
}
bool med;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=read();
	while(T--)work();
}