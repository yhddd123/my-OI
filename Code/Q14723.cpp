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

int n,a[maxn],b[maxn];
void work(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	sort(a+1,a+n+1),sort(b+1,b+n+1);
	bool fl=1;for(int i=1;i<=n;i++)fl&=a[i]==b[i];
	if(fl)puts("Yes");
	else{
		fl=0;for(int i=1;i<n;i++)if(a[i+1]-a[i]==1)fl=1;
		if(!fl)puts("No");
		else{
		fl=0;for(int i=1;i<n;i++)if(b[i+1]-b[i]==1)fl=1;
		if(!fl)puts("No");
		else{
			int num=0;
			for(int i=1;i<=n;i++)num+=(a[i]&1);
			for(int i=1;i<=n;i++)num-=(b[i]&1);
			if(!num)puts("Yes");
			else puts("No");
		}
		}
	}
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