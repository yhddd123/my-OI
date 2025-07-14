#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,s,t;
vector<int> g[maxn];
int rad[maxn];
int in[maxn],out[maxn];
int cnt;
int st[maxn],tp;
void dfs(int u){
	for(int i=rad[u];i<g[u].size();i=rad[u]){
		int v=g[u][i];rad[u]=i+1;
		dfs(v);
	}
	st[++tp]=u;
}

int T;
signed main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		g[u].push_back(v);
		out[u]++;in[v]++;
	}
	for(int i=1;i<=n;i++)sort(g[i].begin(),g[i].end());
	for(int i=1;i<=n;i++){
		if(in[i]!=out[i]){
			cnt++;
			if(in[i]==out[i]+1)t=i;
			else if(in[i]==out[i]-1)s=i;
			else{
				printf("No\n");
				return 0;
			}
		}
	}
	if(cnt&&cnt!=2){
		printf("No\n");
		return 0;
	}
	if(!cnt)s=1,t=1;
	if(!s||!t){
		printf("No\n");
		return 0;
	}
	dfs(s);
	while(tp){
		printf("%lld ",st[tp]);
		tp--;
	}
}
