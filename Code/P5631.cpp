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

int n,m;
struct nd{
	int u,v;
}e[maxn*20];
int st[maxn*20],tp;
vector<int> tree[maxn<<2];
#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
void updata(int ql,int qr,int id,int nd=1,int l=0,int r=maxn-9){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		tree[nd].push_back(id);
		return ;
	}
	if(ql<=mid)updata(ql,qr,id,ls,l,mid);
	if(qr>mid)updata(ql,qr,id,rs,mid+1,r);
}
int f[maxn*20],siz[maxn*20];
int fd(int x){
	if(x==f[x])return x;
	return fd(f[x]);
}
void merge(int u,int v){
	if(siz[u]<siz[v])swap(u,v);
	st[++tp]=v;
	f[v]=u;siz[u]+=siz[v];
}
void dfs(int nd=1,int l=0,int r=maxn-9){
//	cout<<nd<<" "<<l<<" "<<r<<"\n";
//	for(int i=1;i<=n;i++)cout<<f[i]<<" "<<siz[i]<<" in"<<"\n";
	int nw=tp;
	for(int i:tree[nd]){
//		cout<<e[i].u<<" "<<e[i].v<<"\n";
		if(fd(e[i].u)!=fd(e[i].v))merge(fd(e[i].u),fd(e[i].v));
	}
	if(l==r){
		if(siz[fd(1)]==n){
			printf("%lld\n",l);
			exit(0);
		}
		while(tp>nw){
			siz[f[st[tp]]]-=siz[st[tp]];
			f[st[tp]]=st[tp];
			tp--;
		}
//		for(int i=1;i<=n;i++)cout<<f[i]<<" "<<siz[i]<<" out1"<<"\n";
		return ;
	}
	dfs(ls,l,mid);dfs(rs,mid+1,r);
	while(tp>nw){
		siz[f[st[tp]]]-=siz[st[tp]];
		f[st[tp]]=st[tp];
		tp--;
	}
//	for(int i=1;i<=n;i++)cout<<f[i]<<" "<<siz[i]<<" out2"<<"\n";
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=m;i++){
		e[i].u=read(),e[i].v=read();int w=read();
		updata(0,w-1,i);updata(w+1,maxn-9,i);
	}
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	dfs();
}
