// Problem: P11983 [JOIST 2025] 展览会 3 / Exhibition 3
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11983
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-12-04 18:01:39
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
const int inf=1e9;
bool mbe;

int n,m,t[maxn],lst;
pii a[maxn];
int ans[maxn];
#define mid ((l+r)>>1)
#define ls nd<<1
#define rs nd<<1|1
struct heap{
	priority_queue<int,vector<int>,greater<int>> q1,q2;
	void ins(int id){q1.push(id);}
	void del(int id){q2.push(id);}
	int top(){
		while(q2.size()&&q1.top()==q2.top())q1.pop(),q2.pop();
		return !q1.size()?inf:q1.top();
	}
}tree[maxn<<2];
int mn[maxn<<2];
void build(int nd,int l,int r){
	mn[nd]=inf;
	if(l==r)return ;
	build(ls,l,mid),build(rs,mid+1,r);
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr){
		if(w>0)tree[nd].ins(w);
		else tree[nd].del(-w);
		mn[nd]=l==r?tree[nd].top():min({mn[ls],mn[rs],tree[nd].top()});
		return ;
	}
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min({mn[ls],mn[rs],tree[nd].top()});
}
int query(int nd,int l,int r,int ql,int qr){
	if(l>=ql&&r<=qr)return mn[nd];
	int res=tree[nd].top();
	if(ql<=mid)res=min(res,query(ls,l,mid,ql,qr));
	if(qr>mid)res=min(res,query(rs,mid+1,r,ql,qr));
	return res;
}
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int id[maxn];
int chk(int k){
	if(k>lst)return inf;
	for(int i=1,p=fd(1);i<=k;i++,p=fd(p+1))id[i]=p;
	// for(int i=1;i<=k;i++)cout<<id[i]<<" ";cout<<endl;
	sort(id+1,id+k+1,[&](int u,int v){return a[u].se<a[v].se;});
	int num=0;for(int i=1,p=0;i<=k;i++)if(p<a[id[i]].fi)++num,p=a[id[i]].se;
	return num;
}
int pl[maxn],pr[maxn],num;
priority_queue<pii> ql[maxn],qr[maxn];
void rebuild(int p){
	if(p>1){
		int lst=pl[p-1];
		while(!ql[p-1].empty()&&-(ql[p-1].top()).fi<pl[p])pl[p-1]=max(pl[p-1],(ql[p-1].top()).se),ql[p-1].pop();
		if(lst!=pl[p-1])rebuild(p-1);
	}
	if(p+1<=num){
		int lst=pr[p+1];
		while(!qr[p+1].empty()&&(qr[p+1].top()).fi>pr[p])pr[p+1]=min(pr[p+1],(qr[p+1].top()).se),qr[p+1].pop();
		if(lst!=pr[p+1])rebuild(p+1);
	}
}
void del(int id,int w){
	int ll=lower_bound(pr+1,pr+num+1,a[id].fi)-pr,rr=upper_bound(pl+1,pl+num+1,a[id].se)-pl-1;
	// cout<<id<<" "<<w<<" "<<ll<<" "<<rr<<endl;
	if(ll>rr){
		updata(1,1,n,a[id].fi,a[id].se,id);
		return ;
	}
	ff[id]=fd(id+1),ans[id]=w;lst--;
	if(ll==rr){
		pl[ll]=max(pl[ll],a[id].fi),pr[rr]=min(pr[rr],a[id].se);
		rebuild(ll);
	}
	else{
		ql[ll].push({-a[id].se,a[id].fi});
		qr[rr].push({a[id].fi,a[id].se});
	}
}
priority_queue<pii,vector<pii>,greater<pii>> q;
void mdf(int p){
	int id=query(1,1,n,pl[p],pr[p]);
	if(id==inf)return ;
	updata(1,1,n,a[id].fi,a[id].se,-id),q.push({id,p});
}
void work(){
	n=read();m=read();lst=m;
	for(int i=1;i<=n;i++)t[read()]++;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int l=read(),r=read();a[i]={l,r};
		updata(1,1,n,l,r,i);
	}
	for(int i=1;i<=m+1;i++)ff[i]=i;
	for(int v=n;v&&lst;v--)if(t[v]){
		int k=1;while(chk(2*k)<=t[v])k<<=1;
		for(int j=__lg(k)-1;~j;j--)if(chk(k+(1<<j))<=t[v])k+=(1<<j);
		num=chk(k);
		// cout<<v<<" "<<k<<" "<<num<<" "<<t[v]<<endl;
		// for(int i=1;i<=k;i++)cout<<id[i]<<" "<<a[id[i]].fi<<" "<<a[id[i]].se<<"\n";
		for(int i=1,p=0,nn=0;i<=k;i++)if(p<a[id[i]].fi)pr[++nn]=p=a[id[i]].se;
		sort(id+1,id+k+1,[&](int u,int v){return a[u].fi>a[v].fi;});
		for(int i=1,p=n+1,nn=num+1;i<=k;i++)if(p>a[id[i]].se)pl[--nn]=p=a[id[i]].fi;
		// for(int i=1;i<=num;i++)cout<<pl[i]<<" "<<pr[i]<<"\n";
		for(int i=1;i<=k;i++)updata(1,1,n,a[id[i]].fi,a[id[i]].se,-id[i]),del(id[i],v);
		for(int i=1;i<=num;i++)mdf(i);
		while(!q.empty()){
			auto[id,p]=q.top();q.pop();mdf(p);
			if(ff[id]!=id)continue;
			del(id,v);
		}
		for(int i=1;i<=num;i++){
			priority_queue<pii>().swap(ql[i]);
			priority_queue<pii>().swap(qr[i]);
		}
	}
	for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
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