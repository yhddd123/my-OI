// Problem: P4384 [八省联考 2018] 制胡窜
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4384
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2024-07-18 08:15:04
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q;
char s[maxn];
int rt[maxn];
namespace sgt{
	#define mid (l+r>>1)
	#define ls lc[nd]
	#define rs rc[nd];
	int mn[maxn<<6],mx[maxn<<6];
	int lc[maxn<<6],rc[maxn<<6],idx;
	void up(int nd){
		mn[nd]=min(mn[ls],mn[rs]),mx[nd]=max(mx[ls],mx[rs]);
	}
	void updata(int &nd,int l,int r,int p){
		if(!nd)nd=++idx,mn[nd]=inf;
		if(l==r){
			mn[nd]=mx[nd]=p;
			return ;
		}
		if(p<=mid)updata(ls,l,mid,p);
		else updata(rs,mid+1,r,p);
		up(nd);
	}
	int merge(int u,int v,int l,int r){
		if(!u||!v)return u|v;
		int nd=++idx;
		if(l==r){
			
			return nd;
		}
		ls=merge(lc[u],lc[v],l,mid),rs=merge(rc[u],rc[v],mid+1,r);
		up(nd);
		return nd;
	}
	int quemn(int nd,int l,int r,int ql,int qr){
		if(!nd||ql>qr)return inf;
		if(l>=ql&&r<=qr)return mn[nd];
		if(qr<=mid)return quemn(ls,l,mid,ql,qr);
		if(ql>mid)return quemn(rs,mid+1,r,ql,qr);
		return min(quemn(ls,l,mid,ql,qr),quemn(rs,mid+1,r,ql,qr));
	}
	int quemx(int nd,int l,int r,int ql,int qr){
		if(!nd||ql>qr)return 0;
		if(l>=ql&&r<=qr)return mx[nd];
		if(qr<=mid)return quemx(ls,l,mid,ql,qr);
		if(ql>mid)return quemx(rs,mid+1,r,ql,qr);
		return max(quemx(ls,l,mid,ql,qr),quemx(rs,mid+1,r,ql,qr));
	}
}
int len[maxn],lnk[maxn],cur=1,p=1,ch[maxn][10];
void insert(int c){
	int nd=++cur;
	len[nd]=len[p]+1;
	sgt::updata(rt[nd],1,n,len[nd]);
	while(p&&!ch[p][c])ch[p][c]=nd,p=lnk[p];
	if(!p){lnk[p=nd]=1;return ;}
	int q=ch[p][c];
	if(len[p]+1==len[q])lnk[nd]=q;
	else{
		int cl=++cur;
		len[cl]=len[p]+1,lnk[cl]=lnk[q];
		memcpy(ch[cl],ch[q],sizeof(ch[q]);
		lnk[q]=lnk[nd]=cl;
		while(p&&ch[p][c]==q)ch[p][c]=cl,p=lnk[p];
	}
	p=nd;
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int pos[maxn],f[maxn][19];
void dfs(int u){
	for(int i=1;i<=18;i++)f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		to[u][0]=v;
		dfs(v);
		rt[u]=sgt::merge(rt[u],rt[v],1,n);
	}
}
int query(int l,int r){
	int u=pos[r],ll=r-l+1;
	for(int i=18;~i;i--){
		if(to[u][i]&&len[to[u][i]]>=ll)u=to[u][i];
	}
	int pl=sgt::quemn(rt[u],1,n,1,n),pr=sgt::quemx(rt[u],1,n,1,n),lm=qr-ll+1;
	if(sgt::quemx(rt[u],1,n,1,lm-1)-ll+1>pl)return (n-1)*(n-2)/2;
	if(pl>=qr-(r-l+1)+1){
		int ans=sgt::sum1[rt[u]]-sgt::sum2[rt[u]]*lm+(pl-lm)*(pr-lm-1)/2+(ql-lm)*(n-ll);
		return (n-1)*(n-2)/2-ans;
	}
	int p1=sgt::quemx(rt[u],1,n,1,pl+ll-1),p2=sgt::quemn(rt[u],1,n,pl+ll,n),p3=sgt::quemx(rt[u],1,n,1,lm);
	pii res=sgt::query(rt[u],1,n,p3,pl+len);
}
void work(){
	n=read();q=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)insert(s[i]-'0'),pos[i]=nd;
	for(int i=2;i<=cur;i++)add(lnk[i],i);
	sgt::mn[0]=inf;dfs(1);
	while(q--){
		int u=read(),v=read();
		return query(u,v);
	}
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
