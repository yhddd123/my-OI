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
const int maxn=1<<20;
bool mbe;

int n,m=20;
int f[maxn];
void fwt(int *a,int n,int fl=1){
	for(int l=2;l<=n;l<<=1){
		int k=l>>1;
		for(int i=0;i<n;i+=l){
			for(int j=i;j<i+k;j++){
				int u=a[j],v=a[j+k];
				a[j]=(u+v)*fl%mod,a[j+k]=(u+mod-v)*fl%mod;
			}
		}
	}
}
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();
	for(int i=1;i<=n;i++)f[0]++,f[read()]+=2;
	fwt(f,1<<m);
	for(int i=0;i<(1<<m);i++){
		int x=(n*3+mod-f[i])*ksm(4)%mod;
		f[i]=((x&1)?mod-1:1)*ksm(3,n-x)%mod;
	}
	fwt(f,1<<m,(mod+1)/2);
	printf("%lld\n",(f[0]+mod-1)%mod);
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