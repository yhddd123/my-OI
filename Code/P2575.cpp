// Problem: P2575 高手过招
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2575
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-09 18:36:23
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

int n;
bool vis[21];
void work(){
	n=read();int ans=0;
	for(int i=1;i<=n;i++){
		int m=read();
		for(int j=1;j<=m;j++)vis[read()]=1;
		int num=0,cnt=0;
		for(int j=20;~j;j--){
			if(vis[j])++cnt;
			else{
				if(num&1)ans^=cnt;
				num++;cnt=0;
			}
		}
		mems(vis,0);
	}
	if(ans)puts("YES");
	else puts("NO");
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
