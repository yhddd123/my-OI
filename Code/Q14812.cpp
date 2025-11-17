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
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n,m,k;
int X0=-50,Y0=0,r=600;
int X1=0,Y1=700,X2=-600,Y2=-500,X3=600,Y3=-400;
int X4=-500,Y4=600,X5=700,Y5=300;
void work(){
	n=read();m=read();k=read();
	int V=n*(n-1)+6*n*m+2*n*k+3*m*(m-1)+2*m*k+k*(k-1)/2+3*m;
	int E=n*(2*(n-1)+6*m+2*k)+m*(6*n+6*(m-1)+2*k+3)+k*(2*n+2*m+k);
	int F=E-V+1+(!k);
	printf("%d\n",F);
	for(int i=0;i<n;i++)printf("%d %d %d\n",X0+i,Y0,r);
	for(int i=0;i<m;i++)printf("%d %d %d %d %d %d\n",X1+i,Y1,X2,Y2+i,X3-i,Y3-i);
	for(int i=0;i<k;i++)printf("%d %d %d %d\n",X4+i,Y4,X5,Y5-i);
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