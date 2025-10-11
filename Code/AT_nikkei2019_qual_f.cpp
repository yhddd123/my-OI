// Problem: AT_nikkei2019_qual_f Jewels
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_nikkei2019_qual_f
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-10-10 10:01:27
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
const int inf=1e18;
bool mbe;

int n,m;
vector<int> pos[maxn];
pii a[maxn];
int t[maxn];
multiset<pii> l2,l3,r1,r3;
void add(int c){
	if(t[c]==2)l2.insert({pos[c][0]+pos[c][1],c});
	if(t[c]>=3)l3.insert({pos[c][t[c]-1],c});
	if(t[c]>=2&&t[c]<pos[c].size())r1.insert({pos[c][t[c]],c});
}
void del(int c){
	if(t[c]==2)l2.erase({pos[c][0]+pos[c][1],c});
	if(t[c]>=3)l3.erase({pos[c][t[c]-1],c});
	if(t[c]>=2&&t[c]<pos[c].size())r1.erase({pos[c][t[c]],c});
	if(!t[c]&&pos[c].size()>=3)r3.erase({pos[c][0]+pos[c][1]+pos[c][2],c});
}
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)pos[read()].pb(read());
	for(int i=1,nn=0;i<=m;i++)if(pos[i].size()){
		sort(pos[i].begin(),pos[i].end(),[&](int u,int v){return u>v;});
		pos[i][0]=pos[i][1]=pos[i][0]+pos[i][1];
		for(int j=2;j<pos[i].size();j++)pos[i][j]*=2;
		for(int v:pos[i])a[++nn]={v,i};
	}
	sort(a+1,a+n+1,greater<pii>());
	for(int i=1;i<=m;i++)if(pos[i].size()>=3)r3.insert({pos[i][0]+pos[i][1]+pos[i][2],i});
	for(int i=1,ans=0;i<=n;i++){
		del(a[i].se),t[a[i].se]++,add(a[i].se);ans+=a[i].fi;
		if(t[a[i].se]>=2){printf("%lld\n",ans/2);continue;}
		int mx=-inf;
		if(l2.size()){
			if(r3.size())mx=max(mx,-a[i].fi-(*l2.begin()).fi+(*--r3.end()).fi);
			if(pos[a[i].se].size()>=3)mx=max(mx,-(*l2.begin()).fi+pos[a[i].se][1]+pos[a[i].se][2]);
		}
		if(l3.size())mx=max(mx,a[i+1].fi-(*l3.begin()).fi);
		if(r1.size())mx=max(mx,-a[i].fi+(*--r1.end()).fi);
		if(ans+mx<0)puts("-1");
		else printf("%lld\n",(ans+mx)/2);
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