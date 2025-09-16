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
const int maxn=200010;
bool mbe;

int n,m,k,ans;
int id(int u,int v){return u*(m+2)+v;}
int head[maxn],tot=1,s,t;
struct nd{
	int nxt,to,w;
}e[maxn<<1];
void add(int u,int v,int w){
    // cout<<u<<" "<<v<<" "<<(w==1e8?"1e8":"1e15")<<"\n";
	e[++tot]={head[u],v,w};head[u]=tot;
	e[++tot]={head[v],u,0};head[v]=tot;
}
int rad[maxn],dis[maxn];
queue<int> q;
bool bfs(){
	for(int i=0;i<=t;i++)rad[i]=head[i],dis[i]=0;
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
    n=read();m=read();k=read();
    s=id(n+2,0),t=id(n+2,1);
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=m+1;j++)if(!(!i&&!j)&&!(i==n+1&&j==m+1)){
            // cout<<i<<" "<<j<<"\n";
            ans-=1e8;
            add(s,id(i,j),(i==n+1||j==0)?1e15:1e8);
            add(id(i,j),t,(i==0||j==m+1)?1e15:1e8);
            if(i<=n)add(id(i,j),id(i+1,j),1e15);
            if(j)add(id(i,j),id(i,j-1),1e15);
        }
    }
    while(k--){
        int x=read(),y=read(),xx=read(),yy=read(),va=read(),vb=read();
        if((x==0&&y==0)||(x==0&&yy==m)||(xx==n&&y==0)||(xx==n&&yy==m))continue;
        add(id(x,y),id(xx+1,yy+1),va);
        add(id(xx+1,yy+1),id(x,y),vb);
    }
    while(bfs())ans+=dfs(s,2e18);
    printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
    // freopen("A.in","r",stdin);
    // freopen(".out","w",stdout);
    
    // cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
    
    T=1;
    while(T--)work();
}