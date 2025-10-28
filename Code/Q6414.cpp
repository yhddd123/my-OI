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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n;
bool vis[maxn],bk[maxn];
vector<pii> ans;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
map<int,int> mpx,mpy;int idx,idy;
int dep[maxn];
int dfs(int u,int fa){
	vis[u]=1;
	dep[u]=dep[fa]+1;
	int lst=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		// cout<<u<<" "<<v<<"\n";
		if(vis[v]&&dep[v]<dep[u])continue;
		if(vis[v]){
			if(lst)ans.pb({lst,e[i].w}),lst=0;
			else lst=e[i].w;
		}
		else{
			int id=dfs(v,u);
			if(id)ans.pb({e[i].w,id});
			else{
				if(lst)ans.pb({lst,e[i].w}),lst=0;
				else lst=e[i].w;
			}
		}
	}
	return lst;
}
void work(){
	n=read();
	mpx.clear(),mpy.clear();idx=0,idy=0;
	for(int i=1;i<=4*n;i++)head[i]=0;tot=0;
	for(int i=1;i<=2*n;i++){
		int x=read(),y=read();
		if(!mpx[x])mpx[x]=++idx;
		if(!mpy[y])mpy[y]=++idy;
		// cout<<mpx[x]<<" "<<mpy[y]<<"\n";
		add(mpx[x],2*n+mpy[y],i),add(2*n+mpy[y],mpx[x],i);
	}
	for(int i=1;i<=4*n;i++)vis[i]=0;
	ans.clear();
	int res=n;
	for(int i=1,lst=0;i<=4*n;i++)if(!vis[i]){
		int id=dfs(i,0);
		// cout<<i<<" "<<id<<" "<<ans.size()<<"\n";
		if(id){
			if(lst)ans.pb({lst,id}),lst=0,res--;
			else lst=id;
		}
	}
	printf("%d\n",res);
	for(auto[u,v]:ans)printf("%d %d\n",u,v);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}