#include<iostream>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=110;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,a[15];
double p[15],f[15][maxn];
inline double ksm(double a,int b){
	double ans=1.0;
	while(b){
		if(b&1)ans*=a;
		a*=a;
		b>>=1;
	}
	return ans;
}

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			scanf("%lf",&p[i]);
		}
		for(int i=1;i<=n;i++){
			double mul=1.0;
			for(int j=0;j<=maxn-10;j++){
				f[i][j]=ksm(1.0-mul,a[i]);
				mul*=p[i];
			}
		}
		for(int i=1;i<=n;i++){
			double ans=0;
			for(int j=0;j<maxn-10;j++){
				double res=1.0;
				for(int k=1;k<=n;k++){
					if(i!=k)res*=f[k][j];
				}
				res*=(f[i][j+1]-f[i][j]);
				ans+=res;
			}
			if(i==n)printf("%.6lf\n",ans);
			else printf("%.6lf ",ans);
		}
	}
}
