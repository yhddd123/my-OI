// Problem: P10439 [JOIST 2024] 逃生路线 2 / Escape Route 2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10439
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-04 12:33:34
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=100010;
const int maxq=300010;
const int B=200;
const int inf=1e18;
bool mbe;

int n,t,m,q;
int pl[maxn],pr[maxn];
pii a[maxn];
int to[17][maxn],tim[17][maxn];
vector<pii> que[maxn];
int ans[maxq];
int dis[maxn],val[maxn];
void work(){
	n=read();t=read();
	pl[0]=1;for(int i=1;i<n;i++){
		int k=read();pl[i]=m+1,pr[i]=m+k;
		for(int j=pl[i];j<=pr[i];j++)a[j]={read(),read()};
		sort(a+pl[i],a+pr[i]+1,[&](pii u,pii v){return u.fi<v.fi||(u.fi==v.fi&&u.se>v.se);});
		int p=pl[i];for(int j=pl[i]+1;j<=pr[i];j++){
			while(p>=pl[i]&&a[j].se<=a[p].se)p--;
			a[++p]=a[j];
		}
		pr[i]=p;m=p;
		for(int j=pl[i-1];j<=pr[i-1];j++){
			to[0][j]=lower_bound(a+pl[i],a+pr[i]+1,make_pair(a[j].se,0ll))-a;
			if(to[0][j]==pr[i]+1){
				to[0][j]=pl[i],tim[0][j]=t+a[pl[i]].se-a[j].se;
			}
			else tim[0][j]=a[to[0][j]].se-a[j].se;
			// cout<<i<<" "<<j<<" "<<to[0][j]<<" "<<tim[0][j]<<"\n";
		}
	}
	for(int j=pl[n-1];j<=m+1;j++)to[0][j]=m+1;
	for(int j=1;j<=16;j++){
		for(int i=1;i<=m+1;i++){
			to[j][i]=to[j-1][to[j-1][i]];
			tim[j][i]=tim[j-1][i]+tim[j-1][to[j-1][i]];
		}
	}
	q=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();ans[i]=inf;
		if(pr[l]-pl[l]+1<=B){
			for(int j=pl[l];j<=pr[l];j++){
				if(l+1<r){
					int p=j,t=a[j].se-a[j].fi;
					for(int k=16;~k;k--)if(to[k][p]<pl[r-1])t+=tim[k][p],p=to[k][p];
					ans[i]=min(ans[i],t+tim[0][p]);
				}
				else ans[i]=min(ans[i],a[j].se-a[j].fi);
			}
		}
		else que[l].pb({r,i});
	}
	for(int i=1;i<n;i++)if(que[i].size()){
		for(int j=1;j<=m;j++)dis[j]=inf;
		for(int j=pl[i];j<=pr[i];j++)dis[j]=a[j].se-a[j].fi;
		for(int j=pl[i];j<=m;j++){
			dis[to[0][j]]=min(dis[to[0][j]],dis[j]+tim[0][j]);
		}
		for(int j=i+1;j<=n;j++){
			val[j]=inf;
			for(int k=pl[j-1];k<=pr[j-1];k++)val[j]=min(val[j],dis[k]);
		}
		for(auto[r,id]:que[i])ans[id]=val[r];
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
}

bool med;
int T;
signed main(){
	// freopen("A.in","r",stdin);
	// freopen("A.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}