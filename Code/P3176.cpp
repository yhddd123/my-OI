#include<bits/stdc++.h>
#define int long long
#define db double
#define mod 998244353
using namespace std;
const int maxn=510;
const int inf=1e9;
const db eps=1e-9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,ans;
char c[maxn];
struct mat{
	int e[5][5];
	mat(){memset(e,0,sizeof(e));}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				for(int k=0;k<m;k++)res.e[i][j]+=e[i][k]*tmp.e[k][j]%mod;
				res.e[i][j]%=mod;
			}
		}
		return res;
	}
	mat operator+(const mat&tmp)const{
		mat res;
		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				res.e[i][j]=(e[i][j]+tmp.e[i][j])%mod;
			}
		}
		return res;
	}
}pw[maxn],f[maxn][maxn],g[maxn];
mat ksm(mat a,int b){
	mat ans;
	for(int i=0;i<m;i++)ans.e[i][i]=1;
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
void sovle(){
	scanf("%s",c+1);n=strlen(c+1);m=read();
	for(int i=0;i<m;i++)pw[0].e[i][m-1]=1;
	for(int i=1;i<m;i++)pw[0].e[i][i-1]=1;
	for(int i=1;i<n;i++)pw[i]=ksm(pw[i-1],10);
	for(int i=1;i<=n;i++)f[i][i]=ksm(pw[0],c[i]-'0');
	for(int len=2;len<=n;len++){
		for(int i=1;i+len-1<=n;i++){
			int j=i+len-1;
			f[i][j]=f[i+1][j]*ksm(pw[j-i],c[i]-'0');
		}
	}
	for(int i=0;i<m;i++)g[0].e[i][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++)g[i]=g[i]+g[j]*f[j+1][i];
	}
	for(int i=0;i<m;i++)ans+=g[n].e[0][i],ans%=mod;
	printf("%lld\n",ans);
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=1;
	while(T--)sovle();
}
