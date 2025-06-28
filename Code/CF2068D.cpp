// Problem: CF2068D Morse Code
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2068D
// Memory Limit: 1000 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-03-25 17:10:41
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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
const int maxn=210;
const int inf=1e9;
bool mbe;

int n,a[maxn],id[maxn],b[maxn];
char c[10];
int dp[21][maxn][maxn][maxn];
void chkmn(int &u,int v){(u>v)&&(u=v);}
pii fa[maxn*15];
int t[21],pos;
vector<char> ans[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),a[i]=read();
	for(int i=1;i<=n;i++)id[i]=i,b[i]=a[i];
	sort(id+1,id+n+1,[&](int u,int v){return a[u]<a[v];});
	sort(a+1,a+n+1);
	mems(dp,0x3f);dp[20][0][0][0]=0;
	for(int x=20;x;x--){
		for(int i=0;i<n;i++){
			for(int j=0;j<=i;j++){
				for(int k=0;j+k<=i;k++){
					chkmn(dp[x][i+1][j][k+1],dp[x][i][j][k]+a[i+1]*x);
				}
			}
		}
		for(int i=0;i<=n;i++){
			for(int j=0;j<=i;j++){
				for(int k=j;j+k<=i;k++)if(dp[x][i][j][k]<inf){
					// cout<<x<<" "<<i<<" "<<j<<" "<<k<<" "<<dp[x&1][i][j][k]<<"\n";
					chkmn(dp[x-1][i][k-j][j],dp[x][i][j][k]);
				}
			}
		}
	}
	// for(int i=0;i<=n;i++){
		// for(int j=0;j<=i;j++){
			// for(int k=j;j+k<=i;k++)if(dp[0][i][j][k]<inf){
				// cout<<i<<" "<<j<<" "<<k<<" "<<dp[0][i][j][k]<<"\n";
			// }
		// }
	// }
	// printf("%lld\n",dp[0][n][0][1]);
	vector<int> val;
	for(int x=0,i=n,j=0,k=1;x<=20;){
		x++,j+=k,swap(j,k);
		while(i&&k&&dp[x][i][j][k]==dp[x][i-1][j][k-1]+a[i]*x){
			i--,k--;
			// cout<<x<<" "<<i<<" "<<j<<" "<<k<<"\n";
			val.pb(x);
		}
	}
	reverse(val.begin(),val.end());
	// for(int x:val)cout<<x<<" ";cout<<"\n";
	for(int x:val)t[x]++;
	vector<int> id1,id2;
	int pos=n;
	for(int x=20,i=1;~x;x--){
		while(t[x]--)id2.pb(i++);
		vector<int> tmp;
		while(id2.size()&&id1.size()){
			++pos,tmp.pb(pos);
			fa[id2.back()]={pos,1},id2.pop_back(),fa[id1.back()]={pos,2},id1.pop_back();
		}
		// cout<<id2.size()<<" "<<id1.size()<<"\n";
		id1=id2,id2=tmp;
	}
	// for(int i=1;i<=pos;i++)cout<<fa[i].fi<<" "<<fa[i].se<<"\n";
	for(int i=1;i<=n;i++){
		vector<int> res;
		int u=i;
		// cout<<i<<endl;
		while(fa[u].fi){
			// cout<<u<<" "<<fa[u].fi<<endl;
			res.pb(fa[u].se);
			u=fa[u].fi;
		}
		// cout<<i<<" "<<id[i]<<" "<<res.size()<<endl;
		reverse(res.begin(),res.end());
		for(int w:res)ans[id[i]].pb(w==1?'.':'-');
	}
	// int sum=0;
	for(int i=1;i<=n;i++){
		// int cnt=0;for(char c:ans[i])cnt+=(c=='.')+(c=='-')*2;
		// sum+=cnt*b[i];
		for(char c:ans[i])putchar(c);puts("");
	}
	// cout<<sum<<"\n";
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