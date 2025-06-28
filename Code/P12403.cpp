// Problem: P12403 [COI 2025] 象掌兽 / Lirili Larila
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12403
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-26 19:57:53
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,a,b;
namespace sub1{
	int dis[310][310];
	void sovle(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)dis[i][j]=inf;
			dis[i][i]=0;
		}
		for(int i=1;i<=m;i++){
			int u=read(),v=read();
			dis[u][v]=dis[v][u]=1;
		}
		for(int k=1;k<=n;k++){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
		for(int s=1;s<=n;s++){
			for(int t=1;t<=n;t++){
				int cnta=0,cntb=0;
				for(int i=1;i<=n;i++){
					cnta+=dis[s][i]<dis[t][i];
					cntb+=dis[s][i]>dis[t][i];
				}
				if(a==cnta&&b==cntb){printf("%d %d\n",s,t);return ;}
			}
		}
	}
}
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
namespace sub2{
	int siz[maxn],fa[maxn];
	void dfs(int u){
		siz[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(v==fa[u])continue;
			fa[v]=u,dfs(v);siz[u]+=siz[v];
		}
	}
	void sovle(){
		for(int i=1;i<=n;i++)head[i]=0;tot=0;
		for(int i=1;i<=m;i++){
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		dfs(1);
		for(int u=1;u<=n;u++)if(siz[u]==a){
			if(n-siz[u]==b){printf("%d %d\n",u,fa[u]);return ;}
			if(n-siz[fa[u]]==b){printf("%d %d\n",u,fa[fa[u]]);return ;}
			for(int i=head[fa[u]];i;i=e[i].nxt){
				int v=e[i].to;if(u==v||v==fa[fa[u]])continue;
				if(siz[v]==b){printf("%d %d\n",u,v);return ;}
			}
		}
		for(int u=1;u<=n;u++)if(siz[u]==b){
			if(n-siz[u]==a){printf("%d %d\n",fa[u],u);return ;}
			if(n-siz[fa[u]]==a){printf("%d %d\n",fa[fa[u]],u);return ;}
			for(int i=head[fa[u]];i;i=e[i].nxt){
				int v=e[i].to;if(u==v||v==fa[fa[u]])continue;
				if(siz[v]==a){printf("%d %d\n",v,u);return ;}
			}
		}
	}
}
namespace sub3{
	int d[maxn];
	int siz[maxn],fa[maxn],mxd[maxn],dep[maxn];
	int dfn[maxn],rnk[maxn],idx;
	vector<int> id[maxn];
	void dfs(int u,int tp){
		siz[u]=1,id[tp].pb(u);
		dep[u]=dep[fa[u]]+1,mxd[u]=1;
		rnk[dfn[u]=++idx]=u;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(d[v]!=1||v==fa[u])continue;
			fa[v]=u,dfs(v,tp);siz[u]+=siz[v],mxd[u]=max(mxd[u],mxd[v]+1);
		}
	}
	int st[maxn*2],tp,sum[maxn*2];
	void dfs1(int u){
		st[++tp]=u,d[u]=0;
		fa[u]=0,id[u].clear(),dfs(u,u);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;if(d[v]!=2)continue;
			dfs1(v);
		}
	}
	int mx[19][maxn];
	int quemx(int l,int r){
		int k=__lg(r-l+1);
		return max(mx[k][l],mx[k][r-(1<<k)+1]);
	}
	void sovle(){
		for(int i=1;i<=n;i++)head[i]=d[i]=fa[i]=0;tot=0;
		for(int i=1;i<=m;i++){
			int u=read(),v=read();
			add(u,v),add(v,u);
			d[u]++,d[v]++;
		}
		queue<int> q;
		for(int i=1;i<=n;i++)if(d[i]==1)q.push(i);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(d[v]>1){
					d[v]--;
					if(d[v]==1)q.push(v);
				}
			}
		}
		tp=idx=0;for(int i=1;i<=n;i++)if(d[i]==2)dfs1(i);
		for(int u=1;u<=n;u++)if(d[u]==1&&siz[u]==a){
			if(n-siz[u]==b){printf("%d %d\n",u,fa[u]);return ;}
			if(fa[fa[u]]&&n-siz[fa[u]]==b){printf("%d %d\n",u,fa[fa[u]]);return ;}
			for(int i=head[fa[u]];i;i=e[i].nxt){
				int v=e[i].to;if(u==v||v==fa[fa[u]]||d[v]!=1)continue;
				if(siz[v]==b){printf("%d %d\n",u,v);return ;}
			}
		}
		for(int u=1;u<=n;u++)if(d[u]==1&&siz[u]==b){
			if(n-siz[u]==a){printf("%d %d\n",fa[u],u);return ;}
			if(fa[fa[u]]&&n-siz[fa[u]]==a){printf("%d %d\n",fa[fa[u]],u);return ;}
			for(int i=head[fa[u]];i;i=e[i].nxt){
				int v=e[i].to;if(u==v||v==fa[fa[u]]||d[v]!=1)continue;
				if(siz[v]==a){printf("%d %d\n",v,u);return ;}
			}
		}
		// cout<<tp<<"\n";for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
		for(int i=1;i<=tp;i++)st[i+tp]=st[i];
		if(!(tp&1)){
			for(int i=1,j=tp/2+1;i<=tp;i++,j++){
				for(int ii=head[st[j]];ii;ii=e[ii].nxt){
					int v=e[ii].to;
					if(d[v]==1&&mxd[v]>=tp/2){
						if(siz[v]==a&&n-siz[st[j]]==b){
							for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++)if(dep[rnk[jj]]-1==tp/2){printf("%d %d\n",rnk[jj],st[i]);return ;}
						}
						if(siz[v]==b&&n-siz[st[j]]==a){
							for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++)if(dep[rnk[jj]]-1==tp/2){printf("%d %d\n",st[i],rnk[jj]);return ;}
						}
					}
				}
			}
		}
		else{
			for(int i=1,j=tp/2+1;i<=tp;i++,j++){
				for(int ii=head[st[j]];ii;ii=e[ii].nxt){
					int v=e[ii].to;
					if(d[v]==1&&mxd[v]>=tp/2){
						if(siz[v]==a&&n-siz[st[j]]==b){
							for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++)if(dep[rnk[jj]]-1==tp/2){printf("%d %d\n",rnk[jj],st[i]);return ;}
						}
						if(siz[v]==b&&n-siz[st[j]]==a){
							for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++)if(dep[rnk[jj]]-1==tp/2){printf("%d %d\n",st[i],rnk[jj]);return ;}
						}
					}
				}
				for(int ii=head[st[j+1]];ii;ii=e[ii].nxt){
					int v=e[ii].to;
					if(d[v]==1&&mxd[v]>=tp/2){
						if(siz[v]==a&&n-siz[st[j+1]]==b){
							for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++)if(dep[rnk[jj]]-1==tp/2){printf("%d %d\n",rnk[jj],st[i]);return ;}
						}
						if(siz[v]==b&&n-siz[st[j+1]]==a){
							for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++)if(dep[rnk[jj]]-1==tp/2){printf("%d %d\n",st[i],rnk[jj]);return ;}
						}
					}
				}
			}
		}
		for(int i=1;i<=2*tp;i++)sum[i]=sum[i-1]+siz[st[i]];
		for(int i=1;i<=tp;i++){
			int p=lower_bound(sum+1,sum+2*tp+1,a+sum[i])-sum;
			if(sum[p]-sum[i]!=a)continue;
			for(int ii=head[st[i]];ii;ii=e[ii].nxt){
				int v=e[ii].to;
				if(d[v]==1&&siz[v]==b&&i+mxd[v]+(tp-1)/2>=p){
					for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++){
						if(i+dep[rnk[jj]]-1+(tp-1)/2==p){printf("%d %d\n",st[i+dep[rnk[jj]]-1],rnk[jj]);return ;}
					}
				}
			}
		}
		for(int i=1;i<=tp;i++){
			int p=lower_bound(sum+1,sum+2*tp+1,b+sum[i])-sum;
			if(sum[p]-sum[i]!=b)continue;
			for(int ii=head[st[i]];ii;ii=e[ii].nxt){
				int v=e[ii].to;
				if(d[v]==1&&siz[v]==a&&i+mxd[v]+(tp-1)/2>=p){
					for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++){
						if(i+dep[rnk[jj]]-1+(tp-1)/2==p){printf("%d %d\n",rnk[jj],st[i+dep[rnk[jj]]-1]);return ;}
					}
				}
			}
		}
		for(int i=tp+1;i<=2*tp;i++){
			int p=lower_bound(sum+1,sum+2*tp+1,sum[i-1]-a)-sum+1;
			if(sum[i-1]-sum[p-1]!=a)continue;
			for(int ii=head[st[i]];ii;ii=e[ii].nxt){
				int v=e[ii].to;
				if(d[v]==1&&siz[v]==b&&i-mxd[v]-(tp-1)/2<=p){
					for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++){
						if(i-dep[rnk[jj]]+1-(tp-1)/2==p){printf("%d %d\n",st[i-dep[rnk[jj]]+1],rnk[jj]);return ;}
					}
				}
			}
		}
		for(int i=tp+1;i<=2*tp;i++){
			int p=lower_bound(sum+1,sum+2*tp+1,sum[i-1]-b)-sum+1;
			if(sum[i-1]-sum[p-1]!=b)continue;
			for(int ii=head[st[i]];ii;ii=e[ii].nxt){
				int v=e[ii].to;
				if(d[v]==1&&siz[v]==a&&i-mxd[v]-(tp-1)/2<=p){
					for(int jj=dfn[v];jj<dfn[v]+siz[v];jj++){
						if(i-dep[rnk[jj]]+1-(tp-1)/2==p){printf("%d %d\n",rnk[jj],st[i-dep[rnk[jj]]+1]);return ;}
					}
				}
			}
		}
		for(int i=1;i<=2*tp;i++)mx[0][i]=mxd[st[i]];
		for(int j=1;j<=18;j++){
			for(int i=1;i+(1<<j)-1<=2*tp;i++)mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
		}
		for(int l=1;l<=tp;l++){
			int r=lower_bound(sum+1,sum+2*tp+1,a+sum[l-1])-sum;
			if(sum[r]-sum[l-1]!=a)continue;
			if(tp&1){
				int p=r+1,q=l+tp-2;
				if(sum[q]-sum[p-1]==b){
					if(q-p+1<=r-l+1){
						int d=((r-l+1)-(q-p+1))/2;
						if(quemx(p,q)>=d){
							for(int i=p,j=r;i<=q;i++,j--){
								for(int u:id[st[i]])if(dep[u]==d+1){printf("%d %d\n",st[j-d],u);return ;}
							}
						}
					}
					else{
						int d=((q-p+1)-(r-l+1))/2;
						if(quemx(l,r)>=d){
							for(int i=l,j=q;i<=r;i++,j--){
								for(int u:id[st[i]])if(dep[u]==d+1){printf("%d %d\n",u,st[j-d]);return ;}
							}
						}
					}
				}
				p=r+2,q=l+tp-1;
				if(sum[q]-sum[p-1]==b){
					if(q-p+1<=r-l+1){
						int d=((r-l+1)-(q-p+1))/2;
						if(quemx(p,q)>=d){
							for(int i=p,j=r;i<=q;i++,j--){
								for(int u:id[st[i]])if(dep[u]==d+1){printf("%d %d\n",st[j-d],u);return ;}
							}
						}
					}
					else{
						int d=((q-p+1)-(r-l+1))/2;
						if(quemx(l,r)>=d){
							for(int i=l,j=q;i<=r;i++,j--){
								for(int u:id[st[i]])if(dep[u]==d+1){printf("%d %d\n",u,st[j-d]);return ;}
							}
						}
					}
				}
			}
			else{
				int p=r+1,q=l+tp-1;
				if(sum[q]-sum[p-1]==b){
					if(q-p+1<=r-l+1){
						int d=((r-l+1)-(q-p+1))/2;
						if(quemx(p,q)>=d){
							for(int i=p,j=r;i<=q;i++,j--){
								for(int u:id[st[i]])if(dep[u]==d+1){printf("%d %d\n",st[j-d],u);return ;}
							}
						}
					}
					else{
						int d=((q-p+1)-(r-l+1))/2;
						if(quemx(l,r)>=d){
							for(int i=l,j=q;i<=r;i++,j--){
								for(int u:id[st[i]])if(dep[u]==d+1){printf("%d %d\n",u,st[j-d]);return ;}
							}
						}
					}
				}
				p=r+2,q=l+tp-2;
				if(sum[q]-sum[p-1]==b){
					if(q-p+1<=r-l+1){
						int d=((r-l+1)-(q-p+1))/2;
						if(quemx(p,q)>=d){
							for(int i=p,j=r;i<=q;i++,j--){
								for(int u:id[st[i]])if(dep[u]==d+1){printf("%d %d\n",st[j-d],u);return ;}
							}
						}
					}
					else{
						int d=((q-p+1)-(r-l+1))/2;
						if(quemx(l,r)>=d){
							for(int i=l,j=q;i<=r;i++,j--){
								for(int u:id[st[i]])if(dep[u]==d+1){printf("%d %d\n",u,st[j-d]);return ;}
							}
						}
					}
				}
			}
		}
	}
}
void work(){
	n=read();m=read();a=read();b=read();
	if(m==n-1)return sub2::sovle();
	if(m==n)return sub3::sovle();
	if(n<=300)return sub1::sovle();
}

bool med;
int T;
signed main(){
	// freopen("recallrevenge.in","r",stdin);
	// freopen("recallrevenge.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}