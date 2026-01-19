#include<bits/stdc++.h>
// #define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
inline void write(int x){static char buf[20];static int len=-1;if(x<0)putchar('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)putchar(buf[len--]+48);}
const int maxn=500010;
const int inf=1e9;
bool mbe;

int Tim;

int n,m,q,w[maxn];
int ql[maxn],qr[maxn];
vector<int> e[maxn];
int p[maxn];
int fa[maxn],siz[maxn],son[maxn],dep[maxn];
void dfs(int u){
	siz[u]++;son[u]=0;dep[u]=dep[fa[u]]+1;
	for(int v:e[u]){
		dfs(v);siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])son[u]=v;
	}
}
int dfn[maxn],rnk[maxn],idx,top[maxn];
void dfs(int u,int lst){
	rnk[dfn[u]=++idx]=u;top[u]=lst;
	if(!son[u])return ;dfs(son[u],lst);
	for(int v:e[u])if(v!=son[u])dfs(v,v);
}
struct node{
	int s0,s1,fl;
}ans[maxn];
inline void inc(node &u,const node v){
	if(v.fl)swap(u.s0,u.s1);
	u.s0+=v.s0,u.s1+=v.s1,u.fl^=v.fl;
}
inline void inc1(node &u,const int v){v?(u.s0+=v):(swap(u.s0,u.s1),u.fl^=1);}
vector<int> ask[maxn],add[maxn];
int a[maxn<<1],b[maxn<<1],cnt;
pii que[maxn];int qq;
const int BB=800;
int lsh[maxn],len;
struct bit{
#define lb(x) (x&(-x))
	bool tree[maxn];
	inline void upd(int x){
		while(x<=n)tree[x]^=1,x+=lb(x);
	}
	inline bool que(int x){
		bool res=0;
		while(x)res^=tree[x],x-=lb(x);
		return res;
	}
	inline bool que(int l,int r){return que(r)^que(l-1);}
}t;
const int maxm=1210;
int tx[maxm],ty[maxm];
int id[maxm*maxm],tim;
inline int &get(int u,int v){return id[u*len+v];}
int to[maxm*maxm];
node val[maxm*maxm];
struct opt{
	int x,y,w;
}upd[maxn<<1];int uu;
inline void mdf(int x,node &w){if(x)inc(val[x],w);}
inline void mdf1(int x,int &w){if(x)inc1(val[x],w);}
int tmpx[maxm],tmpy[maxm];
int _idx[12][maxm],_idy[12][maxm],_tpx[12],_tpy[12];
void sovle(int l,int r,int d=0){
	int *idx=_idx[d],*idy=_idy[d];
	int &tpx=_tpx[d],&tpy=_tpy[d];
	if(1ll*tpx*tpy<=BB){
		for(int i=1;i<=tpx;i++)tmpx[idx[i]]=i;
		for(int i=1;i<=tpy;i++)tmpy[idy[i]]=i;
		for(int i=l;i<=r;i++){
			auto[x,y,w]=upd[i];
			int px=tmpx[x],py=tmpy[y];
			for(int j=1;j<=px;j++){
				for(int k=py;k<=tpy;k++)mdf1(get(idx[j],idy[k]),w);
			}
		}
		return ;
	}
	if(l==r){
		// cout<<l<<" "<<upd[l].w<<" "<<id[upd[l].x][upd[l].y]<<" sov\n";
		return mdf1(get(upd[l].x,upd[l].y),upd[l].w);
	}
	auto add=[&](){
		for(int i=tpx,lstx=len+1;i;i--){
			int x=idx[i];
			if(tx[x])lstx=x;
			else tmpx[x]=lstx;
		}
		for(int i=1,lsty=0;i<=tpy;i++){
			int y=idy[i];
			if(ty[y])lsty=y;
			else tmpy[y]=lsty;
		}
		for(int i=tpx;i;i--){
			int x=idx[i];
			int lstx=tx[x]?x:tmpx[x];
			if(lstx==len+1)continue;
			for(int j=1;j<=tpy;j++){
				int y=idy[j];
				int lsty=ty[y]?y:tmpy[y];
				if(lsty==0)continue;
				if(!tx[x]||!ty[y]){
					int &id1=get(x,y),&id2=get(lstx,lsty);
					if(id1&&id2){
						val[++tim]={0,0,0};
						// cout<<x<<" "<<y<<" "<<lstx<<" "<<lsty<<" a\n";
						to[x*len+y]=id1,id2=tim;
					}
				}
			}
		}
	};
	auto del=[&](){
		for(int i=1;i<=tpx;i++){
			int x=idx[i];
			int lstx=tx[x]?x:tmpx[x];
			if(lstx==len+1)continue;
			for(int j=tpy;j;j--){
				int y=idy[j];
				int lsty=ty[y]?y:tmpy[y];
				if(lsty==0)continue;
				if(!tx[x]||!ty[y]){
					int &id1=get(x,y),&id2=get(lstx,lsty);
					if(id1&&id2){
						mdf(id1,val[tim]);
						mdf(id2=to[x*len+y],val[tim]);
						tim--;
					}
					// cout<<x<<" "<<y<<" "<<lstx<<" "<<lsty<<" d\n";
				}
			}
		}
	};
	
	int *nwx=_idx[d+1],*nwy=_idy[d+1];
	int &nwtpx=_tpx[d+1],&nwtpy=_tpy[d+1];
	
	int mid=l+r>>1;
	for(int i=mid+1;i<=r;i++)tx[upd[i].x]--,ty[upd[i].y]--;
	add();
	{
		nwtpx=0;for(int i=1;i<=tpx;i++){
			int x=idx[i];
			if(tx[x])nwx[++nwtpx]=x;
		}
		nwtpy=0;for(int i=1;i<=tpy;i++){
			int y=idy[i];
			if(ty[y])nwy[++nwtpy]=y;
		}
		sovle(l,mid,d+1);
	}
	del();
	for(int i=mid+1;i<=r;i++)tx[upd[i].x]++,ty[upd[i].y]++;
	for(int i=l;i<=mid;i++)tx[upd[i].x]--,ty[upd[i].y]--;
	add();
	{
		nwtpx=0;for(int i=1;i<=tpx;i++){
			int x=idx[i];
			if(tx[x])nwx[++nwtpx]=x;
		}
		nwtpy=0;for(int i=1;i<=tpy;i++){
			int y=idy[i];
			if(ty[y])nwy[++nwtpy]=y;
		}
		sovle(mid+1,r,d+1);
	}
	del();
	for(int i=l;i<=mid;i++)tx[upd[i].x]++,ty[upd[i].y]++;
	// cout<<l<<" "<<r<<" "<<id[1][1]<<" s\n";
}
pii qql[maxn],qqr[maxn];
int lshl[maxn],lshr[maxn];
void sovle(){
	if(!qq)return ;
	// for(int i=1;i<=cnt;i++)cout<<a[i]<<" "<<b	[i]<<"\n";
	if(cnt<=BB){
		for(int i=1;i<=qq;i++){
			auto[p,id]=que[i];
			for(int j=1;j<=p;j++){
				if(a[j]>0)inc1(ans[id],a[j]);
				if(a[j]==0&&ql[id]<=b[j]&&b[j]<=qr[id])inc1(ans[id],0);
			}
			for(int j=p+1;j<=cnt;j++){
				if(ql[id]<=b[j]&&b[j]<=qr[id])inc1(ans[id],0);
			}
		}
		return ;
	}
	int B=max(1.0,sqrt(cnt)*1.2);
	// int B=4;
	for(int i=1;i<=qq;i++)qql[i]={ql[que[i].se],que[i].se},qqr[i]={qr[que[i].se],que[i].se};
	sort(qql+1,qql+qq+1),sort(qqr+1,qqr+qq+1);
	for(int i=1;i<=cnt;i++)if(b[i])t.upd(b[i]);
	// cout<<cnt<<" "<<"S"<<endl;
	for(int l=1,r,j=0;l<=cnt;l=r+1){
		r=min(l+B-1,cnt);
		for(int i=l;i<=r;i++){
			if(b[i])t.upd(b[i]);
			while(j<qq&&que[j+1].fi==i){
				auto[p,id]=que[++j];
				for(int j=l;j<=p;j++){
					if(a[j]>0)inc1(ans[id],a[j]);
					if(a[j]==0&&ql[id]<=b[j]&&b[j]<=qr[id])inc1(ans[id],0);
				}
				if(t.que(ql[id],qr[id]))inc1(ans[id],0);
			}
		}
		// cout<<l<<" "<<r<<endl;
		if(j<qq){
			len=0;for(int i=l;i<=r;i++)if(a[i]==0&&b[i])lsh[++len]=b[i];lsh[++len]=1,lsh[++len]=m;
			sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
			tim=0;
			for(int i=1;i<=len;i++){
				for(int j=i-1;j<=len;j++){
					val[++tim]={0,0,0},get(i,j)=tim;
				}
			}
			val[++tim]={0,0,0},get(len,1)=tim;
			uu=0;
			for(int i=l;i<=r;i++){
				if(b[i]){
					if(a[i]==0){
						int bb=lower_bound(lsh+1,lsh+len+1,b[i])-lsh;
						if(uu&&!upd[uu].w&&upd[uu].x==bb)uu--;
						else upd[++uu]={bb,bb,0};
					}
				}
				else{
					if(uu&&upd[uu].w)upd[uu].w+=a[i];
					else upd[++uu]={len,1,a[i]};
				}
			}
			// cout<<len<<" "<<tim<<" "<<uu<<endl;
			for(int i=1;i<=uu;i++){
				auto[x,y,w]=upd[i];
				tx[x]++,ty[y]++;
			}
			int *idx=_idx[0],*idy=_idy[0];_tpx[0]=_tpy[0]=len;
			for(int i=1;i<=len;i++)idx[i]=i,idy[i]=i;
			sovle(1,uu,0);
			for(int i=1;i<=uu;i++){
				auto[x,y,w]=upd[i];
				tx[x]--,ty[y]--;
			}
			for(int i=1,k=1;i<=qq;i++){
				while(lsh[k]<qql[i].fi)k++;
				lshl[qql[i].se]=k;
			}
			for(int i=1,k=1;i<=qq;i++){
				while(k<len&&lsh[k+1]<=qqr[i].fi)k++;
				lshr[qqr[i].se]=k;
			}
			for(int k=j+1;k<=qq;k++){
				int i=que[k].se;
				int idd=get(lshl[i],lshr[i]);
				// cout<<i<<" "<<lshl[i]<<" "<<lshr[i]<<" "<<idd<<" "<<val[idd].s0<<" "<<val[idd].s1<<" "<<val[idd].fl<<"\n";
				inc(ans[i],val[idd]);
			}
		}
		// cout<<l<<" "<<r<<" s\n";
		// for(int i=1;i<=qq;i++)cout<<ans[i].s0<<" "<<ans[i].s1<<" "<<ans[i].fl<<"\n";
	}
}
void work(){
	n=read();m=read();q=read();
	for(int i=2;i<=n;i++)fa[i]=read(),e[fa[i]].pb(i);
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=m;i++)p[i]=read(),siz[p[i]]++;
	dfs(1),dfs(1,1);
	for(int i=1;i<=m;i++){
		int u=p[i];
		while(u)add[u].pb(i),u=fa[top[u]];
	}
	for(int i=1;i<=q;i++){
		ql[i]=read(),qr[i]=read();
		int u=read();
		while(u)ask[u].pb(i),u=fa[top[u]];
	}
	for(int i=1;i<=n;i++)if(top[i]==i){
		cnt=qq=0;
		int u=i;
		while(u){
			a[++cnt]=w[u],b[cnt]=0;
			for(int v:ask[u])que[++qq]={cnt,v};
			for(int v:add[u])a[++cnt]=(p[v]==u?0:-1),b[cnt]=v;
			u=son[u];
		}
		sovle();
		// cout<<i<<" s\n";
		// for(int i=1;i<=q;i++)cout<<ans[i].s0<<" "<<ans[i].s1<<" "<<ans[i].fl<<"\n";
	}
	for(int i=1;i<=q;i++)write(ans[i].s1),puts("");
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