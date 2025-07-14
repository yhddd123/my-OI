// Problem: P9525 [JOISC2022] 团队竞技
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9525
// Memory Limit: 1 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
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

int n,a[maxn],b[maxn],c[maxn];
priority_queue<pii> q1,q2,q3;
bool vis[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read(),b[i]=read(),c[i]=read();
		q1.push({a[i],i}),q2.push({b[i],i}),q3.push({c[i],i});
	}
	while(q1.size()&&q2.size()&&q3.size()){
		bool fl=0;int x=q1.top().second,y=q2.top().second,z=q3.top().second;
		if(b[x]==b[y]||c[x]==c[z])vis[x]=1,fl=1;
		if(a[x]==a[y]||c[y]==c[z])vis[y]=1,fl=1;
		if(a[x]==a[z]||b[y]==b[z])vis[z]=1,fl=1;
		if(!fl){printf("%lld\n",a[x]+b[y]+c[z]);return ;}
		while(q1.size()&&vis[q1.top().second])q1.pop();
		while(q2.size()&&vis[q2.top().second])q2.pop();
		while(q3.size()&&vis[q3.top().second])q3.pop();
	}
	printf("-1\n");
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
