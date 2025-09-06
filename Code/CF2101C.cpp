// Problem: C. 23 Kingdom
// Contest: Codeforces - Codeforces Round 1024 (Div. 1)
// URL: https://codeforces.com/problemset/problem/2101/C
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// Written by yhm.
// Start codeing:2025-09-06 08:02:43
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

int n,a[maxn],ans;
int val[maxn],pos[maxn];
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)val[i]=pos[i]=0;
	set<int> s;
	for(int i=1;i<=n;i++)s.insert(i);
	for(int i=1,cnt=0,sum=0;i<=n;i++){
		auto it=s.upper_bound(a[i]);
		if(it!=s.begin()){
			it--;
			s.erase(it);
			cnt++,sum+=i;
			val[cnt]=sum,pos[cnt]=i;
		}
		// cout<<i<<" "<<cnt<<" "<<sum<<"\n";
	}
	s.clear();
	for(int i=1;i<=n;i++)s.insert(i);
	for(int i=n,cnt=0,sum=0;i;i--){
		auto it=s.upper_bound(a[i]);
		if(it!=s.begin()){
			it--;
			s.erase(it);
			cnt++,sum+=i;
			if(pos[cnt]&&pos[cnt]<i)ans=max(ans,sum-val[cnt]);
		}
	}
	printf("%lld\n",ans);
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}