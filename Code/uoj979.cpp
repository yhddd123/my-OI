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
const int maxn=500010;
const int inf=1e9;
bool mbe;

int n,a[maxn],ans;
void work(){
	n=read();ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	while(n){
		int m=n;while(m&&a[m]>a[n]/2)m--;
		ans=max(ans,a[n]-a[m+1]);
		for(int i=1;i<=m;i++)if(a[i]>a[n]-a[m+1]){
			int d=a[m+1]/a[i];
			if(a[n]/a[i]==d)ans=max(ans,a[n]-a[i]*d);
			else{
				int p=lower_bound(a+1,a+n+1,(d+1)*a[i])-a;
				ans=max(ans,a[n]-a[i]*(d+1));
				ans=max(ans,a[p-1]-a[i]*d);
			}
		}
		n=m;
	}
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