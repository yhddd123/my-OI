// Problem: #121. 「离线可过」动态图连通性
// Contest: LibreOJ
// URL: https://loj.ac/p/121
// Memory Limit: 512 MB
// Time Limit: 800 ms
// Written by yhm.
// Start codeing:2024-05-22 07:16:00
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mod 1000000007
using namespace std;
const int maxn=500010;
const int maxm=5010;
const int inf=1e9;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}


int n,m,k,a[maxn];
int f[maxm],siz[maxm];
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
vector<pii> tree[maxn<<2];
void updata(int nd,int l,int r,int ql,int qr,pii p){
	if(l>=ql&&r<=qr){
		tree[nd].push_back(p);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr,p);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,p);
}
pii que[maxn];
void dfs(int nd,int l,int r){
	// cout<<l<<" "<<r<<"\n";
	if(!(a[r]-a[l-1]))return ;
	int nw=tp;
	for(pii p:tree[nd])merge(fd(p.fi),fd(p.se));
	if(l==r){
		if(que[l].fi){
			if(fd(que[l].fi)==fd(que[l].se))puts("Y");
			else puts("N");
		}
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
int id(int u,int v){return u*n+v-1;}
int mp[maxm][maxm];

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++){
		int op=read(),u=read(),v=read();a[i]=a[i-1];
		if(u>v)swap(u,v);
		if(op==0)mp[u][v]=i;
		if(op==1)updata(1,1,m,mp[u][v],i,{u,v}),mp[u][v]=0;
		if(op==2)que[i]={u,v},a[i]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)if(mp[i][j])updata(1,1,m,mp[i][j],m,{i,j});
	}
	dfs(1,1,m);
}