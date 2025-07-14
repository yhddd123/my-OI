#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
int mn[maxn<<6],num[maxn<<6],tag[maxn<<6];
int lc[maxn<<6],rc[maxn<<6],rt,idx;
void down(int nd){
	mn[ls]+=tag[nd],tag[ls]+=tag[nd];
	mn[rs]+=tag[nd],tag[rs]+=tag[nd];
	tag[nd]=0;
}
void updata(int &nd,int l,int r,int ql,int qr,int w){
	if(!nd)nd=++idx,num[nd]=r-l+1;
	if(l>=ql&&r<=qr){
		mn[nd]+=w,tag[nd]+=w;
		return ;
	}
	if(!ls)ls=++idx,num[ls]=mid-l+1;
	if(!rs)rs=++idx,num[rs]=r-mid;
	if(tag[nd])down(nd);
	if(ql<=mid)updata(ls,l,mid,ql,qr,w);
	if(qr>mid)updata(rs,mid+1,r,ql,qr,w);
	mn[nd]=min(mn[ls],mn[rs]);
	num[nd]=(mn[nd]==mn[ls])*num[ls]+(mn[nd]==mn[rs])*num[rs];
	// cout<<l<<" "<<r<<" "<<mn[nd]<<" "<<num[nd]<<"\n";
}
double sq;
map<pii,bool> vis;
void work(){
	n=read();m=read();sq=sqrt(2.0);
	for(int i=1;i<=n;i++){
		int u=read(),v=read();
		int uu=max(0ll,u-v),vv=min(m,u+v);
		// cout<<uu<<" "<<vv<<"\n";
		if(!vis[{u,v}]){
			vis[{u,v}]=1;
			updata(rt,1,m,uu+1,vv,1);
		}
		else{
			vis[{u,v}]=0;
			updata(rt,1,m,uu+1,vv,-1);
		}
		// cout<<num[1]<<"\n";
		printf("%.10lf\n",sq*(m-(!mn[1])*num[1]));
	}
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
