#include<bits/stdc++.h>
#define int long long
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

int n,m;
int head[maxn],tot;
struct nd{
	int nxt,to,w;
}e[maxn<<2];
void add(int u,int v,int w){
	e[++tot].nxt=head[u];e[tot].to=v;e[tot].w=w;
	head[u]=tot;
}
int u,v,w;

struct Dis{
	int id,dis;
	bool operator <(const Dis&tmp)const{return dis>tmp.dis;};
};
int dis1[maxn],disn[maxn];
bool bk[maxn];
priority_queue<Dis> q;
void dij1(){
	memset(dis1,0x3f,sizeof(dis1));
	dis1[1]=0;q.push({1,dis1[1]});
	while(!q.empty()){
		u=q.top().id;q.pop();
		if(bk[u])continue;
		bk[u]=true;
		for(int i=head[u];i;i=e[i].nxt){
			v=e[i].to;
			if(dis1[v]>dis1[u]+e[i].w){
				dis1[v]=dis1[u]+e[i].w;
				q.push({v,dis1[v]});
			}
		}
	}
}
void dijn(){
	memset(disn,0x3f,sizeof(disn));
	memset(bk,false,sizeof(bk));
	disn[n]=0;q.push({n,disn[n]});
	while(!q.empty()){
		u=q.top().id;q.pop();
		if(bk[u])continue;
		bk[u]=true;
		for(int i=head[u];i;i=e[i].nxt){
			v=e[i].to;
			if(disn[v]>disn[u]+e[i].w){
				disn[v]=disn[u]+e[i].w;
				q.push({v,disn[v]});
			}
		}
	}
}

int d[maxn],tp,id[maxn];
int lst[maxn],fir[maxn];
bool vis[maxn<<2];
queue<int> q1;
void bfs1(int x){
	q1.push(d[x]);lst[d[x]]=x;
	while(!q1.empty()){
		u=q1.front();q1.pop();
		for(int i=head[u];i;i=e[i].nxt){
			v=e[i].to;
			if(!id[v]&&!lst[v]&&dis1[u]+e[i].w==dis1[v]){
				lst[v]=x;
				q1.push(v);
			}
		}
	}
}
void bfsn(int x){
	q1.push(d[x]);fir[d[x]]=x;
	while(!q1.empty()){
		u=q1.front();q1.pop();
		for(int i=head[u];i;i=e[i].nxt){
			v=e[i].to;
			if(!id[v]&&!fir[v]&&disn[u]+e[i].w==disn[v]){
				fir[v]=x;
				q1.push(v);
			}
		}
	}
}

int tree[maxn<<2],ans[maxn];
void build(int nd,int l,int r){
	tree[nd]=inf;
	if(l==r)return ;
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		tree[nd]=min(tree[nd],w);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
void down(int nd,int l,int r){
	if(l==r){
		ans[l]=tree[nd];
		return;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	tree[ls]=min(tree[nd],tree[ls]);
	tree[rs]=min(tree[nd],tree[rs]);
	down(ls,l,mid);down(rs,mid+1,r);
}
int mn,cnt;

signed main(){
	n=read();m=read();
	if(n==1){
		printf("0 1\n");
		return 0;
	}
	for(int i=1;i<=m;i++){
		u=read();v=read();w=read();
		if(u==v)continue;
		add(u,v,w);add(v,u,w);
	}
	dij1();dijn();u=1;
	while(u<n){
		d[++tp]=u;id[u]=tp;
		for(int i=head[u];i;i=e[i].nxt){
			v=e[i].to;
			if(disn[v]+e[i].w==disn[u]){
				vis[i]=1;u=v;
				break;
			}
		}
	}
	d[++tp]=u;id[u]=tp;
	for(int i=1;i<=tp;i++)bfs1(i);
	for(int i=tp;i>=1;i--)bfsn(i);
	tp--;build(1,1,tp);
	for(u=1;u<=n;u++){
		for(int i=head[u];i;i=e[i].nxt){
			v=e[i].to;
			if(!vis[i]&&lst[u]<fir[v]){
				updata(1,1,tp,lst[u],fir[v]-1,dis1[u]+e[i].w+disn[v]);
			}
		}
	}
	down(1,1,tp);
	for(int i=1;i<=tp;i++){
		if(mn<ans[i])mn=ans[i],cnt=1;
		else if(mn==ans[i])++cnt;
	}
	if(mn==dis1[n])cnt=m;
	printf("%lld %lld\n",mn,cnt);
}
