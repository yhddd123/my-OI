// Problem: P6136 【模板】普通平衡树（数据加强版）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6136
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2026-03-06 08:41:39
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
//#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=1100010;
const int inf=1e9;
bool mbe;

mt19937 rnd(time(0));
int val[maxn],siz[maxn];
int lc[maxn],rc[maxn],w[maxn],idx;
void up(int u){siz[u]=siz[lc[u]]+siz[rc[u]]+1;}
int merge(int u,int v){
	if(!u||!v)return u|v;
	if(w[u]<w[v]){
		rc[u]=merge(rc[u],v);
		up(u);return u;
	}
	else{
		lc[v]=merge(u,lc[v]);
		up(v);return v;
	}
}
pii splitval(int u,int k){
	if(!u)return {0,0};
	if(val[u]>k){
		pii t=splitval(lc[u],k);
		lc[u]=t.se;up(u);
		return {t.fi,u};
	}
	else{
		pii t=splitval(rc[u],k);
		rc[u]=t.fi;up(u);
		return {u,t.se};
	}
}
pii splitsiz(int u,int k){
	if(!u)return {0,0};
	if(siz[lc[u]]+1>k){
		pii t=splitsiz(lc[u],k);
		lc[u]=t.se;up(u);
		return {t.fi,u};
	}
	else{
		pii t=splitsiz(rc[u],k-siz[lc[u]]-1);
		rc[u]=t.fi;up(u);
		return {u,t.se};
	}
}
int newnode(int v){
	++idx;w[idx]=rnd();lc[idx]=rc[idx]=0;
	siz[idx]=1,val[idx]=v;
	return idx;
}
int n,q,rt,ans,res;
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++){
		int w=read();
		pii t=splitval(rt,w);
		rt=merge(merge(t.fi,newnode(w)),t.se);
	}
	while(q--){
		int o=read(),w=read()^ans,x,y,z;
		if(o==1){
			pii t=splitval(rt,w);
			rt=merge(merge(t.fi,newnode(w)),t.se);
		} 
		if(o==2){
			pii t=splitval(rt,w-1);x=t.fi,y=t.se;
			t=splitsiz(y,1);y=t.fi,z=t.se;
			rt=merge(x,z);
		}
		if(o==3){
			pii t=splitval(rt,w-1);x=t.fi,y=t.se;
//			printf("%d\n",ans=siz[x]+1);
			ans=siz[x]+1,res^=ans;
			rt=merge(x,y);
		}
		if(o==4){
			pii t=splitsiz(rt,w-1);x=t.fi,y=t.se;
			t=splitsiz(y,1);y=t.fi,z=t.se;
//			printf("%d\n",ans=val[y]);
			ans=val[y],res^=ans;
			rt=merge(merge(x,y),z);
		}
		if(o==5){
			pii t=splitval(rt,w-1);y=t.fi,z=t.se;
			t=splitsiz(y,siz[y]-1);x=t.fi,y=t.se;
//			printf("%d\n",ans=val[y]);
			ans=val[y],res^=ans;
			rt=merge(merge(x,y),z);
		}
		if(o==6){
			pii t=splitval(rt,w);x=t.fi,y=t.se;
			t=splitsiz(y,1);y=t.fi,z=t.se;
//			printf("%d\n",ans=val[y]);
			ans=val[y],res^=ans;
			rt=merge(merge(x,y),z);
		}
	}
	printf("%d\n",res);
}

bool med;
signed main(){
//	 freopen("A.in","r",stdin);
//	 freopen("A.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}
