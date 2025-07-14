// Problem: P3387 【模板】缩点
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3387
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=10010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
	return x*f;
}

int n,m,a[maxn],ans;
int head[maxn],tot,head1[maxn];
struct nd{
	int nxt,from,to;
}e[maxn*10],e1[maxn*10];
void add(int u,int v){
	e[++tot].nxt=head[u];e[tot].from=u;e[tot].to=v;
	head[u]=tot;
}
void add1(int u,int v){
	e1[++tot].nxt=head1[u];e1[tot].to=v;
	head1[u]=tot;
}
int in[maxn];

int dfn[maxn],lw[maxn],cnt;
int scc[maxn],scct;
int st[maxn],tp;
queue<int> q;
int t[maxn],val[maxn],f[maxn];
void tar(int u){
	lw[u]=dfn[u]=++cnt;st[++tp]=u;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],dfn[v]);
	}
	if(dfn[u]==lw[u]){
		++scct;
		scc[st[tp]]=scct;
		val[scct]+=a[st[tp]];
		while(st[tp--]!=u){
			scc[st[tp]]=scct;
			val[scct]+=a[st[tp]];
		}
	}
}


int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		add(u,v);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i])tar(i);
	}
//	for(int i=1;i<=n;i++)cout<<scc[i]<<" "<<val[scc[i]]<<"\n";;
	tot=0;
	for(int i=1;i<=m;i++){
		if(scc[e[i].from]!=scc[e[i].to]){
//			cout<<e[i].from<<" "<<e[i].to<<" "<<scc[e[i].from]<<" "<<scc[e[i].to]<<"\n";
			add1(scc[e[i].from],scc[e[i].to]);
			add1(scc[e[i].to],scc[e[i].from]);
			++in[scc[e[i].from]];
		}
	}
	for(int i=1;i<=scct;i++){
		if(!in[i])q.push(i);
//		cout<<in[i]<<" ";
	}
//	cout<<"\n";
	cnt=0;
	while(!q.empty()){
		t[++cnt]=q.front();q.pop();
		for(int i=head1[t[cnt]];i;i=e1[i].nxt){
			int v=e1[i].to;
			if(in[v]){
				--in[v];
				if(!in[v])q.push(v);
			}
		}
//		cout<<t[cnt]<<" ";
	}
//	cout<<cnt<<"\n";
	for(int i=1;i<=scct;i++){
		f[t[i]]=val[t[i]];
		for(int j=head1[t[i]];j;j=e1[j].nxt){
			int v=e1[j].to;
//			cout<<v<<" ";
			f[t[i]]=max(f[t[i]],f[v]+val[t[i]]);
		}
//		cout<<t[i]<<" "<<f[t[i]]<<"\n";
	}
	for(int i=1;i<=scct;i++)ans=max(ans,f[i]);
	printf("%lld\n",ans);
}