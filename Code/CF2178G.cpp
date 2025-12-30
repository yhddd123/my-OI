// Problem: CF2178G deCH OR Dations
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF2178G
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// Written by yhm.
// Start codeing:2025-12-30 16:19:13
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

int n;
#define lb(x) (x&(-x))
struct bit{
	ull tree[maxn];
	void upd(int x,ull w){
		while(x<=2*n)tree[x]^=w,x+=lb(x);
	}
	ull que(int x){
		ull res=0;
		while(x)res^=tree[x],x-=lb(x);
		return res;
	}
	void clr(){
		for(int i=1;i<=2*n;i++)tree[i]=0;
	}
}f,g;
mt19937_64 rnd(time(0));
void work(){
	n=read();
	f.clr(),g.clr();
	ull sum=0;
	for(int i=1;i<=n;i++){
		int l=read(),r=read();
		ull w=rnd();
		ull ff=f.que(r)^f.que(l-1),gg=g.que(r)^g.que(l-1);
		ff=ff^(w*gg)^w,gg^=1;
		f.upd(l,ff),f.upd(r,ff),g.upd(l,gg),g.upd(r,gg);
		sum^=ff;
		putchar(!sum?'1':'0');
	}
	puts("");
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