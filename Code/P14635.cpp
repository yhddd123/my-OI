#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;

int n,m,ans;
int a[maxn],b[maxn];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=a[i]+read();
	sort(a+1,a+n+1),sort(b+1,b+n+1);
	for(int i=0,sum=0;i<=n;i++){
		sum+=a[i];
		if(sum>m)break;
		ans=max(ans,(m-sum)/b[1]*2+i);
	}
	printf("%lld\n",ans);
}


int T;
signed main(){
	// freopen("candy.in","r",stdin);
	// freopen("candy.out","w",stdout);
	
	T=1;
	while(T--)work();
}