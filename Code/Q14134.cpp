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
const int maxn=2010;
const db eps=1e-12;
const db inf=1e18;
bool mbe;

int n,m;
int a[maxn],b[maxn],c[maxn],d[maxn];
db sa[maxn],sb[maxn],sc[maxn],sd[maxn];
db f[maxn][maxn],g[maxn][maxn],ans;
struct worker{
	int p,op,mx;
	db calc(int i,int j){
		if(op==1)return g[j][p-1]+sqrtl((db)d[p-1]*d[p-1]+(sa[i]-sa[j-1]+sb[i-1]-sb[j-1])*(sa[i]-sa[j-1]+sb[i-1]-sb[j-1]));
		else return f[p-1][j]+sqrtl((db)b[p-1]*b[p-1]+(sc[i]-sc[j-1]+sd[i-1]-sd[j-1])*(sc[i]-sc[j-1]+sd[i-1]-sd[j-1]));
	}
	struct node{
		int l,r,p;
	};
	node st[maxn];int h,t;
	void init(int _p,int _op){
		p=_p,op=_op;mx=(op==1?n:m);
		st[h=t=1]={1,mx,1};
	}
	void ins(int i){
		while(h<=t&&calc(st[t].l,st[t].p)-calc(st[t].l,i)>eps)t--;
		int l=st[t].l,r=st[t].r,res=l;
		while(l<=r){
			int mid=l+r>>1;
			if(calc(mid,i)-calc(mid,st[t].p)>eps)res=mid,l=mid+1;
			else r=mid-1;
		}
		// if(h<=t){
		// for(int j=st[t].l;j<=res;j++)assert(calc(j,i)>calc(j,st[t].p));
		// for(int j=res+1;j<=n;j++)assert(calc(j,i)<calc(j,st[t].p));
		// }
		st[t].r=res;
		if(res<mx)st[++t]={res+1,mx,i};
	}
	db que(int i){
		while(st[h].l<i){
			st[h].l++;
			if(st[h].l>st[h].r)h++;
		}
		// db val=1e18;
		// for(int j=1;j<=i;j++)val=min(val,calc(i,j));
		// for(int j=1;j<=i;j++)if(calc(i,j)==val&&calc(i,st[h].p)!=val&&st[h].p!=j){
			// cout<<p<<" "<<op<<" "<<i<<" "<<j<<" "<<st[h].p<<"\n";
			// exit(0);
		// }
		// return val;
		return calc(i,st[h].p);
	}
}s1[maxn],s2[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),sa[i]=sa[i-1]+a[i];
	for(int i=1;i<=n;i++)b[i]=read(),sb[i]=sb[i-1]+b[i];
	for(int i=1;i<=m;i++)c[i]=read(),sc[i]=sc[i-1]+c[i];
	for(int i=1;i<=m;i++)d[i]=read(),sd[i]=sd[i-1]+d[i];
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++)f[i][j]=g[i][j]=inf;
	}
	for(int i=2;i<=m;i++)s1[i].init(i,1);
	for(int i=2;i<=n;i++)s2[i].init(i,2);
	f[0][1]=g[1][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			f[i][j]=f[i-1][j]+a[i]+b[i-1];
			// cout<<i<<" "<<j<<" "<<f[i][j]<<"\n";
			if(j>1){
				s1[j].ins(i);
				f[i][j]=min(f[i][j],s1[j].que(i));
			}
			g[i][j]=g[i][j-1]+c[j]+d[j-1];
			if(i>1){
				s2[i].ins(j);
				g[i][j]=min(g[i][j],s2[i].que(j));
			}
		}
	}
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=m;j++)printf("%.5Lf ",f[i][j]);puts("");
	// }
	// for(int i=1;i<=n;i++){
		// for(int j=1;j<=m;j++)printf("%.5Lf ",g[i][j]);puts("");
	// }
	db ans=inf;
	for(int i=1;i<=m;i++)ans=min(ans,f[n][i]+sc[m]-sc[i-1]+sd[m]-sd[i-1]);
	for(int i=1;i<=n;i++)ans=min(ans,g[i][m]+sa[n]-sa[i-1]+sb[n]-sb[i-1]);
	printf("%.10Lf\n",ans);
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