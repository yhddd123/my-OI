// Problem: B - Rivalry
// Contest: AtCoder - AtCoder Regular Contest 198 (Div. 2)
// URL: https://atcoder.jp/contests/arc198/tasks/arc198_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-05-25 20:16:28
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
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

int a,b,c;
void work(){
	a=read(),b=read(),c=read();
	int d=min({a,b/2,c}),dd=d;
	a-=d,b-=2*d,c-=d;
	d=min(a,b/2);
	a-=d,b-=2*d;
	if(!b&&!c){puts("Yes");return ;}
	if(!a&&(b||c)){puts("No");return ;}
	if(!c&&b&&!dd){puts("No");return ;}
	if(b>1){puts("No");return ;}
	if(a>=c){puts("Yes");return ;}
	puts("No");
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