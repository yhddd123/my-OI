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
const int inf=1e18;
bool mbe;

int n,a[maxn<<1],res;
int p1[maxn],p2[maxn];
#define lb(x) (x&(-x))
int tree[maxn<<2];
void upd(int x,int w){
	while(x<=4*n)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
void clr(){
	for(int i=1;i<=4*n;i++)tree[i]=0;
}
void work(){
	n=read();
	for(int i=1;i<=2*n;i++)a[i]=read();
	for(int i=1;i<=2*n;i++){
		if(!p1[a[i]])p1[a[i]]=i;
		else p2[a[i]]=i;
	}
	for(int i=1;i<=n;i++)if(p2[i]-p1[i]>p1[i]+2*n-p2[i])p1[i]+=2*n,swap(p1[i],p2[i]);
	int p=0;for(int i=1;i<=n;i++)if(p2[i]-p1[i]==p1[i]+2*n-p2[i])p=i;
	res=0;for(int i=1;i<=n;i++)res+=p2[i]-p1[i];
	res=(res-n)/2;
	for(int i=4*n;i;i--){
		int j=(i-1)%(2*n)+1;
		if(p1[a[j]]==i){
			res+=que(p2[a[j]]);
			upd(p2[a[j]],1);
		}
		if(p2[a[j]]==i){
			res-=que(p2[a[j]]);
		}
	}
	clr();
	for(int i=1;i<=n;i++)if(p2[i]<=2*n)upd(p2[i],1);
	for(int i=4*n;i;i--){
		int j=(i-1)%(2*n)+1;
		if(p1[a[j]]==i&&p2[a[j]]>2*n){
			res+=que(p2[a[j]]-2*n);
		}
	}
	printf("%lld\n",res);
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