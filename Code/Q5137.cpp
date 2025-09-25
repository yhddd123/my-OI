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
const int inf=1e9+1;
bool mbe;

int n,m,ans,a[maxn];
int id[maxn],val[maxn];
int lsh[maxn<<5],len;
int calc(int x){
	if(!x)return inf;
	int res=0;
	for(int i=1;i<=n;i++){
		if(a[i]<x)val[i]=x-a[i];
		else{
			int num=__lg(a[i]/x);
			int va=a[i]/(1<<num);
			val[i]=min(num+abs(va-x),num+1+abs(va/2-x));
		}
	}
	sort(id+1,id+n+1,[&](int u,int v){return val[u]<val[v];});
	for(int i=1;i<=n-m;i++)res+=val[id[i]];
	// cout<<x<<" "<<res<<" "<<val[1]<<" "<<val[2]<<"\n";
	return res;
}
void work(){
	n=read();m=read();ans=inf;
	for(int i=1;i<=n;i++)a[i]=read(),id[i]=i;
	len=0;for(int i=1;i<=n;i++){
		int x=a[i];
		lsh[++len]=x;
		while(x){
			lsh[++len]=(x+x/2)/2;
			lsh[++len]=x/2;
			x/=2;
		}
	}
	lsh[++len]=inf;
	sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
	for(int i=1;i<len;i++)ans=min({ans,calc(lsh[i]),calc(lsh[i+1]-1)});
	printf("%lld\n",ans);
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