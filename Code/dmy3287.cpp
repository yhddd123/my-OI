#include<bits/stdc++.h>
// #define int long long
using namespace std;
static char buf[1000000],*p1=buf,*p2=buf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
const int maxn=3000010;
bool mbe;

int n,m;
int sum[maxn<<1];
int val[maxn];
void work(){
	n=read();m=3000001;
	for(int i=1;i<=n;i++){
		int u=read(),v=read();
		sum[u+maxn]++,sum[v+maxn]--,sum[u-v+maxn]--;
	}
	for(int i=1;i<maxn*2;i++)sum[i]+=sum[i-1];
	for(int i=1;i<=m;i++){
		for(int j=1;i*j<=m;j++)val[i]+=-sum[i*j-1+maxn];val[i]+=sum[m+maxn]*(m/i);
		for(int j=-1;i*(j+1)>-m;j--)val[i]+=j*(sum[i*(j+1)-1+maxn]-sum[max(-m,i*j-1)+maxn]);
	}
	// for(int i=1;i<=m;i++)cout<<val[i]<<" ";cout<<"\n";
	int mx=0;for(int i=1;i<=m;i++)mx=max(mx,val[i]);
	long long sum=0;for(int i=1;i<=m;i++)if(val[i]==mx)sum+=i;
	if(val[m]==mx)sum=-1;
	printf("%d %lld\n",mx,sum);
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