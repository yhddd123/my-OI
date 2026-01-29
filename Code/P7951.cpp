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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,m,a[maxn];
vector<int> e[maxn];
vector<tuple<int,int,int,int>> ans;
bool vis[maxn];
int pos[maxn];
void dfs(int u,int fa){
	vis[u]=1;
	for(int v:e[u])if(!vis[v]){
		dfs(v,u);
		if(fa){
			pos[v]=ans.size();
			ans.pb({fa,u,v,-a[v]}),a[fa]-=a[v],a[u]+=2*a[v],a[v]=0;
		}
	}
}
void outno(){
	puts("No");
	// puts("0");
}
void outyes(){
	puts("Yes");
	// puts("1");
	printf("%lld\n",(int)ans.size());
	for(auto[u,v,w,k]:ans)printf("%lld %lld %lld %lld\n",u,v,w,k);
}
int st[maxn],tp,dep[maxn],rnk[maxn];
int vk[maxn],vb[maxn],k[maxn],b[maxn];
void dfs1(int u,int fa){
	vis[u]=1;dep[u]=dep[fa]+1;rnk[dep[u]]=u;
	if(!tp){
		pii mx={0,0};
		for(int v:e[u])if(vis[v]&&((dep[u]-dep[v]+1)&1))mx=max(mx,{dep[v],v});
		if(mx.fi){
			int v=mx.se;
			for(int i=dep[v];i<=dep[u];i++)st[++tp]=rnk[i];
		}
	}
	for(int v:e[u]){
		if(!vis[v])dfs1(v,u);
	}
}
int tmp[maxn];
void work(int TT){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)a[i]-=read();
	int sum=0;for(int i=1;i<=n;i++)sum+=a[i];
	for(int i=1;i<=n;i++)e[i].clear(),vis[i]=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	if(sum){outno();return ;}
	ans.clear();
	int rt=0;for(int i=1;i<=n;i++)if(e[i].size()>=3)rt=i;
	if(rt){
		tp=0;dfs1(1,0);
		if(tp){
			for(int i=1;i<=n;i++)vis[i]=0;
			for(int i=1;i<=tp;i++)vis[st[i]]=1,tmp[i]=st[i];
			if(tp==n){
				bool fl=0;
				for(int i=1;i<=tp;i++)rnk[st[i]]=i;
				for(int i=1;i<=tp;i++)if(e[st[i]].size()>=3){
					int u=st[i];
					for(int v:e[u])if(vis[v]&&v!=st[i%tp+1]&&v!=st[i==1?tp:i-1]){
						int j=rnk[v];
						if((j-i+1)&1){
							tp=0;for(int k=i;k<=j;k++)st[++tp]=tmp[k];
						}
						else{
							int lst=tp;tp=0;
							for(int k=j;k<=lst;k++)st[++tp]=tmp[k];
							for(int k=1;k<=i;k++)st[++tp]=tmp[k];
						}
						fl=1;
					}
					if(fl)break;
				}
			}
			for(int i=1;i<=n;i++)vis[i]=0;
			for(int i=1;i<=tp;i++)vis[st[i]]=1;
			bool fl=0;
			for(int i=1;i<=tp;i++){
				int num=0;for(int v:e[st[i]])if(!vis[v])++num;
				if(num){
					rt=st[i];
					rotate(st+1,st+i,st+tp+1);
					vector<int> nw;
					nw.pb(st[2]),nw.pb(st[tp]);
					for(int v:e[rt])if(!vis[v])nw.pb(v);
					e[rt]=nw;
					for(int i=1;i<tp;i++){
						int u=st[i];
						for(int j=0;j<e[u].size();j++)if(e[u][j]==st[i+1]){swap(e[u][0],e[u][j]);break;}
					}
					fl=1;
					break;
				}
			}
			if(!fl){
				for(int i=1;i<=tp;i++)cerr<<st[i]<<" ";cerr<<"\n";
				cerr<<"err\n";
			}
			// cout<<st[1]<<" "<<rt<<"\n";
			// cout<<st[2]<<" "<<e[rt][0]<<"\n";
		}
		for(int i=1;i<=n;i++)vis[i]=0;
		vis[rt]=1;
		for(int v:e[rt])vis[v]=1;
		for(int v:e[rt])dfs(v,rt);
		if(abs(a[rt])&1){
			if(!tp)return outno();
			ans.pb({st[tp-2],st[tp-1],st[tp],1});
			a[st[tp-2]]++,a[st[tp-1]]-=2,a[st[tp]]++;
			// for(int i=1;i<=tp;i++)cout<<st[i]<<" ";cout<<"\n";
			for(int i=tp-1;i>=3;i--){
				int u=st[i];
				auto &[x,y,z,d]=ans[pos[u]];
				// cout<<u<<" "<<x<<" "<<y<<" "<<z<<" "<<d<<" "<<a[u]<<"\n";
				d-=a[u],a[x]-=a[u],a[y]+=2*a[u],a[z]=0;
			}
		}
		// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<"\n";
		int v=e[rt].back();
		for(int i=0;i<e[rt].size()-1;i++){
			ans.pb({e[rt][i],rt,v,-a[e[rt][i]]});
			a[rt]+=2*a[e[rt][i]],a[v]-=a[e[rt][i]],a[e[rt][i]]=0;
		}
		if(a[v]){
			int x1=get<0>(ans.back());
			int &d1=get<3>(ans.back());
			int x2=get<0>(ans[ans.size()-2]);
			int &d2=get<3>(ans[ans.size()-2]);
			d1-=a[v]/2;
			d2-=a[v]/2;
			a[x1]-=a[v]/2,a[rt]+=a[v];
			a[x2]-=a[v]/2,a[rt]+=a[v];
			ans.pb({x1,rt,x2,a[v]/2});
			a[x1]+=a[v]/2,a[x2]+=a[v]/2,a[rt]-=a[v];a[v]=0;
		}
		outyes();
	}
	else if(m==n-1){
		for(int i=1;i<=n;i++)if(e[i].size()==1)rt=i;
		dfs(rt,0);
		if(!a[rt])outyes();
		else outno();
	}
	else{
		int u=1;
		tp=0;while(!vis[u]){
			st[++tp]=u,vis[u]=1;
			for(int v:e[u])if(!vis[v])u=v;
		}
		for(int i=1;i<=n;i++)k[i]=0,b[i]=a[i];
		k[st[tp]]=-1;
		for(int i=tp-1;i>1;i--){
			vk[i]=-k[st[i+1]];
			vb[i]=-b[st[i+1]];
			k[st[i]]-=2*vk[i],b[st[i]]-=2*vb[i];
			k[st[i-1]]+=vk[i],b[st[i-1]]+=vb[i];
		}
		if(abs(b[st[2]])%abs(1-k[st[2]])==0){
			int d=b[st[2]]/(1-k[st[2]]);
			ans.pb({st[tp],st[1],st[2],-d});
			for(int i=2;i<tp;i++)ans.pb({st[i-1],st[i],st[i+1],vk[i]*d+vb[i]});
			outyes();
		}
		else outno();
	}
}

bool med;
int T;
signed main(){
	 // freopen("years.in","r",stdin);
	 // freopen("years.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	for(int t=1;t<=T;t++)work(t);
}