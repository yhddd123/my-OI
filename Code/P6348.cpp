#include<bits/stdc++.h>
using namespace std;
const int maxn=500010;
const int N=4200100;
const int M=13000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,x,idx;
int rnk[maxn];
int head[N],tot;
struct nd{
	int nxt,to,w;
}e[M];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};
	head[u]=tot;
}
void build(int nd,int l,int r){
	if(l==r){
		rnk[l]=nd;
		add(nd,nd+maxn*4,0);add(nd+maxn*4,nd,0);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	add(nd,ls,0);add(nd,rs,0);//in
	add(ls+maxn*4,nd+maxn*4,0);add(rs+maxn*4,nd+maxn*4,0);//out
}
void updout(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr){
		add(nd+maxn*4,idx,1);//out
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updout(ls,l,mid,ql,qr);
	if(qr>mid)updout(rs,mid+1,r,ql,qr);
}
void updin(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr){
		add(idx,nd,1);//in
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updin(ls,l,mid,ql,qr);
	if(qr>mid)updin(rs,mid+1,r,ql,qr);
}
int tim[N];
deque<int> q;

signed main(){
	n=read();m=read();x=read();
	memset(tim,0x3f,sizeof(tim));
	build(1,1,n);
	idx=maxn*8;
	for(int i=1;i<=m;i++){
		int u,v,uu,vv;
		u=read();v=read();uu=read();vv=read();
		++idx;
		updout(1,1,n,u,v);updin(1,1,n,uu,vv);
		++idx;
		updout(1,1,n,uu,vv);updin(1,1,n,u,v);
	}
	tim[rnk[x]]=0;q.emplace_back(rnk[x]);
	while(!q.empty()){
		int u=q.front();q.pop_front();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(tim[v]>tim[u]+e[i].w){
				tim[v]=tim[u]+e[i].w;
				if(e[i].w==1)q.emplace_back(v);
				else q.emplace_front(v);
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d\n",tim[rnk[i]]/2);
}
