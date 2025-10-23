#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<db,db>
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
const int maxn=150010;
const int maxm=600010;
const int inf=1e9;
bool mbe;

int n,q;
#define lb(x) (x&(-x))
struct seg{
	db k[maxn],b[maxn];
	void upd(int nd,db wk,db wb){k[nd]+=wk,b[nd]+=wb;}
	void updata(int nd,int l,int r,int ql,int qr,db wk,db wb){
		if(l>=ql&&r<=qr)return upd(nd,wk,wb);
		if(ql<=mid)updata(ls,l,mid,ql,qr,wk,wb);
		if(qr>mid)updata(rs,mid+1,r,ql,qr,wk,wb);
	}
	db query(int nd,int l,int r,int p){
		if(l==r)return k[nd]*p+b[nd];
		if(p<=mid)return query(ls,l,mid,p)+k[nd]*p+b[nd];
		else return query(rs,mid+1,r,p)+k[nd]*p+b[nd];
	}
}t1,t2;
db a[maxn],b[maxn],c[maxn],d[maxn];
db x[maxn],y[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
	q=read();
	for()
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