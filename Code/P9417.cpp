// Problem: P9417 [POI 2021/2022 R1] Druk
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9417
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-10-18 14:34:40
// 
// Powered by CP Editor (https://cpeditor.org)

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
const int maxn=1010;
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
char s[maxn][maxn];
bool vis[maxn][maxn];
vector<int> ans;
char t[maxn];
bool check(int len,bool fl){
	if(!fl){
		if(len>m)return 0;
		for(int i=1;i<=len;i++)t[i]=s[1][i];
	}
	else{
		if(len>n)return 0;
		for(int i=1;i<=len;i++)t[i]=s[i][1];
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)vis[i][j]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)if(!vis[i][j]){
			if(j+len-1<=m){
				bool fl=1;
				for(int k=j;k<=j+len-1;k++)fl&=(!vis[i][k]&&s[i][k]==t[k-j+1]);
				if(fl){
					for(int k=j;k<=j+len-1;k++)vis[i][k]=1;
					continue;
				}
			}
			if(i+len-1<=n){
				bool fl=1;
				for(int k=i;k<=i+len-1;k++)fl&=(!vis[k][j]&&s[k][j]==t[k-i+1]);
				if(fl){
					for(int k=i;k<=i+len-1;k++)vis[k][j]=1;
					continue;
				}
			}
			return 0;
		}
	}
	return 1;
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	bool fl=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)fl&=(s[i][j]==s[1][1]);
	}
	if(fl){
		for(int i=1;i<=max(n,m);i++)if(n%i==0||m%i==0){
			ans.pb(i);
		}
		printf("%lld\n",ans.size());
		for(int i:ans)printf("%lld ",i);
	}
	else{
		for(int i=1;i<=max(n,m);i++)if(n%i==0||m%i==0){
			if(check(i,0)||check(i,1))ans.pb(i);
		}
		printf("%lld\n",ans.size());
		for(int i:ans)printf("%lld ",i);
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
	
	T=1;
	while(T--)work();
}
