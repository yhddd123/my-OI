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
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,q,a[maxn];
struct node{
	int l,r,v,t;
	bool operator<(const node&tmp)const{return r<tmp.l;}
};
set<node> s;
bool vis[maxn];
int pos[maxn],pre[maxn];
vector<tuple<int,int,int,int,int>> b;
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
int mx[maxn<<2];
void build(int nd,int l,int r){
    mx[nd]=n+1;
    if(l==r)return ;
    build(ls,l,mid),build(rs,mid+1,r);
}
void modif(int nd,int l,int r,int p,int w){
    if(l==r){mx[nd]=w;return ;}
    if(p<=mid)modif(ls,l,mid,p,w);
    else modif(rs,mid+1,r,p,w);
    mx[nd]=max(mx[ls],mx[rs]);
}
int findl(int nd,int l,int r,int w){
	if(l==r)return l;
	if(mx[ls]<=w)return findl(rs,mid+1,r,w);
	return findl(ls,l,mid,w);
}
vector<pii> upd[maxn],ask[maxn];
int ans[maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n,mex=1;i;i--){
		vis[a[i]]=1;while(vis[mex])mex++;
		s.insert({i,i,mex,n});
	}
	for(int i=1;i<=n;i++)pre[i]=pos[a[i]],pos[a[i]]=i;
	for(int i=n;i;i--){
		{
		auto it=s.find({i,i,0,0});
		auto[l,r,v,t]=*it;s.erase(it);
		if(l<i)s.insert({l,i-1,v,t});
		b.pb({v,i,i,i,t});
		}
		if(pre[i]+1==i)continue;
		{
			auto it=s.find({pre[i]+1,pre[i]+1,0,0});
			auto[l,r,v,t]=*it;
			if(l<=pre[i]){
				s.erase(it);
				s.insert({l,pre[i],v,t});
				s.insert({pre[i]+1,r,v,t});
			}
		}
		auto it=s.find({pre[i]+1,pre[i]+1,0,0});
		int p=pre[i];
		while(it!=s.end()&&(*it).v>a[i]){
			auto[l,r,v,t]=(*it);it=s.erase(it);
			// cout<<l<<" "<<r<<" "<<v<<" "<<t<<" "<<p<<endl;
			b.pb({v,l,r,i,t});p=r;
		}
		if(pre[i]+1<=p)s.insert({pre[i]+1,p,a[i],i-1});
		// cout<<i<<" "<<(*--s.end()).l<<" "<<(*--s.end()).r<<endl;
	}
	for(auto[v,l1,r1,l2,r2]:b){
		// cout<<v<<" "<<l1<<" "<<r1<<" "<<l2<<" "<<r2<<"\n";
		upd[r1].pb({l2,v});
	}
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		ask[l].pb({r,i});
	}
	build(1,1,n+2);
	for(int i=n;i;i--){
		for(auto[p,v]:upd[i])modif(1,1,n+2,v,p);
		for(auto[p,id]:ask[i])ans[id]=findl(1,1,n+2,p);
	}
	for(int i=1;i<=q;i++)write(ans[i]),puts("");
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