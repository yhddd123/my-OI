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
const int inf=1e15;
bool mbe;

int n,q;
char s[maxn];
int st[maxn],tp;
int pl[maxn],pr[maxn],idx;
int id[maxn];
int wl[maxn],wr[maxn],a[maxn];
vector<int> e[maxn];
int vl1[maxn],vr1[maxn],vl2[maxn],vr2[maxn];
void dfs(int u){
	if(!e[u].size()){
		a[pl[u]]=min(a[pl[u]],wr[pl[u]]);
		a[pr[u]]=min(a[pr[u]],wl[pr[u]]);
		return ;
	}
	for(int v:e[u])dfs(v);
	for(int i=0,s1=0,s2=0;i<e[u].size();i++){
		s1+=wl[pl[e[u][i]]];
		vl1[pl[e[u][i]]]=s1;
		s1+=a[pr[e[u][i]]];
		vl1[pr[e[u][i]]]=s1;
		s2+=wr[pl[e[u][i]]-1];
		vl2[pl[e[u][i]]]=s2;
		s2+=a[pl[e[u][i]]];
		vl2[pr[e[u][i]]]=s2;
	}
	a[pr[u]]=min(a[pr[u]],vl1[pr[e[u].back()]]+wl[pr[u]]);
	for(int i=e[u].size()-1,s1=0,s2=0;~i;i--){
		s1+=wr[pr[e[u][i]]];
		vr1[pr[e[u][i]]]=s1;
		s1+=a[pl[e[u][i]]];
		vr1[pl[e[u][i]]]=s1;
		s2+=wl[pr[e[u][i]]+1];
		vr2[pr[e[u][i]]]=s2;
		s2+=a[pr[e[u][i]]];
		vr2[pl[e[u][i]]]=s2;
	}
	a[pl[u]]=min(a[pl[u]],vr1[pl[e[u][0]]]+wr[pl[u]]);
}
void dfs1(int u){
	if(!e[u].size())return ;
	for(int v:e[u]){
		a[pl[v]]=min(a[pl[v]],vl1[pl[v]]+a[pl[u]]+vr2[pr[v]]);
		a[pr[v]]=min(a[pr[v]],vr1[pr[v]]+a[pr[u]]+vl2[pl[v]]);
		dfs1(v);
	}
}
int to[maxn][17],dep[maxn];
int val1[maxn][17][2],val2[maxn][17][2];
void dfs(int u,int fa){
	to[u][0]=fa,dep[u]=dep[fa]+1;
	val1[pl[u]][0][0]=min(vl1[pl[u]],a[pl[u]]+vr1[pr[u]]+a[pr[fa]]);
	val1[pl[u]][0][1]=min(vl1[pl[u]]+a[pl[fa]],a[pl[u]]+vr1[pr[u]]);
	val1[pr[u]][0][0]=min(vr1[pr[u]],a[pr[u]]+vl1[pl[u]]+a[pl[fa]]);
	val1[pr[u]][0][1]=min(vr1[pr[u]]+a[pr[fa]],a[pr[u]]+vl1[pl[u]]);
	val2[pl[u]][0][0]=min(vl2[pl[u]],a[pr[u]]+vr2[pr[u]]+a[pl[fa]]);
	val2[pl[u]][0][1]=min(vl2[pl[u]]+a[pr[fa]],a[pr[u]]+vr2[pr[u]]);
	val2[pr[u]][0][0]=min(vr2[pr[u]],a[pl[u]]+vl2[pl[u]]+a[pr[fa]]);
	val2[pr[u]][0][1]=min(vr2[pr[u]]+a[pl[fa]],a[pl[u]]+vl2[pl[u]]);
	for(int i=1;i<=16;i++){
		to[u][i]=to[to[u][i-1]][i-1];
		val1[pl[u]][i][0]=min(val1[pl[u]][i-1][0]+val1[pl[to[u][i-1]]][i-1][0],val1[pl[u]][i-1][1]+val1[pr[to[u][i-1]]][i-1][1]);
		val1[pl[u]][i][1]=min(val1[pl[u]][i-1][0]+val1[pl[to[u][i-1]]][i-1][1],val1[pl[u]][i-1][1]+val1[pr[to[u][i-1]]][i-1][0]);
		val1[pr[u]][i][0]=min(val1[pr[u]][i-1][0]+val1[pr[to[u][i-1]]][i-1][0],val1[pr[u]][i-1][1]+val1[pl[to[u][i-1]]][i-1][1]);
		val1[pr[u]][i][1]=min(val1[pr[u]][i-1][0]+val1[pr[to[u][i-1]]][i-1][1],val1[pr[u]][i-1][1]+val1[pl[to[u][i-1]]][i-1][0]);
		val2[pl[u]][i][0]=min(val2[pl[u]][i-1][0]+val2[pl[to[u][i-1]]][i-1][0],val2[pl[u]][i-1][1]+val2[pr[to[u][i-1]]][i-1][1]);
		val2[pl[u]][i][1]=min(val2[pl[u]][i-1][0]+val2[pl[to[u][i-1]]][i-1][1],val2[pl[u]][i-1][1]+val2[pr[to[u][i-1]]][i-1][0]);
		val2[pr[u]][i][0]=min(val2[pr[u]][i-1][0]+val2[pr[to[u][i-1]]][i-1][0],val2[pr[u]][i-1][1]+val2[pl[to[u][i-1]]][i-1][1]);
		val2[pr[u]][i][1]=min(val2[pr[u]][i-1][0]+val2[pr[to[u][i-1]]][i-1][1],val2[pr[u]][i-1][1]+val2[pl[to[u][i-1]]][i-1][0]);
	}
	for(int v:e[u])dfs(v,u);
}
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v])u=to[u][i];
	if(u==v)return u;
	for(int i=16;~i;i--)if(to[u][i]!=to[v][i])u=to[u][i],v=to[v][i];
	return to[u][0];
}
int kth(int u,int k){
	for(int i=0;i<=16;i++)if(k&(1<<i))u=to[u][i];
	return u;
}
tuple<int,int,int,int> que1(int u,int v){
	int l0=0,l1=a[pl[u]],r0=0,r1=a[pr[u]];
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v]){
		int nl0=min(l0+val1[pl[u]][i][0],l1+val1[pr[u]][i][1]);
		int nl1=min(l0+val1[pl[u]][i][1],l1+val1[pr[u]][i][0]);
		int nr0=min(r0+val1[pr[u]][i][0],r1+val1[pl[u]][i][1]);
		int nr1=min(r0+val1[pr[u]][i][1],r1+val1[pl[u]][i][0]);
		l0=nl0,l1=nl1,r0=nr0,r1=nr1;
		u=to[u][i];
	}
	return {l0,l1,r0,r1};
}
tuple<int,int,int,int> que2(int u,int v){
	int l0=0,l1=a[pr[u]],r0=0,r1=a[pl[u]];
	for(int i=16;~i;i--)if(dep[to[u][i]]>=dep[v]){
		int nl0=min(l0+val2[pl[u]][i][0],l1+val2[pr[u]][i][1]);
		int nl1=min(l0+val2[pl[u]][i][1],l1+val2[pr[u]][i][0]);
		int nr0=min(r0+val2[pr[u]][i][0],r1+val2[pl[u]][i][1]);
		int nr1=min(r0+val2[pr[u]][i][1],r1+val2[pl[u]][i][0]);
		l0=nl0,l1=nl1,r0=nr0,r1=nr1;
		u=to[u][i];
	}
	return {l0,l1,r0,r1};
}
pii ask[maxn];
void work(){
	n=read();q=read();
	scanf("%s",s+1);s[0]='(',s[n+1]=')';
	for(int i=1;i<=n;i++)wl[i]=read();
	for(int i=1;i<=n;i++)wr[i]=read();
	for(int i=1;i<=n;i++)a[i]=read();a[0]=a[n+1]=inf;
	for(int i=1;i<=idx;i++)e[i].clear();
	idx=0;for(int i=0;i<=n+1;i++){
		if(s[i]=='('){
			st[++tp]=++idx;pl[idx]=i;
		}
		else{
			pr[st[tp]]=i;tp--;
			if(tp)e[st[tp]].pb(st[tp+1]);
		}
	}
	// for(int i=1;i<=idx;i++){
		// cout<<pl[i]<<" "<<pr[i]<<"\n";
		// for(int v:e[i])cout<<v<<" ";cout<<"\n";
	// }
	for(int i=1;i<=idx;i++)id[pl[i]]=id[pr[i]]=i;
	dfs(1),dfs1(1),dfs(1,1);
	for(int i=1;i<=q;i++)ask[i].fi=read();
	for(int i=1;i<=q;i++)ask[i].se=read();
	int res=0;
	for(int qq=1;qq<=q;qq++){
		auto[u,v]=ask[qq];int tp=lca(id[u],id[v]);
		int opu=(u==pr[id[u]]),opv=(v==pr[id[v]]);
		// cout<<id[u]<<" "<<id[v]<<" "<<opu<<" "<<opv<<" "<<tp<<"\n";
		if(u==v){}
		else if(id[u]==id[v])res+=a[u];
		else if(id[u]==tp){
			auto[l0,l1,r0,r1]=que2(id[v],id[u]);
			// cout<<l0<<" "<<l1<<" "<<r0<<" "<<r1<<"\n";
			if(!opv){
				if(!opu)res+=l0;
				else res+=l1;
			}
			else{
				if(!opu)res+=r1;
				else res+=r0;
			}
		}else if(id[v]==tp){
			auto[l0,l1,r0,r1]=que1(id[u],id[v]);
			if(!opu){
				if(!opv)res+=l0;
				else res+=l1;
			}
			else{
				if(!opv)res+=r1;
				else res+=r0;
			}
		}
		else{
			int p1=kth(id[u],dep[id[u]]-dep[tp]-1),p2=kth(id[v],dep[id[v]]-dep[tp]-1),ans=inf;
			// cout<<id[u]<<" "<<id[v]<<" "<<p1<<" "<<p2<<" "<<tp<<" "<<e[tp].back()<<"\n";
			auto[lu0,lu1,ru0,ru1]=que1(id[u],p1);
			auto[lv0,lv1,rv0,rv1]=que2(id[v],p2);
			int lu,ru,lv,rv;
			if(!opu)lu=lu0,ru=lu1;
			else lu=ru1,ru=ru0;
			if(!opv)lv=lv0,rv=lv1;
			else lv=rv1,rv=rv0;
			if(p1<p2){
				ans=min(ans,ru+vl2[pl[p2]]-vl2[pr[p1]]+lv);
				ans=min(ans,lu+vl1[pl[p1]]+a[pl[tp]]+vr2[pr[p2]]+rv);
			}
			else{
				// cout<<lu<<" "<<ru<<" "<<lv<<" "<<rv<<"\n";
				ans=min(ans,lu+vr2[pr[p2]]-vr2[pl[p1]]+rv);
				ans=min(ans,ru+vr1[pr[p1]]+a[pr[tp]]+vl2[pl[p2]]+lv);
			}
			res+=ans;
		}
		// cout<<res<<"\n";
	}
	printf("%lld\n",res);
}

bool med;
int T;
signed main(){
	// freopen("string.in","r",stdin);
	// freopen("string.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	for(int t=1;t<=T;t++){
		printf("Case #%lld: ",t);
		work();
	}
}