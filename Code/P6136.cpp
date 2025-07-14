// Problem: P6136 【模板】普通平衡树（数据加强版）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6136
// Memory Limit: 89 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2024-04-10 16:30:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define mod 998244353ll;
#define pii pair<int,int>
using namespace std;
const int maxn=1100010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
int val[maxn],w[maxn],ls[maxn],rs[maxn],idx,rt,siz[maxn];
int ans,lst;
void pushup(int u){siz[u]=siz[ls[u]]+siz[rs[u]]+1;}
pii split(int u,int k){
	if(!u)return {0,0};
	if(val[u]<k){
		pii t=split(rs[u],k);
		rs[u]=t.first;
		pushup(u);
		return {u,t.second};
	}
	else{
		pii t=split(ls[u],k);
		ls[u]=t.second;
		pushup(u);
		return {t.first,u};
	}
}
int merge(int u,int v){
	if(!u||!v)return u|v;
	if(w[u]<w[v]){
		rs[u]=merge(rs[u],v);
		pushup(u);
		return u;
	}
	else{
		ls[v]=merge(u,ls[v]);
		pushup(v);
		return v;
	}
}
void insert(int x){
	val[++idx]=x,w[idx]=rand()*rand()%mod;siz[idx]=1;
	pii t=split(rt,x);
	rt=merge(merge(t.first,idx),t.second);
}
void del(int x){
	pii u=split(rt,x),v=split(u.second,x+1);
	v.first=merge(ls[v.first],rs[v.first]);
	rt=merge(u.first,merge(v.first,v.second));
}
int rnk(int x){
	int res=0;
	pii u=split(rt,x);
	res=siz[u.first]+1;
	rt=merge(u.first,u.second);
	return res;
}
int que(int x,int u=rt){
	if(x==siz[ls[u]]+1)return val[u];
	if(x<=siz[ls[u]])return que(x,ls[u]);
	else return que(x-siz[ls[u]]-1,rs[u]);
}
int pre(int x){return que(rnk(x)-1);}
int nxt(int x){return que(rnk(x+1));}
void work(){
	n=read();m=read();srand(time(0));
	for(int i=1;i<=n;i++){
		int x=read();
		insert(x);
	}
	while(m--){
		int op=read(),x=read()^lst;
		if(op==1)insert(x);
		if(op==2)del(x);
		if(op==3)lst=rnk(x),ans^=lst;
		if(op==4)lst=que(x),ans^=lst;
		if(op==5)lst=pre(x),ans^=lst;
		if(op==6)lst=nxt(x),ans^=lst;
	}
	printf("%lld\n",ans);
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
	
	// cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
