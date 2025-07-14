#include<bits/stdc++.h>
using namespace std;
const int maxn=2010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,q;
int a[maxn][maxn],to[maxn][maxn];
int work(int u,int v){
	int u1=u-1,u2=u%n+1;v=(v%m)+1;
	if(!u1)u1=n;
	if(a[u1][v]>max(a[u][v],a[u2][v]))return u1;
	if(a[u][v]>max(a[u1][v],a[u2][v]))return u;
	if(a[u2][v]>max(a[u1][v],a[u][v]))return u2;
}
struct seg{
	int t[maxn];
}tree[maxn<<2];
void push(int nd){
	int ls=nd<<1,rs=nd<<1|1;
	for(int i=1;i<=n;i++)tree[nd].t[i]=tree[rs].t[tree[ls].t[i]];
}
void build(int nd,int l,int r){
	if(l==r){
		for(int i=1;i<=n;i++)tree[nd].t[i]=to[i][l];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	build(ls,l,mid);build(rs,mid+1,r);
	push(nd);
}
void updata(int nd,int l,int r,int p){
	if(l==r){
		for(int i=1;i<=n;i++)tree[nd].t[i]=to[i][l];
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(p<=mid)updata(ls,l,mid,p);
	else updata(rs,mid+1,r,p);
	push(nd);
}
int f[maxn][21];
int x,y;
char opt[10];

int T;
signed main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i][j]=read();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)to[i][j]=work(i,j);
	}
	build(1,1,m);
	for(int i=1;i<=n;i++)f[i][0]=tree[1].t[i];
	for(int j=1;j<=20;j++){
		for(int i=1;i<=n;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	q=read();x=y=1;
	while(q--){
		scanf("%s",opt+1);
		if(opt[1]=='c'){
			int u,v,w;
			u=read();v=read();w=read();
			a[u][v]=w;
			v--;if(!v)v=m;
			for(int i=1;i<=n;i++){
				to[i][v]=work(i,v);
			}
			updata(1,1,m,v);
			for(int i=1;i<=n;i++)f[i][0]=tree[1].t[i];
			for(int j=1;j<=20;j++){
				for(int i=1;i<=n;i++){
					f[i][j]=f[f[i][j-1]][j-1];
				}
			}
		}
		else{
			int k=read();
			while(k&&y!=1)x=to[x][y],y=y%m+1,k--;
			int d=k/m;k%=m;
			for(int i=20;i>=0;i--){
				if(d>=(1<<i)){
					x=f[x][i];
					d-=(1<<i);
				}
			}
			while(k)x=to[x][y],y=y%m+1,k--;
			printf("%d %d\n",x,y);
		}
	}
}
