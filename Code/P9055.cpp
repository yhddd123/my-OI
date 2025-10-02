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
const int maxn=10000010;
const int inf=1e9;
bool mbe;

int n,m,l,r,x,ans;
char s[maxn];
int a[maxn],f[maxn];
int calc(int l,int r){return (l+r)*(r-l+1)/2%mod;}
void work(){
	m=read();l=read();r=read();x=read();
	scanf("%s",s);
	for(int i=0;i<m;i++)a[i]=s[i]-'0'+x,n+=a[i];
	f[0]=calc(1,n);
	for(int i=1,num=a[0],mn=a[0];i<=m;num+=a[i],mn=min(mn,a[i]),i++){
		f[i]=calc(1,n)-calc(num-i+2,num);
		int cnt=n-num,d=min(2*(i-1),cnt);
		// cout<<num<<" "<<cnt<<" "<<d<<" "<<f[i]<<"\n";
		f[i]-=calc(i,i+d/2-1)+calc(i,i+(d+1)/2-1);
		cnt-=d;
		int q=cnt/(mn+1),r=cnt%(mn+1);
		f[i]-=calc(2*(i-1)+1,2*(i-1)+q)*(mn+1-r);
		f[i]-=calc(2*(i-1)+1,2*(i-1)+q+1)*r;
	}
	// for(int i=0;i<=m;i++)cout<<f[i]<<"\n";
	for(int i=0,mul=1;i<=m;i++,mul=mul*233%mod)if(l<=i&&i<=r)ans^=mul*(f[i]%mod+mod)%mod;
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