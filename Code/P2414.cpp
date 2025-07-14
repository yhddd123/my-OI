#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
char c[maxn];
int tree[maxn][30],cnt,fa[maxn];
int ed[maxn],k;
int fail[maxn];
void insert(char *c){
	int nd=0;
	for(int i=1;i<=n;i++){
		if(c[i]>='a'&&c[i]<='z'){
			if(!tree[nd][c[i]-'a'+1]){
				tree[nd][c[i]-'a'+1]=++cnt;
				fa[cnt]=nd;
			}
			nd=tree[nd][c[i]-'a'+1];
		}
		if(c[i]=='B')nd=fa[nd];
		if(c[i]=='P')ed[++k]=nd;
	}
}
queue<int> q;
void build(){
	for(int i=1;i<=26;i++){
		if(tree[0][i])q.push(tree[0][i]);
	}
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=26;i++){
			if(tree[u][i]){
				fail[tree[u][i]]=tree[fail[u]][i];
				q.push(tree[u][i]);
			}
			else tree[u][i]=tree[fail[u]][i];
		}
	}
}
struct ask{
	int num,id;
};
vector<ask> p[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int dfn[maxn],siz[maxn],idx;
void dfs(int u){
	dfn[u]=++idx;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);
		siz[u]+=siz[v];
	}
}
int val[maxn<<2];
void updata(int nd,int l,int r,int ql,int w){
	if(l==r){
		val[nd]+=w;
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,w);
	else updata(rs,mid+1,r,ql,w);
	val[nd]=val[ls]+val[rs];
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return val[nd];
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
int ans[maxn];
void sovle(){
	int nd=0;
	for(int i=1;i<=n;i++){
		if(c[i]>='a'&&c[i]<='z'){
			nd=tree[nd][c[i]-'a'+1];
			updata(1,1,cnt,dfn[nd],1);
		}
		if(c[i]=='B'){
			updata(1,1,cnt,dfn[nd],-1);
			nd=fa[nd];
		}
		if(c[i]=='P'){
			k++;
			for(int j=0;j<p[k].size();j++){
				ans[p[k][j].id]=query(1,1,cnt,dfn[p[k][j].num],dfn[p[k][j].num]+siz[p[k][j].num]-1);
			}
		}
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	scanf("%s",c+1);
	n=strlen(c+1);
	insert(c);build();
	m=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		if(u==v)ans[i]=1;
		else p[v].push_back({ed[u],i});
	}
	for(int i=1;i<=cnt;i++)add(fail[i],i);
	dfs(0);
	k=0;sovle();
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
}
