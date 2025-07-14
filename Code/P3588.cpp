#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,p,a[maxn*7];
int dis[maxn*7],d[maxn*7];
int head[maxn*7],tot,idx;
struct nd{
	int nxt,to,w;
}e[maxn*72];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;d[v]++;}
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
void build(int nd=1,int l=1,int r=n){
	if(l==r){
		add(nd,l+maxn*4,0);
		return ;
	}
	build(ls,l,mid);build(rs,mid+1,r);
	add(nd,ls,0);add(nd,rs,0);
}
void updata(int ql,int qr,int nd=1,int l=1,int r=n){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		add(idx,nd,0);
		return ;
	}
	if(ql<=mid)updata(ql,qr,ls,l,mid);
	if(qr>mid)updata(ql,qr,rs,mid+1,r);
}
queue<int> q;
bool vis[maxn*7];

int T;
signed main(){
//		freopen("P3588_1.in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();p=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		a[u+maxn*4]=dis[u+maxn*4]=v;
	}
	idx=n+maxn*4;
	build(1,1,n);
	while(p--){
		int u=read(),v=read(),x=read();
		int lst=u;++idx;
		while(x--){
			int pos=read();
			add(pos+maxn*4,idx,-1);
			updata(lst,pos-1);
			lst=pos+1;
		}
		updata(lst,v);
	}
	for(int i=1;i<=idx;i++){
		if(!d[i])q.push(i);
		if(!dis[i])dis[i]=inf;
	}
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			dis[v]=min(dis[v],dis[u]+e[i].w);
			if(a[v]&&dis[v]<a[v]){
				printf("NIE\n");
				return 0;
			}
			--d[v];
			if(!d[v])q.push(v);
		}
	}
	for(int i=maxn*4+1;i<=maxn*4+n;i++){
		if(!vis[i]||dis[i]<1){
			printf("NIE\n");
			return 0;
		}
	}
	printf("TAK\n");
	for(int i=maxn*4+1;i<=maxn*4+n;i++)printf("%lld ",dis[i]);
}
