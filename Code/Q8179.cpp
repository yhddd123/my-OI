#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=400010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,ans[maxn];
struct nd{
	int x,y,id,fl;
	bool operator<(const nd&tmp)const{return x<tmp.x||(x==tmp.x&&y<tmp.y);}
}a[maxn];
multiset<nd> s;
struct ask{
	int p,l,r,fl;
	ull val;
}que[maxn];
int lsh[maxn],len;
#define mid (l+r>>1)
#define ls nd<<1
#define rs nd<<1|1
bool vis[maxn<<2];
ull tree[maxn<<2],tag[maxn<<2];
void down(int nd){
	tree[ls]^=tag[nd],tag[ls]^=tag[nd];
	tree[rs]^=tag[nd],tag[rs]^=tag[nd];
	tag[nd]=0;
}
void updata(int nd,int l,int r,int ql,int qr,ull w){
	if(ql>qr)return ;
	if(l>=ql&&r<=qr){
		tree[nd]^=w,tag[nd]^=w;
		return ;
	}
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls];vis[nd]=vis[ls]&&vis[rs]&&(tree[ls]==tree[rs]);
	// cout<<l<<" "<<r<<" "<<tree[nd]<<" "<<vis[nd]<<"\n";
}
bool fl;ull lst;
bool query(int nd,int l,int r,int ql,int qr){
	if(ql>qr||qr<l||ql>r)return 1;
	if(l>=ql&&r<=qr){
		if(!fl)lst=tree[nd],fl=1;
		// cout<<l<<" "<<r<<" "<<lst<<" "<<tree[nd]<<" "<<vis[nd]<<"\n";
		return vis[nd]&&(lst==tree[nd]);
	}
	if(tag[nd])down(nd);
	return query(ls,l,mid,ql,qr)&&query(rs,mid+1,r,ql,qr);
}
mt19937 rnd(1);
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]={read(),read(),i,0};
	for(int i=1;i<=n;i++)a[n+i]={read(),read(),i,1};
	sort(a+1,a+2*n+1,[&](nd u,nd v){
		if(u.y==v.y){
			if(u.fl==v.fl)return u.x<v.x;
			return u.fl>v.fl;
		}
		return u.y<v.y;
	});
	for(int i=1;i<=2*n;i++){
		if(!a[i].fl)s.insert(a[i]);
		else{
			if(!s.size()){printf("No\n");return ;}
			auto it=s.lower_bound({a[i].x-1,a[i].y,a[i].id,a[i].fl});
			if(it==s.begin()){printf("No\n");return ;}
			it--;ans[(*it).id]=a[i].id;s.erase(it);
		}
	}
	sort(a+1,a+2*n+1,[&](nd u,nd v){
		if(u.fl==v.fl)return u.id<v.id;
		return u.fl<v.fl;
	});
	for(int i=1;i<=n;i++){
		ull val=rnd();
		que[i]={a[i].x,a[i].y,a[ans[i]+n].y-1,1,val};
		que[i+n]={a[ans[i]+n].x,a[i].y,a[ans[i]+n].y-1,0,val};
		lsh[++len]=a[i].y,lsh[++len]=a[ans[i]+n].y-1;
	}
	sort(lsh+1,lsh+len+1);len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<=2*n;i++)que[i].l=lower_bound(lsh+1,lsh+len+1,que[i].l)-lsh;
	for(int i=1;i<=2*n;i++)que[i].r=lower_bound(lsh+1,lsh+len+1,que[i].r)-lsh;
	sort(que+1,que+2*n+1,[&](ask u,ask v){
		if(u.p==v.p){
			if(u.fl!=v.fl)return u.fl<v.fl;
			if(u.fl)return u.r-u.l>v.r-v.l;
			return u.r-u.l<v.r-v.l;
		}
		return u.p<v.p;
	});
	mems(vis,1);
	for(int i=1;i<=2*n;i++){
		updata(1,1,len,que[i].l,que[i].r,que[i].val);
		// cout<<que[i].l<<" "<<que[i].r<<"\n";
		fl=0;if(!query(1,1,len,que[i].l,que[i].r)){printf("No\n");return ;}
		// cout<<i<<"\n";
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
