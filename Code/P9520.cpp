// Problem: P9520 [JOISC2022] 监狱
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9520
// Memory Limit: 1 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=120010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int head[maxn*37],tot;
struct nd{
	int nxt,to;
}e[maxn*100];
int d[maxn*37];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;d[v]++;}
int to[maxn][17],dep[maxn];
int in[maxn][17],out[maxn][17],idx;
void dfs(int u,int fa){
	to[u][0]=fa;dep[u]=dep[fa]+1;
	for(int i=1;i<=16;i++)to[u][i]=to[to[u][i-1]][i-1];
	for(int i=0;i<=16;i++)if(to[u][i])in[u][i]=++idx,out[u][i]=++idx,d[idx-1]=d[idx]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=16;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
int kth(int u,int k){
	for(int i=16;~i;i--)if((k>>i)&1)u=to[u][i];
	return u;
}
void updata(int u,int v,int w){
	if(u==v){
		add(w,u),add(u+n,w);
		return ;
	}
	if(dep[u]<dep[v])swap(u,v);
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v]){
		add(w,in[u][i]),add(out[u][i],w);
		u=to[u][i];
	}
	if(u==v)return ;
	for(int i=16;~i;i--)if(to[u][i]!=to[v][i]){
		add(w,in[u][i]),add(out[u][i],w);
		add(w,in[v][i]),add(out[v][i],w);
		u=to[u][i],v=to[v][i];
	}
	add(w,to[u][0]),add(to[u][0]+n,w);
	add(w,u),add(w,v),add(u+n,w),add(v+n,w);
}
queue<int> q;
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	m=read();idx=2*n+m;
	dfs(1,0);
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=1;i<=idx;i++)d[i]=0;
	for(int u=1;u<=n;u++){
		for(int i=1;i<=16;i++)if(to[u][i]){
			add(in[u][i],in[u][i-1]),add(in[u][i],in[to[u][i-1]][i-1]);
			add(out[u][i-1],out[u][i]),add(out[to[u][i-1]][i-1],out[u][i]);
		}
		if(to[u][0]){
			add(in[u][0],u),add(in[u][0],to[u][0]);
			add(u+n,out[u][0]),add(to[u][0]+n,out[u][0]);
		}
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		add(i+2*n,u+n),add(v,i+2*n);
		// cout<<i+2*n<<" "<<u+n<<" "<<v<<"\n";
		add(v+n,i+2*n),add(i+2*n,u);
		int tp=lca(u,v);
		if(tp!=u&&tp!=v)u=to[u][0],v=to[v][0];
		else if(tp==u){
			if(dep[v]-dep[u]==1)continue;
			u=kth(v,dep[v]-dep[u]-1),v=to[v][0];
		}
		else{
			if(dep[u]-dep[v]==1)continue;
			v=kth(u,dep[u]-dep[v]-1),u=to[u][0];
		}
		// cout<<u<<" "<<v<<" q\n";
		updata(u,v,i+2*n);
	}
	// for(int u=1;u<=idx;u++){
		// for(int i=head[u];i;i=e[i].nxt){
			// int v=e[i].to;
			// cout<<u<<" "<<v<<"\n";
		// }
	// }
	for(int i=1;i<=idx;i++)if(!d[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		// cout<<u<<" t\n";
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(d[v]){
				d[v]--;
				if(!d[v])q.push(v);
			}
		}
	}
	for(int i=1;i<=idx;i++)head[i]=0;tot=0;
	// for(int i=1;i<=idx;i++)if(d[i])cout<<i<<" "<<d[i]<<" d\n";
	for(int i=2*n+1;i<=2*n+m;i++)if(d[i]){puts("No");return ;}
	puts("Yes");
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
	// for(int t=1;t<=T;t++){
		// if(t==4){
			// n=read();cout<<n<<"\n";
			// for(int i=1;i<n;i++){
				// int u=read(),v=read();
				// cout<<u<<" "<<v<<"\n";
			// }
			// m=read();cout<<m<<"\n";
			// for(int i=1;i<=m;i++){
				// int u=read(),v=read();
				// cout<<u<<" "<<v<<"\n";
			// }
			// return 0;
		// }
		// work();
	// }
	while(T--)work();
}