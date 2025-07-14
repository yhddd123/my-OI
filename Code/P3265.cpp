// Problem: P3265 [JLOI2015] 装备购买
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3265
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-04-19 11:27:16
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
const int maxn=510;
const int inf=1e18;
#define db double
const db eps=1e-3;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int n,m;
struct nd{
	db b[maxn];
	int w;
}a[maxn];
int p[maxn],cnt,ans;
bool cmp(nd u,nd v){return u.w<v.w;}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[i].b[j]=read();
	}
	for(int i=1;i<=n;i++)a[i].w=read();
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(fabs(a[i].b[j])<eps)continue;
			if(!p[j]){
				p[j]=i,++cnt,ans+=a[i].w;
				break;
			}
			db d=a[i].b[j]/a[p[j]].b[j];
			for(int k=j;k<=m;k++)a[i].b[k]-=a[p[j]].b[k]*d;
		}
	}
	printf("%lld %lld\n",cnt,ans);
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
