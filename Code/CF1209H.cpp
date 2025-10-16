// Problem: CF1209H Moving Walkways
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1209H
// Memory Limit: 250 MB
// Time Limit: 2500 ms
// Written by yhm.
// Start codeing:2025-10-16 20:44:03
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<db,db>
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
const db eps=1e-12;
bool mbe;

int n,l;db ans;
void work(){
	n=read();l=read();
	priority_queue<pii> q;
	auto upd=[&](int l,db v){
		if(v<1+eps)q.push({v,1e18});
		else q.push({v,l/(v-1)+l/(v+1)});
		ans+=l/(v+1);
		db d=l/(v+1);
		while(d>eps){
			auto[vv,e]=q.top();q.pop();
			db del=min(e,d);d-=del,e-=del;ans+=del/vv;
			// cout<<d<<" "<<e<<" "<<del<<"\n";
			if(e>eps)q.push({vv,e});
		}
		// cout<<l<<" "<<v<<" "<<ans<<" u\n";
	};
	int lst=0;
	for(int i=1;i<=n;i++){
		int pl=read(),pr=read();db v;scanf("%Lf",&v);
		upd(pl-lst,1),upd(pr-pl,v+1);lst=pr;
	}
	upd(l-lst,1);
	printf("%.12Lf\n",ans);
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