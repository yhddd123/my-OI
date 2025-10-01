#include<bits/stdc++.h>
#define ll long long
#define mod 1000000007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,qq,a[maxn],b[maxn];
int fa[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
vector<int> id;
int f[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
ll del[maxn];int ans[maxn];
void sovle(){
	for(int i=1;i<=n;i++)f[i]=i,del[i]=ans[i]=0;
	for(int i=2;i<=n;i++)del[fa[i]]+=a[i];
	for(int u:id){
		int p=fd(u),num=a[u];
		inc(ans[u],1ll*a[u]*b[u]%mod);
		while(p&&num){
			int d=min(del[p],(ll)num);
			del[p]-=d,num-=d;
			inc(ans[p],mod-1ll*d*b[u]%mod);
			if(!del[p])f[p]=fd(fa[p]);
			p=fd(p);
		}
	}
	for(int u=n;u;u--)inc(ans[fa[u]],ans[u]);
	int res=1;for(int i=1;i<=n;i++)res=1ll*res*ans[i]%mod;
	write(res);puts("");
}
void work(){
	qq=read()-1;n=read();
	for(int i=2;i<=n;i++)fa[i]=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	id.resize(n);for(int i=1;i<=n;i++)id[i-1]=i;
	sort(id.begin(),id.end(),[&](int u,int v){return b[u]<b[v];});
	sovle();
	while(qq--){
		int k=read();
		for(int i=1;i<=k;i++){
			int u=read();
			swap(a[u],a[u+1]);
		}
		sovle();
	}
}

bool med;
int T;
signed main(){
	// freopen("1.in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}