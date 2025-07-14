// Problem: #3646. 「2021 集训队互测」《关于因为与去年互测zjk撞题而不得不改题这回事》
// Contest: LibreOJ
// URL: https://loj.ac/p/3646
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,t,a[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int fa[maxn],dep[maxn],siz[maxn],son[maxn];
void dfs(int u){
	dep[u]=dep[fa[u]]+1;siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u])continue;
		fa[v]=u;dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],idx,rnk[maxn],tp[maxn];
void dfs1(int u,int lst){
	rnk[dfn[u]=++idx]=u;tp[u]=lst;
	if(!son[u])return ;
	dfs1(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa[u]||v==son[u])continue;
		dfs1(v,v);
	}
}
#define pii pair<int,int>
pii st[20][maxn];
int ans;
struct node{
	int l,r;pii val;bool fl;
	bool operator <(const node &tmp)const{
		if(val.first==tmp.val.first)return val.second>tmp.val.second;
		return val.first<tmp.val.first;
	}
};
vector<node> nw;
priority_queue<node> q;
pii query(int l,int r){
	if(l>r)return {-1,0};
	int k=log2(r-l+1);
	return max(st[k][l],st[k][r-(1<<k)+1]);
}
void updata(int u,int v){
	while(tp[u]!=tp[v]){
		if(dep[tp[u]]<dep[tp[v]])swap(u,v);
		q.push({dfn[tp[u]],dfn[u],query(dfn[tp[u]],dfn[u]),0});
		u=fa[tp[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	q.push({dfn[v],dfn[u],query(dfn[v],dfn[u]),0});
}
void get(node u){
	if(u.l==u.r)return ;
	if(u.val.second==u.l)q.push({u.l+1,u.r,query(u.l+1,u.r),0});
	else if(u.val.second==u.r)q.push({u.l,u.r-1,query(u.l,u.r-1),0});
	else q.push({u.l,u.val.second-1,query(u.l,u.val.second-1),0}),q.push({u.val.second+1,u.r,query(u.val.second+1,u.r),0});
}
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1),dfs1(1,1);
	// for(int i=1;i<=n;i++)cout<<dfn[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)st[0][i]={a[rnk[i]],i};
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=max(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	t=read();
	while(t--){
		int u=(read()^ans)%n+1,v=(read()^ans)%n+1,k=read();ans=0;
		// cout<<u<<" "<<v<<"\n";cerr<<"run\n";
		while(!q.empty())q.pop();updata(u,v);
		// cout<<q.top().val.first<<"\n";
		for(int i=61;~i;i--){
			vector<node>().swap(nw);bool fl=1;
			for(int j=1;j<=k;j++){
				if(q.empty()){fl=0;break;}
				node u=q.top();
				// cout<<i<<" "<<j<<" "<<u.val.first<<" "<<u.val.second<<" "<<q.size()<<" "<<u.l<<" "<<u.r<<"\n";
				if(u.val.first&(1ll<<i)){
					q.pop();if(!u.fl)get(u),u.fl=1;
					nw.push_back(u);
				}
				else{fl=0;break;}
			}
			// cout<<i<<" "<<nw.size()<<" "<<fl<<"\n";
			if(fl){
				ans+=(1ll<<i);
				for(node j:nw)q.push(j);
			}
			else{
				for(node j:nw)j.val.first^=(1ll<<i),q.push(j);
			}
		}
		printf("%lld\n",ans);
	}
}

// \
444

bool Med;
int T;
signed main(){
	// freopen("loj3646_3.in","r",stdin);
	// freopen("1.out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
