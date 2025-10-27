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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,q;
int f[maxn],siz[maxn];
int fd(int x){
	if(f[x]==x)return x;
	return f[x]=fd(f[x]);
}
vector<int> e[maxn];
int d[210][maxn],id[maxn];
mt19937 rnd(time(0));
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
		u=fd(u),v=fd(v);
		if(u==v)continue;
		f[u]=v,siz[v]+=siz[u];
	}
	for(int i=1;i<=n;i++)id[i]=i;
	shuffle(id+1,id+n+1,rnd);
	memset(d,0x3f,sizeof(d));
	for(int i=1;i<=200&&i<=n;i++){
		queue<int> q;
		d[i][id[i]]=0;q.push(id[i]);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int v:e[u])if(d[i][v]>d[i][u]+1)d[i][v]=d[i][u]+1,q.push(v);
		}
	}
	while(q--){
		int u=read(),v=read();
		if(fd(u)!=fd(v))puts("YES");
		else if(siz[fd(u)]<=20000)puts("NO");
		else{
			int ans=inf;
			for(int i=1;i<=200;i++)ans=min(ans,d[i][u]+d[i][v]);
			puts(ans<=20000?"NO":"YES");
		}
	}
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