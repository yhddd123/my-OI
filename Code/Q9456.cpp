#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
#define db double
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
int a[10],ans=inf;
void dfs(int dep,int lst,int sum){
	// cout<<dep<<" "<<lst<<" "<<sum<<endl;
	if(dep==m+1){
		if(sum)return ;
		int val=0;
		for(int i=1;i<=m;i++)val=val|a[i];
		ans=min(ans,val);
		// if(val==11){
			// for(int i=1;i<=m;i++)cout<<a[i]<<" ";cout<<"\n";
			// cout<<val<<"\n";
		// }
		return ;
	}
	for(int i=lst;i<=sum;i++){
		a[dep]=i;
		dfs(dep+1,i,sum-i);
	}
}
void work(){
	n=read();m=read();
	ans=inf;dfs(1,0,n);
	printf("%lld\n",ans);
	return ;
	int k=(n+m-1)/m;
	int res=k*m-n;
	int pw=k&(-k);
	// cout<<k<<" "<<res<<"\n";
	if(res%pw==0){
		printf("%lld\n",k);
		return ;
	}
	else{
		res%=pw;
		printf("%lld\n",k|(k-res));
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
	
	T=read();
	while(T--)work();
}
