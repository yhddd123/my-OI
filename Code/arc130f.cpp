// Problem: AT_arc130_f [ARC130F] Replace by Average
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc130_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-08 15:12:43
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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,a[maxn];
pii st[maxn];int tp;
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++){
		int x=a[i]-a[i-1];
		int sum=x,cnt=1;
		while(tp&&st[tp].fi>=sum/cnt){
			sum+=st[tp].fi*st[tp].se,cnt+=st[tp].se;
			tp--;
		}
		if(sum%cnt==0)st[++tp]={sum/cnt,cnt};
		else if(sum>=0)st[++tp]={sum/cnt,cnt-sum%cnt},st[++tp]={sum/cnt+1,sum%cnt};
		else sum=-sum,st[++tp]={-sum/cnt-1,sum%cnt},st[++tp]={-sum/cnt,cnt-sum%cnt};
	}
	int ans=a[1];
	for(int i=1,v=a[1];i<=tp;i++){
		for(int j=1;j<=st[i].se;j++)v+=st[i].fi,ans+=v;
	}
	printf("%lld\n",ans);
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