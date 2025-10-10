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
const int maxn=3010;
const int maxm=500010;
const int maxk=210;
const int inf=1e9;
bool mbe;

int n,m,q,op,ans;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
pii edge[maxm];
bool vis[maxm];
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
int dfn[maxn],rnk[maxn],tim,siz[maxn];
void dfs(int u,int fa){
	rnk[dfn[u]=++tim]=u;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);siz[u]+=siz[v];
	}
}
int sum[maxn][maxn];
int que(int l1,int r1,int l2,int r2){return sum[r1][r2]-sum[l1-1][r2]-sum[r1][l2-1]+sum[l1-1][l2-1];}
bool bk[maxk][maxk];
int lsh[maxk],len;
int num[maxk][maxk];
int bel(int u){return upper_bound(lsh+1,lsh+len+1,u)-lsh-1;}
int d[maxk];
int ddfn[maxk],lw[maxk],idx;
int scc[maxk],scct;
int st[maxk],tp;
void tar(int u){
	ddfn[u]=lw[u]=++idx,st[++tp]=u;
	for(int v=1;v<len;v++)if(bk[u][v]){
		if(!ddfn[v]){
			tar(v);
			lw[u]=min(lw[u],lw[v]);
		}
		else if(!scc[v])lw[u]=min(lw[u],ddfn[v]);
	}
	if(ddfn[u]==lw[u]){
		scc[st[tp]]=++scct;
		while(st[tp--]!=u)scc[st[tp]]=scct;
	}
}
void work(){
	n=read();m=read();q=read();op=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		edge[i]={u,v};
		if(fd(u)!=fd(v))f[fd(u)]=fd(v),add(u,v),add(v,u),vis[i]=1;
	}
	dfs(1,0);
	for(int i=1;i<=m;i++){
		auto[u,v]=edge[i];
		if(dfn[u]>dfn[v])swap(u,v);
		sum[dfn[u]][dfn[v]]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
	}
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	while(q--){
		int k=read();
		vector<tuple<int,int,int>> upd(k);
		for(int i=1;i<=k;i++){
			int id=read(),op1=read(),op2=read();
			if(op)id=(id+ans)%m+1;
			upd[i-1]={id,op1,op2};
		}
		len=0;lsh[++len]=1,lsh[++len]=n+1;
		for(auto[id,op1,op2]:upd)if(vis[id]){
			auto[u,v]=edge[id];
			if(dfn[u]>dfn[v])swap(u,v);
			// cout<<u<<" "<<v<<" "<<dfn[v]<<" "<<dfn[v]+siz[v]<<"\n";
			lsh[++len]=dfn[v],lsh[++len]=dfn[v]+siz[v];
		}
		sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
		for(int i=1;i<len;i++){
			for(int j=1;j<len;j++)num[i][j]=0;
		}
		for(auto[id,op1,op2]:upd){
			auto[u,v]=edge[id];
			// cout<<u<<" "<<v<<" "<<bel(dfn[u])<<" "<<bel(dfn[v])<<"\n";
			u=bel(dfn[u]),v=bel(dfn[v]);
			if(op1)num[u][v]++;
			if(op2)num[v][u]++;
		}
		for(int i=1;i<len;i++){
			for(int j=i+1;j<len;j++){
				int val=que(lsh[i],lsh[i+1]-1,lsh[j],lsh[j+1]-1);
				// cout<<i<<" "<<j<<" "<<val<<" "<<num[i][j]<<" "<<num[j][i]<<"\n";
				bk[i][j]=(val!=num[i][j]);
				bk[j][i]=(val!=num[j][i]);
			}
		}
		// for(int i=1;i<len;i++)cout<<lsh[i]<<" ";cout<<"\n";
		// for(int i=1;i<len;i++){
			// for(int j=1;j<len;j++)cout<<bk[i][j];cout<<"\n";
		// }
		for(int i=1;i<len;i++)scc[i]=ddfn[i]=0;
		scct=idx=0;
		for(int i=1;i<len;i++)if(!ddfn[i])tar(i);
		for(int i=1;i<=scct;i++)d[i]=0;
		for(int i=1;i<len;i++){
			for(int j=1;j<len;j++)if(scc[i]!=scc[j]&&bk[i][j])d[scc[i]]++;
		}
		int p=0,fl=0;
		for(int i=1;i<=scct;i++)if(!d[i]){
			if(p)fl=1;
			p=i;
		}
		if(fl){puts("0");continue;}
		int cnt=0;for(int i=1;i<len;i++)if(scc[i]==p)cnt+=lsh[i+1]-lsh[i];
		printf("%d\n",cnt);ans+=cnt;
	}
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