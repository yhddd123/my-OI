#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=110;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int n,k;
struct nd{
	int e[maxn][maxn];
	nd operator *(const nd &tmp){
		nd nw;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				nw.e[i][j]=0;
				for(int k=1;k<=n;k++){
					nw.e[i][j]+=tmp.e[i][k]%mod*e[k][j]%mod;
					nw.e[i][j]%=mod;
				}
			}
		}
		return nw;
	}
}a,ans;

nd ksm(nd a,int b){
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}

signed main(){
	n=read();k=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)a.e[i][j]=read();
	}
	for(int i=1;i<=n;i++)ans.e[i][i]=1;
	ans=ksm(a,k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%lld ",ans.e[i][j]);
		}
		printf("\n");
	}
}

