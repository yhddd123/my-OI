// Problem: P10833 [COTS/CETS 2023] 下 Niz
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10833
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-08-06 21:10:53
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
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,a[maxn],ans;
int st[maxn],tp;
int mx[20][maxn];
int que(int l,int r){
	int k=log2(r-l+1);
	return max(mx[k][l],mx[k][r-(1<<k)+1]);
}
int val[maxn],f[maxn];
mt19937 rnd(1);
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)mx[0][i]=a[i];
	for(int j=1;j<=19;j++){
		for(int i=1;i+(1<<j)-1<=n;i++)mx[j][i]=max(mx[j-1][i],mx[j-1][i+(1<<j-1)]);
	}
	for(int i=1;i<=n;i++)if(a[i]==1)st[++tp]=i;st[tp+1]=n+1;
	for(int i=1;i<=n;i++)val[i]=rnd()%mod;
	for(int i=1;i<=n;i++)f[i]=f[i-1]^val[a[i]];
	for(int i=1;i<=n;i++)val[i]^=val[i-1];
	for(int i=1;i<=tp;i++){
		for(int j=st[i-1]+1;j<=st[i];j++){
			int v=que(j,st[i]);
			if(j+v-1>=st[i]&&j+v-1<=n){
				if((f[j+v-1]^f[j-1])==val[v])++ans;
				// cout<<st[i]<<" "<<j<<" "<<v<<"\n";
			}
		}
		for(int j=st[i]+1;j<=st[i+1]-1;j++){
			int v=que(st[i],j);
			if(j-v+1<=st[i]&&j-v+1>=1){
				if((f[j]^f[j-v+1-1])==val[v])++ans;
				// cout<<st[i]<<" "<<j<<" "<<v<<"\n";
			}
		}
	}
	printf("%lld\n",ans);
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
