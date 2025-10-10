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
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=23;
const int inf=1e9;
bool mbe;

int n,m;
pii edge[maxn*maxn];
int head[maxn],tot;
struct nd{
	int nxt,to,id;
}e[maxn<<1];
void add(int u,int v,int id){e[++tot]={head[u],v,id};head[u]=tot;}
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int val[maxn];
void dfs(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		val[v]=val[u]^(1<<e[i].id-1),dfs(v,u);
	}
}
int num[1<<maxn-1];
pii f[1<<maxn-1];
inline int inc(int u,int v){((u+=v)>=mod)&&(u-=mod);return u;}
inline pii operator+(pii u,pii v){return {inc(u.fi,v.fi),inc(u.se,v.se)};}
inline pii operator*(pii u,pii v){return {1ll*u.fi*v.fi%mod,(1ll*u.fi*v.se+1ll*u.se*v.fi)%mod};}
inline pii operator*(pii u,int v){return {1ll*u.fi*v%mod,1ll*u.se*v%mod};}
int lgx[1<<maxn-1];
vector<int> id;
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		edge[i]={u,v};
	}
	for(int i=1;i<n;i++)ff[i]=i;
	for(int i=1;i<n;i++){
		auto[u,v]=edge[i];
		if(fd(u)==fd(v)){puts("0");return ;}
		ff[fd(u)]=fd(v);
		add(u,v,i),add(v,u,i);
	}
	dfs(0,0);
	for(int i=n;i<=m;i++){
		auto[u,v]=edge[i];
		// cout<<u<<" "<<v<<" "<<(val[u]^val[v])<<"\n";
		num[val[u]^val[v]]++;
	}
	for(int i=0;i<n-1;i++){
		for(int s=0;s<(1<<n-1);s++)if(s&(1<<i))num[s]+=num[s^(1<<i)];
	}
	for(int s=1;s<(1<<n-1);s++)num[s]+=__builtin_popcount(s),lgx[s]=__lg(s);
	f[0]={1,0};
	for(int i=1;i<=m;i++){
		for(int s=(1<<n-1)-1;~s;s--)if(f[s].fi||f[s].se){
			// cout<<s<<" "<<f[s].fi<<" "<<f[s].se<<endl;
			int ss=((1<<n-1)-1)^s;
			pii val=f[s]*make_pair(1,i);
			while(ss){
				int j=lgx[ss];ss^=1<<j;
				f[s|(1<<j)]=f[s|(1<<j)]+val;
			}
			f[s]=f[s]*(num[s]-i+1);
		}
	}
	printf("%d\n",f[(1<<n-1)-1].se);
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