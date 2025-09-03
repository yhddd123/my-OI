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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
int st[maxn],tp;
int sum[maxn];
int b[maxn];
int ans[maxn];
#define lb(x) (x&(-x))
struct bit1{
	int tree[maxn<<1];
	void upd(int x,int w){
		x++;while(x)tree[x]+=w,x-=lb(x);
	}
	int que(int x){
		int res=0;
		x++;while(x<=2*n+2)res+=tree[x],x+=lb(x);
		return res;
	}
}tk;
struct bit2{
	int tree[maxn<<1];
	void upd(int x,int w){
		x++;while(x<=2*n+2)tree[x]+=w,x+=lb(x);
	}
	int que(int x){
		int res=0;
		x++;while(x)res+=tree[x],x-=lb(x);
		return res;
	}
}tb;
void upd(int p,int k,int b){tk.upd(p,k),tb.upd(p,b);}
int que(int v){return tb.que(v)+tk.que(v+1)*v;}
bool vis[maxn];
void work(){
	n=read();	
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=0;i<=n;i++)ans[i]=0;
	tp=0;for(int i=1,mn=n+1;i<=n;i++){
		if(mn>a[i])mn=a[i],st[++tp]=i;
		sum[i]=sum[i-1]+mn;
	}
	for(int i=1;i<=n;i++)vis[i]=0;
	vector<int> id;
	for(int i=n,mx=-1;i;i--){
		if(mx<a[i])vis[i]=1,id.pb(i);
	}
	st[++tp]=n+1;
	a[0]=2*n+1;
	// for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
	for(int i=tp-1;i;i--){
		b[st[i]]=a[st[i-1]];
		upd(b[st[i]],1,b[st[i]]);
		for(int j=st[i]+1,mn=a[st[i-1]];j<st[i+1];j++){
			mn=min(mn,a[j]);b[j]=mn;
			if(vis[j])ans[j-st[i]]=max(ans[j-st[i]],sum[st[i]-1]+que(a[st[i]]+a[j]));
			upd(b[j],1,b[j]);
		}
		for(int j:id){
			if(j<st[i+1])break;
			ans[j-st[i]]=max(ans[j-st[i]],sum[st[i]-1]+que(a[st[i]]+a[j])+sum[j-1]-sum[st[i+1]-1]);
			if(a[j]+a[st[i]]>a[st[i-1]])break;
		}
		for(int j=st[i];j<st[i+1];j++)upd(b[j],-1,-b[j]);
	}
	for(int i=n-1;~i;i--)ans[i]=max(ans[i],ans[i+1]);
	for(int i=0;i<n;i++)printf("%lld ",ans[i]);puts("");
	
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}