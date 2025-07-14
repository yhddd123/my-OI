#include<bits/stdc++.h>
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a,b;
char s[maxn];
int s1[maxn],s2[maxn];
int dp[maxn];
#define mid (l+r>>1)
#define ls lc[nd]
#define rs rc[nd]
#define lsn lson[nd]
#define rsn rson[nd]
int rt[maxn];
int id[maxn<<5],idx,lson[maxn<<5],rson[maxn<<5];
int tree[maxn*400],tim,lc[maxn*400],rc[maxn*400];
void updata(int &nd,int l,int r,int p,int w){
	if(!nd)nd=++tim,tree[nd]=inf;
	tree[nd]=min(tree[nd],w);
	if(l==r)return ;
	if(p<=mid)updata(ls,l,mid,p,w);
	else updata(rs,mid+1,r,p,w);
}
void updata(int &nd,int l,int r,int p,int q,int w){
	if(!nd)nd=++idx;
	updata(id[nd],-n,n,q,w);
	if(l==r)return ;
	if(p<=mid)updata(lsn,l,mid,p,q,w);
	else updata(rsn,mid+1,r,p,q,w);
}
int query(int nd,int l,int r,int ql,int qr){
	if(!nd||ql>qr)return inf;
	if(l>=ql&&r<=qr)return tree[nd];
	if(qr<=mid)return query(ls,l,mid,ql,qr);
	if(ql>mid)return query(rs,mid+1,r,ql,qr);
	return min(query(ls,l,mid,ql,qr),query(rs,mid+1,r,ql,qr));
}
int query(int nd,int l,int r,int ql,int qr,int qql,int qqr){
	if(!nd||ql>qr)return inf;
	if(l>=ql&&r<=qr)return query(id[nd],-n,n,qql,qqr);
	if(qr<=mid)return query(lsn,l,mid,ql,qr,qql,qqr);
	if(ql>mid)return query(rsn,mid+1,r,ql,qr,qql,qqr);
	return min(query(lsn,l,mid,ql,qr,qql,qqr),query(rsn,mid+1,r,ql,qr,qql,qqr));
}
void work(){
	n=read();a=read(),b=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		s1[i]=s1[i-1],s2[i]=s2[i-1];
		s1[i]+=(s[i]=='R'),s2[i]+=(s[i]=='B');
	}
	for(int i=1;i<=n;i++)s1[i]-=(i+a+b-1)/(a+b)*a,s2[i]-=(i+a+b-1)/(a+b)*b;
	// for(int i=1;i<=n;i++)cout<<s1[i]<<" "<<s2[i]<<"\n";
	updata(rt[0],-n,n,0,0,0);
	for(int i=1;i<=n;i++){
		dp[i]=min(dp[i-1]+1,query(rt[i%(a+b)],-n,n,s1[i],n,s2[i],n));
		// cout<<i<<" "<<dp[i]<<"\n";
		updata(rt[i%(a+b)],-n,n,s1[i],s2[i],dp[i]);
	}
	printf("%lld\n",(n-dp[n])/(a+b));
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
	
	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
