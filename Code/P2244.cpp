#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n;
int head[maxn],tot;
struct edgend{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
queue<int> q;
int f[maxn];
int fd(int x){
	if(x==f[x])return x;
	return f[x]=fd(f[x]);
}
int d[maxn],mx;
bool los[maxn];
int ans;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();ans=n;
	for(int i=1;i<=n;i++){
		d[i]=read();
		for(int j=1;j<=d[i];j++)add(i,read());
		mx=max(mx,d[i]);
	}
	for(int i=1;i<=n+1;i++)f[i]=i;
	for(int i=1;i<=n;i++)if(d[i]==mx)f[i]=fd(i+1),q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			los[v]=1;
		}
		for(int i=fd(1);i<=n;i=fd(i+1))if(!los[i])f[i]=fd(i+1),q.push(i);;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			los[v]=0;
		}
	}
	for(int i=fd(1);i<=n;i=fd(i+1))los[i]=1,--ans;
	printf("%lld ",ans);
	for(int i=1;i<=n;i++)if(!los[i])printf("%lld ",i);
}
