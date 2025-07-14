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

int n,m,k;
struct nd{
	int u,v;
}e[maxn];
int tim[maxn];
int f[maxn],siz[maxn];
int fd(int x){
	if(x==f[x])return x;
	return fd(f[x]);
}
int st[maxn],tp;
void merge(int u,int v){
	if(u==v)return ;
	if(siz[u]>siz[v])swap(u,v);
	st[++tp]=u;f[u]=v;siz[v]+=siz[u];
}
vector<int> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,int idx){
	if(l>=ql&&r<=qr){
		tree[nd].push_back(idx);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr,idx);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,idx);
}
void dfs(int nd,int l,int r){
	int nw=tp;
	for(int x:tree[nd])merge(fd(e[x].u),fd(e[x].v));
	if(l==r){
		if(siz[fd(1)]==n)printf("Connected\n");
		else printf("Disconnected\n");
	}
	else{
		int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
		dfs(ls,l,mid);dfs(rs,mid+1,r);
	}
	while(tp>nw){
		siz[f[st[tp]]]-=siz[st[tp]];
		f[st[tp]]=st[tp];
		tp--;
	}
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].u=read();e[i].v=read();
		tim[i]=1;
	}
	k=read();
	for(int i=1;i<=k;i++){
		int c=read();
		for(int j=1;j<=c;j++){
			int x=read();
			if(tim[x]<i)updata(1,1,k,tim[x],i-1,x);
			tim[x]=i+1;
		}
	}
	for(int i=1;i<=m;i++)if(tim[i]!=k+1)updata(1,1,k,tim[i],k,i);
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	dfs(1,1,k);
}
