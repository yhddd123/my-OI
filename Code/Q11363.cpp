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

int n,k,a[maxn],fl;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
bool vis[maxn];
void dfs(int u,int fa){
	int s1=0,s2=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		if(vis[v])s1+=a[v];
		else s2+=a[v];
	}
	if(vis[u]){
		if(s1+a[u]>k)fl=1;
		else{
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;if(v==fa||vis[v])continue;
				if(s1+s2+a[u]>k){
					int d=min(a[v],s1+s2+a[u]-k);
					a[v]-=d,s2-=d;
				}
			}
		}
	}
	else{
		if(s1>k)fl=1;
		else{
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;if(v==fa||vis[v])continue;
				if(s1+s2>k){
					int d=min(a[v],s1+s2-k);
					a[v]-=d,s2-=d;
				}
			}
			a[u]=k-s1-s2;
		}
	}
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read(),vis[i]=(a[i]!=-1);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);
	if(fl){puts("-1");return ;}
	int s=0;for(int i=1;i<=n;i++)s+=a[i];
	printf("%lld\n",s);
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