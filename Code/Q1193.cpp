#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=1010;
const int maxm=20;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
string s[maxn];
int head[maxn*maxm],tot;
struct nd{
	int nxt,to,w;
}e[maxn*maxn*maxm];
void add(int u,int v,int w){e[++tot]={head[u],v,w};head[u]=tot;}
int dis[maxn*maxm];
struct Dis{
	int dis,id;
	bool operator<(const Dis&tmp)const{return dis>tmp.dis;}
};
bool vis[maxn*maxm];
priority_queue<Dis> q;
int id(int u,int v){return (u-1)*(m+1)+v+1;}
const int inf=1e9;
void work(){
	cin>>n;m=16;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1;i<=n;i++){
		for(int j=0;j<s[i].size();j++){
			for(int k=1;k<=n;k++){
				if(i==k&&!j)continue;
				if(s[k].size()>=s[i].size()-j){
					if(s[i].substr(j,s[i].size()-j)==s[k].substr(0,s[i].size()-j)){
						int res=s[k].size()-(s[i].size()-j);
						add(id(i,s[i].size()-j),id(k,res),res);
					}
				}
				else{
					if(s[i].substr(j,s[k].size())==s[k]){
						int res=s[i].size()-j-s[k].size();
						add(id(i,s[i].size()-j),id(i,res),0);
					}
				}
			}
		}
	}
	mems(dis,0x3f);
	for(int i=1;i<=n;i++){
		dis[id(i,s[i].size())]=s[i].size();
		q.push({s[i].size(),id(i,s[i].size())});
	}
	while(!q.empty()){
		int u=q.top().id;q.pop();
		if(vis[u])continue;vis[u]=1;
		// cout<<u<<" "<<dis[u]<<"\n";
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				q.push({dis[v],v});
			}
		}
	}
	int ans=inf;
	for(int i=1;i<=n;i++)ans=min(ans,dis[id(i,0)]);
	if(ans==inf)ans=0;
	cout<<ans;
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
