#include<bits/stdc++.h>
using namespace std;

namespace my{
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
const int maxn=150010;
const int maxq=500010;
const int infll=1e18;

#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
struct line{
	int k,b;
	int calc(int x){return k*x+b;}
}tree[maxn<<6];
int lc[maxn<<6],rc[maxn<<6],idx,rt;
void updata(int &nd,int l,int r,line w){
	if(!nd)tree[nd=++idx]={0,-infll};
	if(l==r){
		if(tree[nd].calc(l)<w.calc(l))tree[nd]=w;
		return ;
	}
	if(tree[nd].calc(mid)<w.calc(mid))swap(tree[nd],w);
	if(tree[nd].calc(l)<w.calc(l))updata(ls,l,mid,w);
	if(tree[nd].calc(r)<w.calc(r))updata(rs,mid+1,r,w);
}
void updata(int &nd,int l,int r,int ql,int qr,line w){
	if(!nd)tree[nd=++idx]={0,-infll};
	if(l>=ql&&r<=qr)return updata(nd,l,r,w);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
}
int query(int nd,int l,int r,int p){
	if(!nd)return -infll;
	if(l==r)return tree[nd].calc(p);
	if(p<=mid)return max(query(ls,l,mid,p),tree[nd].calc(p));
	else return max(query(rs,mid+1,r,p),tree[nd].calc(p));
}
void clr(){
	while(idx){
		lc[idx]=rc[idx]=0;
		idx--;
	}
	rt=0;
}


int n,m,q;
int a[maxn],b[maxn];
vector<pii> ask;
int lsh[maxn<<1],len;
int stk[maxn],tp;
int val[maxn<<1],l[maxn],r[maxn];
int res[maxn];
vector<int> upd[maxn],que[maxn];

int st[18][maxn];
int quemn(int l,int r){
	int k=__lg(r-l+1);
	return min(st[k][l],st[k][r-(1<<k)+1]);
}
#define lb(x) (x&(-x))
struct bit{
	int tree[maxn];
	void upd(int x,int w){
		while(x)tree[x]=max(tree[x],w),x-=lb(x);
	}
	int que(int x){
		int res=0;
		while(x<=m)res=max(res,tree[x]),x+=lb(x);
		return res;
	}
	void clr(){
		for(int i=1;i<=m;i++)tree[i]=0;
	}
}t;

vector<int> sovle(){
	for(int i=1;i<=n;i++)lsh[++len]=a[i];
	for(int i=1;i<=m;i++)lsh[++len]=b[i];
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
	for(int i=1;i<=m;i++)b[i]=lower_bound(lsh+1,lsh+len+1,b[i])-lsh;
	vector<int> ans(q);
	stk[tp=0]=0;for(int i=1;i<=n;i++){
		while(a[stk[tp]]>=a[i])tp--;
		l[i]=stk[tp]+1;stk[++tp]=i;
	}
	stk[tp=0]=n+1;for(int i=n;i;i--){
		while(a[stk[tp]]>=a[i])tp--;
		r[i]=stk[tp]-1;stk[++tp]=i;
		val[a[i]]=max(val[a[i]],r[i]-l[i]+1);
	}
	for(int i=len;i;i--)val[i]=max(val[i],val[i+1]);
	stk[tp=0]=0;for(int i=1;i<=m;i++){
		while(b[stk[tp]]>=b[i])tp--;
		l[i]=stk[tp]+1;stk[++tp]=i;
	}
	stk[tp=0]=m+1;for(int i=m;i;i--){
		while(b[stk[tp]]>=b[i])tp--;
		r[i]=stk[tp]-1;stk[++tp]=i;
	}
	for(int i=1;i<=m;i++)st[0][i]=b[i];
	for(int j=1;j<18;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
	}
	for(int i=0;i<q;i++){
		auto[l,r]=ask[i];
		que[quemn(l,r)].pb(i);
	}
	for(int i=1;i<=len;i++){
		updata(rt,1,len,{lsh[i],lsh[i]*val[i]});
		for(int j:que[i])ans[j]=max(ans[j],query(rt,1,m,ask[j].se-ask[j].fi+1));
	}
	clr();
	for(int i=1;i<=len;i++)que[i].clear();
	for(int i=1;i<=m;i++)que[b[i]].pb(i);
	for(int i=1;i<=len;i++){
		updata(rt,1,len,{lsh[i],lsh[i]*val[i]});
		for(int j:que[i])res[j]=max(res[j],query(rt,1,m,r[j]-l[j]+1));
	}
	clr();
	for(int i=1;i<=len;i++)que[i].clear();
	for(int i=1;i<=m;i++)upd[r[i]].pb(i);
	for(int i=0;i<q;i++)que[ask[i].se].pb(i);
	for(int i=1;i<=n;i++){
		for(int j:upd[i])t.upd(l[i],lsh[b[i]]);
		for(int j:que[i])ans[j]=max(ans[j],t.que(ask[j].fi));
	}
	for(int i=1;i<=m;i++)upd[i].clear(),que[i].clear();
	for(int j=0;j<q;j++){
		for(int i=1;i<=m;i++){
			if(l[i]<=ask[j].fi&&ask[j].fi<=r[i]&&r[i]<=ask[j].se){
				ans[j]=max(ans[j],(r[i]-ask[j].fi+1+val[b[i]])*lsh[b[i]]);
			}
			if(ask[j].fi<=l[i]&&l[i]<=ask[j].se&&ask[j].se<=r[i]){
				ans[j]=max(ans[j],(ask[j].se-l[i]+1+val[b[i]])*lsh[b[i]]);
			}
		}
	}
	int res=0;for(int i=1;i<=len;i++)res=max(res,val[i]*lsh[i]);
	for(int j=0;j<q;j++)ans[j]=max(ans[j],res);
	return ans;
}

#undef int
}

std::vector<long long> max_stability(std::vector<int> A, std::vector<int> B, std::vector<int> L, std::vector<int> R){
	my::n=A.size(),my::m=B.size(),my::q=L.size();
	for(int i=1;i<=my::n;i++)my::a[i]=A[i-1];
	for(int i=1;i<=my::m;i++)my::b[i]=B[i-1];
	for(int i=0;i<my::q;i++)my::ask.pb({L[i]+1,R[i]+1});
	return my::sovle();
}
void my_assert(bool x){ if(!x) { puts("invalid input"); exit(0); } } 

int main(){
    int N, M, Q;
	my_assert(scanf("%d%d%d", &N, &M, &Q) == 3);
	std::vector<int> A(N), B(M), L(Q), R(Q);
	for(int i = 0; i < N; i++) my_assert(scanf("%d",&A[i])==1);
	for(int i = 0; i < M; i++) my_assert(scanf("%d",&B[i])==1);
    for(int i = 0; i < Q; i++){
        my_assert(scanf("%d%d",&L[i],&R[i])==2);
    }
    auto res = max_stability(A,B,L,R);
    for(auto &t: res){
        printf("%lld\n",t);
    }
}