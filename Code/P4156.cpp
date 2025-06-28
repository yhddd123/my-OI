// Problem: P4156 [WC2016] 论战捆竹竿
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4156
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-04-18 14:32:23
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
#define mems(x,y) memset(x,y,sizeof x)
using namespace std;
const int maxn=530010;
const ll inf=2e18;
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

ll n,m;
char c[maxn];
int nxt[maxn],st[maxn],tp;
ll dis[maxn],p,res[maxn];
int gcd(int a,int b){
	if(!b)return a;
	return gcd(b,a%b);
}
int q[maxn],t;
void bfs(int len){
	int g=gcd(p,len);
	for(int i=0;i<p;i++)res[i]=dis[i];
	for(int i=0;i<len;i++)dis[i]=inf;
	for(int i=0;i<p;i++){
		int tmp=res[i]%len;
		dis[tmp]=min(dis[tmp],res[i]);
	}
	for(int i=0;i<g;i++){
		q[t=1]=i;
		int tmp=(i+p)%len;while(tmp!=i){q[++t]=tmp;tmp=(tmp+p)%len;}
		tmp=1;for(int j=2;j<=t;j++)if(dis[q[j]]<dis[q[tmp]])tmp=j;
		for(int j=tmp+1;j<=t;j++)dis[q[j]]=min(dis[q[j]],dis[q[j-1]]+p);
		dis[i]=min(dis[i],dis[q[t]]+p);
		for(int j=2;j<tmp;j++)dis[q[j]]=min(dis[q[j]],dis[q[j-1]]+p);
	}
	p=len;
}
int hh,tt,qq[maxn];
void change(int a,int nw,int len){
	int g=gcd(p,nw);
	for(int i=0;i<g;i++){
		q[t=1]=i;
		int tmp=(i+nw)%p;while(tmp!=i){q[++t]=tmp;tmp=(tmp+nw)%p;}
		tmp=1;for(int j=2;j<=t;j++)if(dis[q[j]]<dis[q[tmp]])tmp=j;
		for(int j=1;j<=t;j++)res[j]=q[j];
		for(int j=tmp;j<=t;j++)q[j-tmp+1]=res[j];
		for(int j=1;j<tmp;j++)q[j+t-tmp+1]=res[j];
		qq[hh=tt=1]=1;
		for(int j=2;j<=t;j++){
			while(hh<=tt&&j-qq[hh]>len)hh++;
			dis[q[j]]=min(dis[q[j]],dis[q[qq[hh]]]+a+nw*(j-qq[hh]));
			while(hh<=tt&&dis[q[qq[tt]]]+nw*(j-qq[hh])>dis[q[j]])tt--;
			qq[++tt]=j;
		}
	}
}
void work(){
	n=read();m=read()-n;
	scanf("%s",c+1);
	if(m<0){printf("0\n");return ;}
	for(int i=2,j=0;i<=n;i++){
		while(j&&c[i]!=c[j+1])j=nxt[j];
		if(c[i]==c[j+1])j++;
		nxt[i]=j;
	}
	int x=nxt[n];tp=0;
	while(x)st[++tp]=n-x,x=nxt[x];st[++tp]=n;st[tp+1]=0;
	for(int i=0;i<n;i++)dis[i]=inf;
	dis[0]=0;p=n;
	int l=1;
	while(l<tp){
		int r=l+1;
		while(r<=tp&&st[r+1]-st[r]==st[l+1]-st[l])++r;
		bfs(st[l]);
		change(st[l],st[l+1]-st[l],r-l);
		l=r;
	}
	ll ans=0;for(int i=0;i<p;i++)if(dis[i]<=m)ans+=(m-dis[i])/p+1;
	printf("%lld\n",ans);fflush(stdout);
}

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=read();
	while(T--)work();
}