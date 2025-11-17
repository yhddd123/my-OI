// Problem: B - Remove Median Operations
// Contest: AtCoder - AtCoder Regular Contest 210
// URL: https://atcoder.jp/contests/arc210/tasks/arc210_b
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-11-16 20:03:55
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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n,m,q,a[maxn],ans;
set<pii> s,s1,s2;
void work(){
	n=read();m=read();q=read();
	for(int i=1;i<=n+m;i++)a[i]=read(),s.insert({a[i],i});
	auto it=s.begin();
	for(int t=1;t<=n/2;t++,it++)s1.insert(*it),ans+=(*it).fi;
	it=--s.end();
	for(int t=1;t<=n/2;t++,it--)s2.insert(*it),ans+=(*it).fi;
	while(q--){
		int op=read(),p=read(),w=read();
		if(op==2)p+=n;
		s.erase({a[p],p});
		if(s1.find({a[p],p})!=s1.end())s1.erase({a[p],p}),ans-=a[p];
		else ans-=(*--s1.end()).fi,s1.erase(--s1.end());
		if(s2.find({a[p],p})!=s2.end())s2.erase({a[p],p}),ans-=a[p];
		else ans-=(*s2.begin()).fi,s2.erase(s2.begin());
		// cout<<ans<<" "<<s1.size()<<" "<<s2.size()<<"\n";
		a[p]=w;
		s.insert({a[p],p});
		{
			auto it=s.begin();
			if(s1.size())it=s.upper_bound(*--s1.end());
			pii res=min((*it),make_pair(a[p],p));
			s1.insert(res);ans+=(res).fi;
		}
		{
			auto it=--s.end();
			if(s2.size())it=--s.lower_bound(*s2.begin());
			pii res=max((*it),make_pair(a[p],p));
			s2.insert(res);ans+=(res).fi;
		}
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