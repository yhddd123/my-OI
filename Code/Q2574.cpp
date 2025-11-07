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
const int maxk=310;
const int inf=1e9;
bool mbe;

int m,q,l;
vector<int> a[60];
struct mat{
	int e[maxk][maxk];
	mat(){memset(e,0,sizeof(e));}
}bas,pw[60];
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
struct vec{
	int e[maxk];
	vec(){memset(e,0,sizeof(e));}
};
vec operator*(mat &u,vec &v){
	vec res;
	for(int i=0;i<l;i++){
		for(int j=0;j<l;j++)(res.e[i]+=u.e[i][j]*v.e[j])%=mod;
	}
	return res;
}
int C[60][60],pwi[60][60];
vector<int> b[maxk],c;
int num[maxk];
void dfs(int d){
	if(d==60){
		b[l]=c;
		int mul=1;for(int i=0;i<60;i++)mul=mul*C[a[i].size()][c[i]]%mod*pwi[i][c[i]]%mod;
		num[l]=mul;l++;
		// cout<<l<<" "<<mul<<"\n";
		// cout<<c[1]<<" "<<c[2]<<"\n";
		return ;
	}
	for(int i=0;i<=a[d].size();i++){
		c.pb(i);
		dfs(d+1);
		c.pop_back();
	}
}
void work(){
	m=read();q=read();
	vector<pii> p;
	int x=m;
	for(int i=2;i*i<=x;i++)if(x%i==0){
		int num=0;
		while(x%i==0)x/=i,++num;
		a[num].pb(i);
	}
	if(x>1)a[1].pb(x);
	for(int i=0;i<60;i++){
		C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		pwi[i][0]=1;for(int j=1;j<60;j++)pwi[i][j]=pwi[i][j-1]*i%mod;
	}
	dfs(0);
	for(int i=0;i<l;i++){
		for(int j=0;j<l;j++){
			int mx=0;for(int k=0;k<60;k++)mx=max(mx,min(b[i][k],b[j][k]));
			if(!mx)continue;
			int f0=1,f1=0;
			for(int k=0;k<60;k++){
				int g0=0,g1=0;
				for(int t=max(0ll,b[i][k]+b[j][k]-c[k]);t<=min(b[i][k],b[j][k]);t++){
					int coef=C[b[j][k]][t]*C[c[k]-b[j][k]][b[i][k]-t]%mod*pwi[k][b[i][k]]%mod;
					if(t){
						(g1+=(f0+f1)*coef)%=mod;
					}
					else{
						(g0+=f0*coef)%=mod,(g1+=f1*coef)%=mod;
					}
				}
				f0=g0,f1=g1;
			}
			bas.e[i][j]=f1;
			// cout<<i<<" "<<j<<" "<<f1<<" "<<num[i]<<"\n";
		}
	}
	pw[0]=bas;for(int i=1;i<60;i++)pw[i]=pw[i-1]*pw[i-1];
	while(q--){
		int n=read();
		vec ans;ans.e[l-1]=1;
		for(int i=0;i<60;i++)if(n&(1ll<<i))ans=pw[i]*ans;
		int res=0;for(int i=0;i<l;i++)(res+=ans.e[i])%=mod;
		// mat ans=qpow(bas,n);
		// int res=0;for(int i=0;i<l;i++)(res+=ans.e[i][l-1])%=mod;
		printf("%lld\n",res+(n==1));
	}
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