// Problem: P5540 [BalkanOI 2011] timeismoney
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5540
// Memory Limit: 64 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2026-01-27 09:10:56
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
const int maxn=100010;
const int inf=1e9;
bool mbe;

int n,m,va=inf,vb=inf;
int ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
struct node{
	int u,v,a,b;
}edge[maxn];
pii calc(int ka,int kb){
	sort(edge+1,edge+m+1,[&](node u,node v){return u.a*ka+u.b*kb<v.a*ka+v.b*kb;});
	for(int i=1;i<=n;i++)ff[i]=i;
	pii ans={0,0};
	for(int i=1;i<=m;i++){
		auto[u,v,a,b]=edge[i];
		u=fd(u),v=fd(v);
		if(u==v)continue;
		ff[u]=v;
		ans.fi+=a,ans.se+=b;
	}
	return ans;
}
void sovle(pii a,pii b){
	if(a.fi*b.se>=va*vb)return ;
	pii c=calc(a.se-b.se,b.fi-a.fi);
	if((b.fi-a.fi)*(c.se-a.se)>=(b.se-a.se)*(c.fi-a.fi))return ;
	if(c.fi*c.se<va*vb)va=c.fi,vb=c.se;
	sovle(a,c),sovle(c,b);
}
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read()+1,v=read()+1,a=read(),b=read();
		edge[i]={u,v,a,b};
	}
	sovle({0,inf},{inf,0});
	printf("%lld %lld\n",va,vb);
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