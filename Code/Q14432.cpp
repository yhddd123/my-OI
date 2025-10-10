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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,m,ans,num;
vector<int> e[maxn];
int d[maxn],tmp[maxn];
bool vis[maxn];
int id[maxn];
mt19937 rnd(time(0));
int st[maxn],tp;
queue<int> q;
int sovle(int u){
	d[u]=0;q.push(u);st[tp=1]=u;
	int num=0;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=1;++num;
		for(int v:e[u])if(d[v]>0){
			if(d[v]==tmp[v])st[++tp]=v;
			d[v]--;
			if(!d[v])q.push(v);
		}
	}
	for(int i=1;i<=tp;i++)d[st[i]]=tmp[st[i]];
	// cout<<u<<" "<<num<<"\n";
	return num;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v);
		d[v]++;
	}
	for(int i=1;i<=n;i++)tmp[i]=d[i];
	for(int i=1;i<=n;i++)if(!d[i])q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=1;++num;
		for(int v:e[u])if(d[v]>0){
			d[v]--;
			if(!d[v])q.push(v);
		}
	}
	ans=num;
	for(int u=1;u<=n;u++)if(!d[u]){
		for(int v:e[u])tmp[v]--;
		tmp[u]=-1;
	}
	for(int i=1;i<=n;i++)d[i]=tmp[i];
	for(int i=1;i<=n;i++)id[i]=i;
	shuffle(id+1,id+n+1,rnd);
	for(int i=1;i<=n;i++)if(!vis[id[i]]){
		ans=max(ans,sovle(id[i])+num);
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