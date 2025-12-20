// Problem: T712268 [JOI 2026 二次预选] 船 / Ship
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T712268?contestId=298530
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-12-19 19:50:59
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
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

int n,a[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(n&1){
		map<int,bool> vis;for(int i=1;i<=n;i++)vis[a[i]]=1;
		int ans=-1;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				int k=0;
				if(vis.find(2*a[i]-a[j])!=vis.end())k=lower_bound(a+1,a+n+1,2*a[i]-a[j])-a;
				if(vis.find(2*a[j]-a[i])!=vis.end())k=lower_bound(a+1,a+n+1,2*a[j]-a[i])-a;
				if(!k)continue;
				int res=a[j]-a[i];
				int p=1;
				while(p==i||p==j||p==k)p++;
				for(int t=1;t<=(n-3)/2;t++){
					p++;
					while(p==i||p==j||p==k)p++;
				}
				for(int t=1,p1=1,p2=p;t<=(n-3)/2;t++){
					while(p1==i||p1==j||p1==k)p1++;
					while(p2==i||p2==j||p2==k)p2++;
					res=min(res,a[p2]-a[p1]);
					p1++,p2++;
				}
				ans=max(ans,res);
			}
		}
		printf("%lld\n",ans);
	}
	else{
		int ans=inf;
		for(int i=1;i<=n/2;i++)ans=min(ans,a[i+n/2]-a[i]);
		printf("%lld\n",ans);
	}
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