// Problem: P14516 [NFLSPC #8] 小 W，小 P，彩丝带
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P14516
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-17 14:46:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ull unsigned long long
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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,a[maxn],pre[maxn];
ull ans;
ull sum[maxn];int pl[maxn];
int st[maxn],tim[maxn],tp;ull val[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1,lst=0;i<=n;i++){
		if(a[i])pre[i]=lst,lst=i;
	}
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;i++)if(a[i]){
		if(!((i-pre[i])&1))pl[i]=pl[pre[i]];
		else pl[i]=i;
	}
	// for(int i=1;i<=n;i++){
		// ull lst=0,mx=0;
		// for(int j=i;j<=n;j++){
			// if(a[j]){
				// if((j-pre[j])&1)lst=a[j],mx=max(mx,lst);
				// else lst+=a[j],mx=max(mx,lst);
			// }
			// ans+=mx;
			// // cout<<i<<" "<<j<<" "<<mx<<"\n";
		// }
	// }
	for(int i=1;i<=n;i++){
		if(a[i]){
			if((i-pre[i])&1){
				int v=a[i];
				while(tp&&val[tp]<=v)ans+=val[tp]*(st[tp]-st[tp-1])*(i-tim[tp]),tp--;
				st[++tp]=pre[i],val[tp]=v,tim[tp]=i;
			}
			else{
				while(tp&&val[tp]<=sum[i]-sum[max(st[tp],pl[i])-1])ans+=val[tp]*(st[tp]-st[tp-1])*(i-tim[tp]),tp--;
			}
		}
		st[++tp]=i,val[tp]=a[i],tim[tp]=i;
		// cout<<i<<" "<<ans<<"\n";
	}
	// for(int i=1;i<=tp;i++)cout<<st[i]<<" "<<val[i]<<" "<<tim[i]<<"\n";
	while(tp){
		ans+=val[tp]*(st[tp]-st[tp-1])*(n+1-tim[tp]);
		tp--;
	}
	printf("%llu\n",ans);
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