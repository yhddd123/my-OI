// Problem: E - Subset Sum Gaps
// Contest: AtCoder - AtCoder Regular Contest 210
// URL: https://atcoder.jp/contests/arc210/tasks/arc210_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-17 18:35:47
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

int n;
inline void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
vector<pii> a;
void work(){
	n=read();
	a.pb({0,1});
	for(int i=1;i<=n;i++){
		int x=read();
		vector<pii> nw=a;
		for(auto[v,t]:a)nw.pb({v+x,t});
		sort(nw.begin(),nw.end());
		a.clear();
		for(auto[v,t]:nw){
			if(!a.size()||a.back().fi!=v){
				while(a.size()>=2){
					auto[vv,tt]=a[a.size()-2];
					if((__int128)vv*101>(__int128)v*100)inc(a[a.size()-2].se,a.back().se),a.pop_back();
					else break;
				}
				a.pb({v,t});
			}
			else inc(a.back().se,t);
		}
	}
	vector<tuple<int,int,int>> ans;
	for(int i=0,s=0;i+1<a.size();i++){
		inc(s,a[i].se);
		if((__int128)a[i].fi*101<=(__int128)a[i+1].fi*100)ans.pb({a[i].fi,a[i+1].fi,s});
	}
	printf("%lld\n",ans.size());
	for(auto[u,v,w]:ans)printf("%lld %lld %lld\n",u,v,w);
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