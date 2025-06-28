// Problem: A - I hate 1
// Contest: AtCoder - AtCoder Regular Contest 198 (Div. 2)
// URL: https://atcoder.jp/contests/arc198/tasks/arc198_a
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-25 20:00:11
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n;
bool vis[maxn];
void work(){
	n=read();
	vector<int> ans,res;
	for(int i=n;i;i--){
		bool fl=0;for(int j=i;j<=n;j+=i)if(vis[j+1])fl=1;
		if(!fl)vis[i]=1,ans.pb(i);
	}
	for(int i=1;i<=n;i++)vis[i]=0;
	for(int i=n-1;i;i--){
		bool fl=0;for(int j=i;j<=n;j+=i)if(vis[j+1])fl=1;
		if(!fl)vis[i]=1,res.pb(i);
	}
	if(res.size()>ans.size())swap(ans,res);
	printf("%lld\n",ans.size());
	sort(ans.begin(),ans.end());
	for(int u:ans)printf("%lld ",u);
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