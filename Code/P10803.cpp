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
const int inf=1e15;
bool mbe;

int n,a[maxn],ans=inf;
int sx,sy,ex,ey;
int mn[20][maxn];
int que(int l,int r){
	int k=__lg(r-l+1);
	return min(mn[k][l],mn[k][r-(1<<k)+1]);
}
priority_queue<pii> q;
int dis[maxn<<1];bool vis[maxn<<1];
vector<pii> e[maxn<<1];
void add(int u,int v,int w){e[u].pb({v,w}),e[v].pb({u,w});}
void work(){
	n=read();sx=read(),sy=read()-1,ex=read(),ey=read()-1;
	for(int i=1;i<=n;i++)a[i]=read(),mn[0][i]=a[i];
	for(int j=1;j<20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<j-1)]);
	}
	if(que(min(sx,ex),max(sx,ex))>=min(sy,ey))ans=abs(sx-ex)+abs(sy-ey);
	for(int i=1;i<=n;i++){
		dis[i]=abs(sx-i)+sy,q.push({-dis[i],i});
		if(que(min(i,sx),max(i,sx))>=min(a[i],sy)){
			dis[i+n]=abs(sx-i)+(a[i]>=sy)*abs(a[i]-sy),q.push({-dis[i+n],i+n});
		}
		else dis[i+n]=inf;
	}
	for(int i=1;i<=n;i++){
		add(i,i+n,a[i]);
		if(i>1){
			add(i,i-1,1),add(i,i-1+n,1),add(i+n,i-1+n,1+abs(a[i]-a[i-1]));
		}
	}
	while(!q.empty()){
		int u=q.top().se;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(auto[v,w]:e[u]){
			if(dis[v]>dis[u]+w)dis[v]=dis[u]+w,q.push({-dis[v],v});
		}
	}
	for(int i=1;i<=n;i++){
		ans=min(ans,dis[i]+abs(ex-i)+ey);
		if(que(min(i,ex),max(i,ex))>=min(a[i],ey)){
			ans=min(ans,dis[i+n]+abs(ex-i)+abs(a[i]-ey));
		}
	}
	printf("%lld\n",ans);
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