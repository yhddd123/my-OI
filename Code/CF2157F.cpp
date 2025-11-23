// Problem: F. Git Gud
// Contest: Codeforces - Codeforces Round 1066 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2157/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-23 19:26:10
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
const int maxn=1<<19;
const int inf=1e9;
bool mbe;

int n;
vector<pii> ans;
bool vis[maxn];
int lst,res;
void chk(int p,int l){
	if(lst&&lst<p)res+=1000;
	lst=p;res+=l;
	vis[p]=0,vis[p+l]=1;
}
void upd(int p,int l){
	if(p<=0)return ;
	ans.pb({p,l});
	// chk(p,l);
}
void work(){
	n=1<<18;
	// for(int i=1;i<=n;i++)vis[i]=1;
	for(int t=0,pw=1;t<3;t++,pw*=64){
		for(int j=1;j<=63;j++){
			for(int i=n-pw*64;i>=0;i-=pw*64){
				upd(i+j*pw,pw);
			}
		}
		// cout<<t<<" "<<vis[63]<<" "<<vis[64]<<" "<<ans.size()<<" "<<res<<"\n";
	}
	printf("%lld\n",(int)ans.size());
	for(auto[u,v]:ans)printf("%lld %lld\n",u,v);
	// for(auto[u,v]:ans)assert(1<=u&&u<=1000000&&1<=v&&v<=1000000);
	// cout<<res<<"\n";
	// for(int i=1;i<=n;i++)if(vis[i]){
		// cerr<<"err\n";
		// cerr<<i<<"\n";
		// assert(0);
	// }
	// for(int i=1;i<=4;i++){
		// int x=i;
		// cout<<i<<"\n";
		// for(auto[u,v]:ans)if(x==u){
			// x+=v;
			// cout<<u<<" "<<v<<"\n";
		// }
	// }
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