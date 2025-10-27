// Problem: B - Swap if Equal Length and Sum
// Contest: AtCoder - AtCoder Grand Contest 074
// URL: https://atcoder.jp/contests/agc074/tasks/agc074_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-27 16:00:38
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
// #define int long long
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

int n,a[maxn],b[maxn];
vector<int> p1,p2;
vector<pii> a1,a2;
vector<tuple<int,int,int,int>> ans;
void work(){
	p1.clear(),p2.clear(),a1.clear(),a2.clear();ans.clear();
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	int cnt=0;for(int i=1;i<=n;i++)cnt+=(a[i]==1);
	if(cnt>n/2){
		for(int i=1;i<=n;i++)a[i]=!a[i];
		for(int i=1;i<=n;i++)b[i]=!b[i];
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		if(a[i]==1)p1.pb(i),sum+=i;
	}
	for(int i=1;i<=n;i++){
		if(b[i]==1)p2.pb(i),sum-=i;
	}
	if(p1.size()!=p2.size()||sum){puts("No");return ;}
	for(int i=0;i<p1.size();i++){
		if(p1[i]<p2[i])a1.pb({p1[i],p2[i]});
		if(p1[i]>p2[i])a2.pb({p1[i],p2[i]});
	}
	sort(a1.begin(),a1.end(),[&](pii u,pii v){return u.fi>v.fi;});
	sort(a2.begin(),a2.end(),[&](pii u,pii v){return u.fi<v.fi;});
	for(int i=0,j=0;i<a1.size();i++){
		while(a1[i].fi<a1[i].se){
			int d=min(a1[i].se-a1[i].fi,a2[j].fi-a2[j].se);
			if(a1[i].fi+d<a2[j].fi-d)ans.pb({a1[i].fi,a1[i].fi+d,a2[j].fi-d,a2[j].fi});
			else ans.pb({a2[j].fi-d,a2[j].fi,a1[i].fi,a1[i].fi+d});
			a1[i].fi+=d,a2[j].fi-=d;
			if(a2[j].fi==a2[j].se)j++;
		}
	}
	puts("Yes");
	printf("%d\n",ans.size());
	for(auto[l1,r1,l2,r2]:ans)printf("%d %d %d %d\n",l1,r1,l2,r2);
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