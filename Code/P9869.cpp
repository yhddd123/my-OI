#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl; 
}
const int maxn=200010;

int n,m;
int f[maxn];
char c[3];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
int vis[maxn];
int ans,fl;
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v<=n){
			if(!vis[v]){
				vis[v]=vis[u];
				dfs(v);
			}
			else if(vis[v]!=vis[u])fl=1;
		}
		else{
			if(!vis[v-n]){
				vis[v-n]=3-vis[u];
				dfs(v-n);
			}
			else if(vis[v-n]!=3-vis[u])fl=1;
		}
	}
	for(int i=head[u+n];i;i=e[i].nxt){
		int v=e[i].to;
		if(v<=n){
			if(!vis[v]){
				vis[v]=3-vis[u];
				dfs(v);
			}
			else if(vis[v]!=3-vis[u])fl=1;
		}
		else{
			if(!vis[v-n]){
				vis[v-n]=vis[u];
				dfs(v-n);
			}
			else if(vis[v-n]!=vis[u])fl=1;
		}
	}
}
bool bk[maxn];
void dfs1(int u){
	++ans;bk[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v<=n){
			if(!bk[v])dfs1(v);
		}
		else{
			if(!bk[v-n])dfs1(v-n);
		}
	}
	for(int i=head[u+n];i;i=e[i].nxt){
		int v=e[i].to;
		if(v<=n){
			if(!bk[v])dfs1(v);
		}
		else{
			if(!bk[v-n])dfs1(v-n);
		}
	}
}
void sovle(){
	n=read()+1;m=read();
	for(int i=1;i<=n;i++)f[i]=i;
	f[n]=2*n;
	while(m--){
		scanf("%s",c+1);
		int u,v;
		if(c[1]=='-'){
			u=read();v=read();
			if(!f[v])f[u]=f[v];
			else if(f[v]<=n)f[u]=f[v]+n;
			else f[u]=f[v]-n;
		}
		if(c[1]=='+'){
			u=read();v=read();
			f[u]=f[v];
		}
		if(c[1]=='T'){
			u=read();
			f[u]=0;
		}
		if(c[1]=='F'){
			u=read();
			f[u]=0;
		}
		if(c[1]=='U'){
			int u=read();
			f[u]=f[n];
		}
	}
//	for(int i=1;i<=n;i++)cout<<f[i]<<" ";
//	cout<<"\n";
	for(int i=1;i<=2*n;i++)head[i]=0;tot=0;
	for(int i=1;i<=n;i++)vis[i]=bk[i]=0;
	for(int i=1;i<=n;i++)if(f[i])add(f[i],i),add(i,f[i]);
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=1;fl=0;
			dfs(i);
			if(fl)dfs1(i);
		}
	}
	printf("%lld\n",ans-1);ans=0;
}

int op,T;
signed main(){
//	freopen("tribool.in","r",stdin);
//	freopen("tribool.out","w",stdout);
	
	op=read();T=read();
	while(T--)sovle();
}
