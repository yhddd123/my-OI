// Problem: P5574 [CmdOI2019] 任务分配问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5574
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353
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

int n,k,a[maxn];
int l=1,r=0,ans;
int c[maxn];
int lowbit(int x){return x&(-x);}
void updata(int x,int w){
	while(x<=n){
		c[x]+=w;
		x+=lowbit(x);
	}
}
int query(int x){
	int res=0;
	while(x){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int dp[maxn],f[maxn];
int calc(int ql,int qr){
	while(r<qr){
		updata(a[++r],1);
		ans+=query(a[r]-1);
	}
	while(l>ql){
		updata(a[--l],1);
		ans+=r-l+1-query(a[l]-1)-1;
	}
	while(r>qr){
		ans-=query(a[r]-1);
		updata(a[r--],-1);
	}
	while(l<ql){
		ans-=r-l+1-query(a[l]-1)-1;
		updata(a[l++],-1);
	}
	return ans;
}
void sovle(int l,int r,int ql,int qr){
	if(l>r)return ;
	int mid=l+r>>1,pos=ql;f[mid]=inf;
	for(int i=ql;i<=min(qr,mid-1);i++){
		if(f[mid]>dp[i]+calc(i+1,mid)){
			f[mid]=dp[i]+calc(i+1,mid);
			pos=i;
		}
	}
	sovle(l,mid-1,ql,pos),sovle(mid+1,r,pos,qr);
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)dp[i]=calc(1,i);
	for(int i=2;i<=k;i++){
		sovle(1,n,1,n);
		for(int j=1;j<=n;j++)dp[j]=f[j];
	}
	printf("%lld\n",dp[n]);
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
