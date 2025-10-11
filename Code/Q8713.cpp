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
const int maxn=18;
const int maxm=150;
const int inf=1e9;
bool mbe;

int n,a[1<<maxn];
char s[maxn+5];
int to[maxm][2],fail[maxm],idx,ed[maxm];
int f[1<<maxn][maxm];
bool vis[maxm];
vector<int> e[maxm];
int d[maxm];
void work(){
	n=read();
	for(int i=0;i<n;i++){
		scanf("%s",s+1);int l=strlen(s+1),nd=0;
		for(int j=1;j<=l;j++){
			if(!to[nd][s[j]-'0'])to[nd][s[j]-'0']=++idx;
			nd=to[nd][s[j]-'0'];
		}
		ed[nd]|=1<<i;
		a[1<<i]=read();
	}
	for(int s=1;s<(1<<n);s++)a[s]=a[s^(s&(-s))]+a[s&(-s)];
	queue<int> q;
	for(int i=0;i<2;i++)if(to[0][i])q.push(to[0][i]);
	while(!q.empty()){
		int u=q.front();q.pop();ed[u]|=ed[fail[u]];
		for(int i=0;i<2;i++){
			int &v=to[u][i];
			if(v)fail[v]=to[fail[u]][i],q.push(v);
			else v=to[fail[u]][i];
		}
	}
	// cout<<idx<<"\n";
	for(int s=(1<<n)-1;~s;s--){
		for(int i=0;i<=idx;i++)vis[i]=0,e[i].clear(),d[i]=0,f[s][i]=-inf;
		priority_queue<pii> q;
		for(int u=0;u<=idx;u++)if((s|ed[u])==s){
			for(int i=0;i<2;i++){
				int v=to[u][i];
				if((s|ed[v])!=s){
					if(f[s][u]<-f[s|ed[v]][v]+a[ed[v]^(s&ed[v])]){
						f[s][u]=-f[s|ed[v]][v]+a[ed[v]^(s&ed[v])];
						q.push({f[s][u],u});
					}
				}
				else e[v].pb(u),d[u]++;
			}
		}
		queue<int> qq;
		for(int u=0;u<=idx;u++)if((s|ed[u])==s&&!d[u])qq.push(u);
		while(!qq.empty()&&vis[qq.front()])qq.pop();
		if(qq.empty()){
			if(!q.empty()){
				int u=q.top().se;q.pop();
				if(f[s][u]>=0)qq.push(u);
			}
		}
		while(!qq.empty()){
			int u=qq.front();qq.pop();
			if(vis[u])continue;vis[u]=1;
			for(int v:e[u]){
				d[v]--;
				if(!d[v])qq.push(v);
				if(f[s][v]<-f[s][u]){
					f[s][v]=-f[s][u];
					q.push({f[s][v],v});
				}
			}
			while(!qq.empty()&&vis[qq.front()])qq.pop();
			if(qq.empty()){
				while(!q.empty()){
					int u=q.top().se;q.pop();
					if(vis[u])continue;
					if(f[s][u]<0)break;
					qq.push(u);
					break;
				}
			}
		}
		for(int u=0;u<=idx;u++)if(!vis[u])f[s][u]=0;
		// for(int u=0;u<=idx;u++)cout<<f[s][u]<<" ";cout<<"\n";
	}
	int qq=read();
	while(qq--){
		scanf("%s",s+1);int l=strlen(s+1);
		int nd=0,ss=0;
		for(int i=1;i<=l;i++){
			nd=to[nd][s[i]-'0'];
			ss|=ed[nd];
		}
		// cout<<nd<<" "<<ss<<"\n";
		printf("%lld\n",f[ss][nd]);
	}
	
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("a.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}