#include<bits/stdc++.h>
#define int unsigned int
#define db double
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,s,a[maxn],ans;
int sum[450][maxn];

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();s=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=s;i++){
		for(int j=1;j<=i;j++)sum[i][j]=a[j];
		for(int j=i+1;j<=n;j++)sum[i][j]=a[j]+sum[i][j-i];
	}
	m=read();
	while(m--){
		int d=read(),p1=read(),p2=read();ans=0;
		for(int j=0;j<d;j++)ans+=(sum[1][p2+d*(j+1)-1]-sum[1][p2+d*j-1])*(sum[d][p1+d*(d-1)+j]-sum[d][p1+j]+a[p1+j]);
		cout<<ans<<"\n";
	}
}
