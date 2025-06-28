// Problem: P11923 [PA 2025] 砖块收集 / Zbieranie klocków
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11923
// Memory Limit: 1 MB
// Time Limit: 15000 ms
// Written by yhm.
// Start codeing:2025-03-27 18:16:26
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,k,q;
struct node{
	int vl,vr,ans;
	bool tag;
}tree[maxn<<7];
int lc[maxn<<7],rc[maxn<<7],rt1[maxn<<1],rt2[maxn<<1],idx;
node merge(node u,node v){
	node res;
	res.tag=u.tag&v.tag;
	if(res.tag){
		res.vl=res.vr=u.vl+v.vl,res.ans=0;
	}
	else if(u.tag){
		res.vl=(v.vl==-1?-1:u.vl+v.vl),res.vr=v.vr,res.ans=v.ans;
	}
	else if(v.tag){
		res.vl=u.vl,res.vr=(u.vr==-1?-1:u.vr+v.vr),res.ans=u.ans;
	}
	else{
		res.vl=u.vl,res.vr=v.vr,res.ans=u.ans+v.ans+(u.vr!=-1&&v.vl!=-1)*(u.vr+v.vl);
	}
	return res;
}
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
void updata(int &nd,int l,int r,int p,int w){
	if(!nd)nd=++idx;
	if(l==r){
		if(!w)tree[nd]={-1,-1,0,0};
		else if(w==1)tree[nd]={1,1,0,1};
		else tree[nd]={0,0,1,0};
		return ;
	}
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
	tree[nd]=merge(tree[ls],tree[rs]);
}
int sum,num,ans;
void upd(int u,int v,int lst,int col){
	if(lst==col)return ;
	if(lst==2)--num;
	if(col==2)++num;
	ans-=tree[rt1[u+v]].ans,updata(rt1[u+v],1,n,u,col),ans+=tree[rt1[u+v]].ans;
	ans-=tree[rt2[u+m-v]].ans,updata(rt2[u+m-v],1,n,u,col),ans+=tree[rt2[u+m-v]].ans;
}
int lst[3][3];
bool vis[3][3];
map<pii,bool> mp;
int getcol(int u,int v){
	if(mp.find({u,v})==mp.end())return 0;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(mp.find({u+i,v+j})!=mp.end())vis[i+1][j+1]=1;
			else vis[i+1][j+1]=0;
		}
	}
	if(!vis[0][1]&&!vis[2][1])return 0;
	if(!vis[1][0]&&!vis[1][2])return 0;
	if(vis[0][0]&&vis[0][1]&&vis[1][0])return 2;
	if(vis[0][1]&&vis[0][2]&&vis[1][2])return 2;
	if(vis[1][2]&&vis[2][2]&&vis[2][1])return 2;
	if(vis[2][1]&&vis[2][0]&&vis[1][0])return 2;
	return 1;
}
void rev(int u,int v){
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++)lst[i+1][j+1]=getcol(u+i,v+j);
	}
	if(mp[{u,v}])sum--,mp.erase({u,v});
	else sum++,mp[{u,v}]=1;
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++)upd(u+i,v+j,lst[i+1][j+1],getcol(u+i,v+j));
	}
}
void work(){
	tree[0]={-1,-1,0,0};
	n=read();m=read();k=read();q=read();
	while(k--){
		int x=read(),y=read();
		rev(x,y);
	}
	printf("%lld\n",sum-ans+num);
	while(q--){
		int x=read(),y=read();
		rev(x,y);
		printf("%lld\n",sum-ans+num);
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}