#include<bits/stdc++.h>
// #define int long long
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
const int maxn=400010;
const int inf=1e9;
bool mbe;

int n,op,a[maxn];
int lsh[maxn*5],len;
#define lb(x) (x&(-x))
int tree[maxn*5];
void upd(int x,int w){
	while(x<=len)tree[x]+=w,x+=lb(x);
}
int que(int x){
	int res=0;
	while(x)res+=tree[x],x-=lb(x);
	return res;
}
void clr(){
	for(int i=1;i<=len;i++)tree[i]=0;
}
int f[maxn],g[maxn];
void sovle(int *f){
	if(n&1)f[(n+1)/2]=0;
	for(int i=1;i<=(n+1)/2;i++){
		int p=lower_bound(lsh+1,lsh+len+1,a[i]+i)-lsh;
		f[i]+=que(p-1);
		p=lower_bound(lsh+1,lsh+len+1,a[i]+i)-lsh;
		upd(p,1);
	}
	clr();
	for(int i=n;i;i--){
		if(i&1){
			int p=lower_bound(lsh+1,lsh+len+1,a[(i+1)/2]+(i+1)/2-1)-lsh;
			f[(i+1)/2]+=que(p-1);
		}
		int p=lower_bound(lsh+1,lsh+len+1,a[i])-lsh;
		upd(p,1);
	}
	clr();
	for(int i=n;i;i--){
		if(i&1){
			int p=lower_bound(lsh+1,lsh+len+1,a[(i+1)/2]-(i+1)/2)-lsh;
			f[(i+1)/2]-=que(p-1);
		}
		if(i<=(n+1)/2){
			int p=lower_bound(lsh+1,lsh+len+1,a[i]-i)-lsh;
			f[i]+=que(p-1);
		}
		int p=lower_bound(lsh+1,lsh+len+1,a[i]-i)-lsh;
		upd(p,1);
	}
	clr();
	// for(int i=1;i<=n;i++)cout<<f[i]<<" ";cout<<"\n";
}
void work(){
	n=read();op=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(op==1){
		for(int i=1;i<=n;i++)lsh[++len]=a[i]-i,lsh[++len]=a[i]+i;
		sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
		for(int i=1;i<=n;i++){
			int p=lower_bound(lsh+1,lsh+len+1,a[i]-i)-lsh;
			f[i]+=que(p-1);
			p=lower_bound(lsh+1,lsh+len+1,a[i]-i)-lsh;
			upd(p,1);
		}
		clr();
		for(int i=n;i;i--){
			int p=lower_bound(lsh+1,lsh+len+1,a[i]+i)-lsh;
			f[i]+=que(p-1);
			p=lower_bound(lsh+1,lsh+len+1,a[i]+i)-lsh;
			upd(p,1);
		}
		clr();
		for(int i=1;i<=n;i++)printf("%d\n",f[i]+1);
	}
	else{
		for(int i=1;i<=n;i++)lsh[++len]=a[i];
		for(int i=1;i<=n;i++)lsh[++len]=a[i]-i,lsh[++len]=a[i]+i;
		reverse(a+1,a+n+1);
		for(int i=1;i<=n;i++)lsh[++len]=a[i]-i,lsh[++len]=a[i]+i;
		reverse(a+1,a+n+1);
		sort(lsh+1,lsh+len+1),len=unique(lsh+1,lsh+len+1)-lsh-1;
		sovle(f);
		reverse(a+1,a+n+1),reverse(f+1,f+n+1);
		sovle(f);
		reverse(a+1,a+n+1),reverse(f+1,f+n+1);
		for(int i=1;i<=n;i++){
			int p=lower_bound(lsh+1,lsh+len+1,a[i]-i)-lsh;
			upd(p,1);
		}
		for(int i=1;i<=n;i++){
			int p=lower_bound(lsh+1,lsh+len+1,a[i]-i)-lsh;
			f[i]=max(f[i],que(p-1));
		}
		clr();
		for(int i=1;i<=n;i++){
			int p=lower_bound(lsh+1,lsh+len+1,a[i]+i)-lsh;
			upd(p,1);
		}
		for(int i=1;i<=n;i++){
			int p=lower_bound(lsh+1,lsh+len+1,a[i]+i)-lsh;
			f[i]=max(f[i],que(p-1));
		}
		clr();
		for(int i=1;i<=n;i++)printf("%d\n",f[i]+1);
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen("1.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}