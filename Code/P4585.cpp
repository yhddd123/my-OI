#include<bits/stdc++.h>
using namespace std;
const int maxn=600010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m;
int rt[maxn],idx;
int tree[maxn<<5][2],val[maxn<<5];
void upd(int &x,int nd1,int v){
	x=++idx;int nd=x;
	for(int i=18;i>=0;i--){
		int u=(v>>i)&1;
		tree[nd][!u]=tree[nd1][!u];
		tree[nd][u]=++idx;
		val[tree[nd][u]]=val[tree[nd1][u]]+1;
		nd=tree[nd][u];nd1=tree[nd1][u];
	}
}
int query(int nd,int nd1,int w){
	int res=0;
	for(int i=18;i>=0;i--){
		int u=(w>>i)&1;
		if(val[tree[nd1][!u]]>val[tree[nd][!u]]){
			nd=tree[nd][!u];nd1=tree[nd1][!u];
			res+=(1<<i);
		}
		else nd=tree[nd][u],nd1=tree[nd1][u];
	}
	return res;
}
int cnt1,cnt2,ans[maxn];
struct ask{
	int l,r,tl,tr,val;
}p[maxn];
struct nd{
	int s,v,t;
}e[maxn],el[maxn],er[maxn];
bool cmp(nd u,nd v){return u.s<v.s;}
vector<int> id[maxn];
void updata(int nd,int l,int r,int ql,int qr,int idx){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		id[nd].push_back(idx);
		return ;
	}
	int mid=l+r>>1,ls=nd<<1,rs=nd<<1|1;
	if(ql<=mid)updata(ls,l,mid,ql,qr,idx);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,idx);
}
int st[maxn],tp;
void dfs(int nd,int l,int r,int tl,int tr){
	if(l>r)return ;
	tp=idx=0;
	for(int i=l;i<=r;i++){
		st[++tp]=e[i].s;
		upd(rt[tp],rt[tp-1],e[i].v);
	}
	for(int x:id[nd]){
		int l=upper_bound(st+1,st+tp+1,p[x].l-1)-st-1;
		int r=upper_bound(st+1,st+tp+1,p[x].r)-st-1;
		ans[x]=max(ans[x],query(rt[l],rt[r],p[x].val));
	}
	if(tl==tr)return ;
	int mid=tl+tr>>1,ls=nd<<1,rs=nd<<1|1;
	int c1=0,c2=0;
	for(int i=l;i<=r;i++){
		if(e[i].t<=mid)el[++c1]=e[i];
		else er[++c2]=e[i];
	}
	for(int i=1;i<=c1;i++)e[l+i-1]=el[i];
	for(int i=1;i<=c2;i++)e[l+c1+i-1]=er[i];
	dfs(ls,l,l+c1-1,tl,mid);dfs(rs,l+c1,r,mid+1,tr);
}

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++){
		int u=read();
		upd(rt[i],rt[i-1],u);
	}
	for(int i=1;i<=m;i++){
		int opt,u,v,uu,vv;
		opt=read();
		if(opt){
			u=read();v=read();uu=read();vv=read();
			p[++cnt2]={u,v,max(1,cnt1-vv+1),cnt1,uu};
			ans[cnt2]=query(rt[u-1],rt[v],uu);
		}
		else{
			u=read();v=read();
			e[++cnt1]={u,v,cnt1};
		}
	}
	for(int i=1;i<=cnt2;i++)updata(1,1,cnt1,p[i].tl,p[i].tr,i);
	sort(e+1,e+cnt1+1,cmp);
	dfs(1,1,cnt1,1,cnt1);
	for(int i=1;i<=cnt2;i++)printf("%d\n",ans[i]);
}
