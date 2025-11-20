// Problem: CF1774G Segment Covering
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1774G
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-20 19:09:20
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

int n,q;
pii a[maxn];
int nxt[18][maxn];
void work(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]={read(),read()};
	sort(a+1,a+n+1,[&](pii u,pii v){return u.se<v.se||(u.se==v.se&&u.fi>v.fi);});
	int nn=0;for(int i=1,mx=0;i<=n;i++){
		if(mx<a[i].fi){
			mx=a[i].fi;
			a[++nn]=a[i];
		}
	}
	n=nn;
	for(int i=1;i<=n;i++)nxt[0][i]=upper_bound(a+1,a+n+1,a[i],[&](pii u,pii v){return u.se<v.fi;})-a;
	nxt[0][n+1]=n+1;
	for(int j=1;j<18;j++){
		for(int i=1;i<=n+1;i++)nxt[j][i]=nxt[j-1][nxt[j-1][i]];
	}
	while(q--){
		int l=read(),r=read();
		int st=lower_bound(a+1,a+n+1,make_pair(l,r),[&](pii u,pii v){return u.fi<v.fi;})-a;
		int ed=lower_bound(a+1,a+n+1,make_pair(l,r),[&](pii u,pii v){return u.se<v.se;})-a;
		if(a[st].fi!=l||a[ed].se!=r){puts("0");continue;}
		int p1=st,p2=st+1;
		for(int j=17;~j;j--)if(nxt[j][p1]<=ed)p1=nxt[j][p1];
		for(int j=17;~j;j--)if(nxt[j][p2]<=ed)p2=nxt[j][p2];
		if(p1==p2||(p1!=ed&&p2!=ed))puts("0");
		else if(p1==ed)puts("998244352");
		else puts("1");
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