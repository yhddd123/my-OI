#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 1000000007
using namespace std;
const int maxn=1000010;
const int inf=1e18;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

#define ls nd<<1
#define rs nd<<1|1
#define mid (l+r>>1)
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define vii vector<int,int>
#define pb push_back

int n,a[maxn],s[maxn];
int dp[maxn];
int K(int u){return -2*a[u];}
int B(int u){return a[u]*a[u]+dp[u]-s[u];}
int tree[maxn<<2];
int calc(int u,int x){return K(u)*x+B(u);}
void updata(int nd,int l,int r,int id){
	if(l==r){
		if(calc(id,l)<calc(tree[nd],l))tree[nd]=id;
		return ;
	}
	if(calc(id,mid)<calc(tree[nd],mid))swap(tree[nd],id);
	if(calc(id,l)<calc(tree[nd],l))updata(ls,l,mid,id);
	else updata(rs,mid+1,r,id);
}
int query(int nd,int l,int r,int p){
	if(l==r)return tree[nd];
	int res=0;
	if(p<=mid)res=query(ls,l,mid,p);
	else res=query(rs,mid+1,r,p);
	if(calc(tree[nd],p)<calc(res,p))return tree[nd];
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)s[i]=s[i-1]+read();
	dp[0]=inf;dp[1]=0;updata(1,0,maxn-10,1);
	for(int i=2;i<=n;i++){
		int j=query(1,0,maxn-10,a[i]);
		dp[i]=a[i]*a[i]+s[i-1]+calc(j,a[i]);
//		cout<<i<<" "<<dp[i]<<" "<<j<<" "<<calc(j,a[i])<<"\n";
		updata(1,0,maxn-10,i);
	}
	printf("%lld\n",dp[n]);
}
