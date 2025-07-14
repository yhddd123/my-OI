// Problem: J: Rikka 与子集 IV
// Contest: BUCTOJ
// URL: https://buctcoder.com/problem.php?cid=3664&pid=9
// Memory Limit: 512 MB
// Time Limit: 10000 ms
// Written by yhm.
// Start codeing:2024-08-09 20:53:59
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int fa[maxn],siz[maxn],son[maxn];
void dfs(int u){
	siz[u]=1;son[u]=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);siz[u]+=siz[v];
		if(siz[v]>=siz[son[u]])son[u]=v;
	}
}
int tp[maxn];
void dfs(int u,int lst){
	tp[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==son[u])continue;
		dfs(v,v);
	}
}
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
namespace ploy{
	inline int ksm(int a,int b=mod-2){
		int ans=1;
		while(b){
			if(b&1)ans=ans*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ans;
	}
	int gg=3,invg=ksm(gg);
	int to[maxn*5];
	vector<int> ntt(vector<int> a,int flag){
		int n=a.size();
		for(int i=0;i<n;i++)if(i<to[i])swap(a[i],a[to[i]]);
		for(int len=2;len<=n;len<<=1){
			int bas=ksm(flag==1?gg:invg,(mod-1)/len),l=len>>1;
			for(int i=0;i<n;i+=len){
				int mul=1;
				for(int j=i;j<i+l;j++){
					int val=mul*a[j+l]%mod;
					inc(a[j+l]=a[j],mod-val);
					inc(a[j],val);
					mul=mul*bas%mod;
				}
			}
		}
		if(flag==-1){
			int inv=ksm(n);
			for(int i=0;i<n;i++)a[i]=a[i]*inv%mod;
		}
		return a;
	}
	vector<int> mul(vector<int> a,vector<int> b){
		int n=a.size()-1,m=b.size()-1;int k=1;
		while(k<n+m+1)k<<=1;
		vector<int> f(k),g(k);
		for(int i=0;i<=n;i++)f[i]=a[i];
		for(int i=0;i<=m;i++)g[i]=b[i];
		for(int i=0;i<k;i++)to[i]=(to[i>>1]>>1)|((i&1)?(k>>1):0);
		f=ntt(f,1),g=ntt(g,1);
		for(int i=0;i<k;i++)f[i]=f[i]*g[i]%mod;
		f=ntt(f,-1);f.resize(n+m+1);
		return f;
	}
	vector<int> add(vector<int> a,vector<int> b){
		int n=a.size()-1,m=b.size()-1;
		vector<int> f(max(n,m)+1);
		for(int i=0;i<=n;i++)f[i]=a[i];
		for(int i=0;i<=m;i++)inc(f[i],b[i]);
		return f;
	}
}
using ploy::mul;
using ploy::add;
vector<int> f[maxn],g[maxn],a[maxn],ans;
struct node{
	vector<int> pre,suf,mul,sum;
};
node calc1(int l,int r){
	if(l==r){return {g[l],g[l],g[l],g[l]};}
	int mid=l+r>>1;
	node al=calc1(l,mid),ar=calc1(mid+1,r);
	return {add(al.pre,mul(al.mul,ar.pre)),add(mul(al.suf,ar.mul),ar.suf),mul(al.mul,ar.mul),add(add(al.sum,ar.sum),mul(al.suf,ar.pre))};
}
vector<int> calc2(int l,int r){
	if(l==r)return a[l];
	int mid=l+r>>1;
	return mul(calc2(l,mid),calc2(mid+1,r));
}
void dfs1(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;dfs1(v);
	}
	if(u==tp[u]){
		int num=0;
		for(int v=u;v;v=son[v]){
			++num;
			if(!e[head[v]].nxt||!head[v])g[num]={0,1};
			else{
				int cnt=0;
				for(int i=head[v];i;i=e[i].nxt){
					int vv=e[i].to;if(vv==son[v])continue;
					a[++cnt]=f[vv];
				}
				g[num]=mul(calc2(1,cnt),{0,1});
			}
			// cout<<u<<" "<<v<<" "<<num<<" g\n";
			// for(int i:g[num])cout<<i<<" ";cout<<"\n";
		}
		node res=calc1(1,num);
		f[u]=res.pre;inc(f[u][0],1);
		ans=add(ans,res.sum);
		// cout<<u<<" "<<num<<"\n";
		// for(int i:f[u])cout<<i<<" ";cout<<"\n";
		// for(int i:res.sum)cout<<i<<" ";cout<<"\n";
	}
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)head[i]=0;tot=0;
	for(int i=2;i<=n;i++){
		fa[i]=read();
		add(fa[i],i);
	}
	dfs(1),dfs(1,1);
	ans.clear();dfs1(1);
	for(int i=1;i<=n;i++)printf("%lld ",i<ans.size()?ans[i]:0);puts("");
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
	
	T=read();
	while(T--)work();
}
