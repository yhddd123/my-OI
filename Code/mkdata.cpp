#include<bits/stdc++.h>
#define ll long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
using namespace std;
const int maxn=100010;
const ll inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,q,a[maxn];
int ask[maxn][3];
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
ll sum[maxn*400];int lc[maxn*400],rc[maxn*400],idx;
void updata(int &nd,int l,int r,int p,int w){
	if(!nd)nd=++idx;sum[nd]+=w;
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
}
ll query(int nd,int l,int r,int ql,int qr){
	if(!nd)return 0;
	if(l>=ql&&r<=qr)return sum[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return query(ls,l,mid,ql,qr)+query(rs,mid+1,r,ql,qr);
}
#define lb(x) (x&(-x))
int rt[maxn];
void upd(int x,int p,int val){
	while(x<=n){
		updata(rt[x],1,inf,p,val);
		x+=lb(x);
	}
}
ll que(int l,int r,int ql,int qr){
	int x=r;ll res=0;
	while(x){
		res+=query(rt[x],1,inf,ql,qr);
		x-=lb(x);
	}
	x=l-1;
	while(x){
		res-=query(rt[x],1,inf,ql,qr);
		x-=lb(x);
	}
	return res;
}
void work(){
	for(int i=1;i<=n;i++)upd(i,a[i],a[i]);
	for(int i=1;i<=q;i++){
		int op=ask[i][0],u=ask[i][1],v=ask[i][2];
		if(op==1){
			upd(u,a[u],-a[u]);
			a[u]=v;
			upd(u,a[u],a[u]);
		}
		else{
			ll sum=que(u,v,1,1);
			while(1){
				ll val=que(u,v,1,min(sum+1,inf));
				if(val>sum)sum=val;
				else break;
			}
			printf("%lld\n",sum+1);
		}
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
	
	freopen("10034_10.in","w",stdout);
	n=100000,q=100000;int w=inf;srand(time(0));
	cout<<n<<" "<<q<<"\n";
	for(int i=1;i<=n;i++){
		a[i]=1ll*rand()*rand()%w+1;
		if(i%1000==0)a[i]=1;
		cout<<a[i]<<" ";
	}
	cout<<"\n";
	for(int i=1;i<=q;i++){
		int op=rand()%2+1,u,v;
		if(i>=100)op=2;
		if(op==1){
			u=1ll*rand()*rand()%n+1,v=1ll*rand()*rand()%w+1;
		}
		else{
			u=1ll*rand()*rand()%n+1,v=1ll*rand()*rand()%n+1;
			if(u>v)swap(u,v);
		}
		ask[i][0]=op,ask[i][1]=u,ask[i][2]=v;
		cout<<op<<" "<<u<<" "<<v<<"\n";
	}
	freopen("10034_10.out","w",stdout);
	work();
}
