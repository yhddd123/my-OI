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

int n,m,k,a[maxn];
void work(){
	n=m=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	while(k&&n>3){
		sort(a+1,a+n+1);
		reverse(a+1,a+n+1);while(n&&!a[n])n--;
		reverse(a+1,a+n+1);
		for(int i=2;i<=n;i++)a[i]-=a[i-1];
		k--;
	}
	if(k&&n==3){
		sort(a+1,a+n+1);
		while(a[1]&&k){
			int l=1,r=k,res=1;
			__int128 a1=a[1],a2=a[2],a3=a[3];
			while(l<=r){
				int mid=l+r>>1;
				if(a1<=a2-mid*a1&&a2-mid*a1<=a3-mid*a2+mid*(mid+1)/2*a1)res=mid,l=mid+1;
				else r=mid-1;
			}
			a[3]=a3-res*a2+res*(res+1)/2*a1;
			a[2]=a2-res*a[1];
			k-=res;
			if(k)sort(a+1,a+n+1);
		}
		if(k){
			sort(a+1,a+n+1);
			a[1]=a[2],a[2]=a[3];n=2;
			while(a[1]&&k){
				int d=min(k,a[2]/a[1]);
				a[2]-=a[1]*d,k-=d;
				if(k)sort(a+1,a+n+1);
			}
		}
	}
	for(int i=n+1;i<=m;i++)printf("0 ");
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);puts("");
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