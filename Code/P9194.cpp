#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=400010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,ans;;
int p[maxn],f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int s[maxn],t[maxn];
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==p[u])continue;
		p[v]=u;dfs(v);
		if(u<=n)s[u]+=s[v];
		else ++s[u],t[u]+=s[v];
	}
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,i+n);add(i+n,v);add(v,i+n);add(i+n,u);
	}
	dfs(n);
	for(int i=1;i<=n*2;i++)f[i]=i;
	for(int i=1;i<=n;i++)ans+=s[i]*s[i];
	for(int i=n+1;i<2*n;i++)ans+=s[i]*s[i]*s[i]-s[i]*s[i]-s[i]+2*s[i]*t[i];
	for(int u=1;u<=n;u++){
		printf("%lld\n",ans);
		int x=fd(p[u]),y=p[x],d=-1;
//		cout<<x<<" "<<y<<"\n";
		ans-=s[x]*s[x]*s[x]-s[x]*s[x]-s[x]+2*s[x]*t[x]+s[y]*s[y];
		s[y]-=s[x];--s[x];
		t[x]-=s[u];ans-=s[u]*s[u];s[u]=0;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==p[u])continue;
			f[v]=x;s[x]+=s[v];t[x]+=t[v];d+=s[v];
			ans-=s[v]*s[v]*s[v]-s[v]*s[v]-s[v]+2*s[v]*t[v];s[v]=t[v]=0;
		}
		s[y]+=s[x];ans+=s[x]*s[x]*s[x]-s[x]*s[x]-s[x]+2*s[x]*t[x]+s[y]*s[y];
		t[fd(p[p[x]])]+=d;ans+=2*s[fd(p[p[x]])]*d;
//		cout<<fd(p[p[x]])<<" "<<d<<" "<<ans<<"\n";
	}
}
