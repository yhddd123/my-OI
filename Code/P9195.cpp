// Problem: P9195 [JOI Open 2016] JOIRIS
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9195
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-05-10 15:17:10
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
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

int n,a[maxn],k,p,b[maxn],c[maxn];
vector<pii> ans;
void work(){
	n=read();k=read();p=(n-1)%k;
	for(int i=0;i<n;i++)a[i]=read(),b[i%k]+=a[i];
	for(int i=0;i<=p;i++)if(b[i]%k!=b[0]%k){printf("-1\n");return ;}
	for(int i=p+1;i<k;i++)if(b[i]%k!=b[p+1]%k){printf("-1\n");return ;}
	for(int i=1;i<n;i++){
		while(a[i]<a[i-1])a[i]+=k,ans.push_back({1,i});
	}
	for(int i=0;i<n-1;i++){
		for(int j=a[i];j<a[i+1];j++){
			for(int x=i-k+1;x>=0;x-=k)ans.push_back({2,x});
			if(i%k!=k-1)c[i%k]++;
		}
	}
	for(int i=k-3;i>=0;i--)c[i]+=c[i+1];
	for(int i=0;i<=k-2;i++){
		while(c[i]>0){
			c[i]-=k;
			ans.push_back({1,i});
		}
	}
	for(int i=p+1;i<n;i+=k){
		for(int j=1;j<=-c[0];j++)ans.push_back({2,i});
	}
	printf("%lld\n",(int)ans.size());
	for(auto [op,p]:ans)printf("%lld %lld\n",op,p+1);
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
