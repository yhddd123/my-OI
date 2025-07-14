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

int n,m;
struct ask{
	int num,id;
}a[4];
bool cmp(ask u,ask v){return u.num<v.num;}
int ans[maxn];
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){
	e[++tot]={head[u],v};
	head[u]=tot;
}
int siz[maxn],w[maxn];
int dep[maxn];
void dfs(int u){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!dep[v]){
			dep[v]=dep[u]+1;
			dfs(v);
			siz[u]+=siz[v];
			w[u]=max(w[u],siz[v]);
		}
	}
	w[u]=max(w[u],n-siz[u]);
}
void dfs1(int u,int c){
	ans[u]=c;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(dep[v]==dep[u]+1)dfs1(v,c);
	}
}
int sum[maxn];
bool vis[maxn];
void col(int u,int s){
	vis[u]=1;sum[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(!vis[v]&&ans[u]==ans[v]){
			col(v,s);
			sum[u]+=sum[v];
//			cout<<u<<" "<<v<<" "<<s<<" "<<sum[v]<<"\n";
			if(s<=sum[v])return ;
			s-=sum[v];
		}
	}
	if(s)ans[u]=3;
}
int g=1,s=1;
int mn[maxn];
int calcmn(int u){
	int res=n+1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		res=min(res,dep[v]);
	}
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(dep[v]==dep[u]+1)res=min(res,calcmn(v));
	}
	return res;
}
int cnt[4];

int T;
signed main(){
//	freopen("P5811_5.27.in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	a[1].num=read();a[2].num=read();a[3].num=read();
	a[1].id=1;a[2].id=2;a[3].id=3;
	sort(a+1,a+4,cmp);
	for(int i=1;i<=m;i++){
		int u,v;
		u=read();v=read();
		u++;v++;
		add(u,v);add(v,u);
	}
	dep[1]=1;dfs(1);
	for(int u=2;u<=n;u++){
		if(a[1].num<=siz[u]&&siz[u]+a[2].num<=n){
			dfs1(u,1);
			for(int i=1;i<=n;i++)if(!ans[i])ans[i]=2;
			for(int i=1;i<=n;i++){
				if(ans[i]==1){
					col(i,siz[u]-a[1].num);
					break;
				}
			}
//			for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
//			cout<<"\n";
			for(int i=1;i<=n;i++){
				if(ans[i]==2){
					col(i,n-siz[u]-a[2].num);
					break;
				}
			}
			for(int i=1;i<=n;i++)printf("%lld ",a[ans[i]].id);
			return 0;
		}
		if(a[2].num<=siz[u]&&siz[u]+a[1].num<=n){
			dfs1(u,2);
			for(int i=1;i<=n;i++)if(!ans[i])ans[i]=1;
			for(int i=1;i<=n;i++){
				if(ans[i]==2){
					col(i,siz[u]-a[2].num);
					break;
				}
			}
			for(int i=1;i<=n;i++){
				if(ans[i]==1){
					col(i,n-siz[u]-a[1].num);
					break;
				}
			}
			for(int i=1;i<=n;i++)printf("%lld ",a[ans[i]].id);
			return 0;
		}
	}
	for(int i=2;i<=n;i++)if(w[i]<w[g])g=i;
	for(int i=head[g];i;i=e[i].nxt){
		int v=e[i].to;
		if(dep[v]==dep[g]+1){
			mn[v]=calcmn(v);
			if(mn[v]>=dep[g])s+=siz[v];
		}
	}
	if(s>n-a[1].num){
		for(int i=1;i<=n;i++)printf("0 ");
		return 0;
	}
	dfs1(g,2);
	for(int i=1;i<=n;i++)if(!ans[i])ans[i]=1;
	s=siz[g];
	for(int i=head[g];i;i=e[i].nxt){
		int v=e[i].to;
		if(mn[v]<dep[g]&&dep[v]==dep[g]+1&&s>n-a[1].num){
			s-=siz[v];
			dfs1(v,1);
		}
	}
	for(int i=1;i<=n;i++){
		if(ans[i]==1){
			col(i,n-s-a[1].num);
			break;
		}
	}
	for(int i=1;i<=n;i++){
		if(ans[i]==2){
			col(i,s-a[2].num);
			break;
		}
	}
	for(int i=1;i<=n;i++)printf("%lld ",a[ans[i]].id);
}
