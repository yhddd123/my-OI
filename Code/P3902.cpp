#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,a[maxn],cnt,x,ans;

signed main(){
//	freopen("P3902_1.in","r",stdin);
	n=read();
	for(int i=1;i<=n;i++){
		x=read();
		if(x>a[cnt])a[++cnt]=x;
		else{
			++ans;
			*lower_bound(a+1,a+cnt+1,x)=x;
		}
//		for(int j=1;j<=cnt;j++)cout<<a[j]<<" ";
//		cout<<"\n";
	}
	printf("%lld",ans);
}

