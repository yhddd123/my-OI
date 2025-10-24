// Problem: CF1152F2 Neko Rules the Catniverse (Large Version)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1152F2
// Memory Limit: 250 MB
// Time Limit: 7000 ms
// Written by yhm.
// Start codeing:2025-10-24 16:08:39
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 1000000007ll
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
const int maxk=210;
const int inf=1e9;
bool mbe;

int n,k,m,l,ans;
int id(int i,int s){return i*16+s;}
struct mat{
	int e[maxk][maxk];
	mat(){memset(e,0,sizeof(e));}
}bas;
mat operator*(mat &u,mat &v){
	mat res;
	for(int i=0;i<l;i++){
		for(int k=0;k<l;k++){
			for(int j=0;j<l;j++)(res.e[i][j]+=u.e[i][k]*v.e[k][j])%=mod;
		}
	}
	return res;
}
mat one(){
	mat res;
	for(int i=0;i<l;i++)res.e[i][i]=1;
	return res;
}
mat qpow(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
void work(){
	n=read();k=read();m=read();l=(k+1)*16;
	for(int i=0;i<=k;i++){
		for(int s=0;s<(1<<m);s++){
			if(i<k)bas.e[id(i+1,(2*s+1)&((1<<m)-1))][id(i,s)]+=__builtin_popcount(s)+1;
			bas.e[id(i,(2*s)&((1<<m)-1))][id(i,s)]++;
		}
	}
	bas=qpow(bas,n);
	for(int s=0;s<(1<<m);s++)(ans+=bas.e[id(k,s)][0])%=mod;
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