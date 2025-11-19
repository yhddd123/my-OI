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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]=max(tree[x],w),x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res=max(res,tree[x]),x-=lb(x);
	return res;
}
int f[maxn];
vector<int> pos[maxn];
bool dfs(int d,int p){
	if(d==m+1)return 1;
	while(pos[d].size()&&pos[d].back()<p)pos[d].pop_back();
	while(pos[d].size()&&a[pos[d].back()]>a[p]){
		int nw=pos[d].back();pos[d].pop_back();
		if(dfs(d+1,nw))return 1;
	}
	return 0;
}
int lsh[maxn],len;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),lsh[++len]=a[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	for(int i=1;i<=n;i++){
		f[i]=que(a[i]-1)+1;
		upd(a[i],f[i]);
		m=max(m,f[i]);
		pos[f[i]].pb(i);
	}
	for(int i=1;i<=m;i++)reverse(pos[i].begin(),pos[i].end());
	for(int t=1;;t++){
		if(!dfs(1,0)){printf("%lld\n",n-(t-1));break;}
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