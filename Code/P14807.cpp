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
int a[maxn],b[maxn];
pii que[maxn];
int ans[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sort(a+1,a+n+1,greater<int>());
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)a[i]+=a[i-1],b[i]+=b[i-1];
	q=read();
	for(int i=1;i<=q;i++)que[i]={read(),i};
	sort(que+1,que+q+1,[&](pii u,pii v){return u.fi<v.fi;});
	for(int i=1,j=n;i<=q;i++){
		while(j&&a[j]-que[i].fi*b[j]<a[j-1]-que[i].fi*b[j-1])j--;
		ans[que[i].se]=a[j]-que[i].fi*b[j];
	}
	for(int i=1;i<=q;i++)printf("%lld ",ans[i]);puts("");
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