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
const int maxn=300010;
const int inf=1e9;
bool mbe;

int n,k;
int p[maxn],q[maxn];
int a[maxn],b[maxn];
#define lb(x) (x&(-x))
int tree[maxn];
void upd(int x,int w){
	while(x<=n)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
void work(){
	n=read();k=read();
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<=n;i++)q[i]=read();
	for(int i=1;i<=n;i++)upd(q[i],1);
	for(int i=1,j=n;i<=n;i++){
		while(j-que(p[i])>k){
			upd(q[j],-1);
			b[q[j--]]=-(i-1);
		}
		k-=j-que(p[i]);
		a[p[i]]=i-1;
		// cout<<i<<" "<<j<<" "<<k<<" "<<que(p[i])<<"\n";
		if(i==n){
			while(j)b[q[j--]]=-n;
		}
	}
	puts("Yes");
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);puts("");
	for(int i=1;i<=n;i++)printf("%lld ",b[i]);puts("");
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