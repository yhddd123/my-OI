#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn];
vector<pii> p[maxn];
vector<int> g[maxn];
namespace sgt{
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
	int tree[maxn<<5],lc[maxn<<5],rc[maxn<<5];
	int rt[maxn],idx;
	void updata(int &nd,int nd1,int p,int w,int l=0,int r=n){
		if(!nd)nd=++idx;
		if(l==r){tree[nd]=w;return ;}
		if(p<=mid)updata(ls,lc[nd1],p,w,l,mid),rs=rc[nd1];
		else updata(rs,rc[nd1],p,w,mid+1,r),ls=lc[nd1];
		tree[nd]=min(tree[ls],tree[rs]);
	}
	int query(int nd,int p,int l=0,int r=n){
		if(tree[nd]>=p)return r+1;
		if(l==r)return l;
		if(tree[ls]<p)return query(ls,p,l,mid);
		else return query(rs,p,mid+1,r);
	}
#undef mid
}
bool cmp(pii u,pii v){
	if(u.first==v.first)return u.second<v.second;
	return u.first>v.first;
}
vector<int> add[maxn],del[maxn];
set<int> s;
int t[maxn];
void work(){
	n=read();
	for(int i=0;i<=n;i++)g[i].push_back(0);
	for(int i=1;i<=n;i++)a[i]=read(),g[a[i]].push_back(i);
	for(int i=0;i<=n;i++)g[i].push_back(n+1);
	for(int i=1;i<=n;i++)sgt::updata(sgt::rt[i],sgt::rt[i-1],a[i],i);
	for(int i=1;i<=n;i++)a[i]?p[0].push_back({i,i}):p[1].push_back({i,i});
	for(int i=1;i<=n;i++){
		for(pii j:p[i-1]){
			int pl=*(--lower_bound(g[i-1].begin(),g[i-1].end(),j.first)),pr=*upper_bound(g[i-1].begin(),g[i-1].end(),j.second);
//			cout<<pl<<" "<<pr<<" "<<j.first<<" "<<j.second<<"\n";
			if(pl)p[sgt::query(sgt::rt[j.second],pl)].push_back({pl,j.second});
			if(pr<=n)p[sgt::query(sgt::rt[pr],j.first)].push_back({j.first,pr});
		}
		sort(p[i].begin(),p[i].end(),cmp);
//		for(pii j:p[i])cout<<j.first<<" "<<j.second<<"\n";
//		cout<<"\n";
		vector<pii> pp;int lst=n+1;
		for(pii j:p[i])if(lst>j.second)pp.push_back(j),lst=j.second;
		p[i]=pp;
//		for(pii j:p[i])cout<<j.first<<" "<<j.second<<"\n";
//		cout<<i<<"\n";
	}
	for(int i=0;i<=n;i++){
		for(pii j:p[i]){
			int pl=*(--lower_bound(g[i].begin(),g[i].end(),j.first))+1,pr=*upper_bound(g[i].begin(),g[i].end(),j.second)-1;
			add[j.second-j.first+1].push_back(i);
			del[pr-pl+2].push_back(i);
//			cout<<j.first<<" "<<j.second<<" "<<pr-pl+1<<" "<<i<<"\n";
		}
	}
	for(int i=0;i<=n;i++)s.insert(i);
	for(int i=1;i<=n;i++){
		for(int j:add[i]){
			t[j]++;
			if(t[j]==1)s.erase(j);
		}
		for(int j:del[i]){
			t[j]--;
			if(!t[j])s.insert(j);	
		}
		printf("%lld ",*s.begin());
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
