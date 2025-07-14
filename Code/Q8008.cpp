#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
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

int n,p,m,a[maxn];
int dis[maxn];queue<int> q;
int id[maxn],sum[maxn];
int x,y;double ans;
void work(){
	n=read();p=read();m=read();
	for(int i=1;i<=m;i++)a[i]=read();
	mems(dis,0x3f);
	dis[0]=0;q.push(0);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=m;i++){
			int v=(u-a[i]+n)%n;
			if(dis[v]>dis[u]+1)dis[v]=dis[u]+1,q.push(v);
		}
	}
	// for(int i=0;i<n;i++)cout<<dis[i]<<" ";cout<<"\n";
	for(int i=1;i<=n;i++)id[i]=i-1;
	sort(id+1,id+n+1,[&](int u,int v){return dis[u]<dis[v];});
	for(int i=1;i<=n;i++)sum[i]=min(inf,sum[i-1]+dis[id[i]]);
	ans=inf;
	for(int i=1;i<=n;i++){
		if(id[i]==p){
			if(ans>dis[p])ans=dis[p],x=dis[p],y=1;
			break;
		}
		if(ans>1.0*(n+sum[i])/i)ans=1.0*(n+sum[i])/i,x=n+sum[i],y=i;
	}
	int gg=__gcd(x,y);x/=gg,y/=gg;
	cout<<x<<" "<<y<<"\n";
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
