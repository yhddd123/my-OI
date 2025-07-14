#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 999911658
using namespace std;
const int maxn=50010;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,bas,m[5],p,a[5],ans;
int fac[maxn],inv[maxn];
inline int ksm(int a,int b,int p){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}
int C(int n,int m,int p){
	if(n<m)return 0;
	return fac[n]*inv[m]%p*inv[n-m]%p;
}
int lucas(int n,int m,int p){
	if(n<m)return 0;
	if(!n)return 1;
	return lucas(n/p,m/p,p)*C(n%p,m%p,p)%p;
}
void crt(){
	for(int i=1;i<=4;i++)ans+=a[i]*(mod/m[i])%mod*ksm(mod/m[i],m[i]-2,m[i])%mod;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();bas=read();
	if(bas%(mod+1)==0){
		printf("0\n");
		return 0;
	}
	m[1]=2;m[2]=3;m[3]=4679;m[4]=35617;
	for(int k=1;k<=4;k++){
		p=m[k];
		fac[0]=1;for(int i=1;i<p;i++)fac[i]=fac[i-1]*i%p;
		inv[p-1]=ksm(fac[p-1],p-2,p);
		for(int i=p-2;i>=0;i--)inv[i]=inv[i+1]*(i+1)%p;
		for(int i=1;i*i<=n;i++){
			if(n%i==0){
				a[k]+=lucas(n,i,p),a[k]%=p;
				if(i*i!=n)a[k]+=lucas(n,n/i,p),a[k]%=p;
			}
		}
	}
	crt();
	printf("%lld\n",ksm(bas,ans,mod+1));
}
