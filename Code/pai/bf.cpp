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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,x,a[maxn],ans;
int id[maxn],ff[maxn];
int fd(int x){
	if(ff[x]==x)return x;
	return ff[x]=fd(ff[x]);
}
int to[maxn],siz[maxn];
int calc(){
	int res=-n*(n-1)/2;
	for(int i=1;i<=n;i++)id[i]=i;
	sort(id+1,id+n+1,[&](int u,int v){return u+a[u]>v+a[v];});
	for(int i=1;i<=n;i++)ff[i]=i;ff[n+1]=n+1;
	for(int ii=1;ii<=n;ii++){
		int i=id[ii];
		for(int j=fd(max(1ll,i-a[i]));j<=min(n,i+a[i]);j=fd(j)){
			to[j]=min(n,i+a[i]);
			ff[j]=fd(j+1);
		}
	}
	for(int i=1;i<=n;i++)siz[i]=0;
	for(int i=1;i<=n;i++){
		res+=siz[i]*(n-i+1)+n-i;siz[i]++;
		siz[to[i]+1]+=siz[i];
		// cout<<i<<" "<<to[i]<<" "<<siz[i]<<" "<<res<<"\n";
	}
	return res;
}
void work(){
	n=read();x=read();
	for(int i=1;i<=n;i++)a[i]=read();
	ans=calc();
	for(int i=1;i<=n;i++)if(a[i]<x){
		swap(a[i],x);
		ans=min(ans,calc());
		swap(a[i],x);
	}
	printf("%lld\n",ans);
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