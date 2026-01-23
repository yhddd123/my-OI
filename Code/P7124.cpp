// Problem: P7124 [Ynoi2008] stcm
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7124
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2026-01-23 07:57:59
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,fa[maxn];
vector<int> e[maxn];
int in[maxn],out[maxn],rnk[maxn],idx;
void dfs(int u){
	rnk[in[u]=++idx]=u;
	for(int v:e[u])if(v!=fa[u])dfs(v);
	out[u]=idx;
}
void sovle(int l,int r,vector<int> &id){
	if(l>r)return ;
	int mid=l+r>>1;
	vector<int> id1,id2,id3;
	for(int u:id){
		if(in[u]==l&&out[u]==r)printf("=%d",u);
		else if(out[u]<mid)id2.pb(u);
		else if(in[u]>mid)id3.pb(u);
		else id1.pb(u);
	}
	int pl=l,pr=r;
	for(int u:id1){
		while(pl<in[u])printf("+%d",rnk[pl++]);
		while(pr>out[u])printf("+%d",rnk[pr--]);
		printf("=%d",u);
	}
	for(int i=l;i<pl;i++)putchar('-');
	for(int i=pr+1;i<=r;i++)putchar('-');
	for(int i=r;i>=mid;i--)printf("+%d",rnk[i]);
	sovle(l,mid-1,id2);
	for(int i=mid;i<=r;i++)putchar('-');
	for(int i=l;i<=mid;i++)printf("+%d",rnk[i]);
	sovle(mid+1,r,id3);
	for(int i=l;i<=mid;i++)putchar('-');
}
void work(){
	for(int i=1;i<=n;i++)e[i].clear();
	for(int i=2;i<=n;i++)fa[i]=read(),e[fa[i]].pb(i);
	idx=0;dfs(1);
	vector<int> id(n);
	for(int i=1;i<=n;i++)id[i-1]=i;
	sort(id.begin(),id.end(),[&](int u,int v){return in[u]<in[v];});
	sovle(1,n,id);puts("!");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	while(~scanf("%d",&n))work();
}