// Problem: D. Game on Array
// Contest: Codeforces - Codeforces Global Round 29 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2147/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-22 09:43:11
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

int n,ans1,ans2,fl;
void work(){
	n=read();ans1=ans2=0;fl=0;
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		int x=read();
		if(x&1)mp[x]++;
		ans1+=x/2,ans2+=x/2;
	}
	vector<int> a;
	for(auto[v,t]:mp)a.pb(t);
	sort(a.begin(),a.end());
	while(a.size()){
		if(fl)ans2+=a.back();
		else ans1+=a.back();
		a.pop_back();fl^=1;
	}
	cout<<ans1<<" "<<ans2<<"\n";
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