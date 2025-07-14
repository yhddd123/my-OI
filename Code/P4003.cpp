#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=10010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m,s,t;
int flow,ans;
struct nd{
	int nxt,to,val,c;
}e[maxn*5];
int head[maxn],tot=1;
void add(int u,int v,int w,int f){
	e[++tot]={head[u],v,w,f};head[u]=tot;
	e[++tot]={head[v],u,0,-f};head[v]=tot;
}
queue<int> q;
int dis[maxn],rad[maxn];
bool vis[maxn];
bool bfs(){
	for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=false,rad[i]=head[i];
	q.push(s);dis[s]=0;vis[s]=true;
	while(!q.empty()){
		int u=q.front();q.pop();vis[u]=false;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(e[i].val&&dis[v]>dis[u]+e[i].c){
				dis[v]=dis[u]+e[i].c;
				if(!vis[v])vis[v]=true,q.push(v);
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int res){
	if(u==t)return res;
	int cnt=0;vis[u]=true;
	for(int i=rad[u];i;i=e[i].nxt){
		int v=e[i].to;rad[u]=i;
		if(e[i].val&&dis[v]==dis[u]+e[i].c&&!vis[v]){
			int out=dfs(v,min(e[i].val,res));
			res-=out;cnt+=out;
			e[i].val-=out;e[i^1].val+=out;
			ans+=out*e[i].c;
			if(!res)break;
		}
	}
	vis[u]=false;
	return cnt;
}
int id(int u,int v){return (u-1)*m+v;}
int l,r,u,d;
void work(){
	n=read();m=read();s=n*m*5+1,t=n*m*5+2;
	l=n*m,r=2*n*m,u=3*n*m,d=4*n*m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int p=id(i,j);
			if((i+j)&1){
				add(s,p,inf,0);
				if(i>1)add(p+u,id(i-1,j)+d,1,0);
				if(i<n)add(p+d,id(i+1,j)+u,1,0);
				if(j>1)add(p+l,id(i,j-1)+r,1,0);
				if(j<m)add(p+r,id(i,j+1)+l,1,0);
				int w=read();
				if(w&1)add(p,p+u,1,0),flow++;
				if(w&2)add(p,p+r,1,0),flow++;
				if(w&4)add(p,p+d,1,0),flow++;
				if(w&8)add(p,p+l,1,0),flow++;
				if(w==1){
					add(p+u,p+l,1,1);
					add(p+u,p+r,1,1);
					add(p+u,p+d,1,2);
				}
				if(w==2){
					add(p+r,p+u,1,1);
					add(p+r,p+d,1,1);
					add(p+r,p+l,1,2);
				}
				if(w==4){
					add(p+d,p+l,1,1);
					add(p+d,p+r,1,1);
					add(p+d,p+u,1,2);
				}
				if(w==8){
					add(p+l,p+u,1,1);
					add(p+l,p+d,1,1);
					add(p+l,p+r,1,2);
				}
				if(w==3){
					add(p+r,p+l,1,1);
					add(p+u,p+d,1,1);
				}
				if(w==6){
					add(p+r,p+l,1,1);
					add(p+d,p+u,1,1);
				}
				if(w==9){
					add(p+l,p+r,1,1);
					add(p+u,p+d,1,1);
				}
				if(w==12){
					add(p+l,p+r,1,1);
					add(p+d,p+u,1,1);
				}
				if(w==7){
					add(p+u,p+l,1,1);
					add(p+d,p+l,1,1);
					add(p+r,p+l,1,2);
				}
				if(w==11){
					add(p+l,p+d,1,1);
					add(p+r,p+d,1,1);
					add(p+u,p+d,1,2);
				}
				if(w==13){
					add(p+u,p+r,1,1);
					add(p+d,p+r,1,1);
					add(p+l,p+r,1,2);
				}
				if(w==14){
					add(p+l,p+u,1,1);
					add(p+r,p+u,1,1);
					add(p+d,p+u,1,2);
				}
			}
			else{
				add(p,t,inf,0);
				int w=read();
				if(w&1)add(p+u,p,1,0),flow++;
				if(w&2)add(p+r,p,1,0),flow++;
				if(w&4)add(p+d,p,1,0),flow++;
				if(w&8)add(p+l,p,1,0),flow++;
				if(w==1){
					add(p+l,p+u,1,1);
					add(p+r,p+u,1,1);
					add(p+d,p+u,1,2);
				}
				if(w==2){
					add(p+u,p+r,1,1);
					add(p+d,p+r,1,1);
					add(p+l,p+r,1,2);
				}
				if(w==4){
					add(p+l,p+d,1,1);
					add(p+r,p+d,1,1);
					add(p+u,p+d,1,2);
				}
				if(w==8){
					add(p+u,p+l,1,1);
					add(p+d,p+l,1,1);
					add(p+r,p+l,1,2);
				}
				if(w==3){
					add(p+l,p+r,1,1);
					add(p+d,p+u,1,1);
				}
				if(w==6){
					add(p+l,p+r,1,1);
					add(p+u,p+d,1,1);
				}
				if(w==9){
					add(p+r,p+l,1,1);
					add(p+d,p+u,1,1);
				}
				if(w==12){
					add(p+r,p+l,1,1);
					add(p+u,p+d,1,1);
				}
				if(w==7){
					add(p+l,p+u,1,1);
					add(p+l,p+d,1,1);
					add(p+l,p+r,1,2);
				}
				if(w==11){
					add(p+d,p+l,1,1);
					add(p+d,p+r,1,1);
					add(p+d,p+u,1,2);
				}
				if(w==13){
					add(p+r,p+u,1,1);
					add(p+r,p+d,1,1);
					add(p+r,p+l,1,2);
				}
				if(w==14){
					add(p+u,p+l,1,1);
					add(p+u,p+r,1,1);
					add(p+u,p+d,1,2);
				}
			}
		}
	}
	if(flow&1){printf("-1\n");return ;}
	flow>>=1;
//	cout<<flow<<"\n";
	while(bfs())flow-=dfs(s,inf);
//	cout<<flow<<" "<<ans<<"\n";
	if(flow)printf("-1\n");
	else printf("%lld\n",ans);
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
