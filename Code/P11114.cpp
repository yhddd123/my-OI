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
const int maxn=1000010;
const int inf=1e9;
bool mbe;

int n,m,k,p,c;
int a[maxn],tim[maxn];
int num[maxn],cnt[maxn];
int d[maxn];
int f[maxn];
int q[maxn],h,t;
void work(){
	n=read();m=read();k=read();p=read();c=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		num[i]=num[i-1],cnt[i]=cnt[i-1];
		if(tim[a[i]]%p==0)num[i]++;
		tim[a[i]]++;
		cnt[i]+=(tim[a[i]]%p==0);
	}
	for(int i=1;i<=n;i++){
		if(c==1)d[i]=2*(n+1-i-1);
		if(c==2)d[i]=2*i;
		if(c==3)d[i]=2*min(i,n+1-i-1);
	}
	mems(f,0x3f);
	f[0]=0;
	q[h=t=1]=0;
	for(int i=1;i<=n;i++){
		while(h<=t&&num[i]-cnt[q[h]]>m)h++;
		f[i]=f[q[h]];
		if(i!=n)f[i]+=d[i];
		while(h<=t&&f[q[t]]>=f[i])t--;q[++t]=i;
	}
	printf("%lld\n",f[n]+n+1);
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