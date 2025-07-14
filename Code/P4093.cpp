#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
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

int n,m,a[maxn];
int mn[maxn],mx[maxn];
int dp[maxn],ans;
int p[maxn];
bool cmp1(int u,int v){return mx[u]<mx[v];}
bool cmp2(int u,int v){return a[u]<a[v];}
int tree[maxn];
int lowbit(int x){return x&(-x);}
void updata(int x,int w){
	while(x<maxn){
		tree[x]=max(tree[x],w);
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x){
		res=max(res,tree[x]);
		x-=lowbit(x);
	}
	return res;
}
void clear(int x){
	while(x<maxn){
		tree[x]=0;
		x+=lowbit(x);
	}
}
void cdq(int l,int r){
	if(l==r){
		dp[l]=max(dp[l],1ll);
		return;
	}
	int mid=l+r>>1;
	cdq(l,mid);
	for(int i=l;i<=r;i++)p[i]=i;
	sort(p+l,p+mid+1,cmp1);
	sort(p+mid+1,p+r+1,cmp2);
	int h=l,t=mid+1;
	while(t<=r){
		while(h<=mid&&mx[p[h]]<=a[p[t]])updata(a[p[h]],dp[p[h]]),h++;
		dp[p[t]]=max(dp[p[t]],query(mn[p[t]])+1);t++;
	}
	for(int i=l;i<=mid;i++)clear(a[p[i]]);
	cdq(mid+1,r);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=mn[i]=mx[i]=read();
	while(m--){
		int u,v;
		u=read();v=read();
		mn[u]=min(mn[u],v);mx[u]=max(mx[u],v);
	}
	cdq(1,n);
	for(int i=1;i<=n;i++)ans=max(ans,dp[i]);
	printf("%lld\n",ans);
}
