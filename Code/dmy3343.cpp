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

int l,r,ans;
int f[maxn];
void work(){
	l=read(),r=read();
	for(int a=1;(a*a+1)*a<=r;a++){
		for(int b=a;(a*b+1)*b<=r;b++){
			for(int c=max(b,(l+(a*b+1)-1)/(a*b+1));c<=r/(a*b+1);c++)f[c*(a*b+1)-l]+=1+(a!=b);
		}
	}
	for(int a=1;(a*a+1)*(a+1)<=r;a++){
		for(int c=a;(a*(c+1)+1)*c<=r;c++){
			for(int b=max(c+1,((l+c-1)/c-1+a-1)/a);b<=(r/c-1)/a;b++)f[c*(a*b+1)-l]+=2;
		}
	}
	for(int c=1;((c+1)*(c+1)+1)*c<=r;c++){
		for(int a=c+1;(a*a+1)*c<=r;a++){
			for(int b=max(a,((l+c-1)/c-1+a-1)/a);b<=(r/c-1)/a;b++)f[c*(a*b+1)-l]+=1+(a!=b);
		}
	}	
	for(int i=l;i<=r;i++)ans+=(f[i-l]+1)^i;
	printf("%lld\n",ans);
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