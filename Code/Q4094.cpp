#include<bits/stdc++.h>
#include "histogram.h"
#define ll long long
#define mod 998244353ll
#define pii pair<ll,ll>
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
const int maxn=500010;
const int inf=1e9;
bool mbe;

ll n,a[maxn],ans;
ll f[maxn],g[maxn];
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int rt[maxn],idx;
int lc[maxn<<6],rc[maxn<<6];
struct line{
	int k;ll b;
	ll calc(int x){return 1ll*k*x+b;}
}tree[maxn<<6];
void clr(){
	while(idx)tree[idx]={0,0},lc[idx]=rc[idx]=0,idx--;
}
void updata(int &nd,int l,int r,line id){
	if(!nd)nd=++idx;
	if(l==r){
		if(tree[nd].calc(l)<id.calc(l))tree[nd]=id;
		return ;
	}
	if(tree[nd].calc(mid)<id.calc(mid))swap(tree[nd],id);
	if(tree[nd].calc(l)<id.calc(l))updata(ls,l,mid,id);
	else updata(rs,mid+1,r,id);
}
int merge(int u,int v,int l,int r){
	if(!u||!v)return u|v;
	if(l!=r){
		lc[u]=merge(lc[u],lc[v],l,mid);
		rc[u]=merge(rc[u],rc[v],mid+1,r);
	}
	updata(u,l,r,tree[v]);
	return u;
}
ll query(int nd,int l,int r,int p){
	if(!nd)return 0;
	if(l==r)return tree[nd].calc(p);
	if(p<=mid)return max(tree[nd].calc(p),query(ls,l,mid,p));
	else return max(tree[nd].calc(p),query(rs,mid+1,r,p));
}
int st[19][maxn];
int mmax(int u,int v){return a[u]<a[v]?u:v;}
int queid(int l,int r){
	int k=__lg(r-l+1);
	return mmax(st[k][l],st[k][r-(1<<k)+1]);
}
int pl[maxn],pr[maxn],len[maxn],lson[maxn],rson[maxn];
int sovle(int l,int r){
	if(l>r)return 0;
	int p=queid(l,r);pl[p]=l,pr[p]=r,len[p]=r-l+1;
	lson[p]=sovle(l,p-1),rson[p]=sovle(p+1,r);
	return p;
}
ll val[maxn];
void sovle1(int l,int r){
	if(l>r)return ;
	int p=queid(l,r);
	sovle1(l,p-1),sovle1(p+1,r);
	rt[p]=merge(rt[lson[p]],rt[rson[p]],1,maxn-10);
	val[p]=query(rt[p],1,maxn-10,a[p])+len[p]*a[p];
	ans=max(ans,val[p]);
	updata(rt[p],1,maxn-10,{-len[p],len[p]*a[p]});
}
void sovle2(int l,int r){
	if(l>r)return ;
	int p=queid(l,r);
	sovle2(l,p-1),sovle2(p+1,r);
	rt[p]=merge(rt[lson[p]],rt[rson[p]],1,maxn-10);
	ans=max(ans,query(rt[p],1,maxn-10,a[p])+len[p]*a[p]);
	updata(rt[p],1,maxn-10,{-len[p],val[p]});
}
vector<int> pos[maxn];
ll dp[maxn][4];
pii operator+(pii u,pii v){return {u.fi+v.fi,u.se+v.se};}
pii operator-(pii u,pii v){return {u.fi-v.fi,u.se-v.se};}
ll cross(pii u,pii v){return u.fi*v.se-u.se*v.fi;}
void insert(vector<pii> &a,pii p){
	while(a.size()>1&&cross(a[a.size()-1]-p,a[a.size()-2]-p)<=0)a.pop_back();
	a.pb(p);
}
ll calc(vector<pii> &a,int x){
	if(!a.size())return -inf;
	int l=0,r=a.size()-2,res=0;
	while(l<=r){
		int mm=l+r>>1;
		if(a[mm].fi*x+a[mm].se<=a[mm+1].fi*x+a[mm+1].se)res=mm+1,l=mm+1;
		else r=mm-1;
	}
	return a[res].fi*x+a[res].se;
}
vector<pii> conv(vector<pii> a,vector<pii> b){
	if(!a.size())return b;
	if(!b.size())return a;
	for(int i=a.size()-1;i;i--)a[i]=a[i]-a[i-1];
	for(int i=b.size()-1;i;i--)b[i]=b[i]-b[i-1];
	vector<pii> c;c.pb(a[0]+b[0]);
	int u=1,v=1;
	while(u<a.size()&&v<b.size()){
		if(cross(a[u],b[v])<0)c.pb(a[u++]);
		else c.pb(b[v++]);
	}
	while(u<a.size())c.pb(a[u++]);
	while(v<b.size())c.pb(b[v++]);
	for(int i=1;i<c.size();i++)c[i]=c[i]+c[i-1];
	return c;
}
vector<pii> merge(vector<pii> a,vector<pii> b){
	if(!a.size())return b;
	if(!b.size())return a;
	vector<pii> c;
	int u=0,v=0;
	while(u<a.size()&&v<b.size()){
		if(a[u]<b[v])c.pb(a[u++]);
		else c.pb(b[v++]);
	}
	while(u<a.size())c.pb(a[u++]);
	while(v<b.size())c.pb(b[v++]);
	return c;
}
vector<pii> vl[maxn],vr[maxn];
pair<vector<pii>,vector<pii>> sovle3(int l,int r){
	if(l==r)return {vl[l],vr[l]};
	auto pvl=sovle3(l,mid),pvr=sovle3(mid+1,r);
	pair<vector<pii>,vector<pii>> res={merge(pvl.fi,pvr.fi),merge(pvl.se,pvr.se)};
	vector<pii> resl,resr;
	for(auto p:pvl.se)insert(resl,p);
	for(auto p:pvr.fi)insert(resr,p);
	// cout<<l<<" "<<r<<" "<<res.fi.size()<<" "<<res.se.size()<<" s\n";
	if(resl.size()&&resr.size()){
		// for(auto[i,v]:resl)cout<<i<<" "<<v<<" l\n";
		// for(auto[i,v]:resr)cout<<i<<" "<<v<<" r\n";
		vector<pii> tmp=conv(resl,resr);
		// for(auto[i,v]:tmp)cout<<i<<" "<<v<<" tmp\n";
		for(auto[i,v]:tmp)val[i]=max(val[i],v);
	}
	return res;
}
ll ans1,ans2,ans3;
vector<long long> max_area(vector<int> H){
	n=H.size();for(int i=1;i<=n;i++)a[i]=H[i-1];
	
	for(int i=1;i<=n;i++)st[0][i]=i;
	for(int j=1;j<=18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=mmax(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	sovle(1,n);
	for(int i=1;i<=n;i++)ans=max(ans,a[i]*len[i]);
	ans1=ans;
	for(int i=1;i<=n;i++)f[pr[i]]=max(f[pr[i]],len[i]*a[i]);
	for(int i=1;i<=n;i++)f[i]=max(f[i],f[i-1]);
	for(int i=1;i<=n;i++)g[pl[i]]=max(g[pl[i]],len[i]*a[i]);
	for(int i=n;i;i--)g[i]=max(g[i],g[i+1]);
	for(int i=1;i<n;i++)ans=max(ans,f[i]+g[i+1]);
	sovle1(1,n);
	ans2=ans;
	for(int i=1;i<=n;i++)pos[pr[i]].pb(i);
	for(int i=1;i<=n;i++){
		for(int j=0;j<=3;j++)dp[i][j]=dp[i-1][j];
		for(int j=1;j<=3;j++){
			for(int k:pos[i])dp[i][j]=max(dp[i][j],dp[pl[k]-1][j-1]+len[k]*a[k]);
		}
	}
	ans=max(ans,dp[n][3]);
	for(int i=1;i<=n;i++)ans=max(ans,val[i]+max(f[pl[i]-1],g[pr[i]+1]));
	clr();sovle2(1,n);
	for(int i=1;i<=n;i++)val[i]=-inf;
	for(int i=1;i<=n;i++)vl[pl[i]].pb({len[i],len[i]*a[i]});
	for(int i=1;i<=n;i++)vr[pr[i]].pb({len[i],len[i]*a[i]});
	for(int i=1;i<=n;i++)sort(vl[i].begin(),vl[i].end());
	for(int i=1;i<=n;i++)sort(vr[i].begin(),vr[i].end());
	sovle3(1,n);
	vector<pii> res;
	// for(int i=1;i<=n;i++)if(val[i]!=-inf)cout<<i<<" "<<val[i]<<"\n";
	for(int i=1;i<=n;i++)if(val[i]!=-inf)insert(res,{i,val[i]});
	for(int i=1;i<=n;i++)ans=max(ans,calc(res,-a[i])+len[i]*a[i]);
	ans3=ans;
	
	return {ans1,ans2,ans3};
}

// int main() {
    // int N;
    // std::vector<int> H;
    // scanf("%d", &N);
    // for(int i = 0; i < N; i++) {
        // int h;
        // scanf("%d", &h);
        // H.push_back(h);
    // }
    // std::vector<long long> ans = max_area(H);
    // for(int i = 0; i < ans.size(); i++) {
        // printf("%lld\n", ans[i]);
    // }
    // return 0;
// }