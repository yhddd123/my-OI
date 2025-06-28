// Problem: CF506E Mr. Kitayuta's Gift
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF506E
// Memory Limit: 750 MB
// Time Limit: 6000 ms
// Written by yhm.
// Start codeing:2025-04-08 17:53:55
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 10007ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=210;
const int inf=1e9;
bool mbe;

int n,m,lim;
char s[maxn];
int f[maxn][maxn][maxn],g[maxn];
void inc(int &u,int v){((u+=v)>=mod)&&(u-=mod);}
struct mat{
	int e[310][310];
	mat(){mems(e,0);}
	mat operator*(const mat&tmp)const{
		mat res;
		for(int i=0;i<=lim;i++){
			for(int k=i;k<=lim;k++){
				for(int j=k;j<=lim;j++)res.e[i][j]+=e[i][k]*tmp.e[k][j];
			}
		}
		for(int i=1;i<=lim;i++){
			for(int j=i;j<=lim;j++)res.e[i][j]%=mod;
		}
		return res;
	}
}a,b;
mat one(){
	mat res;
	for(int i=1;i<=lim;i++)res.e[i][i]=1;
	return res;
}
mat ksm(mat a,int b){
	mat ans=one();
	while(b){
		if(b&1)ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}
void work(){
	scanf("%s%lld",s+1,&m);n=strlen(s+1);
	f[1][n][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=n;j>=i;j--){
			for(int k=0;k<i+n-j;k++){
				if(s[i]==s[j]){
					if(i+1<j)inc(f[i+1][j-1][k],f[i][j][k]);
					else inc(g[k],f[i][j][k]);
				}
				else{
					inc(f[i+1][j][k+1],f[i][j][k]);
					inc(f[i][j-1][k+1],f[i][j][k]);
				}
			}
		}
	}
	lim=n+(n+1)/2+1;
	a.e[0][1]=1,a.e[0][n+1]=g[0];
	b.e[lim][lim]=26;
	for(int i=1;i<=n;i++)b.e[i][i]=24,b.e[i][lim-(n-i+1)/2]=g[i];
	for(int i=1;i<n;i++)b.e[i][i+1]=1;
	for(int i=n+1;i<lim;i++)b.e[i][i]=25,b.e[i][i+1]=1;
	a=a*ksm(b,(n+m+1)>>1);
	if((n+m)&1){
		int ans=a.e[0][lim];
		mems(a.e,0),mems(b.e,0),mems(g,0);
		for(int i=1;i<n;i++)if(s[i]==s[i+1]){
			for(int k=0;k<=n;k++)inc(g[k],f[i][i+1][k]);
		}
		a.e[0][1]=1,a.e[0][n+1]=g[0];
		for(int i=1;i<=n;i++)b.e[i][i]=24,b.e[i][lim-(n-i+1)/2]=g[i];
		for(int i=1;i<n;i++)b.e[i][i+1]=1;
		for(int i=n+1;i<lim;i++)b.e[i][i]=25,b.e[i][i+1]=1;
		a=a*ksm(b,(n+m+1)>>1);
		inc(ans,mod-a.e[0][lim]);
		printf("%lld\n",ans);
	}
	else printf("%lld\n",a.e[0][lim]);
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