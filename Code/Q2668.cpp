// # pragma GCC optimize (2)
// # pragma GCC optimize (3)
// # pragma GCC target ("avx")
// # pragma GCC optimize ("Ofast")
// # pragma GCC optimize ("inline")
// # pragma GCC optimize ("-fgcse")
// # pragma GCC optimize ("-fgcse-lm")
// # pragma GCC optimize ("-fipa-sra")
// # pragma GCC optimize ("-ftree-pre")
// # pragma GCC optimize ("-ftree-vrp")
// # pragma GCC optimize ("-fpeephole2")
// # pragma GCC optimize ("-ffast-math")
// # pragma GCC optimize ("-fsched-spec")
// # pragma GCC optimize ("unroll-loops")
// # pragma GCC optimize ("-falign-jumps")
// # pragma GCC optimize ("-falign-loops")
// # pragma GCC optimize ("-falign-labels")
// # pragma GCC optimize ("-fdevirtualize")
// # pragma GCC optimize ("-fcaller-saves")
// # pragma GCC optimize ("-fcrossjumping")
// # pragma GCC optimize ("-fthread-jumps")
// # pragma GCC optimize ("-funroll-loops")
// # pragma GCC optimize ("-fwhole-program")
// # pragma GCC optimize ("-freorder-blocks")
// # pragma GCC optimize ("-fschedule-insns")
// # pragma GCC optimize ("inline-functions")
// # pragma GCC optimize ("-ftree-tail-merge")
// # pragma GCC optimize ("-fschedule-insns2")
// # pragma GCC optimize ("-fstrict-aliasing")
// # pragma GCC optimize ("-fstrict-overflow")
// # pragma GCC optimize ("-falign-functions")
// # pragma GCC optimize ("-fcse-skip-blocks")
// # pragma GCC optimize ("-fcse-follow-jumps")
// # pragma GCC optimize ("-fsched-interblock")
// # pragma GCC optimize ("-fpartial-inlining")
// # pragma GCC optimize ("no-stack-protector")
// # pragma GCC optimize ("-freorder-functions")
// # pragma GCC optimize ("-findirect-inlining")
// # pragma GCC optimize ("-fhoist-adjacent-loads")
// # pragma GCC optimize ("-frerun-cse-after-loop")
// # pragma GCC optimize ("inline-small-functions")
// # pragma GCC optimize ("-finline-small-functions")
// # pragma GCC optimize ("-ftree-switch-conversion")
// # pragma GCC optimize ("-foptimize-sibling-calls")
// # pragma GCC optimize ("-fexpensive-optimizations")
// # pragma GCC optimize ("-funsafe-loop-optimizations")
// # pragma GCC optimize ("inline-functions-called-once")
// # pragma GCC optimize ("-fdelete-null-pointer-checks")

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=500010;
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
	int pp=p%len;q[t=1]=0;
	int tmp=pp;while(tmp){q[++t]=tmp;((tmp+=pp)>=len)&&(tmp-=len);}
	for(int i=0;i<g;i++){
		if(i)for(int j=1;j<=t;j++)((++q[j])>=len)&&(q[j]-=len);
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
	int pp=nw%p;q[t=1]=0;
	int tmp=pp;while(tmp){q[++t]=tmp;((tmp+=pp)>=p)&&(tmp-=p);}
	for(int i=0;i<g;i++){
		if(i)for(int j=1;j<=t;j++)((++q[j])>=p)&&(q[j]-=p);
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
	printf("%lld\n",ans);
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