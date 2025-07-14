#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
using namespace std;
const int maxn=2000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int n,k;
inline int ksm(int a,int b=mod-2){
	int ans=1;b%=(mod-1);
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
char c[maxn];
int a[maxn],val[26],bas,pw[maxn];
int calc(int l,int r){
	return (a[r]-a[l-1]*pw[r-l+1]%mod+mod)%mod;
}
void work(){
	n=read();k=read();scanf("%s",c+1);
	srand(time(0));bas=rand()*rand()%mod;
	for(int i=0;i<26;i++)val[i]=rand()*rand()%bas;
	for(int i=1;i<=n;i++)a[i]=(a[i-1]*bas+val[c[i]-'a'])%mod;
	pw[0]=1;for(int i=1;i<=n;i++)pw[i]=pw[i-1]*bas%mod;
	int pos=0;
	for(int i=1;i<=n/2;i++)if(n%i==0&&calc(1,n-i)==calc(i+1,n)){pos=i;break;}
//	cout<<pos<<"\n";
	if(pos){printf("%lld\n",(pos+(n-pos)*ksm(2,k))%mod);return ;}
	for(int i=1;i<n;i++)if(calc(1,i)==calc(n-i+1,n))pos=i;
	if(!pos){printf("%lld\n",n);return ;}
	int num=0,cnt=1;
	for(int i=1;i<=pos/2;i++)if(pos%i==0&&calc(1,pos-i)==calc(i+1,pos)){cnt=pos/i;pos=i;break;}
	for(int i=pos;i<=n;i+=pos){
		if(calc(1,pos)==calc(i-pos+1,i))num++;
		else break;
	}
	while(k&&cnt<=num){
		n+=cnt*pos%mod;n%=mod;
		k--;cnt<<=1;
	}
	n+=k%mod*num%mod*pos%mod;n%=mod;
	printf("%lld\n",n);
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	T=1;
	while(T--)work();
}
/*
16 100
abcabcabcdabcabc
*/

