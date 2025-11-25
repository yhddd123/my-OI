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
const int maxn=6016;
const int inf=1e9;
bool mbe;

int n;
char a[maxn];
#define ull unsigned long long
ull pw[65];
struct bs{
	vector<ull> a;
	int len,n;
	void init(int _n){
		n=_n,len=(n+63)/64;a.resize(len);
		for(int i=0;i<len;i++)a[i]=0;
	}
	void set0(int x){a[x>>6]&=~pw[x&63];}
	void set1(int x){a[x>>6]|=pw[x&63];}
	bool operator[](int x){return (a[x>>6]>>(x&63))&1;}
	bs operator&(const bs&b)const{
		bs c;c.init(min(n,b.n));
		for(int i=0;i<c.len;i++)c.a[i]=a[i]&b.a[i];
		return c;
	}
	void operator&=(const bs&b){
		for(int i=0;i<min(len,b.len);i++)a[i]&=b.a[i];
	}
	bs operator<<(int x)const{
		bs res;res.init(n);
		int y=x>>6,z=x&63;
		ull lst=0;
		for(int i=0;i+y<res.len;i++){
			res.a[i+y]=lst|(a[i]<<z);
			if(z)lst=a[i]>>(64ll-z);
		}
		return res;
	}
	int count(){
		int res=0;for(int i=0;i<len;i++)res+=__builtin_popcountll(a[i]);
		return res;
	}
	bool any(){
		bool fl=0;for(int i=0;i<len;i++)fl|=!!a[i];
		return fl;
	}
}f[maxn],g[maxn],vis,tmp;
bool andany(const bs&a,const bs&b){
	bool fl=0;for(int i=0;i<a.len;i++)fl|=(!!(a.a[i]&b.a[i]));
	return fl;
}
vector<pii> ans;
void dfs(int i,int j){
	if(i>j)return ;
	if(a[i]==a[j]){
		if(f[i+1][j-1]){dfs(i+1,j-1),ans.pb({i,2});return ;}
		else{
			for(int k=i+1;k<j;k++)if(a[i]==a[k]&&f[i+1][k-1]&&f[k+1][j-1]){
				dfs(k+1,j-1),dfs(i+1,k-1);ans.pb({i,3});return ;
			}
		}
	}
	for(int k=i+1;k<j;k++)if(f[i][k]&&f[k+1][j]){
		dfs(k+1,j),dfs(i,k);return ;
	}
}
void work(){
	n=read();scanf("%s",a+1);
	for(int i=0;i<=n+1;i++)f[i].init(n+2),g[i].init(n+2);
	pw[0]=1;for(int i=1;i<64;i++)pw[i]=pw[i-1]<<1ull;
	vis.init(n+2),tmp.init(n+2);
	for(int i=1;i<=n+1;i++)f[i].set1(i-1),g[i-1].set1(i-1);
	for(int i=n;i;i--){
		vis=f[i+1]<<1;
		for(int j=i+1;j<=n;j++)if(a[i]!=a[j])vis.set0(j);
		bool fl=0,fl1=vis.any();
		for(int j=i+1;j<=n;j++){
			bool ff=0;
			if(a[i]==a[j]){
				ff=f[i+1][j-1];
				(!ff)&&(ff=andany(g[j-1],vis),0);
				(!ff&&fl)&&(ff=andany(f[i],g[j]),0);
				ff&&(fl=1,f[i].set1(j),g[j].set1(i-1),0);
			}
			else{
				(!ff&&fl)&&(ff=andany(f[i],g[j]),0);
				ff&&(f[i].set1(j),g[j].set1(i-1),0);
			}
			// cout<<i<<" "<<j<<" "<<ff<<"\n";
		}
	}
	if(f[1][n]){
		dfs(1,n);
		printf("%d\n",ans.size());
		for(auto[u,v]:ans)printf("%d %d\n",u,v);
	}
	else puts("-1");
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