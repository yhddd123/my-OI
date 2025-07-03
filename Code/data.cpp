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
const int inf=1e9;
bool mbe;

mt19937 rnd(time(0));
int get(int l,int r){return l+rnd()%(r-l+1);}
int a[maxn];
void work(){
	int n=100000,k=8000;
	cout<<n<<" "<<k<<"\n";
	set<pii> edges;
	// 先生成一棵生成树保证联通
	vector<int> nodes;
	for(int i=1;i<=n;i++) nodes.pb(i);
	shuffle(nodes.begin(), nodes.end(), rnd);
	for(int i=1;i<n;i++){
		int u = nodes[i-1], v = nodes[i];
		if(u>v) swap(u,v);
		edges.insert(mkp(u,v));
	}
	// 再随机生成剩余的边
	while((int)edges.size()<4*n){
		int u=get(1,n), v=get(1,n);
		if(u==v) continue;
		if(u>v) swap(u,v);
		if(edges.count(mkp(u,v))) continue;
		edges.insert(mkp(u,v));
	}
	for(auto e:edges) cout<<e.fi<<" "<<e.se<<"\n";
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	freopen("A.in","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=10;
	cout<<T<<"\n";
	while(T--)work();
}