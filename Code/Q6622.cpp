#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1<<22];
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
static int opos=0;
inline void flush_out(){fwrite(obuf,1,opos,stdout);opos=0;}
inline void pc(char c){if(opos == (1<<22))flush_out();obuf[opos++]=c;}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)pc('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)pc(buf[len--]+48);}
const int maxm=100010;
const int B=800;
const int maxn=B+5;
const int maxd=16;
const ll inf=1e18;
bool mbe;

int n;
struct node{
	int x,y,z00,z01,z10,z11;
}ask[maxm],tmp[maxm];
int tx[maxn],ty[maxn];
int lshx[maxn],lenx,lshy[maxn],leny;
ll mx[maxn*maxn<<1],tag[maxn*maxn<<1];
inline void upd(int u,ll w){mx[u]+=w,tag[u]+=w;}
int id[maxn][maxn],idx;
int to[maxn*maxn<<1];
void merge(int &x,int &y){
	++idx;mx[idx]=max(mx[x],mx[y]),tag[idx]=0;
	to[y]=x,x=idx;
}
void redo(int &x,int &y){
	upd(to[y],tag[idx]),upd(y,tag[idx]),idx--;
	x=to[y];
}
int _idx[maxd][maxn],_idy[maxd][maxn],_tpx[maxd],_tpy[maxd];
int _tmpx[maxd][maxn],_tmpy[maxd][maxn];
void sovle(int l,int r,int d){
	int *idx=_idx[d],*idy=_idy[d];
	int &tpx=_tpx[d],&tpy=_tpy[d];
	
	if(l==r){
		auto[x,y,z00,z01,z10,z11]=ask[l];
		write(mx[id[1][1]]),pc('\n');
		write(mx[id[1][y]]),pc('\n');
		write(mx[id[x][1]]),pc('\n');
		write(mx[id[x][y]]),pc('\n');
		upd(id[1][1],z00),upd(id[1][y],z01),upd(id[x][1],z10),upd(id[x][y],z11);
		return ;
	}
	int mid=l+r>>1;
	
	int *tmpx=_tmpx[d],*tmpy=_tmpy[d];
	auto add=[&](){
		int *nwx=_idx[d+1],*nwy=_idy[d+1];
		int &nwtpx=_tpx[d+1],&nwtpy=_tpy[d+1];
		nwtpx=0;for(int i=1;i<=tpx;i++){
			int x=idx[i];
			if(tx[x])nwx[++nwtpx]=x;
		}
		nwtpy=0;for(int i=1;i<=tpy;i++){
			int y=idy[i];
			if(ty[y])nwy[++nwtpy]=y;
		}
		
		for(int i=1,lst=0;i<=tpx;i++){
			int x=idx[i];
			if(tx[x])lst=x;
			tmpx[i]=lst;
		}
		for(int i=1,lst=0;i<=tpy;i++){
			int y=idy[i];
			if(ty[y])lst=y;
			tmpy[i]=lst;
		}
		for(int i=1;i<=tpx;i++){
			int x=idx[i],xx=tmpx[i];
			for(int j=1;j<=tpy;j++){
				int y=idy[j],yy=tmpy[j];
				if(!tx[x]||!ty[y]){
					merge(id[xx][yy],id[x][y]);
					// cout<<xx<<" "<<yy<<" "<<x<<" "<<y<<" m\n";
				}
			}
		}
	};
	auto del=[&](){
		for(int i=tpx;i>=1;i--){
			int x=idx[i],xx=tmpx[i];
			for(int j=tpy;j>=1;j--){
				int y=idy[j],yy=tmpy[j];
				if(!tx[x]||!ty[y])redo(id[xx][yy],id[x][y]);
			}
		}
	};
	
	for(int i=mid+1;i<=r;i++)tx[ask[i].x]--,ty[ask[i].y]--;
	add();
	sovle(l,mid,d+1);
	del();
	for(int i=mid+1;i<=r;i++)tx[ask[i].x]++,ty[ask[i].y]++;
	for(int i=l;i<=mid;i++)tx[ask[i].x]--,ty[ask[i].y]--;
	add();
	sovle(mid+1,r,d+1);
	del();
	for(int i=l;i<=mid;i++)tx[ask[i].x]++,ty[ask[i].y]++;
}

struct Tag{
	ll tag,htag;bool fl;
	operator bool(){return tag||htag||fl;}
};
Tag operator*(Tag u,Tag v){return {u.tag+v.tag,v.fl?u.tag+v.htag:max(u.tag+v.htag,u.htag),u.fl||v.fl};}
struct Node{
	ll mx,his;
};
Node operator*(Node u,Tag v){return {u.mx+v.tag,v.fl?u.mx+v.htag:max(u.mx+v.htag,u.his)};}
Node operator+(Node u,Node v){return {max(u.mx,v.mx),max(u.his,v.his)};}
namespace sgt{
#define mid ((l+r)>>1)
#define ls lc[nd]
#define rs rc[nd]
Tag tag[maxm<<1];
Node tree[maxm<<1];
int lc[maxm<<1],rc[maxm<<1],idx,rt;
int pos[maxn],pl[maxm<<1],pr[maxm<<1];
ll val[maxm];
void buildsgt(int &nd,int l,int r){
	if(!nd)nd=++idx;ls=rs=0;tree[nd]={0,0},tag[nd]={0,0,0};
	if(l==r){tree[nd]={val[l],val[l]};return ;}
	buildsgt(ls,l,mid),buildsgt(rs,mid+1,r);
	tree[nd]=tree[ls]+tree[rs];
}
void build(int &nd,int l,int r){
	if(!nd)nd=++idx;ls=rs=0;tree[nd]={0,0},tag[nd]={0,0,0};
	pl[nd]=lshy[l],pr[nd]=lshy[r+1]-1;
	if(l==r){pos[l]=nd;return buildsgt(nd,pl[nd],pr[nd]);}
	build(ls,l,mid),build(rs,mid+1,r);	
	tree[nd]=tree[ls]+tree[rs];
}
inline void upd(int nd,Tag w){tree[nd]=tree[nd]*w,tag[nd]=tag[nd]*w;}
inline void down(int nd){upd(ls,tag[nd]),upd(rs,tag[nd]),tag[nd]={0,0,0};}
void updatasgt(int nd,int l,int r,int ql,int qr,int w){
	if(l>=ql&&r<=qr)return upd(nd,{w,w,0});
	if(tag[nd])down(nd);
	if(ql<=mid)updatasgt(ls,l,mid,ql,qr,w);
	if(qr>mid)updatasgt(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
void updata(int nd,int l,int r,int ql,int qr,int w){
	if(pl[nd]>=ql&&pr[nd]<=qr)return upd(nd,{w,w,0});
	if(l==r)return updatasgt(nd,pl[nd],pr[nd],ql,qr,w);
	if(tag[nd])down(nd);
	if(ql<=pr[ls])updata(ls,l,mid,ql,qr,w);
	if(qr>=pl[rs])updata(rs,mid+1,r,ql,qr,w);
	tree[nd]=tree[ls]+tree[rs];
}
void down(int nd,int l,int r){
	if(l==r)return ;
	if(tag[nd])down(nd);
	down(ls,l,mid),down(rs,mid+1,r);
}
vector<tuple<int,int,int>> mdf[maxm];
void init(int p){
	for(int i=1;i<=n;i++)mdf[i].clear(),val[i]=0;
	for(int i=1;i<=p;i++){
		auto[x,y,z00,z01,z10,z11]=ask[i];
		val[1]+=z00,val[y]+=z01-z00;
		mdf[x].pb({1,y-1,z10-z00});
		mdf[x].pb({y,n,z11-z01});
	}
	for(int i=1;i<=n;i++)sort(mdf[i].begin(),mdf[i].end(),[&](auto u,auto v){return get<2>(u)<get<2>(v);});
	for(int i=1;i<=n;i++)val[i]+=val[i-1];
	rt=idx=0;build(rt,1,leny);
	for(int i=1;i<=lenx;i++){
		for(auto[l,r,w]:mdf[lshx[i]])updata(rt,1,leny,l,r,w);
		upd(rt,{0,0,1});
		for(int j=lshx[i]+1;j<lshx[i+1];j++){
			for(auto[l,r,w]:mdf[j])updata(rt,1,leny,l,r,w);
		}
		down(rt,1,leny);
		for(int j=1;j<=leny;j++)mx[id[i][j]]=tree[pos[j]].his;
	}
}
}

void work(){
	n=read();
	for(int i=1;i<=n;i++){
		ask[i]={read(),read(),read(),read(),read(),read()};
	}
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+B-1,n);
		// cout<<l<<" "<<r<<endl;
		lenx=leny=0;
		for(int i=l;i<=r;i++){
			int x=ask[i].x,y=ask[i].y;
			lshx[++lenx]=x,lshy[++leny]=y;
		}
		lshx[++lenx]=1,lshy[++leny]=1;
		sort(lshx+1,lshx+lenx+1),lenx=unique(lshx+1,lshx+lenx+1)-lshx-1;
		sort(lshy+1,lshy+leny+1),leny=unique(lshy+1,lshy+leny+1)-lshy-1;
		lshx[lenx+1]=n+1,lshy[leny+1]=n+1;
		idx=0;
		for(int i=1;i<=lenx;i++){
			for(int j=1;j<=leny;j++){
				mx[id[i][j]=++idx]=0;tag[idx]=0;
			}
		}
		sgt::init(l-1);
		// for(int i=1;i<=lenx;i++){
			// for(int j=1;j<=leny;j++)cout<<mx[id[i][j]]<<" ";
			// cout<<endl;
		// }
		for(int i=1;i<=lenx;i++)tx[i]=0;
		for(int i=1;i<=leny;i++)ty[i]=0;
		for(int i=l;i<=r;i++){
			ask[i].x=lower_bound(lshx+1,lshx+lenx+1,ask[i].x)-lshx;
			ask[i].y=lower_bound(lshy+1,lshy+leny+1,ask[i].y)-lshy;
			tx[ask[i].x]++,ty[ask[i].y]++;
		}
		tx[1]++,ty[1]++;
		_tpx[0]=0;for(int i=1;i<=lenx;i++)_idx[0][++_tpx[0]]=i;
		_tpy[0]=0;for(int i=1;i<=leny;i++)_idy[0][++_tpy[0]]=i;
		sovle(l,r,0);
		for(int i=l;i<=r;i++){
			ask[i].x=lshx[ask[i].x],ask[i].y=lshy[ask[i].y];
		}
	}
	flush_out();
}

bool med;
signed main(){
	// freopen("matrix.in","r",stdin);
	// freopen("matrix.out","w",stdout);
	
	cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	int T=1;
	while(T--)work();
}