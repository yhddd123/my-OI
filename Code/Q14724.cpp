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

int n,m;
pii a[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]=max(tree[x],w),x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res=max(res,tree[x]),x-=lb(x);
	return res;
}
int f[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]={read(),read()};
	sort(a+1,a+m+1,[&](pii u,pii v){return u.se<v.se;});
	for(int i=1;i<=n;i++)f[i]=tree[i]=0;
	for(int i=1;i<=m;i++){
		f[a[i].se]=max(f[a[i].se],que(a[i].fi-1)+1);
		upd(a[i].se,f[a[i].se]);
	}
	int mx=que(n);
	printf("%lld\n",__lg(mx)+1);
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