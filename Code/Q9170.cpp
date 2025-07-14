#include<bits/stdc++.h>
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
using namespace std;
const int maxn=300010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,k;
int vis[maxn],ans[maxn];
int id(int u,int v){return (u-1)*m+v;}
pii a[maxn];
int fx[8][2]={{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,1},{-1,0},{-1,-1}};
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return fd(f[x]);
}
int st[maxn][2],tp;
void merge(int u,int v){
	u=fd(u),v=fd(v);
	if(u==v)return ;
	if(siz[u]>siz[v])swap(u,v);
	st[++tp][0]=u,st[tp][1]=siz[u];
	f[u]=v,siz[v]+=siz[u];
}
void del(){
	siz[f[st[tp][0]]]-=st[tp][1];
	f[st[tp][0]]=st[tp][0];
	tp--;
}
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
vector<pii> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,pii w){
	// if(nd==1)cout<<w.fi<<" "<<w.se<<" "<<ql<<" "<<qr<<"\n";
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){tree[nd].pb(w);return ;}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
int num;
void dfs(int nd,int l,int r){
	int lst=tp;
	for(pii p:tree[nd])merge(p.fi,p.se);
	// cout<<l<<" "<<r<<" "<<siz[fd(n*m+1)]<<"\n";
	if(l==r){		
		int i=a[l].fi,j=a[l].se;ans[l]=1;
		bool fl=1;
		for(int o=0;o<8;o++){
			int nx=i+fx[o][0],ny=j+fx[o][1];
			if(nx<=0||ny<=0||nx>n||ny>m||!ans[vis[id(nx,ny)]])continue;
			bool fl1=0;
			for(int oo=0;oo<8;oo++){
				int nnx=nx+fx[oo][0],nny=ny+fx[oo][1];
				if(nnx<=0||nny<=0||nnx>n||nny>m||ans[vis[id(nnx,nny)]])continue;
				fl1=1;
			}
			if(nx==1||nx==n||ny==1||ny==m)fl1=1;
			fl&=fl1;
		}
		if(siz[fd(n*m+1)]!=num-1||!fl){
			ans[l]=0;
			// cout<<l<<" "<<i<<" "<<j<<" "<<siz[fd(n*m+1)]<<" "<<num<<" "<<fd(id(1,6))<<"\n";
			for(int o=0;o<8;o++){
				int nx=i+fx[o][0],ny=j+fx[o][1];
				if(nx<=0||ny<=0||nx>n||ny>m)continue;
				if(!vis[id(nx,ny)]){
					updata(1,1,k,l+1,k,{id(i,j),id(nx,ny)});
				}
				else if(vis[id(i,j)]<vis[id(nx,ny)]){
					updata(1,1,k,l+1,vis[id(nx,ny)]-1,{id(i,j),id(nx,ny)});
				}
				else if(!ans[vis[id(nx,ny)]]){
					updata(1,1,k,l+1,k,{id(i,j),id(nx,ny)});
				}
			}
			if(i==1||i==n||j==1||j==m)updata(1,1,k,l+1,k,{id(i,j),n*m+1});
		}
		else ans[l]=1,num--;
	}
	else dfs(ls,l,mid),dfs(rs,mid+1,r);
	while(tp>lst)del();
}
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=k;i++)a[i]={read(),read()},vis[id(a[i].fi,a[i].se)]=i;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(vis[id(i,j)]){
			for(int o=0;o<8;o++){
				int nx=i+fx[o][0],ny=j+fx[o][1];
				if(nx<=0||ny<=0||nx>n||ny>m)continue;
				if(!vis[id(nx,ny)]){
					updata(1,1,k,1,vis[id(i,j)]-1,{id(i,j),id(nx,ny)});
				}
				if(vis[id(i,j)]<vis[id(nx,ny)]){
					updata(1,1,k,1,vis[id(i,j)]-1,{id(i,j),id(nx,ny)});
				}
			}
			if(i==1||i==n||j==1||j==m)updata(1,1,k,1,vis[id(i,j)]-1,{id(i,j),n*m+1});
		}
	}
	for(int i=1;i<=n*m+1;i++)f[i]=i,siz[i]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(!vis[id(i,j)]){
			for(int o=0;o<8;o++){
				int nx=i+fx[o][0],ny=j+fx[o][1];
				if(nx<=0||ny<=0||nx>n||ny>m)continue;
				if(!vis[id(nx,ny)])merge(id(i,j),id(nx,ny));
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!vis[id(i,1)])merge(n*m+1,id(i,1));
		if(!vis[id(i,m)])merge(n*m+1,id(i,m));
	}
	for(int j=2;j<m;j++){
		if(!vis[id(1,j)])merge(n*m+1,id(1,j));
		if(!vis[id(n,j)])merge(n*m+1,id(n,j));
	}
	// cout<<siz[fd(1)]<<"\n";
	num=n*m+1;dfs(1,1,k);
	for(int i=1;i<=k;i++)printf("%d",ans[i]);
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
