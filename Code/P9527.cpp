// Problem: P9527 [JOISC2022] 洒水器
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9527
// Memory Limit: 1 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,q,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int f[maxn][44],fa[maxn];
void dfs(int u){
	for(int i=0;i<=40;i++)f[u][i]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u,dfs(v);
	}
}
void work(){
	n=read(),m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1);q=read();
	while(q--){
		int op=read();
		if(op==1){
			int u=read(),d=read(),w=read();
			while(~d&&u){
				if(fa[u]&&d)f[u][d]=f[u][d]*w%m,f[u][d-1]=f[u][d-1]*w%m;
				else for(int i=0;i<=d;i++)f[u][i]=f[u][i]*w%m;
				u=fa[u],d--;
			}
		}
		else{
			int u=read(),res=a[u],d=0;
			while(d<=40&&u){
				res=res*f[u][d]%m;
				u=fa[u],d++;
			}
			printf("%lld\n",res);
		}
	}
	
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
