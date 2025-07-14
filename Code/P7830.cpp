#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1600010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
vector<int> e[maxn];
int f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
int dfn[maxn],idx,pos[maxn];
void dfs(int u,int fa){
	dfn[++idx]=u;
	if(u==1)pos[u]=-1;
	else{
		for(int i=0;i<e[u].size();i++){
			if(e[u][i]==fa)pos[u]=i;
		}
	}
	for(int i=pos[u]+1;i<e[u].size();i++){
		int v=e[u][i];
		dfs(v,u);
		dfn[++idx]=u;
	}
	for(int i=0;i<pos[u];i++){
		int v=e[u][i];
		dfs(v,u);
		dfn[++idx]=u;
	}
}
struct ask{
	int num,id;
}p[maxn];
bool cmp(ask u,ask v){return u.num<v.num;}
int ans[maxn];
bool vis[maxn];
int num,nxt[maxn];
vector<int> st[maxn];
int tim,h;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int x=read()-1,u=read();
		while(x--)e[i].push_back(read());
		e[i].push_back(u);
	}
	for(int i=1;i<=m;i++)p[i]={read(),i};
	sort(p+1,p+m+1,cmp);
	dfs(1,0);
	for(int i=1;i<=2*n;i++)f[i]=i+1;
	for(int i=1;i<=idx;i++){
		if(!vis[dfn[i]]&&pos[dfn[i]]!=e[dfn[i]].size()-1)f[i]=i,++num;
		vis[dfn[i]]=1;
	}
	num--;
	for(int i=idx;i>=1;i--)st[dfn[i]].push_back(i);
	for(int i=1;i<=idx;i++){
		if(f[i]==i){
			nxt[i]=st[dfn[i]][pos[dfn[i]]];
//			cout<<i<<" "<<nxt[i]<<"\n";
		}
	}
	f[1]=2;f[idx]=idx;nxt[idx]=idx;
	h=1;
	while(num){
		int nw=1;
		while(nw<idx){
			int to=fd(nw);int l=to-nw;
			while(l+tim>=p[h].num&&h<=m){
				ans[p[h].id]=dfn[nw+p[h].num-tim],h++;
			}
			if(to!=idx)f[to]=to+1,num--;
			tim+=l;
			nw=nxt[to];
		}
	}
	while(h<=m){
		ans[p[h].id]=dfn[(p[h].num-tim-1)%(idx-1)+2],h++;
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
