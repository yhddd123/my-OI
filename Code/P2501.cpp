#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=35010;
const int inf=1e15;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[maxn],ans;
int b[maxn],len;
int lowbit(int x){return x&(-x);}
vector<int> g;
struct bit{
	int c[maxn];
	vector<int> f[maxn];
	void clear(){
		for(int i=1;i<=len;i++)f[i].push_back(0);
	}
	void updata(int x,int w,int id){
		while(x<=len){
			if(c[x]<w)c[x]=w,f[x].clear(),f[x].push_back(id);
			else if(c[x]==w)f[x].push_back(id);
			x+=lowbit(x);
		}
	}
	int query(int x){
		int res=0;
		g.clear();g.push_back(0);
		while(x){
			if(res<c[x])res=c[x],g=f[x];
			else if(res==c[x])for(int i:f[x])g.push_back(i);
			x-=lowbit(x);
		}
		return res;
	}
}T0;
int dp[maxn],f[maxn];
int st[maxn],tp;
int sum[maxn],suf[maxn];
int work(int l,int r){
	sum[l]=suf[r]=0;
	int res=inf;
	for(int j=l+1;j<=r-1;j++)sum[j]=sum[j-1]+abs(b[a[j]]-b[a[l]]);
	for(int j=r-1;j>=l+1;j--)suf[j]=suf[j+1]+abs(b[a[j]]-b[a[r]]);
	for(int j=l+1;j<=r;j++)res=min(res,sum[j-1]+suf[j]);
	return res;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();T0.clear();
	for(int i=1;i<=n;i++)a[i]=read()-i,b[++len]=a[i];
	a[++n]=2e5;b[++len]=a[n];b[0]=-2e5;
	sort(b+1,b+len+1);len=unique(b+1,b+len+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+len+1,a[i])-b;
	for(int i=1;i<=n;i++){
		dp[i]=T0.query(a[i])+1;f[i]=inf;
		for(int j:g)f[i]=min(f[i],f[j]+work(j,i));
		T0.updata(a[i],dp[i],i);
	}
	printf("%lld\n%lld\n",n-dp[n],f[n]);
}
