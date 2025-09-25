// Problem: A. Incremental Path
// Contest: Codeforces - Codeforces Round 1053 (Div. 1)
// URL: https://codeforces.com/contest/2150/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-09-24 19:35:32
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

int n,m,a[maxn];
char s[maxn];
void work(){
	n=read();m=read();
	scanf("%s",s+1);
	map<int,bool> mp;
	for(int i=1;i<=m;i++){
		a[i]=read();
		mp[a[i]]=1;
	}
	for(int i=1,p=1;i<=n;i++){
		if(s[i]=='A'){
			p++;
			mp[p]=1;
		}
		else{
			p++;while(mp[p])p++;
			mp[p]=1;while(mp[p])p++;
		}
	}
	vector<int> ans;
	for(pii p:mp)if(p.se)ans.pb(p.fi);
	printf("%lld\n",ans.size());
	for(int u:ans)printf("%lld ",u);puts("");
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