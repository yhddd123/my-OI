#include<bits/stdc++.h>
#define db double
#define mod 1000000007
using namespace std;
const int maxn=40000010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

bool mbe;
int n,opt;
long long a[maxn];
int q[maxn],h,t;
int pre[maxn];
long long x,y,z,m,p,l,r,lst;
__int128 ans;
int st[55],tp;
bool med;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
//	cout<<(&med-&mbe)/(1024*1024)<<"\n";
	n=read();opt=read();
	if(opt==1){
		x=read();y=read();z=read();a[1]=read();a[2]=read();m=read();
		int pw=1ll<<30;
		for(int i=3;i<=n;i++)a[i]=(x*a[i-1]+y*a[i-2]+z)%pw;
		for(int i=1;i<=m;i++){
			p=read(),l=read(),r=read();
			for(int j=lst+1;j<=p;j++)a[j]=a[j]%(r-l+1)+l+a[j-1];
			lst=p;
		}
	}
	else for(int i=1;i<=n;i++)a[i]=read()+a[i-1];
	for(int i=1;i<=n;i++){
		while(h<t&a[q[h+1]]-a[pre[q[h+1]]]<=a[i]-a[q[h+1]])h++;
		pre[i]=q[h];
		while(h<t&&a[q[t]]-a[pre[q[t]]]+a[q[t]]>=a[i]-a[pre[i]]+a[i])t--;
		q[++t]=i;
	}
	int x=n;while(x){
		ans+=(__int128)(a[x]-a[pre[x]])*(a[x]-a[pre[x]]);
//		cout<<x<<" "<<pre[x]<<"\n";
		x=pre[x];
	}
	while(ans){
		st[++tp]=ans%10;
		ans/=10;
	}
	while(tp)printf("%d",st[tp--]);
}
