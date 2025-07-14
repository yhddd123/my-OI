#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,k;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int to[maxn][20];
int dep[maxn],rnk[maxn],idx;
int st[20][maxn];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	st[0][rnk[u]=++idx]=fa;
	to[u][0]=fa;for(int i=1;i<20;i++){
		to[u][i]=to[to[u][i-1]][i-1];
		if(!to[u][i])break;
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v!=fa)dfs(v,u);
	}
}
int pw[21],lg[maxn];
int lca(int u,int v){
	if(u==v)return u;
	u=rnk[u],v=rnk[v];
	if(u>v)swap(u,v);++u;
	int k=lg[v-u+1];
	if(rnk[st[k][u]]<rnk[st[k][v-pw[k]+1]])return st[k][u];
	return st[k][v-pw[k]+1];
}
signed main(){
	n=read();m=read();k=read();
	pw[0]=1;for(int i=1;i<=20;i++)pw[i]=pw[i-1]<<1;
	lg[1]=0;for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	dfs(1,0);
	for(int j=1;j<20;j++){
		if(pw[j]>n)break;
		for(int i=1;i+pw[j]-1<=n;i++){
			if(rnk[st[j-1][i]]<rnk[st[j-1][i+pw[j-1]]])st[j][i]=st[j-1][i];
			else st[j][i]=st[j-1][i+pw[j-1]];
		}
	}
	while(k--){
		int d=read(),t=read();
		int tp=lca(m,d);
		int dis=dep[d]+dep[m]-2*dep[tp];
		if(dis<=t)m=d;
		else{
			dis=dep[m]-dep[tp];
			if(dis>=t){
				for(int i=0;i<20;i++){
					if(t&pw[i])m=to[m][i];
					if(pw[i]>t)break;
				}
			}
			else{
				dis=dep[d]+dep[m]-2*dep[tp]-t;
				for(int i=0;i<20;i++){
					if(dis&pw[i])d=to[d][i];
					if(pw[i]>dis)break;
				}
				m=d;
			}
		}
		printf("%d ",m);
	}
}
