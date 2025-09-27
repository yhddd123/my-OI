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
const int maxn=200010;
const int inf=1e18;
bool mbe;

int n,m,ans=-inf;
map<int,int> mp[maxn];
int d[maxn];
queue<int> q;
void add(int u,int v,int w){
	if(mp[u].find(v)!=mp[u].end())ans=max(ans,mp[u][v]+w);
	else mp[u][v]=-inf,d[u]++;
	mp[u][v]=max(mp[u][v],w);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	for(int i=1;i<=n;i++)if(d[i]<=2)q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		if(!d[u])continue;
		else if(d[u]==1){
			int v=(*mp[u].begin()).fi;
			mp[u].erase(v),mp[v].erase(u),d[u]--,d[v]--;
			if(d[v]<=2)q.push(v);
		}
		else if(d[u]==2){
			int v1=(*mp[u].begin()).fi,v2=(*--mp[u].end()).fi;
			int w1=(*mp[u].begin()).se,w2=(*--mp[u].end()).se;
			add(v1,v2,w1+w2),add(v2,v1,w1+w2);
			mp[u].erase(v1),mp[u].erase(v2),mp[v1].erase(u),mp[v2].erase(u),d[u]-=2,d[v1]--,d[v2]--;
			if(d[v1]<=2)q.push(v1);
			if(d[v2]<=2)q.push(v2);
		}
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