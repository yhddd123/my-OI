// Problem: P6646 [CCO 2020] Shopping Plans
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6646
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-06-12 18:05:23
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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
const int maxn=200010;
const int inf=1e18;
bool mbe;

int n,m,k;
vector<int> a[maxn];
struct node{
	int pre,to,lim,val;
};
bool operator<(node u,node v){return u.val<v.val;}
bool operator>(node u,node v){return u.val>v.val;}
int id[maxn];
struct ds{
	vector<int> res;
	int id,l,r;
	priority_queue<node,vector<node>,greater<node>> q;
	void trans(){
		if(!q.size()){res.pb(inf);return ;}
		node u=q.top();q.pop();
		int pre=u.pre,to=u.to,lim=u.lim,val=u.val;res.pb(val);
		// cout<<pre<<" "<<to<<" "<<lim<<" "<<val<<"\n";
		if(to>=0&&to+1<=lim)q.push({pre,to+1,lim,val+a[id][to+1]-a[id][to]});
		if(pre>=0&&pre+1<to)q.push({pre-1,pre+1,to-1,val+a[id][pre+1]-a[id][pre]});
		if(lim==(int)a[id].size()-1&&to==pre+1&&to+2<=r)q.push({to,to+1,lim,val+a[id][to+1]});
	}
	int operator [](int x){
		while(x>=res.size())trans();
		return res[x];
	}
	void build(int _i,int _l,int _r){
		id=_i,l=_l,r=_r;sort(a[id].begin(),a[id].end());
		r=min(r,(int)a[id].size());
		if(a[id].size()>=l){
			int s=0;for(int i=0;i<l;i++)s+=a[id][i];
			q.push({l-2,l-1,(int)a[id].size()-1,s});
		}
	}
}d[maxn];
struct Node{
	int pre,num,val;
};
bool operator<(Node u,Node v){return u.val<v.val;}
bool operator>(Node u,Node v){return u.val>v.val;}
priority_queue<Node,vector<Node>,greater<Node>> q;
void work(){
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++)a[read()].pb(read());
	for(int i=1;i<=m;i++){
		int l=read(),r=read();id[i]=i;
		d[i].build(i,l,r);
		if(d[i][0]==inf){
			while(k)k--,puts("-1");
			return ;
		}
		// cout<<d[i][0]<<" "<<d[i][1]<<" "<<d[i][2]<<"\n";
	}
	sort(id+1,id+m+1,[&](int u,int v){return d[u][1]-d[u][0]<d[v][1]-d[v][0];});
	int s=0;for(int i=1;i<=m;i++)s+=d[i][0];
	q.push({0,0,s});
	while(!q.empty()&&k){
		Node u=q.top();q.pop();k--;
		int pre=u.pre,num=u.num,val=u.val;
		if(val>=inf)val=-1;
		printf("%lld\n",val);
		if(val==-1)break;
		if(pre)q.push({pre,num+1,val+d[id[pre]][num+1]-d[id[pre]][num]});
		if(pre+1<=m)q.push({pre+1,1,val+d[id[pre+1]][1]-d[id[pre+1]][0]});
		if(pre+1<=m&&num==1)q.push({pre+1,1,val+d[id[pre]][0]-d[id[pre]][1]+d[id[pre+1]][1]-d[id[pre+1]][0]});
	}
	while(k--)puts("-1");
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