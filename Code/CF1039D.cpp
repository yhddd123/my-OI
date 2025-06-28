// Problem: CF1039D You Are Given a Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1039D
// Memory Limit: 500 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2025-03-18 18:44:10
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
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
const int maxn=100010;
const int inf=2e9;
bool mbe;

int n;
vector<int> e[maxn];
int ans[maxn];
int fa[maxn],rnk[maxn],idx;
void dfs(int u){
	rnk[++idx]=u;
	for(int v:e[u])if(v!=fa[u])fa[v]=u,dfs(v);
}
int mx[maxn],se[maxn];
void work(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	dfs(1);
	auto calc=[&](int k){
		if(ans[k])return ans[k];
		int res=0;
		for(int i=1;i<=n;i++)mx[i]=se[i]=0;
		for(int i=n;i;i--){
			int u=rnk[i];
			if(mx[u]+se[u]+1>=k)++res;
			else{
				if(mx[fa[u]]<mx[u]+1)se[fa[u]]=mx[fa[u]],mx[fa[u]]=mx[u]+1;
				else if(se[fa[u]]<mx[u]+1)se[fa[u]]=mx[u]+1;
			}
		}
		return ans[k]=res;
	};
	for(int l=1,r;l<=n;l=r+1){
		r=l;
		int res=calc(l);
		int ll=l+1,rr=n;
		while(ll<=rr){
			int mid=ll+rr>>1;
			if(calc(mid)==res)ll=mid+1,r=mid;
			else rr=mid-1;
		}
		for(int i=l;i<=r;i++)ans[i]=res;
	}
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
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