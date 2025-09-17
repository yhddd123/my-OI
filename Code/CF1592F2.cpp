#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
inline int read(){
    int x=0,fl=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*fl;
}
const int maxn=510;
const int inf=1e9;
bool mbe;

int n,m;
char c[maxn];
int a[maxn][maxn],b[maxn][maxn];
int head[maxn*2],tot=1;
struct nd{
	int nxt,to,w;
}e[maxn*maxn<<1];
void add(int u,int v,int w){
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int s,t,flow;
int rad[maxn*2],dis[maxn*2];
queue<int> q;
bool bfs(){
	for(int i=1;i<=t;i++)rad[i]=head[i],dis[i]=0;
	dis[s]=1;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!dis[v]&&e[i].w)dis[v]=dis[u]+1,q.push(v);
		}
	}
	return dis[t];
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(dis[v]==dis[u]+1&&e[i].w){
			int out=dfs(v,min(e[i].w,res));
			e[i].w-=out;e[i^1].w+=out;
			cnt+=out;res-=out;
			if(!res)break;
		}
	}
	return cnt;
}
void work(){
    n=read();m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",c+1);
        for(int j=1;j<=m;j++)a[i][j]=c[j]=='B';
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)a[i][j]^=a[i][j+1]^a[i+1][j]^a[i+1][j+1];
    }
    int num=0;for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)num+=a[i][j];
    }
    num-=a[n][m];
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++)cout<<a[i][j];cout<<"\n";
    // }
    s=n+m+1,t=n+m+2;
    for(int i=1;i<=n;i++)if(a[i][m])add(s,i,1);
    for(int i=1;i<=m;i++)if(a[n][i])add(i+n,t,1);
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++)if(a[i][j])add(i,j+n,1);
    }
    while(bfs())flow+=dfs(s,n);
    // cout<<num<<" "<<flow<<"\n";
    printf("%lld\n",num-flow+(a[n][m]^(flow&1)));
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen("A.out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}